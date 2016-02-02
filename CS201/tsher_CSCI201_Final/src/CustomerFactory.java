import java.util.Vector;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class CustomerFactory extends Thread {

	private Vector<CustomerThread> customerThreadVector = new Vector<CustomerThread>();
	private Hostess hostessThread;
	
	public CustomerFactory(Hostess hostessThread) {
		this.hostessThread = hostessThread;;
		this.start();
	}
	
	
	//Keeps generating new customers
	public void run() {
		try {
			int customerNumber = 0;
			while (true) {
				
				//creates new customer thread
				CustomerThread ct = new CustomerThread(customerNumber++, hostessThread);
				customerThreadVector.add(ct);
				Thread.sleep(1000 * (int)(Math.random() * 5)); // customers come in between 0 and 5 seconds apart
			}
		} catch (InterruptedException ie) {
			System.out.println("CustomerFactory.run(): InterruptedException: " + ie.getMessage());
			for (CustomerThread ct : customerThreadVector) {
				ct.interrupt();
			}
		}
	}
}

class CustomerThread extends Thread {
	private int customerNumber;
	private Hostess hostessThread;
	private Table table;
	
	private ReentrantLock lock = new ReentrantLock();
	private Condition waitingForFood = lock.newCondition();
	
	private int orderNumber;
	
	//customer triggers start of each customer cycle
	public CustomerThread(int customerNumber, Hostess hostessThread) {
		this.customerNumber = customerNumber;
		this.hostessThread = hostessThread;
		this.start();
	}
	
	public int getCustomerNumber() {
		return this.customerNumber;
	}
	
	public Table getTable() {
		return this.table;
	}
	
	public ReentrantLock getLock(){
		return lock;
	}
	
	public Condition getCondition(){
		return waitingForFood;
	}
	
	//Sleeps for a set amount, simulates eating
	public void run() {
		try {
			table = hostessThread.seatCustomer(this);
			
			//make an order
			orderNumber = (int)(Math.random() * 3);
			
			table.getWaiterThread().takeOrder(orderNumber, table);
			
			//customer needs to wait for waiter to deliver food to them
			lock.lock();
			waitingForFood.await();
			lock.unlock();
			
			Restaurant.addMessage("Customer " + customerNumber + " has received order " + Restaurant.foodNames[orderNumber] + " at table " + table.getTableNumber());
			
			
			Thread.sleep(1000 * (int)(Math.random() * 10)); // sleep for between 0 and 10 seconds
			if(hostessThread != null){
				hostessThread.customerLeaving(this);
			}
		} catch (InterruptedException ie) {
			System.out.println("CustomerThread.run(): InterruptedException: " + ie.getMessage());
		} catch (NullPointerException NPE){
			System.out.println("CustomerThread.run(): NullPointerException: " + NPE.getMessage());
		}
	}
}