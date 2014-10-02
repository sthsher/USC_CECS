import java.util.Scanner;

public class Lab_2 {
	public static void main(String [] args){
		
		//Variables
		int arraySize;
		int searchNum;
		Scanner scan = new Scanner(System.in);

		System.out.println("Welcome to CSCI 201 Lab 2!");
		System.out.print("Please enter the size of the array: ");
		arraySize = scan.nextInt();

		sortedArray testArray = new sortedArray(arraySize);

		testArray.print();

		
		System.out.println("--- BRUTE FORCE METHOD ---");

		while (true){

			System.out.print("Search for number: ");
			searchNum = scan.nextInt();

			if (searchNum == -1){
				break;
			}

			int result = testArray.bruteForce(searchNum);

			if (result != -1){
				System.out.println("The number you want to find is at index " + result);
			}
			else{
				System.out.println("The number you want to find does not exist in the array");
			}
		}

		System.out.println("--- BINARY SEARCH METHOD ---");

		while (true){
			System.out.print("Search for number: ");
			searchNum = scan.nextInt();

			if (searchNum == -1){
				break;
			}

			int result = testArray.binarySearch(searchNum);
			if (result != -1){
				System.out.println("The number you want to find is at index " + result);
			}
			else{
				System.out.println("The number you want to find does not exist in the array");
			}


		}

		// while (true){
			
		// }

		
		scan.close();
		
	}
}






class sortedArray{
	private int[] arr;
	private int size;
	
	public sortedArray(int n){
		//Make the array
		this.arr = new int[n];
		this.size = n;

		//Populate the array
		for (int i = 0; i < n; ++i){
			this.arr[i] = i;
		}
	}

	public int bruteForce(int x){
		int numOfTrials = 1;

		for (int i = 0; i < this.size; ++i){
			if (this.arr[i] == x){
				System.out.println("Took " + numOfTrials + " trials to find the number");
				return i;
			}
			++numOfTrials;
		}

		//not in array, return -1
		return -1;
	}

	public int binarySearch(int x){
		int left = 0;
		int right = this.size;
		int middleIndex = (left + right) / 2;
		int numOfTrials = 0;
		while (true)
		{
			//test for base case
			if (left == right){
				break;
			}

			if (this.arr[middleIndex] == x){
				System.out.println("Took " + numOfTrials + " trials to find the number");
				return middleIndex;
			}
			//left side
			else if (this.arr[middleIndex] > x){
				//repeat the same process
				left = left;
				right = middleIndex;
				middleIndex = (left + right) / 2;
			}
			//right side
			else{
				left = middleIndex;
				right = right;
				middleIndex = (left + right) / 2;		
			}
			++numOfTrials;
		}

		return -1;


	}

	public void print(){
		for (int i = 0; i < this.size; ++i)
		{
			System.out.print(arr[i] + " ");
		}
		System.out.println("");
	}
	
}