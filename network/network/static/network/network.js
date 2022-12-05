document.addEventListener('DOMContentLoaded', function() {

    for (let post in Document.querySelectorAll("#post")) {
        if (!post.querySelector("#edit_link")) {
            post.style.marginBottom = "0px";
        }
    }

  });