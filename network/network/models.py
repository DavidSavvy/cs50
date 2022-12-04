from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    following = models.ManyToManyField("self")
    followers = models.ManyToManyField("self")

class Post(models.Model):
    poster = models.ForeignKey(User, on_delete=models.CASCADE ,related_name="posts")
    likes = models.IntegerField()
    likers = models.ManyToManyField(User, on_delete=models.CASCADE, related_name="liked_posts")