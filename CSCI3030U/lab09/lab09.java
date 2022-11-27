import java.sql.*;

public class lab09 {
    private String url = "jdbc:postgresql://localhost:5432/postgres";
    private String user = "postgres";
    private String password = "Sadeem7apple";

    public Connection connect() throws SQLException {
        return DriverManager.getConnection(url, user, password);
    }

    public void getTable(String table) {
        String sql = "SELECT * FROM \"" + table + "\"";
        try (Connection conn = connect();
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(sql)) {
            displayResult(rs);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertFestivals() {
        String sql = "INSERT INTO \"Festivals\" VALUES (uuid_generate_v4(), 'Test Festival')";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertFestivals(String festivalID, String festivalName) {
        String sql = "INSERT INTO \"Festivals\" VALUES (" + festivalID + "," + festivalName + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertAwards() {
        String sql = "INSERT INTO \"Awards\" VALUES (uuid_generate_v4(), 'Test Award', 'Test Category')";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertAwards(String AwardID, String AwardName, String AwardCategory) {
        String sql = "INSERT INTO \"Awards\" VALUES (" + AwardID + "," + AwardName + "," + AwardCategory + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertGenre() {
        String sql = "INSERT INTO \"Genre\" VALUES ('Test Genre', 'Test Genre Description')";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertGenre(String GenreName, String GenreDescription) {
        String sql = "INSERT INTO \"Genre\" VALUES (" + GenreName + "," + GenreDescription + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertLocation() {
        String sql = "INSERT INTO \"location\" VALUES (uuid_generate_v4(), 'Test Location City', 'Test Location Province', 'Test Location Country')";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertLocation(String LocationID, String LocationCity, String LocationProvince,
            String LocationCountry) {
        String sql = "INSERT INTO \"location\" VALUES (" + LocationID + "," + LocationCity + "," + LocationProvince
                + "," + LocationCountry + ")";

        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertDirector() {
        String sql = "INSERT INTO \"Director\" VALUES (uuid_generate_v4(), (SELECT \"locationID\" FROM \"location\" WHERE city = 'Test Location City'), 'Test Director Name', 1984)";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertDirector(String DirectorID, String LocationID, String DirectorName, int DirectorBirthYear) {
        String sql = "INSERT INTO \"Director\" VALUES (" + DirectorID + "," + LocationID + "," + DirectorName + ","
                + DirectorBirthYear + ")";

        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovie() {
        String sql = "INSERT INTO \"Movie\" VALUES (uuid_generate_v4(), (SELECT \"festivalID\" FROM \"Festivals\" WHERE \"festivalName\" = 'Test Festival'), 'Test Movie Name', '2022-11-19', 9, 256000000, 4797508348)";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovie(String movieID, String festivalID, String movieName, String movieReleaseDate, int rating,
            int movieBudget, int gross) {
        String sql = "INSERT INTO \"Movie\" VALUES (uuid_generate_v4(), (SELECT \"festivalID\" FROM \"Festivals\" WHERE \"festivalName\" = 'Test Festival'), 'Test Movie Name', '2022-11-19', 9, 256000000, 4797508348)";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertActor() {
        String sql = "INSERT INTO \"Actor\" VALUES (ARRAY[uuid_generate_v4()], (SELECT \"locationID\" FROM \"location\" WHERE city = 'Test Location City'), NULL, '1984-01-23', 'Test Actor Name', 'Grey')";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertActor(String actorID, String locationID, String universityName, String actorDOB, String actorName,
            String actorHairColor) {
        String sql = "INSERT INTO \"Actor\" VALUES (" + actorID + "," + locationID + "," + universityName + ","
                + actorDOB + "," + actorName + "," + actorHairColor + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertUniversity() {
        String sql = "INSERT INTO \"University\" VALUES ('Test University Name', (SELECT \"directorID\" FROM \"Director\" WHERE \"fName-lName\" = 'Test Director Name'), 'Science', 26123, false, 'green-white', 'test university description')";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertUniversity(String universityName, String directorID, String faculty, int universitySize,
            String isPublic, String universityColors, String universityDescription) {

        String sql = "INSERT INTO \"University\" VALUES (" + universityName + "," + directorID + "," + faculty + ","
                + universitySize + "," + isPublic + "," + universityColors + "," + universityDescription + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertCinema() {
        String sql = "INSERT INTO \"Cinema\" VALUES(uuid_generate_v4(), (SELECT \"locationID\" FROM \"location\" WHERE city = 'Test Location City'), 'Test Cinema Name')";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertCinema(String cinemaID, String locationID, String cinemaName) {
        String sql = "INSERT INTO \"Cinema\" VALUES(" + cinemaID + "," + locationID + "," + cinemaName + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovieAward() {
        String sql = "INSERT INTO \"movie awards\" VALUES ((SELECT \"movieID\" FROM \"Movie\" WHERE \"movieTitle\" = 'Test Movie Name'), (SELECT \"AwardID\" FROM \"Awards\" WHERE \"awardName\" = 'Test Award'))";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovieAward(String movieID, String awardID) {
        String sql = "INSERT INTO \"movie awards\" VALUES (" + movieID + "," + awardID + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovieCast() {
        String sql = "INSERT INTO \"movie cast\" VALUES ((SELECT \"movieID\" FROM \"Movie\" WHERE \"movieTitle\" = 'Test Movie Name'), (SELECT \"actorID\" FROM \"Actor\" WHERE \"fName-lName\" = 'Test Actor Name'))";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovieCast(String movieID, String actorID) {
        String sql = "INSERT INTO \"movie cast\" VALUES (" + movieID + "," + actorID + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertPlayedIn() {
        String sql = "INSERT INTO \"playedIn\" VALUES ((SELECT \"movieID\" FROM \"Movie\" WHERE \"movieTitle\" = 'Test Movie Name'), (SELECT \"CinemaID\" FROM \"Cinema\" WHERE \"cinemaName\" = 'Test Cinema Name'))";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertPlayedIn(String movieID, String cinemaID) {
        String sql = "INSERT INTO \"playedIn\" VALUES (" + movieID + "," + cinemaID + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovieDirector() {
        String sql = "INSERT INTO \"movieDirector\" VALUES ((SELECT \"movieID\" FROM \"Movie\" WHERE \"movieTitle\" = 'Test Movie Name'), (SELECT \"directorID\" FROM \"Director\" WHERE \"fName-lName\" = 'Test Director Name'))";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovieDirector(String movieID, String directorID) {
        String sql = "INSERT INTO \"movieDirector\" VALUES (" + movieID + "," + directorID + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovieGenre() {
        String sql = "INSERT INTO \"movie genre\" VALUES ((SELECT \"movieID\" FROM \"Movie\" WHERE \"movieTitle\" = 'Test Movie Name'), 'Test Genre')";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertMovieGenre(String movieID, String genre) {
        String sql = "INSERT INTO \"movie genre\" VALUES (" + movieID + "," + genre + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertTicket() {
        String sql = "INSERT INTO \"Ticket\" VALUES (uuid_generate_v4(), (SELECT \"movieID\" FROM \"Movie\" WHERE \"movieTitle\" = 'Test Movie Name'), (SELECT \"CinemaID\" FROM \"Cinema\" WHERE \"cinemaName\" = 'Test Cinema Name'), '2022-11-19', '02:45:00', '02:35:00', 'Regular', 7.99)";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void insertTicket(String ticketID, String movieID, String CinemaID, String date, String showTime,
            String duration, String ticketType, double price) {
        String sql = "INSERT INTO \"Ticket\" VALUES (" + ticketID + "," + movieID + "," + CinemaID + "," + date + ","
                + showTime + "," + duration + "," + ticketType + "," + price + ")";
        try (Connection conn = connect(); Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void displayResult(ResultSet rs) throws SQLException {
        ResultSetMetaData rsmd = rs.getMetaData();
        int columnsNumber = rsmd.getColumnCount();
        while (rs.next()) {
            for (int i = 1; i <= columnsNumber; i++) {
                if (i > 1)
                    System.out.print(",  ");
                String columnValue = rs.getString(i);
                System.out.print(columnValue + " (" + rsmd.getColumnName(i) + ")");
            }
            System.out.println("");
        }
    }

    // Queries
    public void getCanadianDirectors() {
        String sql = "SELECT \"fName-lName\" FROM \"Director\" WHERE \"locationID\" IN (SELECT \"locationID\" FROM \"location\" WHERE \"country\" = 'Canada')";
        try (Connection conn = connect();
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(sql)) {
            System.out.println("Canadian Directors:");
            displayResult(rs);
            System.out.println("----------------");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void getMoviesByDirector(String directorName) {
        String sql = "SELECT \"movieTitle\" FROM \"Movie\" WHERE \"movieID\" IN (SELECT \"movieID\" FROM \"movieDirector\" WHERE \"directorID\" IN (SELECT \"directorID\" FROM \"Director\" WHERE \"fName-lName\" = ?))";
        try (Connection conn = connect();
                PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, directorName);
            ResultSet rs = pstmt.executeQuery();
            System.out.printf("Movies by [%s]:\n", directorName);
            displayResult(rs);
            System.out.println("----------------");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void getActorsWhereProductionIsGreaterThanX(int production) {
        String sql = "SELECT \"fName-lName\" FROM \"Actor\" WHERE \"actorID\" IN (SELECT \"actorID\" FROM \"movie cast\" WHERE \"movieID\" IN (SELECT \"movieID\" FROM \"Movie\" WHERE \"budget\" > ?))";
        try (Connection conn = connect();
                PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setInt(1, production);
            ResultSet rs = pstmt.executeQuery();
            System.out.printf("Actors where production is greater than [%d]:\n", production);
            displayResult(rs);
            System.out.println("----------------");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void getSimilarDirectorNames(String pattern) {
        String sql = "SELECT \"fName-lName\" FROM \"Director\" WHERE \"fName-lName\" LIKE ?";
        try (Connection conn = connect();
                PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, pattern);
            ResultSet rs = pstmt.executeQuery();
            System.out.printf("Similar Director Names to pattern [%s]:\n", pattern);
            displayResult(rs);
            System.out.println("----------------");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        lab09 app = new lab09();
        try {
            app.connect();
            System.out.println("Successful Connection");

            // app.insertFestivals(); // Inserted a new festival, if ran again will insert a

            // app.insertAwards();

            // app.insertGenre();

            // app.insertLocation();

            // app.insertDirector();

            // app.insertActor();

            // app.insertMovie();

            // app.insertUniversity();

            // app.insertCinema();

            // app.insertMovieAward();

            // app.insertMovieCast();

            // app.insertPlayedIn();

            // app.insertMovieDirector();

            // app.insertFestivals("uuid_generate_v4()", "'Test Festival 2'");

            // app.insertAwards("uuid_generate_v4()", "'Test Award 2'", "'Test Award
            // Category 2'");

            // app.insertGenre("'Test Genre 2'", "'Test Genre 2 Description'");

            // app.insertLocation("uuid_generate_v4()", "'Test Location 2 City'", "'Test
            // Location 2 State'",
            // "'Test Location 2 Country'");

            // app.insertDirector("uuid_generate_v4()",
            // "(SELECT \"locationID\" FROM \"location\" WHERE city = 'Test Location 2
            // City')",
            // "'Test Director 2 Name'", 1990);

            // app.insertActor("ARRAY[uuid_generate_v4()]",
            // "(SELECT \"locationID\" FROM \"location\" WHERE city = 'Test Location 2
            // City')", "NULL",
            // "'1978-05-17'", "'Test Actor 2 Name'", "Black");

            // app.insertMovie("uuid_generate_v4()",
            // "(SELECT \"festivalID\" FROM \"Festivals\" WHERE \"festivalName\" = 'Test
            // Festival 2')",
            // "'Test Movie 2 Name'", "'2022-12-30'", 4, 256000000, 479750834);

            // app.insertUniversity("'Test University 2 Name'",
            // "(SELECT \"directorID\" FROM \"Director\" WHERE \"fName-lName\" = 'Test
            // Director Name')", "'Arts'",
            // 31000, "false", "'yellow-green'", "'Test University 2 Description'");

            // app.insertCinema("uuid_generate_v4()",
            // "(SELECT \"locationID\" FROM \"location\" WHERE city = 'Test Location 2
            // City')",
            // "'Test Cinema 2 Name'");

            // app.insertMovieAward("'7827b6e1-fbdd-43b4-b220-a607e99028f9'",
            // "(SELECT \"AwardID\" FROM \"Awards\" WHERE \"awardName\" = 'Test Award 2')");

            // app.insertMovieCast("'7827b6e1-fbdd-43b4-b220-a607e99028f9'",
            // "'{e9838673-fca8-486b-a067-caf69f34437a}'");

            // app.insertPlayedIn("'7827b6e1-fbdd-43b4-b220-a607e99028f9'",
            // "(SELECT \"CinemaID\" FROM \"Cinema\" WHERE \"cinemaName\" = 'Test Cinema 2
            // Name')");

            System.out.println("-----Festivals-----");
            app.getTable("Festivals");
            System.out.println("------Awards-------");
            app.getTable("Awards");
            System.out.println("------Genre--------");
            app.getTable("Genre");
            System.out.println("-----Locations-----");
            app.getTable("location");
            System.out.println("------Director-----");
            app.getTable("Director");
            System.out.println("------Actor--------");
            app.getTable("Actor");
            System.out.println("------Movie--------");
            app.getTable("Movie");
            System.out.println("----University-----");
            app.getTable("University");
            System.out.println("------Cinema-------");
            app.getTable("Cinema");
            System.out.println("-----Movie Awards-----");
            app.getTable("movie awards");
            System.out.println("-----Movie Cast-----");
            app.getTable("movie cast");
            System.out.println("-----Played in-----");
            app.getTable("playedIn");
            System.out.println("-----Movie Director-----");
            app.getTable("movieDirector");
            System.out.println("-----Movie Genre-----");
            app.getTable("movie genre");
            System.out.println("-----Ticket-----");
            app.getTable("Ticket");

            System.out.println("\n-----Database Queries-----\n");

            // Queries
            app.getCanadianDirectors();
            app.getMoviesByDirector("WhedonJoss");
            app.getActorsWhereProductionIsGreaterThanX(1000000);
            app.getSimilarDirectorNames("Ru%");

        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }
    }
}