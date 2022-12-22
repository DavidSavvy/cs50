import React from 'react';
import ReactDOM from 'react-dom';


document.addEventListener('DOMContentLoaded', () => {

})

class EditMessage extends React.Component {
  function test(event){
    //alert('test');

    //event.target.parentElement.innerHTML = "";
    ReactDOM.render(<Edit/>, event.target.parentElement);
  }

  function Edit(){
    return (
      <h5>bruh</h5>
    );
  }
}
