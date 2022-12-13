document.addEventListener('DOMContentLoaded', () => {
  
})


function test(event){
  alert('test');

  event.target.parentElement.innerHTML = "<div id="new_post" class="post" style="height: 250px; padding: 15px 15px 15px 15px;">\n
            <h4 style="">New Post</h4>\n
            <form method="POST" action="/post">\n
                {% csrf_token %}\n
                <textarea rows="5" style="width: 100%;" name="body"></textarea>\n
                <br>\n
                <input style="" class="btn btn-primary" type="submit" value="Post">\n
            </form>\n
        </div>";
}

