from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("wiki/<str:title>", views.page, name="page"),
    path("wiki", views.search, name="search"),
    path("create", views.create, name="create"),
    path("edit", views.edit, name="edit")
]
