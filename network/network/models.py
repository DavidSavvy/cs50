from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    following = models.ManyToManyField("self")
    followers = models.ManyToManyField("self")

class Post(models.Model):
    post_id = models.AutoField(primary_key=True)
    poster = models.ForeignKey(User, on_delete=models.CASCADE, related_name="posts")
    likers = models.ManyToManyField(User, related_name="liked_posts")
    timestamp = models.DateTimeField(auto_now_add=True)
    body = models.TextField(blank=True, null=True)
