# Generated by Django 4.1.1 on 2022-10-07 13:16

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0001_initial'),
    ]

    operations = [
        migrations.RenameField(
            model_name='listing',
            old_name='image',
            new_name='image_url',
        ),
    ]
