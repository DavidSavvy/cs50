from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("create", views.create, name="create"),
    path("categories", views.categories, name="categories"),
    path("categories/<str:category>", views.index_modified, name="index_modified"),
    path("listings/<str:id>", views.listing, name="listing"),
    path("listings/<str:id>/bid", views.bid, name="bid"),
    path("listings/<str:id>/close", views.close, name="close"),
    path("listings/<str:id>/comment", views.comment, name="comment"),
    path("listings/<str:id>/watchlist", views.watchlist, name="watchlist"),
    path("remove_watchlist", views.remove_watchlist, name="remove_watchlist")
]
