const express = require('express');
const app = express();

const PORT = 3000;

// Middleware to parse JSON bodies. This must come before any routes that will need it.
app.use(express.json());

app.get('/', (req, res) => {
  res.send('Hello from Raspberry Pi');
});

app.post('/start', (req, res) => {
  const data = req.body; // Access data from the body of the request
  console.log('Received data from ESP8266:', data);
  
  res.status(200).send();
});

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
