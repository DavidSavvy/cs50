from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    pass

class Listing(models.Model):
    title = models.CharField(max_length=64)
    price = models.DecimalField(decimal_places=2, max_digits=10)
    description = models.TextField()
    category = models.CharField(max_length=64)
    lister = models.ForeignKey(User, on_delete=models.CASCADE, related_name='listings')
    image = models.TextField()
    date = models.DateTimeField(auto_now_add=True)

class Bid(models.Model):
    bid = models.DecimalField(decimal_places=2, max_digits=10)
    bid_item = models.ForeignKey(Listing, on_delete=models.CASCADE, related_name='item_bids')
    bidder = models.ForeignKey(User, on_delete=models.CASCADE, related_name='user_bids')

class Comment(models.Model):
    text = models.TextField()
    commenter = models.ForeignKey(User, on_delete=models.CASCADE, related_name='user_comments')
    comment_item = models.ForeignKey(Listing, on_delete=models.CASCADE, related_name='item_comments')