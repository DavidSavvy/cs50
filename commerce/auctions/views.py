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

@csrf_exempt
def create(request):
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

@csrf_exempt
@login_required
def bid(request, id):
    bid_amt = float(request.POST["bid"])
    bid_item = Listing.objects.get(listing_id=id)
    og_price = bid_item.price
    current_bid = Bid.objects.filter(bid_item=bid_item).order_by("-bid")[0].bid
    if bid_amt >= og_price and bid_amt > current_bid:
        bid_obj = Bid.objects.create(bid=bid_amt, bid_item=bid_item, bidder=request.user)
        bid_obj.save()
        return HttpResponseRedirect(reverse('index'))
    else:
        return render(request, "auctions/listing.html", {
            "listing": Listing.objects.get(listing_id=id),
            "is_bid_valid": False
        })



"""
finish bid, check highest, set
need to get list of current bids
"""

@csrf_exempt
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


def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("index"))


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

def listing(request, id):
    if request.method == "GET":
        return render(request, "auctions/listing.html", {
            "listing": Listing.objects.get(listing_id=id),
            "is_bid_valid": True
        })