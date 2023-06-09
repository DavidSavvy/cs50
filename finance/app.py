import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from re import fullmatch

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""

    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    all_symbols_dict = db.execute("SELECT symbol FROM transactions WHERE user_id = ?", session["user_id"])
    all_symbols = set()
    for dictionary in all_symbols_dict:
        all_symbols.add(dictionary["symbol"])

    # make all stock symbols purchased into a dict
    global stock
    stock = dict.fromkeys(all_symbols, 0)
    # "dict" may cause issues if other names not changed

    for symbol in all_symbols:
        shares_dict = db.execute("SELECT shares FROM transactions WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])
        for dictionary in shares_dict:
            stock[symbol] += dictionary["shares"]

    available_money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0].get("cash")

    total = 0
    for symbol, shares in stock.items():
        total += float(lookup(symbol)["price"] * shares)
    total += available_money

    return render_template("index.html", stock=stock, lookup=lookup, cash=available_money, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")
        elif not lookup(symbol):
            return apology("invalid symbol")

        if not shares:
            return apology("must provide shares")

        # might be a problem if fractional shares are allowed
        try:
            shares = int(shares)
        except ValueError:
            return apology("invalid shares")

        if shares < 1:
            return apology("invalid shares")

        price = lookup(symbol)["price"]
        total_cost = price * shares
        available_money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0].get("cash")
        if not available_money > price * shares:
            return apology("not enough money")

        db.execute("UPDATE users SET cash = ? WHERE id = ?", available_money - total_cost, session["user_id"])

        # make sure foreign key works right
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, dt) VALUES (?, ?, ?, ?, datetime('now', 'localtime'))", session["user_id"], symbol, shares, price)

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transaction_list = db.execute("SELECT symbol, shares, price, dt FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transaction_list=transaction_list)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/addfunds", methods=["GET", "POST"])
def addfunds():
    """Add funds to account"""

    if request.method == "GET":
        return render_template("addfunds.html")
    else:
        amount = request.form.get("amount")
        available_money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0].get("cash")
        db.execute("UPDATE users SET cash = ? WHERE id = ?", available_money + int(amount), session["user_id"])

        return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol")
        elif not lookup(symbol):
            return apology("invalid symbol")
        else:
            response = lookup(symbol)

            name = response["name"]
            price = usd(response["price"])
            symbol = response["symbol"]

            return render_template("quoted.html", name=name, symbol=symbol, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        ldict = db.execute("SELECT username FROM users")
        usernames = []
        for dict in ldict:
            usernames.append(dict.get("username"))
        print(usernames)

        if not username:
            return apology("must provide username")
        elif username in usernames:
            return apology("username taken")

        if not password or not confirmation:
            return apology("must provide password")
        elif password != confirmation:
            return apology("passwords must match")

        """
        password must contain 1 number (0-9)
        password must contain 1 uppercase letters
        password must contain 1 lowercase letters
        password must contain 1 non-alpha numeric number
        password is 8-16 characters with no space
        """
        reg = fullmatch(r"^(?=.*\d)(?=.*[A-Z])(?=.*[a-z])(?=.*[^\w\d\s:])([^\s]){8,16}$", password)
        if not reg:
            return apology("invalid password")

        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":
        return render_template("sell.html", stock=stock) # global var stock
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not int(shares) > 0:
            return apology("invalid share count")
        if int(stock[symbol]) < int(shares):
            return apology("invalid share count")

        price = lookup(symbol)["price"]
        total_return = price * int(shares)
        available_money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0].get("cash")
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, dt) VALUES (?, ?, ?, ?, datetime('now', 'localtime'))", session["user_id"], symbol, -int(shares), price)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", available_money + total_return, session["user_id"])

        return redirect("/")

