package GenericSorting;

import java.util.ArrayList;
import java.util.Scanner;

public class GenericSorting<T extends Number> {
	private ArrayList<T> arr;

	public GenericSorting(T arr[]){
		for (int i = 0; i < 10; ++i){
			System.out.print(arr[i] + " ");
		}
		System.out.println("");
	}

	public static void main(String [] args){
		Scanner scan = new Scanner(System.in);
		
		System.out.println("(i) Integer");
		System.out.println("(f) Float");
		System.out.println("(d) Double");
		System.out.println("What type of array would you like to sort?");

		String choice = scan.nextLine();

		if(choice.equalsIgnoreCase("i")){
			Integer arr[] = new Integer[10];
			for (int i = 0; i < 10; ++i){
				arr[i] = (int)(Math.random() * 10);
			}
			GenericSorting<Integer> gs = new GenericSorting<Integer>(arr);
		}
		if(choice.equalsIgnoreCase("f")){
			Float arr[] = new Float[10];
			for (int i = 0; i < 10; ++i){
				arr[i] = (float)(Math.random() * 10);
			}
			GenericSorting<Float> gs = new GenericSorting<Float>(arr);
		}
		if(choice.equalsIgnoreCase("d")){
			Double arr[] = new Double[10];
			for (int i = 0; i < 10; ++i){
				arr[i] = (double)(Math.random() * 10);
			}
			GenericSorting<Double> gs = new GenericSorting<Double>(arr);
		}



	}
	
}
