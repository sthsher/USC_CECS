import java.util.Vector;
import java.util.concurrent.locks.ReentrantLock;

public class CookFactory {
	private static Vector<Order> ordersToCook;
	public ReentrantLock lock = new ReentrantLock();
	
	
	public CookFactory(CookPanel cp, int numCooks ) {
		ordersToCook = new Vector<Order>();

		for ( int i=0; i<numCooks; i++ ) {
			CookThread c = new CookThread( i, cp, this );
			c.start();
		}

	}
	
	public void newOrder(Order newOrder){
		ordersToCook.add(newOrder);
		
	}
	
	public Vector<Order> getVector(){
		return ordersToCook;
	}
	
//	public static void main(String [] args){
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//		System.out.println((int)(Math.random() * 10)+10);
//
//	}
	
}


class CookThread extends Thread {
	private int cookNumber;
	private CookPanel cookPanel;
	private CookFactory cookFactory;
	private Order currentOrder;
	
	public CookThread( int n, CookPanel cp, CookFactory cf ) {
		cookNumber = n;
		cookPanel = cp;
		cookFactory = cf;		
	}
	
	public void run() {
		cookPanel.addCookMessage( "Cook" + cookNumber + " is ready to cook." );
		
		//Checks vector every 10 - 20 seconds
		try{
			while (true){
				Thread.sleep(1000 * (int)(Math.random() * 10)+10);
				
				cookFactory.lock.lock();
				
				//finished waiting, check to see if there's an order to cook
				if (cookFactory.getVector().size() != 0){
					//there's orders
					currentOrder = cookFactory.getVector().get(0);
					cookFactory.getVector().remove(0);
					
					//Now cook it, meaning wait between 
					cookPanel.addCookMessage("Cook " + cookNumber + " is cooking an order for " + Restaurant.foodNames[currentOrder.getOrder()] + " for table " + currentOrder.getTable().getTableNumber() + ".");
					Thread.sleep(1000 * (int)(Math.random() * 5)+5);
					cookPanel.addCookMessage("Cook " + cookNumber + " has completed an order for " + Restaurant.foodNames[currentOrder.getOrder()] + " for table " + currentOrder.getTable().getTableNumber() + ".");
					
					
					//Notify waiter
//					currentOrder.getWaiter().deliverOrder(currentOrder);
					currentOrder.setFinished();
				}
				
				cookFactory.lock.unlock();

				
			}
		} catch (InterruptedException IE){
			System.out.println("CookThread:InterruptedException: " + IE.getMessage());
			IE.printStackTrace();
		}
	}
}

//class TestFrame extends JFrame{
//	public TestFrame(){
//		setSize(400,400);
//		setLocation(100,100);
//		
//		JPanel cp = new CookPanel();
//		add(cp);
//		
//		setVisible(true);
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//	}
//}

