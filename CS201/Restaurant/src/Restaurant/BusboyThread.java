package Restaurant;

import java.util.Vector;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BusboyThread extends Thread{
	private Hostess hostess;
//	private Table table;
//	private Vector<Table> tables;
	public int busboyNumber;
	private BusboyFactory busboyFactory;
	private Lock waiterLock = new ReentrantLock();
//	private Condition tableAssignedCondition = waiterLock.newCondition();
	public boolean isAssigned = false;
	public boolean isFinished = true;
	
	public BusboyThread(Hostess h, int num, BusboyFactory bbf){
		hostess = h;
		busboyNumber = num;
		busboyFactory = bbf;
	}
	
	public void run(){
		isFinished = false;
		try{
			sleep(((busboyNumber+1)*1000));
		} catch (InterruptedException IE){
			IE.printStackTrace();
		}
		System.out.println("Busboy " + busboyNumber + " is finished");
		isFinished = true;
	}
}

class BusboyFactory {

	private Vector<BusboyThread> busboyThreadVector = new Vector<BusboyThread>();
	private int numBusboys;
	private Hostess hostess;
	private Lock lock = new ReentrantLock();
	private Condition waiterAvailable = lock.newCondition();

	public BusboyFactory(Hostess hostess, int numBusboys) {
		this.hostess = hostess;
		this.numBusboys = numBusboys;
		for (int i=0; i < numBusboys; i++) {
			busboyThreadVector.add(new BusboyThread(hostess, i, this));
		}
	}

	public void returnBusboy(BusboyThread bt) {
		lock.lock();
		bt.isAssigned = false;
//		bt.returnTable(bt.getTable(0));
		//waiterThreadVector.set(wt.getWaiterNumber(), new WaiterThread(wt.getHostess(), wt.getWaiterNumber(), this));
		waiterAvailable.signal();
		lock.unlock();

	}

	public BusboyThread getBusboy() {
		BusboyThread bt = null;
		try {
			lock.lock();
			while (bt == null) {
				int i;
				for (i=0; i < busboyThreadVector.size(); i++) {
					bt = busboyThreadVector.get(i);
					// this will only allow one table per waiter
					// use a semaphore to allow more than one table per waiter
					if (!bt.isAssigned) {
//					if (wt.getTable() == null) {
						break;
					}
				}
				if (i == busboyThreadVector.size()) {
					// if i get here, i haven't secured a waiter yet
					bt = null;
					waiterAvailable.await();
				}
			}
		} catch(InterruptedException ie) {
			System.out.println("WaiterFactory.getWaiter(): IE : " + ie.getMessage());
		} finally {
			lock.unlock();
		}
		bt.isAssigned = true;
		return bt;
	}

}