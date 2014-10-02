package tsher_CSCI201_Assignment2;

public abstract class BaseAccount{
	//Variables
	private double balance;

	//Methods
	public BaseAccount(double balance){
		setBalance(balance);
	}
	public double getBalance(){
		return this.balance;
	}
	public void setBalance(double balance){
		this.balance = balance;
	}
	public boolean withdraw(double amount){
		//First check if there's enough to withdraw and if it's valid or not
		if (amount > this.balance || amount < 0){
			return false;
		}
		else{
			//withdraw the money
			this.balance -= amount;
			return true;
		}

	}
	public boolean deposit (double amount){
		//First check if it's a valid amount
		if (amount < 0){
			return false;
		}
		else{
			this.balance += amount;
			return true;
		}
	}

	//Inheritance
	protected abstract double getBalanceAfterNumYears(int numYears);
	public abstract String getAccountType();

	public static void main(String [] args){
		//make an account
		//This is for unit testing
		BaseAccount omega = new CheckingAccount(500);
		System.out.println(omega.getAccountType());
		System.out.println(omega.getBalance());
		System.out.println("Balance after 10 years: " + omega.getBalanceAfterNumYears(10));
		System.out.println("");

		BaseAccount testAccount = new BasicSavings(600, omega);
		System.out.println(testAccount.getAccountType());
		System.out.println(testAccount.getBalance());
		System.out.println("Balance after 10 years: " + testAccount.getBalanceAfterNumYears(10));
		System.out.println("");

		// BaseAccount alpha = new PremiumSavings(2000, omega);
		// System.out.println(alpha.getAccountType());
		// System.out.println(alpha.getBalance());
		// System.out.println("Balance after 10 years: " + alpha.getBalanceAfterNumYears(10));
		// System.out.println("");

		// BaseAccount beta = new DeluxeSavings(20000, omega);
		// System.out.println(beta.getAccountType());
		// System.out.println(beta.getBalance());
		// System.out.println("Balance after 10 years: " + beta.getBalanceAfterNumYears(10));
		// System.out.println("");



	}
}

class CheckingAccount extends BaseAccount{
	public CheckingAccount(double balance){
		super(balance);
	}
	protected double getBalanceAfterNumYears(int numYears){
		return getBalance();
	}
	public String getAccountType(){
		return "Checking Account";
	}
}

abstract class SavingsAccount extends BaseAccount{
	private double basicRate = 1.001;
	private double premiumRate = 1.01;
	private double deluxeRate = 1.05;
	//private double total;
	private BaseAccount checkings;
	public SavingsAccount(double balance, BaseAccount checkings){
		super(balance);
		this.checkings = checkings;
	}

	//Implements at this level because interest rates might change as years pass
	protected double getBalanceAfterNumYears(int numYears){
		double rate;
		double total = this.getBalance() + this.checkings.getBalance();
		double tempBalance = this.getBalance();

		for (int i = 0; i < numYears; ++i){
			//determine which rate it is
			if (total < 1000){
				rate = this.basicRate;
			}
			else if (total < 10000){
				rate = this.premiumRate;
			}
			else{
				rate = this.deluxeRate;
			}

			//now we know the rate, let's get the end result of this iteration
			tempBalance *= rate;
		}

		return tempBalance;

	}
	public abstract String getAccountType();
}

class BasicSavings extends SavingsAccount{
	// private double rate = 1.001;
	public BasicSavings(double balance, BaseAccount checkings){
		super (balance, checkings);
	}
	// protected double getBalanceAfterNumYears(int numYears){
	// 	return (numYears)*(rate)*(getBalance());
	// }
	public String getAccountType(){
		return "Basic Savings Account";
	}
}

class PremiumSavings extends SavingsAccount{
	// private double rate = 1.01;
	public PremiumSavings(double balance, BaseAccount checkings){
		super (balance, checkings);
	}
	// protected double getBalanceAfterNumYears(int numYears){
	// 	return (numYears)*(rate)*(getBalance());
	// }
	public String getAccountType(){
		return "Premium Savings Account";
	}
}

class DeluxeSavings extends SavingsAccount{
	// private double rate = 1.05;
	public DeluxeSavings(double balance, BaseAccount checkings){
		super (balance, checkings);
	}
	// protected double getBalanceAfterNumYears(int numYears){
	// 	return (numYears)*(rate)*(getBalance());
	// }
	public String getAccountType(){
		return "Deluxe Savings Account";
	}
}