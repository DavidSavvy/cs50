from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    pass

class Listing(models.Model):
    listing_id = models.IntegerField(primary_key=True)
    price = models.DecimalField(decimal_places=2)
    category = models.CharField(max_length=64)
    lister = models.ForeignKey

class Bid(models.Model):
    pass

class Comment(models.Model):
    pass