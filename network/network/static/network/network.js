function test(event){
  alert('test');
  event.target.innerHTML = "
  <div class="post" style="height: 250px; padding: 15px 15px 15px 15px;">
            <h4 style="">New Post</h4>
            <form method="POST" action="/post">
                {% csrf_token %}
                <textarea rows="5" style="width: 100%;" name="body"></textarea>
                <br>
                <input style="" class="btn btn-primary" type="submit" value="Post">
            </form>
        </div>";
}

