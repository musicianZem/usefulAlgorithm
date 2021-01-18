// on web.
function sendSlack(p_url, p_text) {
  var xhr = new XMLHttpRequest();
  xhr.open('POST', p_url);
  var sendJson = {
    text: p_text
  };
  xhr.send(JSON.stringify(sendJson));
}

// send example
sendSlack('https://hooks.slack.com/services/XXXXXXXXX/YYYYYYYYY/012340123401234012340123', 'hi');
