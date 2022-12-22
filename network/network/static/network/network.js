import React from 'react';
import ReactDOM from 'react-dom';


document.addEventListener('DOMContentLoaded', () => {

})

class EditMessage extends React.Component {
  function Testfunc(event){
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
