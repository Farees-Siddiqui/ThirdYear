// get the json data from this api and print it to the console: "http://www.omdbapi.com/?i=${tt0059742}&apikey=${575d742d}"
let imdb_id = "tt0059800";
$(document).ready(function () {
    $.getJSON("http://www.omdbapi.com/?i="+imdb_id+"&apikey=575d742d", function (data) {
        console.log(data);

        var rating = Math.floor(data.imdbRating);

        // add the title as the txt of the input with id "Title"
        // the input is defined as follows: <input class="input is-narrow" type="text" id="Title">
        $("#Title").val(data.Title);
        $("#Year").val(data.Year);
        $("#Genre").val(data.Genre);
        $("#Runtime").val(data.Runtime);
        $("#Director").val(data.Director);
        $("#Writer").val(data.Writer);
        $("#Actor").val(data.Actors);
        $("#Plot").val(data.Plot);

        for (let i = 0; i < rating; i++) {
            // add the image with the src "https://img.icons8.com/ios/50/000000/star.png" to the div with id "Rating"
            // the div is defined as follows: <div id="Rating"></div>
            $("#Rating").append(`<img src="images/trophy.png" width="30" height="30"/>`);
        }

        $("#Poster").append(`<img src="${data.Poster}" id="posterImage"/>`);
    });

});