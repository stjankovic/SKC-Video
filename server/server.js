const express = require('express');
const app = express();
const { exec } = require('child_process');

const PORT = 3000;

// Middleware to parse JSON bodies. This must come before any routes that will need it.
app.use(express.json());

app.get('/', (req, res) => {
  // The URL you want to open in Chromium
  const url = 'http://skc.local:3000/';

  // Command to open Chromium in fullscreen mode
  // Adjust the path to Chromium as necessary for your system
  const command = `chromium-browser --kiosk '${url}'`;

  // Execute the command to open Chromium in fullscreen
  exec(command, (error, stdout, stderr) => {
    if (error) {
      console.error(`exec error: ${error}`);
      return res.send('Error opening Chromium');
    }
    res.send('Hello from Raspberry Pi - Chromium should now be open in fullscreen mode.');
  });
});

app.post('/start', (req, res) => {
  const data = req.body; // Access data from the body of the request
  console.log('Received data from ESP8266:', data);
  
  res.status(200).send();
});

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
