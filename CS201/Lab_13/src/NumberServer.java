import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Connection implements Runnable{
	NumberServer server;
	
//	ArrayList<Integer> array;
	List<Integer> array;
	
//	public Connection(NumberServer server, ArrayList<Integer> array){
	public Connection(NumberServer server, List<Integer> array){
		this.server = server;
		this.array = array;
	}
	@Override
	public void run() {
		
		while(true){
			if (server.connectionPermits.availablePermits() > 0){
					int number = server.getNumber();
					System.out.println("Number server gave: " + number);
					array.add(number);
					server.count++;

					break;
			} else{
				try {
					server.commonLock.lock();
					server.cond.await();
					server.commonLock.unlock();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
		
		
	}
	
}

public class NumberServer 
{

	public Semaphore connectionPermits = new Semaphore(NumberServer.numPermits);
	Random rand = new Random(System.currentTimeMillis());
	boolean isAllowed = true;
	int counter = 0;
	
	public Lock commonLock = new ReentrantLock();
	public Condition cond = commonLock.newCondition();
	
	
	public NumberServer()
	{
		
	}
	
	public void ban()
	{
		isAllowed = false;
		
	}

	public boolean isAllowed() 
	{
		return isAllowed;
	}
	
	
	public Integer getNumber()
	{
		try 
		{
			//If you have not been banned, and there is currently a permit available
			if(isAllowed() && connectionPermits.tryAcquire())
			{
				//get the next number
				int val = counter++;
				// wait .1 - 1 second
				Thread.sleep(rand.nextInt(10) * 100);
				//release the permit
				connectionPermits.release();
				commonLock.lock();
				cond.signal();
				commonLock.unlock();
				//return the number
				return val;
			}
			else
			{
				System.out.println("You're banned, stop making requests");
			}
			
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	
		
		return null;
		
		
	}
	
	public Lock lock = new ReentrantLock();
	public Condition finish = lock.newCondition();
	
	public static final int numPermits = 50;
	
	public static int count = 0;
	
	public static void main (String[] args){
		NumberServer server = new NumberServer();
		
		
		
		ArrayList<Integer> array = new ArrayList<Integer>();
		
		List<Integer> arr = Collections.synchronizedList(array);
//		Vector<Integer> arr = new Vector<Integer>();
		
		
		ExecutorService executor = Executors.newFixedThreadPool(NumberServer.numPermits*2);
		for (int i = 0; i < NumberServer.numPermits*2; ++i){
			executor.execute(new Connection(server, arr));
		}
		executor.shutdown();
		
		while(true){
			if (executor.isTerminated()){
				System.out.println("Size: " + arr.size());
				break;
			}
		}
		
	}
	
	
}