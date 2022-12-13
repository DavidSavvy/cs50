function test(event){
  alert('test');

  event.target.parentElement.innerHTML = "<div><label>bruh</label></div>";
}

