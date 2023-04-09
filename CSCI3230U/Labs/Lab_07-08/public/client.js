let imdb_id;
let selected;
let data;

$(document).ready(function () {

    const dropdowns = document.querySelectorAll('.dropdown');
    dropdowns.forEach((dropdown) => {
        dropdown.addEventListener('click', (event) => {
            event.stopPropagation();
            dropdown.classList.toggle('is-active');
        });
    });

    document.addEventListener('click', (event) => {
        dropdowns.forEach((dropdown) => {
            if (dropdown.classList.contains('is-active') && !dropdown.contains(event.target)) {
                dropdown.classList.remove('is-active');
            }
        });
    });

    const dropdownItems = document.querySelectorAll('.dropdown-item');

    dropdownItems.forEach(item => {
        item.addEventListener('click', () => {
            selected = item.textContent;

            const dropdownButton = document.querySelector('.dropdown-trigger button span:first-child');
            dropdownButton.textContent = selected;
        });
    });

    $("#Date").change(function () {
        date = $("#Date").val();

        date = date.replace(/-/g, "/");

        console.log(date);
    });

    fetch('/showtimes.json')
        .then(response => response.json())
        .then(inFile => {
            data = inFile; 
        })
        .catch(error => {
            console.error(error);
        });


    $("#Submit").click(function () {
        let ids = [];
        for (let i = 0; i < data.length; i++) {
            if (data[i].date == date && data[i].location == selected) {
                ids.push(data[i].id);
            }
        }

        const tableBody = document.getElementById("table-body");

        tableBody.innerHTML = "";

        ids.forEach((id) => {
            const movie = data.find((item) => item.id === id);

            const row = document.createElement("tr");

            const nameCell = document.createElement("td");
            nameCell.innerText = movie.title;

            nameCell.style.fontWeight = "bold";
            row.appendChild(nameCell);

            const timesCell = document.createElement("td");
            movie.times.forEach((time) => {
                const timeText = document.createElement("p");
                timeText.innerText = time;
                timesCell.appendChild(timeText);
            });
            row.appendChild(timesCell);

            tableBody.appendChild(row);
        });
    });

    $("#outForm").hide();

    $("#table-body").click(function (e) {
        row = e.target.parentNode.rowIndex;
        imdb_id = data[row].id;

        $("#Title").val("");
        $("#Title").val("");
        $("#Year").val("");
        $("#Genre").val("");
        $("#Runtime").val("");
        $("#Director").val("");
        $("#Writer").val("");
        $("#Actor").val("");
        $("#Plot").val("");

        $("#Rating").empty();
        $("#Poster").empty();

        $.getJSON("http://www.omdbapi.com/?i=" + imdb_id + "&apikey=575d742d", function (data) {
            console.log(data);

            var rating = Math.floor(data.imdbRating);

            $("#Title").val(data.Title);
            $("#Year").val(data.Year);
            $("#Genre").val(data.Genre);
            $("#Runtime").val(data.Runtime);
            $("#Director").val(data.Director);
            $("#Writer").val(data.Writer);
            $("#Actor").val(data.Actors);
            $("#Plot").val(data.Plot);

            for (let i = 0; i < rating; i++) {

                $("#Rating").append(`<img src="images/trophy.png" width="30" height="30"/>`);
            }

            $("#Poster").append(`<img src="${data.Poster}" id="posterImage"/>`);
        });
        $("#outForm").show();
    });

});