package tsher_CSCI201_Assignment2;

import java.util.ArrayList;

public class UserStorage {
	//storage method
	private ArrayList<BankUser> userArray;
	private int numOfUsers;
	
	public UserStorage(){
		this.userArray = new ArrayList<BankUser>();
		this.numOfUsers = 0;
	}
	
	public void addUser(BankUser newUser){
		this.userArray.add(newUser);
		++numOfUsers;
	}
	
	public boolean usernameAlreadyExist(String username){
		for (int i = 0; i < this.userArray.size(); ++i){
			if (this.userArray.get(i).getUsername().equals(username)){
				return true;
			}
		}
		return false;
	}
	
	public BankUser getUser(String username){
		for (int i = 0; i < this.userArray.size(); ++i){
			if (this.userArray.get(i).getUsername().equals(username)){
				return this.userArray.get(i);
			}
		}
		System.out.println("Stephen you messed up");
		return this.userArray.get(0);	
	}
	
	public BankUser getUserByIndex(int index){
		return this.userArray.get(index);
	}
	
	public boolean loginSuccessful(String username, String password){
		for (int i = 0; i < this.userArray.size(); ++i){
			if (this.userArray.get(i).getUsername().equals(username)){
				if (this.userArray.get(i).getPassword().equals(password)){
					return true;
				}
				else{
					return false;
				}
			}
		}
		
		return false;
	}
	
	public int getNumOfUsers(){
		return this.numOfUsers;
	}
	
	public static void main(String [] args){
		
		//make some users
		BankUser alpha 	= new BankUser("Riowena", "Seah", 300, 300);
		BankUser beta	= new BankUser("Stephen", "Sher", 300, 300);
		BankUser omega	= new BankUser("Colin", "Cammarano", 300, 300);
		
		UserStorage newStorage = new UserStorage();
		
		newStorage.addUser(alpha);
		newStorage.addUser(beta);
		newStorage.addUser(omega);
		
		System.out.println("Num: " + newStorage.getNumOfUsers());
		System.out.println("Stephen: " + newStorage.usernameAlreadyExist("Stephen"));
		System.out.println("asdf: " + newStorage.usernameAlreadyExist("asdf"));
		//BankUser theta = newStorage.getUser("Stephen");
		
		// theta.accountMenu();

			
	}
	
}
