// API_Key: 575d742d

const express = require('express');
const https = require('https');
const app = express();
const { readFile } = require('fs').promises;

app.use(express.static('public'));

app.get('/', (req, res) => {
  res.redirect('showtimes.html');
})

app.use((req, res, next) => {
  if (req.url.endsWith('.css')) {
    res.setHeader('Content-Type', 'text/css');
  }
  next();
});


app.listen(process.env.PORT || 3000, () => console.log(`App available on http://localhost:3000`))

app.get('/showtimes.json', (req, res) => {
  readFile('showtimes.json', 'utf8')
    .then(data => {
      res.setHeader('Content-Type', 'application/json');
      res.send(data);
      console.log(data);
    })
    .catch(err => {
      console.error(err);
      res.status(500).send('Internal Server Error');
    });
});



  // const options = {
//     hostname: 'www.omdbapi.com',
//     port: 443,
//     path: '/?i='+imdb_id+'&apikey=575d742d',
//     method: 'GET'
// };

// https.request(options, (response) => {
//     let data = '';
//     response.on('data', (chunk) => {
//         data += chunk;
//     });
//     response.on('end', () => {
//         console.log(JSON.parse(data));

//         // populate the text field for the movie title in the html file with the title from the json data, the id of the text field is "Title"
//         console.log(data.Title);
//         $('#Title').text(data.Title);
//     });
// }).end();