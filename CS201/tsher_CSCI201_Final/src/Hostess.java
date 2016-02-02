
public class Hostess {
	private Tables tables;
	
	public Hostess(int numTables) {
		this.tables = new Tables(numTables);
	}
	
	
	public Table seatCustomer(CustomerThread customerThread) {
		Table table = null;
		try {
			Restaurant.addMessage("Hostess is trying to seat customer " + customerThread.getCustomerNumber());
			
			/* Here, customer is about to wait for a table... add him to waiting label*/
			Restaurant.addCustomerToWaitingLabel(customerThread.getCustomerNumber());
			
			//get an available table
			table = tables.getTable();
			
			//get a waiter
			WaiterThread waiter = Restaurant.getWaiterFactory().getWaiter();
			
			//need both waiter and table to proceed
			
			//waiter gets assigned a table
			waiter.setTable(table);
			
			//set the customer
			table.seatTable(customerThread, waiter);
			
			/* Here, customer is seated */
			Restaurant.addCustomerToSeatedLabel(customerThread.getCustomerNumber());
			Restaurant.addWaiterMessage("Customer " + customerThread.getCustomerNumber() + " is seated at table " + table.getTableNumber(), waiter.getWaiterNumber());
			Restaurant.addMessage("Hostess seated customer " + customerThread.getCustomerNumber() + " at table " + table.getTableNumber() + " with waiter " + waiter.getWaiterNumber());
		
		} catch (InterruptedException ie) {
			System.out.println("HostessThread.seatCustomer():InterruptedException: " + ie.getMessage());
		}
		
		//goes back to customer thread and proceeds with sleep / eating
		return table;
	}
	
	public void customerLeaving(CustomerThread customerThread) {
		Restaurant.addCustomerToLeavingLabel(customerThread.getCustomerNumber());
		Restaurant.addWaiterMessage("Customer " + customerThread.getCustomerNumber() + " is done eating and is leaving.", customerThread.getTable().getWaiterThread().getWaiterNumber());
		Restaurant.addMessage("Customer " + customerThread.getCustomerNumber() + " is done eating and is leaving.");
		
		//release semaphore and removes from vector
		customerThread.getTable().getWaiterThread().returnTable(customerThread.getTable());
		
		//set array as null
		tables.returnTable(customerThread.getTable());
	}

}
