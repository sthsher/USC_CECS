 package tsher_CSCI201_Assignment5;

import java.awt.CardLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

class WorkerObject extends JLabel implements Runnable{
	static final long serialVersionUID = 1;

	private int workerID;
	private Manager manager;
	public int x = Factory.workerStartX;
	public int y = Factory.workerStartY;
	private Recipe recipe;
	private boolean isWorking = false;
	
	int toolArray[] = new int[] {0,0,0,0,0};
	
	private Lock lock = new ReentrantLock(); 
	private Condition workerAction = lock.newCondition();
	
	public WorkerObject(int ID, Manager manager){
		this.manager = manager;
		workerID = ID;
		setIcon(new ImageIcon(Factory.imageDirectory + "worker.png"));
	}
	
	public int getID(){
		return workerID;
	}
	
	public boolean getIsWorking(){
		return isWorking;
	}
	
	public void setIsWorking(boolean b){
		isWorking = b;
	}
	
	public void moveWorker(){
		lock.lock();
		workerAction.signal();
		lock.unlock();
	}
	
	public void setRecipe(Recipe recipe){
			this.recipe = recipe;
			//Worker has recipe, now in progress
			this.recipe.setStatus(1);
	}
			
	public Recipe getRecipe(){
		return recipe;
	}

	@Override
	public void run() {
		//once all the variables are set, get materials and then do the tasks
		Thread thread;
		
		while (manager.existUnfinishedRecipe()){
			try{
				lock.lock();

				this.setRecipe(manager.getRecipe());
				
				thread = new MaterialRunThread(this, workerAction, lock);
				thread.start();
				
				workerAction.await();

				while (recipe.getStatus() != 2 && recipe.getStatus() != -1){
				
					thread = new ToolRunThread(this);
					thread.start();
					
					workerAction.await();
					
					thread = new WorkareaRunThread(this, manager.getWorkarea(recipe.nextWorkarea()));
					thread.start();
				
					workerAction.await();
					
					thread = new ReturnToolThread(this);
					thread.start();
					
					workerAction.await();
					
				}
				
			} catch (InterruptedException IE){
				IE.printStackTrace();
			} finally{
				lock.unlock();
			}
			
		}
		
	manager.returnWorker(this);
	}
}


