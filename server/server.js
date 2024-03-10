const express = require('express');
const app = express();

const PORT = 3000;

app.get('/', (req, res) => {
  res.send('Hello from Raspberry Pi');
});

app.get('/data', (req, res) => {
  const data = req.query;
  console.log('Received data from ESP8266:', data);
  res.send('Data received');
});

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});