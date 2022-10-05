from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    pass

class Listing(models.Model):
    listing_id = models.IntegerField()
    price = models.DecimalField(decimal_places=2)

class Bid(models.Model):
    pass

class Comment(models.Model):
    pass