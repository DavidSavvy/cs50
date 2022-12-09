from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse
from django.contrib.auth.decorators import login_required
from django.core.paginator import Paginator

from .models import User, Post


def index(request):
    posts = Post.objects.all()
    paginator = Paginator(posts, 10)
    return render(request, "network/index.html", {
        "posts": posts,
        "page_obj": page_obj
    })

@login_required
def post(request):
    if request.method == "POST":
        body = request.POST['body']
        Post.objects.create(poster=request.user, body=body)
        return HttpResponseRedirect(reverse("index"))

def user(request, id):

    return render(request, "network/profile.html", {
        "poster": User.objects.get(id=id)
    })

def following(request):
    user_following = request.user.following.all()
    following_posts = []
    for user_followed in user_following:
        posts = user_followed.posts.all()
        for post in posts:
            following_posts.append(post)
    print(user_following)

    return render(request, "network/following.html", {
        "posts": following_posts
    })

"""
check user.authentication in following tab
"""

@login_required
def follow_unfollow(request, poster_id):
    if request.method == "POST":
        button = request.POST["following_btn"]
        current_user = User.objects.get(id=request.user.id)
        poster = User.objects.get(id=poster_id)
        if button == "Follow":
            print(button)
            current_user.following.add(poster)
            poster.followers.add(current_user)
            return user(request, poster_id)
        else:
            current_user.following.remove(poster)
            poster.followers.remove(current_user)
            return user(request, poster_id)

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
            return render(request, "network/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "network/login.html")


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
            return render(request, "network/register.html", {
                "message": "Passwords must match."
            })

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(request, "network/register.html", {
                "message": "Username already taken."
            })
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "network/register.html")
