package Restaurant;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class Tables {
	private int numTables;
	private int numOccupiedTables;
	private Table[] tableArray;
	private Lock lock = new ReentrantLock();
	private Condition noTablesAvailable = lock.newCondition();
	
	public Tables(int numTables) {
		this.numTables = numTables;
		this.tableArray = new Table[numTables];
		this.numOccupiedTables = 0;
	}
	
	public String getOpenTableString(){
		String returnString = "";
		for (int i = 0; i < numTables; ++i){
			if (tableArray[i] == null){
				returnString += i;
				returnString += " ";
			}
		}
		return returnString;
	}
	
	public String getCloseTableString(){
		String returnString = "";
		for (int i = 0; i < numTables; ++i){
			if (tableArray[i] != null){
				returnString += i;
				returnString += " ";
			}
		}
		return returnString;
	}
	
	public Table getTable() throws InterruptedException {
		lock.lock();
		Table tableToReturn = null;
		try {
			while(this.numOccupiedTables == this.numTables) {
				Restaurant.addMessage("No tables available.");
				// wait for a table to become available
				noTablesAvailable.await();
				Restaurant.addMessage("Table became available.");
			}
			// when this thread is signaled, find the table that is available
			for (int i=0; i < this.numTables; i++) {
				if (tableArray[i] == null) {
					tableArray[i] = new Table(i);
					tableToReturn = tableArray[i];
					numOccupiedTables++;
					break;
				}
			}
		} finally {
			lock.unlock();
		}
		return tableToReturn;
	}
	
	public void returnTable(Table table) {
		lock.lock();
		try {
			for (int i=0; i < this.numTables; i++) {
				if (i == table.getTableNumber()) {
					tableArray[i] = null;
					numOccupiedTables--;
					Restaurant.addMessage("Table " + table.getTableNumber() + " is now available.");
					noTablesAvailable.signal();
				}
			}
		} finally {
			lock.unlock();
		}
	}
}