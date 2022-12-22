import React from 'react';
import ReactDOM from 'react-dom';


document.addEventListener('DOMContentLoaded', () => {

})
function Testfunc(event){

  ReactDOM.render(<EditText/>, event.target.parentElement);
}


class EditMessage extends React.Component {

  function EditText(){
    return (
      <h5>bruh</h5>
    );
  }
}
