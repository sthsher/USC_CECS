import java.util.Scanner;
import java.lang.Integer;
import java.lang.NumberFormatException;

public class zig_zag {

	//Print the grid
	//Status: Complete Aug 29
	private static void printGrid(char[][] grid, int rows, int columns){
		//print grid
		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < columns; ++j){
				System.out.print(grid[i][j] + " ");
			}
			System.out.println("");
		}
	}

	//Admin menu
	//Status: Complete Aug 29
	private static void adminMenu(char[][] grid, int rows, int columns, String message){
		//Print the grid first
		System.out.println("Here is the grid, just for you admin!");
		printGrid(grid, rows, columns);

		//Now print the steps
		System.out.println("Here is the step by step, just for you admin!");

		//Same as below
		int x = 0;
		int y = 0;
		boolean down = true;

		for (int i = 0; i < columns; ++i){
			//columns will always increment
			message += grid[x][y];
			
			//Print step by step
			System.out.print("R:" + x + " C:" + y + " L:"+ grid[x][y++] + "\n");
			
			//There's a special case: if rows = 1, it means that rows-1 is 0, which will make the if statement always true.
			//This will cause an out of bounds
			//If rows == 1, we don't move x, if it isn't 1, then it's fine
			
			if (rows > 1)
			{
				//Increment or decrement x
				if (down){
					++x;
				}
				else{
					--x;
				}
							
				//now determine if it's time to switch directions
				if (x > rows-1){
					down = false;
					x = x - 2;		//-2 or +2 to actually go up, one to get into bounds, and another one to not stay in same line
				}
				if (x < 0){
					down = true;
					x = x + 2;
				}
			}
			else	//rows == 1
			{
				//do nothing, x does not increment
			}
		}

	}

	//Checking method, used to check if valid letter set
	//Status: Complete Aug 29
	private static boolean checkLetters(String letters, int product){
		//should have x letters, and x-1 spaces, totaling 2x-1 in length
		int total = (product*2)-1;
		
		if (letters.length() != total){
			return false;
		}
		
		//should have spaces in odd indices
		for (int i = 1; i < total; i = i + 2){
			if (letters.charAt(i) != ' '){
				return false;
			}
		}
		return true;
	}

	//Input method, gets all the necessary inputs from the user
	//Status: Complete Aug 29
	private static void getInputs(zig_zag_inputs inputs){
		
		//Variables
		String adminInput;				//if only look at first character, then "Abcde" will be an invalid admin, String to avoid this situation
		boolean validLetters = false;	//for separate prompt if failed first time
		boolean validNumbers;
		boolean secondLoop;		//if there is an error input, the second loop has a different sequence
		String lineInput = "";

		//Make a scanner
		Scanner scan = new Scanner(System.in);
		
		//Heading
		System.out.println("Welcome to the Maze Game!");
		System.out.println("Are you an admin?");
		
		//Scan for answer: A is yes, otherwise no
		adminInput = scan.nextLine();
		
		//No need for else case since initialized as false
		if (adminInput.equals("A")){
			inputs.setIsAdmin(true);
		}

		System.out.println("How many rows are in the grid?");

		//reset bool
		secondLoop = false;
		validNumbers = true;

		while (true){
			//only do this if in first loop, for second and more loops the scanning will already have taken place
			if (!secondLoop){
				if (!scan.hasNextInt()){
					validNumbers = false;
				}
				else{
					validNumbers = true;
				}
				//Only check if validnumbers is true
				lineInput = scan.nextLine();
			}
			//loop through to see if there's any whitespaces. If there is, then something is wrong
			for (int i = 0; i < lineInput.length(); ++i){
				if (lineInput.charAt(i) == ' '){
					validNumbers = false;
					break;
				}
			}
			//valid or invalid case
			try{
				if (!validNumbers){
					System.out.println("Error: that is not a number. Please try again");
					secondLoop = true;
					//do second scan here
					if (!scan.hasNextInt()){
						validNumbers = false;
					}
					else{
						validNumbers = true;
					}
					lineInput = scan.nextLine();
				}
				else{
					inputs.setRows(Integer.parseInt(lineInput));
					break;
				}
			}
			//take into account pressing enter multiple times without entering anything ("" case)
			catch(NumberFormatException except){
				//reset booleans
				validNumbers = true;
				secondLoop = false;
			}
		}


		//Do the same thing with columns
		System.out.println("How many columns are in the grid?");
		
		//reset bool
		secondLoop = false;
		validNumbers = true;

		while (true){
			//only do this if in first loop, for second and more loops the scanning will already have taken place
			if (!secondLoop){
				if (!scan.hasNextInt()){
					validNumbers = false;
				}
				else{
					validNumbers = true;
				}
				//Only check if validnumbers is true
				lineInput = scan.nextLine();
			}
			//loop through to see if there's any whitespaces. If there is, then something is wrong
			for (int i = 0; i < lineInput.length(); ++i){
				if (lineInput.charAt(i) == ' '){
					validNumbers = false;
					break;
				}
			}
			//valid or invalid case
			try{
				if (!validNumbers){
					System.out.println("Error: that is not a number. Please try again");
					secondLoop = true;
					//do second scan here
					if (!scan.hasNextInt()){
						validNumbers = false;
					}
					else{
						validNumbers = true;
					}
					lineInput = scan.nextLine();
				}
				else{
					inputs.setColumns(Integer.parseInt(lineInput));
					break;
				}
			}
			//take into account pressing enter multiple times without entering anything ("" case)
			catch(NumberFormatException except){
				//reset booleans
				validNumbers = true;
				secondLoop = false;
			}
		}

		//Now we need to get the letters		
		System.out.println("Enter " + (inputs.getRows() * inputs.getColumns()) + " letters separated by spaces");
		String lettersInput = scan.nextLine();
		
		//HARDCODED FOR TESTING
//		inputs.setRows(3);
//		inputs.setColumns(9);
//		lettersInput = "F b c d M f g h ! y I o D v E e ! v v a N o i m ! v i";
		
		//check if valid
		validLetters = checkLetters(lettersInput, (inputs.getRows()*inputs.getColumns()));
		
		
		//Need a loop in case they don't follow the rules
		while(!validLetters){		
			System.out.println("Error: Ths is not " + (inputs.getRows() * inputs.getColumns()) + " letters. Try again!");
			//Keep scanning
			lettersInput = scan.nextLine();
			validLetters = checkLetters(lettersInput, (inputs.getRows()*inputs.getColumns()));
		}

		//At this point they have a valid set of letters, and all inputs are given.
		//Set it into the class
		inputs.setLetters(lettersInput);
		scan.close();
		return;
	}
	
	//Main method
	public static void main(String [] args){

		//Make a new input class
		zig_zag_inputs inputs = new zig_zag_inputs();
		
		//Get the inputs
		getInputs(inputs);
		
		//For simplicity, export inputs class data into local variables
		int rows = inputs.getRows();
		int columns = inputs.getColumns();
		String letters = inputs.getLetters();
		boolean isAdmin = inputs.getIsAdmin();
		
		//Now make a grid of desired size
		char grid[][] = new char[rows][columns];

		//Let's fill the grid
		int letterCounter = 0;
		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < columns; ++j){
				grid[i][j] = letters.charAt(letterCounter);	
				letterCounter += 2;
			}
		}

		//Let's figure out the secret message first, and just pass it into the menus
		//Length of message is number of columns
		String message = "";

		//start off at top left hand corner
		int x = 0;
		int y = 0;
		boolean down = true;	//determins zigzag

		for (int i = 0; i < columns; ++i){
			//columns will always increment
			message += grid[x][y++];
			
			//There's a special case: if rows = 1, it means that rows-1 is 0, which will make the if statement always true.
			//This will cause an out of bounds
			//If rows == 1, we don't move x, if it isn't 1, then it's fine
			
			if (rows > 1)
			{
			
				//Increment or decrement x
				if (down){
					++x;
				}
				else{
					--x;
				}
							
				//now determine if it's time to switch directions
				if (x > rows-1){
					down = false;
					x = x - 2;		//-2 or +2 to actually go up, one to get into bounds, and another one to not stay in same line
				}
				if (x < 0){
					down = true;
					x = x + 2;
				}
			}
			else	//rows == 1
			{
				//do nothing, x does not increment
			}
		}

		//Grid is finished! Now to do output stuff.
		if (isAdmin){
			adminMenu(grid, rows, columns, message);
		}

		//Print result
		System.out.println("Result: " + message);


		System.out.println("\n--- Program End ---\n");

	}
	
}

class zig_zag_inputs{
	private boolean isAdmin;
	private int rows;
	private int columns;
	private String letters;
	
	zig_zag_inputs(){
		//Initialize size of array as 27
		letters = "";
		isAdmin = false;
		rows = 0;
		columns = 0;
	}
	
	public void setIsAdmin(boolean b){
		this.isAdmin = b;
	}
	public boolean getIsAdmin(){
		return this.isAdmin;
	}
	public void setRows(int r){
		this.rows = r;
	}
	public int getRows(){
		return this.rows;
	}
	public void setColumns(int c){
		this.columns = c;
	}
	public int getColumns(){
		return this.columns;
	}
	public void setLetters(String s){
		this.letters = s;
	}
	public String getLetters(){
		return this.letters;
	}
}