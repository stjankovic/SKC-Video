const express = require('express');
const app = express();

const PORT = 3000;

app.get('/', (req, res) => {
  res.send('Hello from Raspberry Pi');
});

app.post('/start', (req, res) => {
  const data = req.query;
  console.log('Received data from ESP8266:', data);
  // console.log(res);
  console.log(req);
  res.send('OK');
});

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});