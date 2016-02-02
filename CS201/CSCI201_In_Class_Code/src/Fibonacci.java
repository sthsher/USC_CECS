import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;


public class Fibonacci extends RecursiveTask<Integer> {
	private int n;
	public Fibonacci (int n){
		this.n = n;
	}
	public Integer compute(){
		if (n == 0 || n == 1){
			return n;
		}
		Fibonacci f1 = new Fibonacci (n-1);
		Fibonacci f2 = new Fibonacci (n-2);
		f1.fork();
		f2.fork();
		return f2.join() + f1.join();
		
	}
	
	public static void main(String [] args){
		int index = 30;
		
		long without;
		long with;
		
		long beforeTime = System.nanoTime();
		Fibonacci fib = new Fibonacci(index);
		fib.compute();
		long afterTime = System.nanoTime();

		without = (afterTime - beforeTime);
		
		ForkJoinPool pool = new ForkJoinPool(8);
		
		beforeTime = System.nanoTime();
		pool.invoke(new Fibonacci(index));
		afterTime = System.nanoTime();
		
		with = (afterTime - beforeTime);
		
		
		System.out.println("Without = " + without);
		System.out.println("With    = " + with);

	}
}
