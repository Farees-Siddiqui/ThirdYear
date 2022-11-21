-- Farees Siddiqui
-- 100 780 513

-- List all directors that were born in canada
SELECT "fName-lName" FROM "Director" WHERE "locationID" IN (SELECT "locationID" FROM "location" WHERE "country" = 'Canada');

-- List all movies which are directed by 'David Lynch'
SELECT "movieTitle" FROM "Movie" WHERE "movieID" IN (SELECT "movieID" FROM "movieDirector" WHERE "directorID" IN (SELECT "directorID" FROM "Director" WHERE "fName-lName" = 'WhedonJoss'));

--List all the actors who played in the movies for which cost of production was more than $1M. 
SELECT "fName-lName" FROM "Actor" WHERE "actorID" IN (SELECT "actorID" FROM "movie cast" WHERE "movieID" IN (SELECT "movieID" FROM "Movie" WHERE "budget" > 1000000));

-- List all the actors who played in the movies for which cost of production was more than $1M in other currencies
SELECT "fName-lName", "budget",
"budget" * 1.36 AS "'CAD'",
"budget" * 147.46 AS "'JPY'",
"budget" * 61.53 AS "'RUB'",
"budget" * 1.0 AS "'EUR'",
"budget" * 1.0 AS "'CHF'" 
FROM (("Actor"
INNER JOIN "movie cast" ON "Actor"."actorID" = "movie cast"."actorID")
INNER JOIN "Movie" on "Movie"."movieID" = "movie cast"."movieID")
WHERE "Movie"."budget" > 1000000;

-- Part D
SELECT "fName-lName" FROM "Director" WHERE "fName-lName" LIKE 'Ru%';

-- Part E
SELECT *
FROM "Movie"
WHERE "Movie"."movieID" IN (
	SELECT "movieID"
	FROM "movie genre"
	WHERE "genreName" = 
		(SELECT "genreName" FROM "Genre" WHERE "Genre"."genreName" = 'Sci-Fi')
	AND "movieID" IN
		(SELECT "movieID"
		 FROM "movie cast"
		 WHERE "actorID" IN
			(SELECT "actorID"
			 FROM "Actor"
			 WHERE "Actor"."dateOfBirth" < DATE('1982-10-30')
			)
		)
);

-- Part F
SELECT "Actor1"."fName-lName", "Actor2"."fName-lName" 
    FROM "Actor" as "Actor1", "Actor" as "Actor2" 
        WHERE ("Actor1"."eyecolour" = 'Dark Brown' 
        AND "Actor2"."eyecolour" = 'Dark Brown' 
        AND "Actor1"."fName-lName" != "Actor2"."fName-lName" 
        AND "Actor1"."fName-lName" < "Actor2"."fName-lName");