from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse
from django.views.decorators.csrf import csrf_exempt, csrf_protect
from django.contrib.auth.decorators import login_required

from .models import *


def index(request):
    return render(request, "auctions/index.html", {
        "listings": Listing.objects.all()
    })


def index_modified(request, category):
    return render(request, "auctions/index.html", {
        "listings": Listing.objects.filter(category=category)
    })


@csrf_protect
def create(request):
    # renders creation page
    if request.method == "GET":
        return render(request, "auctions/create_listing.html", {
            "success": "true"
        })
    else:
        title = request.POST['title']
        category = request.POST['category']
        image_url = request.POST['image_url']
        bid = request.POST['bid']
        description = request.POST['description']

        # makes sure user inputs the required fields
        if not title or not bid or not description:
            return render(request, "auctions/create_listing.html", {
                "success": "false"
            })
        else:
            listing = Listing.objects.create(listing_title=title, price=bid, description=description, lister=request.user)
            listing.category = category if (category != None) else 'No category'
            listing.image_url = image_url if (image_url != None) else None
            listing.save()

            return HttpResponseRedirect(reverse('index'))


def close(request, id):
    current_listing = Listing.objects.get(listing_id=id)
    bid_winner = None

    # tries to find bid winner, if no winner, listing is permanently deleted
    try:
        bid_winner = current_listing.item_bids.order_by("-bid")[0].bidder
    except IndexError:
        current_listing.delete()

    # case for if there is a bid winner, loads a modified listing page
    if bid_winner:
        current_listing.is_listing_open = False
        current_listing.save()
        return listing(request, id)


@csrf_protect
@login_required
def comment(request, id):
    if request.method == "POST":
        comment_text = request.POST["comment_text"]
        current_listing = Listing.objects.get(listing_id=id)
        current_comment = Comment.objects.create(text=comment_text, commenter=request.user, comment_item=current_listing)
        current_comment.save()
        return HttpResponseRedirect(reverse('listing', kwargs={'id': id}))


def categories(request):
    # lists all categories of listings
    #listings = {category for category in set(Listing.objects.values_list("category")) if category != }
    categories = set(Listing.objects.values_list("category").exclude(category=''))
    return render(request, "auctions/categories.html", {
        "category_list": categories
    })


@csrf_protect
@login_required
def bid(request, id):
    # makes sure entered bid is valid
    try:
        bid_amt = float(request.POST["bid"])
    except ValueError:
        return listing(request, id, is_bid_valid=False)

    # finds current highest bid
    bid_item = Listing.objects.get(listing_id=id)
    og_price = bid_item.price
    current_bid = Bid.objects.filter(bid_item=bid_item).order_by("-bid")[0].bid if Bid.objects.filter(bid_item=bid_item) else False

    # checks whether bid is valid compared to previous bids
    if bid_amt >= og_price and bid_amt > current_bid:
        bid_obj = Bid.objects.create(bid=bid_amt, bid_item=bid_item, bidder=request.user)
        bid_obj.save()
        #return HttpResponseRedirect(reverse('index'))
        return listing(request, id, is_bid_valid=True)
    else:
        return listing(request, id, is_bid_valid=False)


@login_required
def watchlist(request, id=-1):
    if request.method == "POST":
        # for adding to the watchlist
        current_listing = Listing.objects.get(listing_id=id)
        current_listing.watch_list_users.add(request.user)
        current_listing.save()
        return listing(request, id)
    else:
        # GET for accessing watchlist
        watch_list = request.user.watch_list.all()
        return render(request, "auctions/watchlist.html", {
            "watch_list": watch_list
        })


@login_required
def remove_watchlist(request):
    if request.method == "POST":
        current_id = request.POST["watchlist_item"]
        current_listing = Listing.objects.get(listing_id=current_id)
        current_listing.watch_list_users.remove(request.user)
        current_listing.save()
        watch_list = request.user.watch_list.all()
        return render(request, "auctions/watchlist.html", {
            "watch_list": watch_list
        })


@csrf_protect
def login_view(request):
    if request.method == "POST":

        # Attempt to sign user in
        username = request.POST["username"]
        password = request.POST["password"]
        user = authenticate(request, username=username, password=password)

        # Check if authentication successful
        if user is not None:
            login(request, user)
            return HttpResponseRedirect(reverse("index"))
        else:
            return render(request, "auctions/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "auctions/login.html")


@csrf_protect
def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("index"))


@csrf_protect
def register(request):
    if request.method == "POST":
        username = request.POST["username"]
        email = request.POST["email"]

        # Ensure password matches confirmation
        password = request.POST["password"]
        confirmation = request.POST["confirmation"]
        if password != confirmation:
            return render(request, "auctions/register.html", {
                "message": "Passwords must match."
            })

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(request, "auctions/register.html", {
                "message": "Username already taken."
            })
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "auctions/register.html")


def listing(request, id, is_bid_valid=True):
    listing = Listing.objects.get(listing_id=id)
    comments = listing.item_comments
    bid_count = Bid.objects.filter(bid_item=listing).count()
    current_bidder = False
    current_bid = None

    # make sure there are bids and whether user is the current one
    if bid_count > 0:
        current_bid = Bid.objects.filter(bid_item=listing).order_by("-bid")[0]
        if current_bid.bidder == request.user:
            current_bidder = True

    # check whether current user is the lister
    is_lister = False
    (is_lister := True) if listing.lister == request.user else False

    return render(request, "auctions/listing.html", {
        "listing": listing,
        "is_lister": is_lister,
        "is_bid_valid": is_bid_valid,
        "bid_count": bid_count,
        "current_bidder": current_bidder,
        "current_bid": current_bid,
        "comment_list": comments
    })



