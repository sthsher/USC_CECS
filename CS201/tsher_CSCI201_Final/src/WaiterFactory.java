import java.util.Vector;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaiterFactory {

	private Vector<WaiterThread> waiterThreadVector = new Vector<WaiterThread>();
	private int numWaiters;
	private int numTablesPerWaiter;
	private Hostess hostess;
	private Lock lock = new ReentrantLock();
	private Condition waiterAvailable = lock.newCondition();

	public WaiterFactory(Hostess hostess, int numWaiters, int numTablesPerWaiter) {
		this.hostess = hostess;
		this.numWaiters = numWaiters;
		this.numTablesPerWaiter = numTablesPerWaiter;
		
		//Vector of waiters to use
		for (int i=0; i < numWaiters; i++) {
			waiterThreadVector.add(new WaiterThread(hostess, i, this, numTablesPerWaiter));
		}
	}

	public void returnWaiter(WaiterThread wt) {
		lock.lock();
		wt.returnTable(wt.getTable(0));
		//waiterThreadVector.set(wt.getWaiterNumber(), new WaiterThread(wt.getHostess(), wt.getWaiterNumber(), this));
		waiterAvailable.signal();
		lock.unlock();

	}

	public WaiterThread getWaiter() {
		WaiterThread wt = null;
		try {
			lock.lock();
			while (wt == null) {
				int i;
				for (i=0; i < waiterThreadVector.size(); i++) {
					wt = waiterThreadVector.get(i);
					if (wt != null) {
						// this will only allow one table per waiter
						// use a semaphore to allow more than one table per waiter
						if (wt.getNumAvailableTables() > 0) {
//						if (wt.getTable() == null) {
							break;
						}
					}
				}
				if (i == waiterThreadVector.size()) {
					// if i get here, i haven't secured a waiter yet
					wt = null;
					waiterAvailable.await();
				}
			}
		} catch(InterruptedException ie) {
			System.out.println("WaiterFactory.getWaiter(): IE : " + ie.getMessage());
		} finally {
			lock.unlock();
		}
		return wt;
	}

}

class WaiterThread extends Thread {
	private Hostess hostess;
//	private Table table;
	private Vector<Table> tables;
	private int waiterNumber;
	private WaiterFactory waiterFactory;
	private Semaphore numTablesSemaphore;
	private Lock waiterLock = new ReentrantLock();
	private Condition tableAssignedCondition = waiterLock.newCondition();
	
	private Vector<Order> orderVector = new Vector<Order>();
	

	public WaiterThread(Hostess hostess, int waiterNumber, WaiterFactory waiterFactory, int numTablesPerWaiter) {
		this.hostess = hostess;
		this.waiterNumber = waiterNumber;
		this.waiterFactory = waiterFactory;
		this.numTablesSemaphore = new Semaphore(numTablesPerWaiter);
		tables = new Vector<Table>(numTablesPerWaiter);
		this.start();
		
		Thread food = new FoodThread();
		food.start();
		
	}

	public int getNumAvailableTables() {
		int numPermitsAvailable = numTablesSemaphore.availablePermits();
		return numPermitsAvailable;
	}
	public Hostess getHostess() {
		return this.hostess;
	}

	public void returnTable(Table table) {
//		this.table = null;
		tables.remove(table);
		numTablesSemaphore.release();
	}

	public void setTable(Table table) {
		try {
			numTablesSemaphore.acquire();
//			this.table = table;
			tables.add(table);
			this.waiterLock.lock();
			this.tableAssignedCondition.signalAll();
			this.waiterLock.unlock();
		} catch (InterruptedException ie) {
			System.out.println("WaiterFactory.setTable(" + table.getTableNumber() + ") IE: " + ie.getMessage());
		}
	}

	public Table getTable(int i) {
		if (tables.size() > i) {
			return tables.elementAt(i);			
		}
		return null;
//		return this.table;
	}

	public int getWaiterNumber() {
		return this.waiterNumber;
	}
	
	
	public void takeOrder(int orderNum, Table table){
		Restaurant.addMessage("Waiter " + waiterNumber + " has taken an order for " + Restaurant.foodNames[orderNum] + " from table " + table.getTableNumber());
		Order newOrder = new Order(orderNum, table.getCustomer().getCustomerNumber(), table, this);
		orderVector.add(newOrder);

		Restaurant.cookFactory.newOrder(newOrder);
	}

	public void deliverOrder(Order order){
		
	}
	
	

	public void run() {
		try {
			while (true) {
				// waiter can only have one table currently
				// wait until notified, meaning that a table has been seated
				// i don't think i always want to do this - what if a table has already been set?
				this.waiterLock.lock();
				this.tableAssignedCondition.await();
				this.waiterLock.unlock();
				Thread.sleep(1000 * (int)(Math.random() * 10)); // sleep for between 0 and 10 seconds
				if (getTable(0) != null) {
					getTable(0).getLock().lock();
					// signal the customer who is "eating"
					getTable(0).getReadyCondition().signal();
					getTable(0).getLock().unlock();
				}
				//waiterFactory.returnWaiter(this);
			}
		} catch (InterruptedException ie) {
			System.out.println("CustomerThread.run(): InterruptedException: " + ie.getMessage());
		}
	}
	
	public Vector<Order> getVector(){
		return orderVector;
	}
	
	class FoodThread extends Thread{
//		private WaiterThread waiter;
		public FoodThread(){
//			waiter = wt;
//			start();
		}
		
		public void run(){
			try{
				while (true){
					//wait between 5 to 10 seconds, then check all the orders
					Thread.sleep(1000 * (int)(Math.random() * 5)+5);
					
					//now go through all the orders and check for completed ones
					int size = orderVector.size();
					for (int i = 0; i < size; ++i){
						if (orderVector.get(i).isFinished()){
							//if it is finished, signal the customer
							Order finishedOrder = orderVector.get(i);
							
							Restaurant.addMessage("Waiter " + waiterNumber + " has delivered order " + Restaurant.foodNames[finishedOrder.getOrder()] + " to table " + finishedOrder.getTable().getTableNumber() + ".");
							
							orderVector.get(i).getTable().getCustomer().getLock().lock();
							orderVector.get(i).getTable().getCustomer().getCondition().signalAll();
							orderVector.get(i).getTable().getCustomer().getLock().unlock();
							orderVector.remove(i);
							--i;
							--size;
							
							
						}
					}
					
					
				}
			} catch (InterruptedException IE){
				System.out.println("FooThread:InterruptedException " + IE.getMessage());
				IE.printStackTrace();
			}
		}
	}
}