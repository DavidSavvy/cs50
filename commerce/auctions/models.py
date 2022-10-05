from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    pass

class Listing(models.Model):
    listing_id = models.IntegerField()

class Bid(models.Model):
    pass

class Comment(models.Model):
    pass