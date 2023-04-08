// API_Key: 575d742d

const express = require('express');
const https = require('https');
const app = express();
const { readFile } = require('fs').promises;

app.use(express.static('public'));

const imdb_id = 'tt0059113';

app.get('/', async (request, response) => {

    response.send(await readFile('./showtimes.html', 'utf8'));

});

app.listen(process.env.PORT || 3000, () => console.log(`App available on http://localhost:3000`))

// get the json data from this api and print it to the console: "http://www.omdbapi.com/?i=${tt0059742}&apikey=${575d742d}"

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