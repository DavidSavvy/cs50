from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse
from django.contrib.auth.decorators import login_required
from django.core.paginator import Paginator

from .models import User, Post


def index(request):
    # Gets posts and sets up paginator
    posts = Post.objects.all().order_by('-timestamp')
    paginator = Paginator(posts, 10)
    page_number = request.GET.get('page')
    page_obj = paginator.get_page(page_number)

    # Renders page with paginator information
    return render(request, "network/index.html", {
        "posts": posts,
        "page_obj": page_obj,
        "page_number": range(1, paginator.num_pages+1)
    })

@login_required
def post(request):
    if request.method == "POST":
        # Creates a new post object from submitted form and redirects to index
        body = request.POST['body']
        Post.objects.create(poster=request.user, body=body)
        return HttpResponseRedirect(reverse("index"))

def user(request, id):
    # Gets a specific user's posts
    poster = User.objects.get(id=id)
    poster_posts = poster.posts.all().order_by('-timestamp')

    # Sets up paginator into 10 pages (see docs)
    paginator = Paginator(poster_posts, 10)
    page_number = request.GET.get('page')
    page_obj = paginator.get_page(page_number)
    print(page_obj)
    print(paginator.num_pages)

    # Renders page with paginator information
    return render(request, "network/profile.html", {
        "poster": poster,
        "page_obj": page_obj,
        "page_number": range(1, paginator.num_pages+1)
    })

def following(request):
    user_following = request.user.following.all()
    following_posts = []

    # Makes list of all the followed users' posts (probably not an efficient way to do this)
    for user_followed in user_following:
        posts = user_followed.posts.all()
        for post in posts:
            following_posts.append(post)

    following_posts = sorted(following_posts, key=)
    print(user_following)
    print(type(following_posts[0]))
    print(type(following_posts))
    # Sets up paginator into 10 pages (see Django paginator docs)
    paginator = Paginator(following_posts, 10)
    page_number = request.GET.get('page')
    page_obj = paginator.get_page(page_number)
    print(paginator.num_pages)

    # Renders page with paginator information
    return render(request, "network/following.html", {
        "posts": following_posts,
        "page_obj": page_obj,
        "page_number": range(1, paginator.num_pages+1)
    })

@login_required
def follow_unfollow(request, poster_id):
    # Checks request
    if request.method == "POST":
        # Gets button which could can have one of two values
        button = request.POST["following_btn"]

        current_user = User.objects.get(id=request.user.id)
        poster = User.objects.get(id=poster_id)

        # Checks type of button, either follows or unfollows, respectively
        if button == "Follow":
            print(button)
            current_user.following.add(poster)
            poster.followers.add(current_user)
            print(reverse("user", kwargs={"id": poster_id}))
            return HttpResponseRedirect(reverse("user", kwargs={"id": poster_id}))
        else:
            current_user.following.remove(poster)
            poster.followers.remove(current_user)
            return HttpResponseRedirect(reverse("user", kwargs={"id": poster_id}))

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
