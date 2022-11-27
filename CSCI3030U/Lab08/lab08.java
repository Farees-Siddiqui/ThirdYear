import java.sql.*;

public class lab08 {
    private String url = "jdbc:postgresql://localhost:5432/postgres";
    private String user = "postgres";
    private String password = "Sadeem7apple";

    public Connection connect() throws SQLException {
        return DriverManager.getConnection(url, user, password);
    }

    public void getBooks() {
        String sql = "SELECT * FROM \"Actor\"";

        try (Connection conn = connect();
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(sql)) {
            System.out.println(rs);

            displayResult(rs);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public void displayResult(ResultSet rs) throws SQLException {
        while (rs.next()) {
            System.out.println(rs.getString("actorID") + "\t"
                    + rs.getString("fName-lName") + "\t"
                    + rs.getString("locationID"));
        }
    }

    public static void main(String[] args) {
        lab08 app = new lab08();
        try {
            app.connect();
            System.out.println("Successful Connection");
            app.getBooks();

        } catch (SQLException ex) {
            System.out.println(ex.getMessage());
        }
    }
}