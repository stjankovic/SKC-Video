const express = require('express');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(express.json());
app.use(express.static('public')); // Serve static files from 'public' directory

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'index.html')); // Serve your index.html file
});

// Other routes...

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});