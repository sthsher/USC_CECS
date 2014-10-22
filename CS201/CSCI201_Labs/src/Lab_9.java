import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Scanner;


public class Lab_9 {
	public static void main(String [] args){
		System.out.println("--Program Start---");
		
		try{
			Class.forName("com.mysql.jdbc.Driver");
			
			java.sql.Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/CSCI201_Lab9", "root", "");
			
			java.sql.PreparedStatement statement = conn.prepareStatement("INSERT INTO User (first_name,last_name) VALUES (?,?)");
		
			String fName, lName;
			
			Scanner scan = new Scanner(System.in);
			
			System.out.print("First name: ");
			fName = scan.next();
			
			System.out.print("Last name: ");
			lName = scan.next();
			
			statement.setString(1,fName);
			statement.setString(2,lName);
			statement.execute();
			
			Statement retrieveState = conn.createStatement();
			ResultSet rs = retrieveState.executeQuery("SELECT * FROM User");
			
			while(rs.next()){
				System.out.println("First Name: " + rs.getString("first_name"));
				System.out.println("Last Name:  " + rs.getString("last_name"));
			}
			
		} catch (ClassNotFoundException CNFE){
			System.out.println("Class not found");
		} catch (Exception e){
			System.out.println("Exception");
		}
		

		
		
		
	}
}
