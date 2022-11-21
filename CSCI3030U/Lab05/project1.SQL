/*
Created: 2022-09-26
Modified: 2022-10-16
Model: PostgreSQL 11
Database: PostgreSQL 11
*/

-- Create tables section -------------------------------------------------

-- Table Movie

CREATE TABLE "Movie"
(
  "movieID" UUID NOT NULL,
  "festivalID" UUID,
  "movieTitle" Character varying NOT NULL,
  "releaseDate" Date NOT NULL,
  "rating" Bigint NOT NULL,
  "budget" Bigint NOT NULL,
  "gross" Bigint
)
WITH (
  autovacuum_enabled=true)
;

CREATE INDEX "IX_Relationship9" ON "Movie" ("festivalID")
;

ALTER TABLE "Movie" ADD CONSTRAINT "PK_Movie" PRIMARY KEY ("movieID")
;

-- Table Genre

CREATE TABLE "Genre"
(
  "genreName" Character varying NOT NULL,
  "Description" Text NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "Genre" ADD CONSTRAINT "PK_Genre" PRIMARY KEY ("genreName")
;

-- Table Actor

CREATE TABLE "Actor"
(
  "actorID" UUID[] NOT NULL,
  "locationID" UUID,
  "universityName" Character varying,
  "dateOfBirth" Date NOT NULL,
  "fName-lName" Character varying NOT NULL,
  "eyecolour" Character varying
)
WITH (
  autovacuum_enabled=true)
;

CREATE INDEX "IX_Relationship7" ON "Actor" ("locationID")
;

CREATE INDEX "IX_Relationship10" ON "Actor" ("universityName")
;

ALTER TABLE "Actor" ADD CONSTRAINT "PK_Actor" PRIMARY KEY ("actorID")
;

-- Table Director

CREATE TABLE "Director"
(
  "directorID" UUID NOT NULL,
  "locationID" UUID,
  "fName-lName" Character varying NOT NULL,
  "yearOfBirth" Bigint NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

CREATE INDEX "IX_Relationship8" ON "Director" ("locationID")
;

ALTER TABLE "Director" ADD CONSTRAINT "PK_Director" PRIMARY KEY ("directorID")
;

-- Table location

CREATE TABLE "location"
(
  "locationID" UUID NOT NULL,
  "city" Character varying NOT NULL,
  "state" Character varying NOT NULL,
  "country" Character varying NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "location" ADD CONSTRAINT "PK_location" PRIMARY KEY ("locationID")
;

-- Table University

CREATE TABLE "University"
(
  "universityName" Character varying NOT NULL,
  "directorID" UUID,
  "department" Character varying NOT NULL,
  "studentCount" Bigint NOT NULL,
  "private" Boolean NOT NULL,
  "color" Character varying NOT NULL,
  "description" Text
)
WITH (
  autovacuum_enabled=true)
;

CREATE INDEX "IX_Relationship12" ON "University" ("directorID")
;

ALTER TABLE "University" ADD CONSTRAINT "PK_University" PRIMARY KEY ("universityName")
;

-- Table movie genre

CREATE TABLE "movie genre"
(
  "movieID" UUID NOT NULL,
  "genreName" Character varying NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "movie genre" ADD CONSTRAINT "PK_movie genre" PRIMARY KEY ("movieID","genreName")
;

-- Table movie cast

CREATE TABLE "movie cast"
(
  "movieID" UUID NOT NULL,
  "actorID" UUID[] NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "movie cast" ADD CONSTRAINT "PK_movie cast" PRIMARY KEY ("movieID","actorID")
;

-- Table movieDirector

CREATE TABLE "movieDirector"
(
  "movieID" UUID NOT NULL,
  "directorID" UUID NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "movieDirector" ADD CONSTRAINT "PK_movieDirector" PRIMARY KEY ("movieID","directorID")
;

-- Table Cinema

CREATE TABLE "Cinema"
(
  "CinemaID" UUID NOT NULL,
  "locationID" UUID,
  "cinemaName" Character varying NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

CREATE INDEX "IX_Relationship2" ON "Cinema" ("locationID")
;

ALTER TABLE "Cinema" ADD CONSTRAINT "PK_Cinema" PRIMARY KEY ("CinemaID")
;

-- Table playedIn

CREATE TABLE "playedIn"
(
  "movieID" UUID NOT NULL,
  "CinemaID" UUID NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "playedIn" ADD CONSTRAINT "PK_playedIn" PRIMARY KEY ("movieID","CinemaID")
;

-- Table Ticket

CREATE TABLE "Ticket"
(
  "ticketID" UUID NOT NULL,
  "movieID" UUID NOT NULL,
  "CinemaID" UUID NOT NULL,
  "date" Date NOT NULL,
  "showTime" Time NOT NULL,
  "duration" Time NOT NULL,
  "cinemaType" Character varying NOT NULL,
  "price" Bigint NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "Ticket" ADD CONSTRAINT "PK_Ticket" PRIMARY KEY ("ticketID","movieID","CinemaID")
;

-- Table Festivals

CREATE TABLE "Festivals"
(
  "festivalID" UUID NOT NULL,
  "festivalName" Character varying NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "Festivals" ADD CONSTRAINT "PK_Festivals" PRIMARY KEY ("festivalID")
;

-- Table Awards

CREATE TABLE "Awards"
(
  "AwardID" UUID NOT NULL,
  "awardName" Character varying NOT NULL,
  "awardCategory" Character varying NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "Awards" ADD CONSTRAINT "PK_Awards" PRIMARY KEY ("AwardID")
;

-- Table movie awards

CREATE TABLE "movie awards"
(
  "movieID" UUID NOT NULL,
  "AwardID" UUID NOT NULL
)
WITH (
  autovacuum_enabled=true)
;

ALTER TABLE "movie awards" ADD CONSTRAINT "PK_movie awards" PRIMARY KEY ("movieID","AwardID")
;

-- Create foreign keys (relationships) section -------------------------------------------------

ALTER TABLE "movie genre"
  ADD CONSTRAINT "is a"
    FOREIGN KEY ("movieID")
    REFERENCES "Movie" ("movieID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "movie genre"
  ADD CONSTRAINT "has a"
    FOREIGN KEY ("genreName")
    REFERENCES "Genre" ("genreName")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "movie cast"
  ADD CONSTRAINT "has"
    FOREIGN KEY ("movieID")
    REFERENCES "Movie" ("movieID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "movie cast"
  ADD CONSTRAINT "has a"
    FOREIGN KEY ("actorID")
    REFERENCES "Actor" ("actorID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "movieDirector"
  ADD CONSTRAINT "has a"
    FOREIGN KEY ("movieID")
    REFERENCES "Movie" ("movieID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "movieDirector"
  ADD CONSTRAINT "has"
    FOREIGN KEY ("directorID")
    REFERENCES "Director" ("directorID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "Actor"
  ADD CONSTRAINT "born in"
    FOREIGN KEY ("locationID")
    REFERENCES "location" ("locationID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "Director"
  ADD CONSTRAINT "born in"
    FOREIGN KEY ("locationID")
    REFERENCES "location" ("locationID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "Actor"
  ADD CONSTRAINT "went to"
    FOREIGN KEY ("universityName")
    REFERENCES "University" ("universityName")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "University"
  ADD CONSTRAINT "went to"
    FOREIGN KEY ("directorID")
    REFERENCES "Director" ("directorID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "Cinema"
  ADD CONSTRAINT "is at"
    FOREIGN KEY ("locationID")
    REFERENCES "location" ("locationID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "playedIn"
  ADD CONSTRAINT "played in"
    FOREIGN KEY ("movieID")
    REFERENCES "Movie" ("movieID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "playedIn"
  ADD CONSTRAINT "plays"
    FOREIGN KEY ("CinemaID")
    REFERENCES "Cinema" ("CinemaID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "Ticket"
  ADD CONSTRAINT "has a"
    FOREIGN KEY ("movieID")
    REFERENCES "Movie" ("movieID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "Ticket"
  ADD CONSTRAINT "played in"
    FOREIGN KEY ("CinemaID")
    REFERENCES "Cinema" ("CinemaID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "Movie"
  ADD CONSTRAINT "playedAt"
    FOREIGN KEY ("festivalID")
    REFERENCES "Festivals" ("festivalID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "movie awards"
  ADD CONSTRAINT "have"
    FOREIGN KEY ("movieID")
    REFERENCES "Movie" ("movieID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

ALTER TABLE "movie awards"
  ADD CONSTRAINT "awarded to"
    FOREIGN KEY ("AwardID")
    REFERENCES "Awards" ("AwardID")
      ON DELETE NO ACTION
      ON UPDATE NO ACTION
;

