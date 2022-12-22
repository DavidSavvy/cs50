import React from 'react';
import ReactDOM from 'react-dom';


document.addEventListener('DOMContentLoaded', () => {

})
function Testfunc(event){

  ReactDOM.render(<Edit/>, event.target.parentElement);
}


class EditMessage extends React.Component {

  function Edit(){
    return (
      <h5>bruh</h5>
    );
  }
}
