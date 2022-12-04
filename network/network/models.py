from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    following = models.ManyToManyField()

class Post(models.Model):
    poster = models.ForeignKey(User, on_delete=models.CASCADE ,related_name="posts")