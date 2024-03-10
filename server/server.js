const express = require('express');
const http = require('http');
const path = require('path');
const fs = require('fs'); // Import the File System module
const { Server } = require("socket.io");

const app = express();
const server = http.createServer(app);
const io = new Server(server);
const PORT = 3000;

const VIDEOS_DIR = '/media/admin/SKC';

app.use(express.json());
app.use(express.static('pages'));

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'pages', 'index.html'));
});

app.post('/start', (req, res) => {
  const data = req.body;
  console.log('Received data from ESP8266:', data);
  
  // Emit an event to all connected clients to restart the video
  io.emit('restart-video');
  
  res.status(200).send();
});

// Endpoint to get the list of videos
app.get('/videos', (req, res) => {
  fs.readdir(VIDEOS_DIR, (err, files) => {
    if (err) {
      console.log("Error reading video directory:", err);
      res.status(500).send("Error reading video directory");
      return;
    }

    // Filter video files if necessary
    const videoFiles = files.filter(file => file.endsWith('.mp4')); // Example filter for mp4 files
    res.json(videoFiles);
  });
});

// Endpoint to serve a video file
app.get('/video/:filename', (req, res) => {
  const filename = req.params.filename;
  const filePath = path.join(VIDEOS_DIR, filename);

  // Check if file exists
  if (fs.existsSync(filePath)) {
    res.sendFile(filePath);
  } else {
    res.status(404).send("File not found");
  }
});

// Socket.io connection
io.on('connection', (socket) => {
  console.log('A user connected');
  socket.on('disconnect', () => {
    console.log('User disconnected');
  });
});

server.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
