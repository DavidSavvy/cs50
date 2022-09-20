from django.shortcuts import render
from django.http import Http404

import markdown2

from . import util


def index(request):
    return render(request, "encyclopedia/index.html", {
        "entries": util.list_entries()
    })

def page(request, title):
    page = util.get_entry(title)
    if not (page):
        raise Http404
    else:
        html = markdown2.markdown(page)
        return render(request, "encyclopedia/pagetemp.html", {
            "title": title,
            "page": html
        })

def search(request, search):
    return HttpsResponse 