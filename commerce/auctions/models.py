from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    pass

class Listing(models.Model):
    listing_id = models.IntegerField(primary_key=True)
    price = models.DecimalField(decimal_places=2)
    description = models.TextField()
    category = models.CharField(max_length=64)
    lister = models.ForeignKey(User, on_delete=models.CASCADE, related_name='listings')
    date = models.DateTimeField()

class Bid(models.Model):
    bid_id = models.IntegerField(primary_key=True)
    bid = models.DecimalField(decimal_places=2)
    bid_item = models.ForeignKey(Listing, on_delete=models.CASCADE, related_name='item_bids')
    bidder = models.ForeignKey(User, on_delete=models.CASCADE, related_name='user_bids')

class Comment(models.Model):
    text = models.TextField()
    commenter = models.ForeignKey(User, on_delete=models.CASCADE, related_name='user_comments')
    comment_item = models.ForeignKey(Listing, on_delete=models.CASCADE, related_name='item_comments')