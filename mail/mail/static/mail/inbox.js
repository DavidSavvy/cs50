document.addEventListener('DOMContentLoaded', function() {

  // Use buttons to toggle between views
  document.querySelector('#inbox').addEventListener('click', () => load_mailbox('inbox'));
  document.querySelector('#sent').addEventListener('click', () => load_mailbox('sent'));
  document.querySelector('#archived').addEventListener('click', () => load_mailbox('archive'));
  document.querySelector('#compose').addEventListener('click', compose_email);

  // By default, load the inbox
  load_mailbox('inbox');
});

function compose_email() {
  // Show compose view and hide other views
  document.querySelector('#emails-view').style.display = 'none';
  document.querySelector('#compose-view').style.display = 'block';

  // Clear out composition fields
  document.querySelector('#compose-recipients').value = '';
  document.querySelector('#compose-subject').value = '';
  document.querySelector('#compose-body').value = '';

  // POST email using API when form is submitted
  document.querySelector('#compose-form').onsubmit = () => {
    // See API details
    fetch('/emails', {
      method: 'POST',
      body: JSON.stringify({
        recipients: document.querySelector('#compose-recipients').value,
        subject: document.querySelector('#compose-subject').value,
        body: document.querySelector('#compose-body').value
      })
    })
    .then(response => response.json())
    .then(result => {
      console.log(result);
      // Sends error
      if (Object.keys(result)[0] === "error") {
        throw new error();
      }
      load_mailbox('sent');

    })
    .catch (error => alert("Invalid email"))

    // Prevents page refresh
    return false;
  };

}

function load_mailbox(mailbox) {

  // Show the mailbox and hide other views
  document.querySelector('#emails-view').style.display = 'block';
  document.querySelector('#compose-view').style.display = 'none';

  // Show the mailbox name
  document.querySelector('#emails-view').innerHTML = `<h3>${mailbox.charAt(0).toUpperCase() + mailbox.slice(1)}</h3>`;


  fetch(`/emails/${mailbox}`)
  .then(response => response.json())
  .then(emails => {
    emails.forEach((email) => {
      child = document.createElement("div");

      if (mailbox === "sent"){
        child.innerHTML = `<span style="font-weight: bold; margin: 0px 15px 0px 10px;">${email["recipients"]}</span> ${email["subject"]} <span style="float: right; margin-right: 10px;">${email["timestamp"]}</span>`;
      } else {
        child.innerHTML = `<span style="font-weight: bold; margin: 0px 15px 0px 10px;">${email["sender"]}</span> ${email["subject"]} <span style="float: right; margin-right: 10px;">${email["timestamp"]}</span>`;
      }

      if (email["read"] === true) {
        child.style.background = "grey";
      } else {
        child.style.background = "white";
      }

      child.style.borderStyle = "solid";
      child.style.borderWidth = "thin";
      child.style.height = "40px";
      child.style.paddingTop = "5px";
      document.querySelector('#emails-view').append(child);
    })
    console.log(emails);
  })

}

