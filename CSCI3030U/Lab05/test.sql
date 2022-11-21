INSERT INTO "movieDirector" VALUES
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Black Panther'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'CooglerRyan')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Endgame'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'RussoJoe')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Infinity War'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'RussoAnthony')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Age of Ultron'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'WhedonJoss')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'The Avengers'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'WhedonJoss'));
