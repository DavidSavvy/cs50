function test(event){
  alert('test');

  event.target.parentNode.innerHTML = "<div><label>bruh</label></div>";
}

