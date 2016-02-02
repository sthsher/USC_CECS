package Restaurant;


public class Hostess {
	private Tables tables;
	
	public Hostess(int numTables) {
		this.tables = new Tables(numTables);
	}
	
	public void customerOrder(CustomerThread customerThread){
		//make assigned waiter to go over to table
		customerThread.getTable().getWaiterThread().takeOrder(customerThread.getTable());
	}
	
	public Table seatCustomer(CustomerThread customerThread) {
		Table table = null;
		try {
			Restaurant.addMessage("Hostess is trying to seat customer " + customerThread.getCustomerNumber());
			table = tables.getTable();
			WaiterThread waiter = Restaurant.getWaiterFactory().getWaiterWithLeastTables();
			waiter.setTable(table);
			table.seatTable(customerThread, waiter);
			Restaurant.addWaiterMessage("Customer " + customerThread.getCustomerNumber() + " is seated at table " + table.getTableNumber(), waiter.getWaiterNumber());
			Restaurant.addMessage("Hostess seated customer " + customerThread.getCustomerNumber() + " at table " + table.getTableNumber() + " with waiter " + waiter.getWaiterNumber());
			
			//update opentables
			//System.out.println("Available: " + tables.getOpenTableString());
			Restaurant.openTableContents.setText(tables.getOpenTableString());
			Restaurant.closeTableContents.setText(tables.getCloseTableString());

		} catch (InterruptedException ie) {
			System.out.println("HostessThread.seatCustomer():InterruptedException: " + ie.getMessage());
		}
		return table;
	}
	
	public void customerLeaving(CustomerThread customerThread) {
		Restaurant.addWaiterMessage("Customer " + customerThread.getCustomerNumber() + " is done eating and is leaving.", customerThread.getTable().getWaiterThread().getWaiterNumber());
		Restaurant.addMessage("Customer " + customerThread.getCustomerNumber() + " is done eating and is leaving.");

		customerThread.getTable().getWaiterThread().returnTable(customerThread.getTable());
		
		//busboy clean the table
		customerThread.getTable().cleanTable();
		
		System.out.println("returning table");
		
		tables.returnTable(customerThread.getTable());
		
		Restaurant.openTableContents.setText(tables.getOpenTableString());
		Restaurant.closeTableContents.setText(tables.getCloseTableString());
	}

}