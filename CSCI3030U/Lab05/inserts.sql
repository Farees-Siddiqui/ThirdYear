CREATE EXTENSION IF NOT EXISTS "uuid-TABLEossp";
--
INSERT INTO "Ticket" VALUES --
    (uuid_generate_v4(), (SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Black Panther'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'Cineplex Cinemas Yonge-Dundas and VIP'), '2020-04-01', '02:55:00', '02:15:00', 'IMAX', 15.99),
    (uuid_generate_v4(), (SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Endgame'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'AMC Saratoga 14'), '2020-04-01', '02:55:00', '03:02:00', '3D', 13.99),
    (uuid_generate_v4(), (SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Infinity War'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'AMC Sunset Place 24'), '2020-04-01', '02:55:00', '02:30:00', 'Regular', 7.99),
    (uuid_generate_v4(), (SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Age of Ultron'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'Cineplex Cinemas Oshawa'), '2020-04-01', '02:55:00', '02:20:00', 'IMAX', 15.99),
    (uuid_generate_v4(), (SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'The Avengers'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'AMC Boston Common 19'), '2020-04-01', '02:55:00', '02:23:00', 'Regular', 7.99);

INSERT INTO "Awards" VALUES -- 
    (uuid_generate_v4(), 'Best Picture', 'best picture'),
    (uuid_generate_v4(), 'Best Director', 'best director'),
    (uuid_generate_v4(), 'Best Actor', 'best actor'),
    (uuid_generate_v4(), 'Best Actress', 'best actress'),
    (uuid_generate_v4(), 'Best Screenplay', 'best screenplay');

INSERT INTO "Festivals" VALUES -- 
    (uuid_generate_v4(), 'Toronto International Film Festival'),
    (uuid_generate_v4(), 'Sundance Film Festival'),
    (uuid_generate_v4(), 'Cannes Film Festival'),
    (uuid_generate_v4(), 'Venice Film Festival'),
    (uuid_generate_v4(), 'Berlin International Film Festival');

INSERT INTO "Movie" VALUES --
    (uuid_generate_v4(), (SELECT "festivalID" FROM "Festivals" WHERE "festivalName" = 'Toronto International Film Festival'), 'Black Panther', '2018-02-16', 7, 200000000, 1347597973),
    (uuid_generate_v4(), (SELECT "festivalID" FROM "Festivals" WHERE "festivalName" = 'Sundance Film Festival'), 'The Avengers', '2012-05-04', 8, 220000000, 1518815515),
    (uuid_generate_v4(), (SELECT "festivalID" FROM "Festivals" WHERE "festivalName" = 'Cannes Film Festival'), 'Avengers: Age of Ultron', '2015-05-01', 7, 250000000, 1402809540),
    (uuid_generate_v4(), (SELECT "festivalID" FROM "Festivals" WHERE "festivalName" = 'Toronto International Film Festival'), 'Avengers: Infinity War', '2018-04-27', 8, 321000000, 2048359754),
    (uuid_generate_v4(), (SELECT "festivalID" FROM "Festivals" WHERE "festivalName" = 'Venice Film Festival'), 'Avengers: Endgame', '2019-04-26', 8, 356000000, 2797501328);

INSERT INTO "Genre" VALUES -- 
    ('Action', 'Movies in the action genre are fast-paced and include a lot of action like fight scenes, chase scenes, and slow-motion shots. They can feature superheroes, martial arts, or exciting stunts. These high-octane films are more about the execution of the plot rather than the plot itself'),
    ('Sci-Fi', 'Science fiction is a genre of fiction in which the stories often tell about science and technology of the future. It is important to note that science fiction has a relationship with the principles of science—these stories involve partially true- partially fictitious laws or theories of science'),
    ('Horror', 'Horror is a genre of literature, film, and television that is meant to scare, startle, shock, and even repulse audiences. The key focus of a horror novel, horror film, or horror TV show is to elicit a sense of dread in the reader through frightening images, themes, and situations'),
    ('Thriller', 'Thriller is a genre of fiction, having numerous, often overlapping subgenres. Thrillers are characterized and defined by the moods they elicit, giving viewers heightened feelings of suspense, excitement, surprise, anticipation and anxiety'),
    ('Romance', 'The romance genre is defined by two aspects that can be found in every romance book or novel: a central love story between characters. an emotionally satisfying, happy ending');

INSERT INTO "location" VALUES -- 
    (uuid_generate_v4(), 'Toronto', 'Ontario', 'Canada'),
    (uuid_generate_v4(), 'San Jose', 'California', 'USA'),
    (uuid_generate_v4(), 'Miami', 'Florida', 'USA'),
    (uuid_generate_v4(), 'Oshawa', 'Ontario', 'Canada'),
    (uuid_generate_v4(), 'Boston', 'Massachusetts', 'USA');

INSERT INTO "Director" VALUES -- 
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'Toronto'), 'CooglerRyan', 1986),
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'San Jose'),'WhedonJoss', 1964),
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'Boston'),'RussoAnthony', 1970),
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'Oshawa'),'RussoJoe', 1971),

INSERT INTO "Actor" VALUES -- 
    (ARRAY[uuid_generate_v4()], (SELECT "locationID" FROM "location" WHERE 'city' = 'Toronto'), NULL, '1965-04-04', 'Downey-Robert', 'Dark Brown');
    (ARRAY[uuid_generate_v4()], (SELECT "locationID" FROM "location" WHERE 'city' = 'San Jose'), NULL, '1981-06-13', 'EvansChris', 'Green'),
    (ARRAY[uuid_generate_v4()], (SELECT "locationID" FROM "location" WHERE 'city' = 'Boston'), NULL, '1984-11-22', 'JohanssonScarlett', 'Green'),
    (ARRAY[uuid_generate_v4()], (SELECT "locationID" FROM "location" WHERE 'city' = 'Oshawa'), NULL, '1983-08-11', 'HemsworthChris', 'Blue'),
    (ARRAY[uuid_generate_v4()], (SELECT "locationID" FROM "location" WHERE 'city' = 'Miami'), NULL, '1967-11-22', 'RuffaloMark', 'Dark Brown');

INSERT INTO "University" VALUES -- 
    ('New York University', (SELECT "directorID" FROM "Director" WHERE "Director.fName-lName" = "CooglerRyan"), 'Science', 28772, true, 'white-purple', 'New York University is a private research university in New York City'),
    ('Massachusetts Institute of Technology', (SELECT "directorID" FROM "Director" WHERE "Director.fName-lName" = "WhedonJoss"), 'Mathematics', 11376, true, 'red-black-silver-cardinal', 'The Massachusetts Institute of Technology is a private land-grant research university in Cambridge, Massachusetts. Established in 1861, MIT has since played a key role in the development of modern technology and science, ranking among the top academic institutions in the world'),
    ('University of Toronto', (SELECT "directorID" FROM "Director" WHERE "Director.fName-lName" = "RussoAnthony"), 'Arts and Science', 72389, false, 'white-blue', 'The University of Toronto is a public research university in Toronto, Ontario, Canada, located on the grounds that surround Queens Park. It was founded by royal charter in 1827 as Kings College, the first institution of higher learning in Upper Canada'),
    ('Queens University', (SELECT "directorID" FROM "Director" WHERE "Director.fName-lName" = "RussoJoe"), 'Computing', 24143, false, 'blue-gold-red', 'Queens University at Kingston, commonly known as Queens University or simply Queens, is a public research university in Kingston, Ontario, Canada. Queens holds more than 1,400 hectares of land throughout Ontario and owns Herstmonceux Castle in East Sussex, England'),
    ('Princeton University', (SELECT "directorID" FROM "Director" WHERE "Director.fName-lName" = "BodenAnna"), 'Science', 8623, true, 'black-orange', 'Princeton University is a private Ivy League research university in Princeton, New Jersey. Founded in 1746 in Elizabeth as the College of New Jersey, Princeton is the fourth-oldest institution of higher education in the United States and one of the nine colonial colleges chartered before the American Revolution.');
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'Miami'),'BodenAnna', 1979);

INSERT INTO "movie genre" VALUES --
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Black Panther'), 'Action'),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Endgame'), 'Sci-Fi'),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Infinity War'), 'Thriller'),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Age of Ultron'), 'Sci-Fi'),

INSERT INTO "movieDirector" VALUES --
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Black Panther'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'CooglerRyan')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Endgame'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'RussoJoe')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Infinity War'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'RussoAnthony')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Age of Ultron'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'WhedonJoss')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'The Avengers'), (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'WhedonJoss'));
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'The Avengers'), 'Action');

INSERT INTO "Cinema" VALUES -- 
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'Toronto'), 'Cineplex Cinemas Yonge-Dundas and VIP'),
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'San Jose'), 'AMC Saratoga 14'),
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'Miami'), 'AMC Sunset Place 24'),
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'Oshawa'), 'Cineplex Cinemas Oshawa'),
    (uuid_generate_v4(), (SELECT "locationID" FROM "location" WHERE city = 'Boston'), 'AMC Boston Common 19');

INSERT INTO "playedIn" VALUES -- 
	((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Black Panther'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'Cineplex Cinemas Yonge-Dundas and VIP')),
	((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Endgame'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'AMC Saratoga 14')),
	((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Infinity War'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'AMC Sunset Place 24')),
	((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Age of Ultron'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'Cineplex Cinemas Oshawa')),
	((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'The Avengers'), (SELECT "CinemaID" FROM "Cinema" WHERE "cinemaName" = 'AMC Boston Common 19'));

INSERT INTO "movie awards" VALUES --
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Black Panther'), (SELECT "AwardID" FROM "Awards" WHERE "awardName" = 'Best Picture')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Endgame'), (SELECT "AwardID" FROM "Awards" WHERE "awardName" = 'Best Picture')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Infinity War'), (SELECT "AwardID" FROM "Awards" WHERE "awardName" = 'Best Picture')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Age of Ultron'), (SELECT "AwardID" FROM "Awards" WHERE "awardName" = 'Best Picture')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'The Avengers'), (SELECT "AwardID" FROM "Awards" WHERE "awardName" = 'Best Picture'));

-- insert movie cast into movie cast table
INSERT INTO "movie cast" VALUES -- 
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Black Panther'), (SELECT "actorID" FROM "Actor" WHERE "fName-lName" = 'Evans-Chris')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Endgame'), (SELECT "actorID" FROM "Actor" WHERE "fName-lName" = 'Downey-Robert')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Infinity War'), (SELECT "actorID" FROM "Actor" WHERE "fName-lName" = 'Hemsworth-Chris')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'Avengers: Age of Ultron'), (SELECT "actorID" FROM "Actor" WHERE "fName-lName" = 'Johansson-Scarlett')),
    ((SELECT "movieID" FROM "Movie" WHERE "movieTitle" = 'The Avengers'), (SELECT "actorID" FROM "Actor" WHERE "fName-lName" = 'Ruffalo-Mark'));


--Find all the pairs of actors who have blue eye color. Produce pairs in alphabetic order, e.g., (Howard before Lynch) and do not produce pairs like (Lynch, Lynch
SELECT "fName-lName" AS "Actor 1", "fName-lName" AS "Actor 2" FROM "Actor" WHERE "eyeColor" = 'Blue' AND "fName-lName" < "fName-lName";

-- find all movies that have actors born in atleast 2 different countries
SELECT "movieTitle" FROM "Movie" WHERE "movieID" IN (SELECT "movieID" FROM "movie cast" WHERE "actorID" IN (SELECT "actorID" FROM "Actor" WHERE "country" = 'USA')) AND "movieID" IN (SELECT "movieID" FROM "movie cast" WHERE "actorID" IN (SELECT "actorID" FROM "Actor" WHERE "country" = 'Canada'));