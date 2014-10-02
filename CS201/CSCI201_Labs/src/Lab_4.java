import java.util.Scanner;

import java.io.FileReader;
import java.io.BufferedReader;

import java.io.FileWriter;
import java.io.PrintWriter;

import java.io.FileNotFoundException;
import java.io.IOException;



public class Lab_4 {

	public static void print(char[] board){
		for (int i = 0; i < 9; ++i){
			System.out.print(board[i]);
			if (i == 2 || i == 5 || i == 8){
				System.out.println("");
			}
		}
	}
	
	public static char checkBoard(char[] board){
		//print(board);
		for (int i = 0; i < 3; ++i){
			if (board[3*i] == board[(3*i)+1] && board[i] == board[(3*i)+2]){
				if (board[3*1] != '_'){
					if(board[3*i] == 'x'){
						// System.out.println("Marker1, i = " + i);
						return 'a';
					}
					else{
						// System.out.println("Marker1, i = " + i);
						return 'b';
					}
				}
			}
		}
		
		for (int i = 0; i < 3; ++i){
			if (board[i] == board[i+3] && board[i] == board[6+i]){
				if (board[i] != '_'){
					if (board[i] == 'x'){
						// System.out.println("Marker2, i = " + i);
						return 'a';
					}
					else{
						// System.out.println("Marker2, i = " + i);
						return 'b';
					}
				}
			}
		}
		
		//check diagnoal
		if (board[0] == board[4] && board[0] == board[8]){
			if (board[0] != '_'){
				if (board[0] == 'x'){
					// System.out.println("Marker3");
					return 'a';
				}
				else{
					// System.out.println("Marker3");
					return 'b';
				}
			}
		}
		
		if (board[2] == board[4] && board[2] == board[6]){
			if (board[2] != '_'){
				if (board[2] == 'x'){
					// System.out.println("Marker4");
					return 'a';
				}
				else{
					// System.out.println("Marker4");
					return 'b';
				}
			}
		}
		
		return 'c';
	}
	
	public static void main(String [] args){
		Scanner scan = new Scanner(System.in);
		System.out.print("Enter file name: ");
		String inputName = scan.nextLine();
		
				
		
		try{
			FileReader fr = new FileReader(inputName);
			BufferedReader reader = new BufferedReader(fr);
			
			//now that the file is open, let's start
			char board[] = new char[9];
			for (int i = 0; i < 9; ++i){
				board[i] = '_';
			}
			
			//now read all the instructions and do stuff
			//read the next line
			String line;			
			int turn = 1;
			line = reader.readLine();
			
			boolean valid = true;
			boolean outOfBounds = false;
			
			while (line != null){
							
				//first character is the row
				int row = Character.getNumericValue((line.charAt(0)));
				int column = Character.getNumericValue((line.charAt(3)));
				
				//place is row*3 + column
				int position = (3*row) + column;
				
				if (row > 2 || column > 2){
					outOfBounds = true;
					line = null;
				}
				
//				System.out.println("Row     : " + row);
//				System.out.println("Column  : " + column);
//				System.out.println("Position: " + position);
				
				//only continue if not out of bounds
				if (!outOfBounds){
				
					//check a repeat
					if (board[position] != '_'){
						//already a position there, invalid
						valid = false;
						line = null;
					}
					
					
					if (valid){
						if (turn++ % 2 == 1){
							//first person's turn
							board[position] = 'x';
						}
						else{
							//second
							board[position] = 'o';
						}
						
						char result = checkBoard(board);
						
						if (result == 'a' || result == 'b'){
							//someone won, exit loop
							line = null;
						}
					}
					line = reader.readLine();
				}
				
//				print(board);
				
			}
			
//			try{
				//make printer
				FileWriter fw = new FileWriter("output.txt");
				PrintWriter printer = new PrintWriter(fw);
				
				//print source
				printer.println(inputName);
				
				//print board
				for (int i = 0; i < 9; ++i){
					printer.print(board[i]);
					if (i == 2 || i == 5 || i == 8){
						printer.println("");
					}
				}
				printer.flush();
				
				//now print winner or result
				char result = checkBoard(board);
				
				if (outOfBounds){
					printer.println("Out of Bounds");
				}
				else if (!valid){
					//there is a conflict
					printer.println("Repeated Move");
				}
				else if (result == 'a'){
					printer.println("Player One");
				}
				else if (result == 'b'){
					printer.println("Player Two");
				}
				else{
					//no winner
					printer.println("Neither");
				}
				
				printer.close();
//			}
//			catch(IOException IOE){
//				System.out.println(IOE.getMessage());
//			}


			
			
		}
		catch(FileNotFoundException fnfe){
			//Write to file
			try{
				FileWriter fw = new FileWriter("output.txt");
				PrintWriter printer = new PrintWriter(fw);
				printer.println("Input DNE");
				printer.flush();
				printer.close();
			}
			catch(IOException IOE){
				System.out.println(IOE.getMessage());
			}
			
		}
		catch(IOException IOE){
			System.out.println(IOE.getMessage());
		}
		
	}
	
	
	
}
