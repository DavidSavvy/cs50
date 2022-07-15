import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

MONTHS = {1, 2, 3, 4, 5, 6, 7, 8, 9}
DAYS = range(1, 32)

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        if not request.form.get("name") or request.form.get("month") not in MONTHS or request.form.get("day") not in DAYS:
            return redirect("/")
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        all_birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", all_birthdays=all_birthdays, months=MONTHS, days=DAYS)


