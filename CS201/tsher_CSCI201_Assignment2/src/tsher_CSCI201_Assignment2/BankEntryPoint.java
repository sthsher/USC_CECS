package tsher_CSCI201_Assignment2;

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.FileNotFoundException;

public class BankEntryPoint {
	private static UserStorage accounts;
	
	private static void readFile(){
		try{

			FileReader fr 			= new FileReader("bank_data.txt");
			BufferedReader reader 	= new BufferedReader(fr);
						
			//first line is the number of users
			String line = reader.readLine();
			
			int lines = Integer.parseInt(line);
			
			for (int i = 0; i < lines; ++i){
				//Read next line
				line = reader.readLine();
				
				//Create datafiles
				String username;
				String password;
				double checkings;
				double savings;
				
				//Open scanner for new scan
				Scanner scan = new Scanner(line);
				
				//Go through the line and extract the information
				username 	= scan.next();
				password 	= scan.next();
				checkings	= scan.nextDouble();
				savings 	= scan.nextDouble();
				
				// System.out.println("name: " + username);
				// System.out.println("pass: " + password);
				// System.out.println("chec: " + checkings);
				// System.out.println("savi: " + savings);
				
				//Make a new user
				BankUser newUser = new BankUser(username, password, checkings, savings);
				
				//add it
				accounts.addUser(newUser);
				
				scan.close();
			}
			
			reader.close();
			
		} catch (FileNotFoundException fnfe){
			System.out.println("No file found, empty database");
		} catch (IOException IOE){
			System.out.println(IOE.getMessage());
		}
	}
	
	private static void writeFile(){
		try{
			//make printer
			FileWriter fw = new FileWriter("bank_data.txt");
			PrintWriter printer = new PrintWriter(fw);
			
			//print num of users
			printer.println(accounts.getNumOfUsers());
			
			for (int i = 0; i < accounts.getNumOfUsers(); ++i){
				//go through and print everything
				//Extract the information first
				BankUser outUser 	= accounts.getUserByIndex(i);
				String username 	= outUser.getUsername();
				String password 	= outUser.getPassword();
				double checkings 	= outUser.getCheckingsAmount();
				double savings 		= outUser.getSavingsAmount();
				
				//Now print it
				printer.println(username + " " + password + " " + checkings + " " + savings);
			
				//flush
				printer.flush();
			}
			
			printer.close();
			
		} catch(IOException IOE){
			System.out.println(IOE.getMessage());
		}
	}

	private static void createAccount(Scanner scan){
		//Variables
		String username = "";
		String password = "";
		// double checking = 0;
		// double savings  = 0;
		boolean success = false;
		boolean loop	= true;

		while (!success){
			System.out.print("\nUsername: ");
			username = scan.nextLine();

			if (username.equals("q")){
				return;
			}

			if (accounts.usernameAlreadyExist(username)){
				System.out.println("I'm sorry, but the username \"" + username + "\" is already associated\nwith an accoiunt. Please try again (or enter 'q' to return to\nthe main menu).");
			}
			else{
				System.out.println("Great, that username is not in use!");
				success = true;
			}
		}

	
	while(loop){
		System.out.print("Password: ");
		password = scan.nextLine();
		
		if (password.equals("q")){
			System.out.println("I'm sorry, but you cannot have the single chacter 'q' as your passowrd");
		}
		else{
			loop = false;
		}
	}
	
	//make the user
	BankUser newUser = new BankUser(username, password, 0, 0);

	//deposit checking and savings
	newUser.depositSubroutine(scan, true, true);
	newUser.depositSubroutine(scan, false, true);

	//add the user
	accounts.addUser(newUser);
	
	}

	private static void login(Scanner scan){
		//Variables
		String username = "";
		String password = "";
		boolean success = false;

		while (!success){
			System.out.print("\nUsername: ");
			username = scan.nextLine();

			if (username.equals("q")){
				return;
			}

			System.out.print("Password: ");
			password = scan.nextLine();

			if (password.equals("q")){
				return;
			}

			//Test if user exists
			success = accounts.loginSuccessful(username, password);

			if (!success){
				System.out.println("I'm sorry, but that username and pssword does not match any\nat our bank. Please try again (or enter 'q' to return to the\nmain menu");
			}
		}

		//login successful. Get the user
		BankUser currentUser = accounts.getUser(username);

		currentUser.accountMenu(scan);
		return;
		
	}
	
	private static void bankMenu(){
		//Make a scanner
		Scanner scan = new Scanner(System.in);

		//Variables
		String choice;
		boolean loop = true;

		while(loop){
			System.out.println("\nWelcome to SherBank!");
			System.out.println("     1) Existing Account Holder");
			System.out.println("     2) Open a New Account");
			System.out.println("     3) Quit");			
			System.out.print("What would you like to do? ");

			choice = scan.nextLine();

			if (choice.equals("1")){
				login(scan);
			}
			else if (choice.equals("2")){
				createAccount(scan);
			}
			else if (choice.equals("3")){
				scan.close();
				loop = false;
			}
			else{
				System.out.println("Sorry, \"" + choice + "\" is not a valid input");
				System.out.print("Please enter any key to continue: ");
				scan.nextLine();
				System.out.println("");
			}
		}

		
	}
	
	public static void main(String [] args){
		//initialize accounts
		accounts = new UserStorage();
		
		//read the initial file
		readFile();
		
		bankMenu();
		
		
		
		//write out the file information
		writeFile();
		
	}
}
