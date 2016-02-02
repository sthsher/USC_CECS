package Restaurant;

import java.util.Vector;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Table extends Thread{
	
	private int tableNumber;

	private Semaphore numBusboySemaphore;
//	private int numPermitsAvailable;
	private Vector<BusboyThread> busboyThreadVector = new Vector<BusboyThread>();
	
	private CustomerThread ct;
	private WaiterThread wt;
	private Lock lock = new ReentrantLock();
	private Condition readyCondition = lock.newCondition();
//	private BusboyThread bbt;
	

	
	public void returnBusboys(){
		numBusboySemaphore.release();
	}
	
	public void cleanTable(){
		try{
			System.out.println("Getting busboys for table " + this.tableNumber);

			while (numBusboySemaphore.availablePermits() != 0){
					numBusboySemaphore.acquire();
					BusboyThread bt = Restaurant.busboyFactory.getBusboy();
					busboyThreadVector.add(bt);
					bt.isFinished = false;
					System.out.println("Busboy: " + bt.busboyNumber + " assigned to table " + tableNumber);

			}
			sleep(10000/(Restaurant.numOfBusboysPerTable));
			
		} catch (InterruptedException ie){
			ie.printStackTrace();
		}
		
		for (int i = 0; i < Restaurant.numOfBusboysPerTable; ++i){
			busboyThreadVector.get(i).isFinished = true;
			Restaurant.busboyFactory.returnBusboy(busboyThreadVector.get(i));
			System.out.println("Busboy " + busboyThreadVector.get(i).busboyNumber + " is now free");
		}
		
		System.out.println("Table " + tableNumber + " is free");
		numBusboySemaphore.release();
		
		
	}
	
	
	public Table(int tableNumber) {
		this.tableNumber = tableNumber;
		numBusboySemaphore = new Semaphore(Restaurant.numOfBusboysPerTable);
	}

	public int getTableNumber() {
		return this.tableNumber;
	}

	public CustomerThread getCustomer() {
		return ct;
	}
	
	public WaiterThread getWaiterThread() {
		return wt;
	}
	
	public Lock getLock() {
		return lock;
	}
	
	public Condition getReadyCondition() {
		return readyCondition;
	}

	public void seatTable(CustomerThread ct, WaiterThread wt) { //, BusboyThread bbt) {
		this.ct = ct;
		this.wt = wt;
//		this.bbt = bbt;
	}


}