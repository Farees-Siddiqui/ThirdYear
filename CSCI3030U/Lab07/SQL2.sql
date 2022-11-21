-- Task 2
-- Siddiqui Farees (100-780-513)

-- 1 a) From table actors find the average age
SELECT AVG(AGE(CURRENT_DATE, "dateOfBirth"))  as "average age" FROM "Actor";

-- 1 b) Find the number of different countries in which actors from the movie “The Avengers” were born
SELECT COUNT(DISTINCT "country") FROM "Actor" WHERE "id" IN (SELECT "actorId" FROM "MovieActor" WHERE "movieId" IN (SELECT "id" FROM "Movie" WHERE "title" = 'The Avengers'));

-- 1 c) Find the number of actors with Dark Brown eyes
SELECT COUNT(*) FROM "Actor" WHERE "eyecolour" = 'Dark Brown';

-- 1 d) what is the number of movies in which Robert Downey Jr. was playing
SELECT COUNT(*) FROM "Movie" WHERE "movieID" IN (SELECT "movieID" FROM "movie cast" WHERE "movie cast"."actorID" IN (SELECT "actorID" FROM "Actor" WHERE "fName-lName" = 'Downey-Robert'));

-- 1 e) Find the minimum, average, and maximum budget for each type of movie
SELECT "Genre"."genreName",
	MIN("Movie"."budget") as "MINIMUM",
	AVG("Movie"."budget") as "AVERAGE",
	MAX("Movie"."budget") as "MAXIMUM"
FROM "Genre", "Movie"
WHERE "Movie"."movieID" IN
	(SELECT "movieID" FROM "movie genre" WHERE "movie genre"."genreName" = "Genre"."genreName")
GROUP BY "Genre"."genreName";

-- 1 f) Find the average rating for each movie which has a director born in Toronto or blue eyecolour
SELECT "movieTitle", "rating"
FROM "Movie"
WHERE "movieID" IN 
	(SELECT "movieID"
	 FROM "movieDirector"
	 WHERE "directorID" in
	 	(SELECT "directorID"
		 FROM "Director"
		 WHERE "directorID" IN
		 	(SELECT "directorID"
			 FROM "location"
			 WHERE city = 'Toronto'
			)
		)
	);

-- 1 g) Find all the movies that have actors born in atleast 2 different countries (this answer seems very wrong)
SELECT DISTINCT "movieTitle", "Actor"."locationID" 
FROM (("Movie"
	  INNER JOIN "movie cast" ON "Movie"."movieID" = "movie cast"."movieID")
	  INNER JOIN "Actor" ON "Actor"."actorID" = "movie cast"."actorID")
WHERE "Actor"."actorID" in (SELECT "actorID" FROM "movie cast")


-- 1 h) Find how many awards each movie in total has received and rank the movies (display the title) by the amount of awards
SELECT "movieTitle", COUNT(*)
    FROM "Movie", "movie awards"
    WHERE "movie awards"."movieID" = "Movie"."movieID"
GROUP BY "movieTitle";