package tsher_CSCI201_Assignment2;

import java.util.Scanner;

public class BankUser {
	//Variables
		private String password;
		private String username;
		private BaseAccount checkings;
		private BaseAccount savings;

		public BankUser(String username, String password, double initialAmount_checking, double initialAmount_savings){
			//Make the savings and checking account
			this.checkings 	= new CheckingAccount(initialAmount_checking);

			//Account type is determined by the sum of both accounts
			double total = initialAmount_savings + initialAmount_checking;

			if (total < 1000){
				this.savings = new BasicSavings(initialAmount_savings, this.checkings);
			}
			else if (total < 10000){
				this.savings = new PremiumSavings(initialAmount_savings, this.checkings);
			}
			else{
				this.savings = new DeluxeSavings(initialAmount_savings, this.checkings);
			}

			//initialize info
			this.username = username;
			this.password = password;

		}

		//Setters and getters
		public void setPassword(String password){
			this.password = password;
		}
		public void getUsername(String username){
			this.username = username;
		}
		public String getPassword(){
			return this.password;
		}
		public String getUsername(){
			return this.username;
		}
		public double getCheckingsAmount(){
			return this.checkings.getBalance();
		}
		public double getSavingsAmount(){
			return this.savings.getBalance();
		}
		
		
		private void chooseAccount(Scanner scan, boolean isDeposit){
			System.out.println("Here are the accounts you have:");
			System.out.println("     1) Checking");
			System.out.println("     2) " + this.savings.getAccountType());

			boolean loop = true;
			String choice = "";
			
			while(loop)
			{
				if (isDeposit){
					System.out.print("Into which account would you like to make a deposit? ");
				}
				else{
					System.out.print("Into which account would you like to make a withdrawal? ");				
				}
				choice = scan.nextLine();
				if (choice.equals("1") || choice.equals("2")){
					loop = false;
				}
				else{
					System.out.println("\"" + choice + "\" is not a valid input");
				}
			}

			//we have a valid input
			if (choice.equals("1")){
				if (isDeposit){
					this.depositSubroutine(scan, false, false);
				}
				else{
					this.withdrawSubroutine(scan, false);
				}
			}
			else if (choice.equals("2")){
				if (isDeposit){
					this.depositSubroutine(scan, true, false);
				}
				else{
					this.withdrawSubroutine(scan, true);
				}		
			}
			else{
				System.out.println("Umm Stephen you did something wrong...");
			}

		}

		public void accountMenu(Scanner scan){
			//Make a scanner
			// Scanner scan = new Scanner(System.in);

			//Variables
			String choice;

			while(true){
				System.out.println("     1) View Account Information");
				System.out.println("     2) Make a Deposit");
				System.out.println("     3) Make a Withdrawal");
				System.out.println("     4) Determine Balance in x Years");
				System.out.println("     5) Logout");
				System.out.print("What would you like to do? ");

				choice = scan.nextLine();

				if (choice.equals("1")){
					this.printInfo();
				}
				else if (choice.equals("2")){
					this.chooseAccount(scan, true);
				}
				else if (choice.equals("3")){
					this.chooseAccount(scan, false);
				}
				else if (choice.equals("4")){
					this.projectBalance(scan);
				}
				else if (choice.equals("5")){
					System.out.println("Thank you for coming into the bank!");
					return;
				}
				else{
					System.out.println("Sorry, \"" + choice + "\" is not a valid input");
					System.out.print("Please enter any key to continue: ");
					scan.nextLine();
					System.out.println("");
				}
			}
		}

		//Checks if current balance allows a upgrade or downgrade
		private void refreshSavings(){
			//Get total in both accounts to determine
			double total = this.savings.getBalance() + this.checkings.getBalance();
			//check for different balances
			if (total < 1000){
				this.savings = new BasicSavings(this.savings.getBalance(), this.checkings);
			}
			else if (total < 10000){
				this.savings = new PremiumSavings(this.savings.getBalance(), this.checkings);
			}
			else{
				this.savings = new DeluxeSavings(this.savings.getBalance(), this.checkings);
			}
		}


		private void projectBalance(Scanner scan){
			//Variables
			int years = 0;
			boolean loop = true;


			while (loop){
				System.out.print("In how many years? ");
				if (!scan.hasNextInt()){
					String dump = scan.nextLine();
					if (dump.equals("")){
						//do nothing since it's empty
					}
					else{
						System.out.println("\"" + dump + "\" is not a valid number of years");
					}
				}
				else{
					years = scan.nextInt();
					scan.nextLine();
					loop = false;
				}

				if (!loop){
					//now test if negative
					if (years < 0){
						System.out.println("You are not allowed to look at a negative year projection");
						loop = true;
					}
					else{
						loop = false;
					}
				}
			}
			//We also need to format the number of decimal places
			
			//Now that we have the number of years, let's start projecting
			//Print titles
			System.out.println("Your " + this.savings.getAccountType() + " will have the following:");
			System.out.println("Year            Amount            Interest");
			System.out.println("----            ------            --------");

			//A loop to print out each iteration
			//Last line is different since no interest, thus only 1 less than number of years
			for (int i = 0; i < (years-1); ++i){
				//For formatting, we want to know how many digits are in years
				int yearDigits = (String.valueOf(i)).length();
				int amountDigits = (String.valueOf((String.format("%.2f",this.savings.getBalanceAfterNumYears(i))))).length();

				//Now we can find out how many white spaces to put between year and amount
				//Don't ask, it's all formatting
				String whiteSpaces  = String.format("%" + (16-yearDigits) + "s","");
				String whiteSpacesB = String.format("%" + (18-amountDigits) + "s", "");
				System.out.println(i + whiteSpaces + (String.format("%.2f",this.savings.getBalanceAfterNumYears(i))) + whiteSpacesB + (String.format("%.2f",(this.savings.getBalanceAfterNumYears(i+1) - this.savings.getBalanceAfterNumYears(i)))));
			}
			int yearDigits = (String.valueOf(years)).length();
			String whiteSpaces = String.format("%" + (16-yearDigits) + "s","");
			System.out.println(years + whiteSpaces + (String.format("%.2f",this.savings.getBalanceAfterNumYears(years))));
		}

		private void printInfo(){
			System.out.println("\nYou have a " + this.checkings.getAccountType() + " with a balance of $" + String.format("%.2f",this.checkings.getBalance()) + ".");
			System.out.println("You have a " + this.savings.getAccountType() + " with a balance of $" + String.format("%.2f",this.savings.getBalance()) + ".\n");
		}

		//public since needs to be accessed when creating a new user
		public void depositSubroutine(Scanner scan, boolean isSavings, boolean isNewSubroutine){
			//Variables	
			boolean valid = false;
			double	depositAmount 	= 0;
			String accountType;
			String prompt;

			if (isSavings){		accountType = this.savings.getAccountType();	}
			else{				accountType = this.checkings.getAccountType();	}

			//Determine what the prompt is
			if (isNewSubroutine){
				if (isSavings){
					prompt = "How much would you like to deposit into savings? ";
				}
				else{
					prompt = "How much would you like to deposit into checking? ";
				}
			}
			else{
				prompt = ("How much to deposit in your " + accountType + "? ");
			}

			while (true){		
				while (true){
					System.out.print(prompt);
					if (!scan.hasNextDouble()){
						String dump = scan.nextLine();
						if (dump.equals("")){
							//do nothing since it's empty
						}
						else{
							System.out.println("\"" + dump + "\" is not a valid amount.");
						}
						//scan.next();
					}
					else{
						depositAmount = scan.nextDouble();
						scan.nextLine();
						break;
					}
				}
			
				//See savings or checkings to deposit
				if (isSavings){		valid = this.savings.deposit(depositAmount);	}
				else{				valid = this.checkings.deposit(depositAmount);	}

				//valid checks if depositAmount is valid (negative or not)
				if (!valid){
					System.out.println("You are not allowed to deposit a negative amount.");
				}
				else{
					if (!isNewSubroutine){
						System.out.println("$" + depositAmount + " deposited into your " + accountType + ".");
					}
					break;
				}
			}
			//Check if upgrade or downgrade
			this.refreshSavings();
		}

		private void withdrawSubroutine(Scanner scan, boolean isSavings){
			//Variables
			boolean valid = false;
			double	withdrawAmount 	= 0;
			String accountType;

			
			if (isSavings){		accountType = this.savings.getAccountType();	}
			else{				accountType = this.checkings.getAccountType();	}
			
			while (true){		
				while (true){
					System.out.print("How much to withdraw? ");
					if (!scan.hasNextDouble()){
						String dump = scan.nextLine();
						if (dump.equals("")){
							//do nothing since it's empty
						}
						else{
							System.out.println("\"" + dump + "\" is not a valid amount.");
						}
						//scan.next();
					}
					else{
						withdrawAmount = scan.nextDouble();
						scan.nextLine();
						break;
					}
				}

				//Now we have the amount, see if there's enough in the account to withdraw
				if (isSavings){
					if (withdrawAmount > this.savings.getBalance())
						valid = false;
					else
						valid = true;
				}
				else{
					if (withdrawAmount > this.checkings.getBalance())
						valid = false;
					else
						valid = true;
				}
				
				//not enough money
				if (!valid){
					System.out.println("You do not have $" + withdrawAmount + " in your " + accountType + ".");
				}

				else{
					//See savings or checkings to withdraw
					if (isSavings){		valid = this.savings.withdraw(withdrawAmount);	}
					else{				valid = this.checkings.withdraw(withdrawAmount);	}

					//valid checks if withdrawAmount is valid (negative or not)
					if (!valid){
						System.out.println("You are not allowed to withdraw a negative amount.");
					}
					else{
						System.out.println("$" + withdrawAmount + " withdrawn from your " + accountType + ".");
						break;
					}
				}
			}
			//Check if upgrade or downgrade
			this.refreshSavings();
		}

	
	
	public static void main(String [] args){
		System.out.println("--- Program Start ---");

		BankUser testUser = new BankUser("tsher", "asdfjkl;", 80000.01, 80000.01);
		// testUser.depositSubroutine(true);
		Scanner scan = new Scanner(System.in);
		testUser.accountMenu(scan);

	}
}

//User class to store stuff
class User{
	
}