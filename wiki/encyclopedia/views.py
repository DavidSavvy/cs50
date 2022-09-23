from django.shortcuts import render
from django.http import Http404, HttpResponse, HttpRequest
from django.views.decorators.csrf import csrf_exempt


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

def search(request):
    query = request.GET['q'].lower()
    entries = util.list_entries()
    results = []
    for entry in entries:
        if query == entry.lower():
            return page(request, entry)
        elif query in entry.lower():
            results.append(entry)

    return render(request, "encyclopedia/results.html", {
        "results": results
    })

@csrf_exempt
def create(request):
    if request.method == "GET":
        return render(request, "encyclopedia/newpage.html")
    else:
        submission_dict = dict(request.POST)
        util.save_entry(submission_dict["title"][0], submission_dict["post"][0])
        return HttpResponse(submission_dict.values())


"""
check for duplicate pages
send user to finished page if clear
"""
