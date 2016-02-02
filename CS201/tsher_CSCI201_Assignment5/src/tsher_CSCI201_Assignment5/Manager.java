package tsher_CSCI201_Assignment5;

import java.util.ArrayList;
import java.util.Vector;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


class Manager extends Thread{
	private Vector<WorkerObject>		workerVector		= new Vector<WorkerObject>();
	private Vector<Thread>				workerThreadVector 	= new Vector<Thread>();
	public int recipeCount = 0;
	
	public int numOfWorkers;
	private Lock lock = new ReentrantLock();
	private ArrayList<Recipe> recipeList;
	private Condition workerAvailable = lock.newCondition();
	private Condition workareaAvailable = lock.newCondition();
	
	//Semaphores
	private Semaphore[] toolSemaphoreArray = new Semaphore[5];
	private Factory factory;
	
	public Manager(int numOfWorkers, ArrayList<Recipe> recipeList, Factory factory){
		this.numOfWorkers = numOfWorkers;
		this.factory = factory;
		for (int i = 0; i < numOfWorkers; ++i){
			WorkerObject newWorker = new WorkerObject(i, this);
			workerVector.add(newWorker);
			workerThreadVector.add(new Thread(newWorker));
		}
		this.recipeList = recipeList;
		for (int i = 0; i < 5; ++i){
			toolSemaphoreArray[i] = new Semaphore(factory.totalToolArray[i]);
		}
		
	}
	
	public void addTool(int i){
		toolSemaphoreArray[i].release(1);
	}
	
	public void removeTool(int i){
		try{
			toolSemaphoreArray[i].acquire(1);
		} catch (InterruptedException IE){
			IE.printStackTrace();
		}
	}
	
	public void getTool(WorkerObject worker, int i){
		if (worker.getRecipe().checkTool(Factory.toolStringArray[i])){
			try{
				toolSemaphoreArray[i].acquire(worker.getRecipe().getToolAmount(Factory.toolStringArray[i]));
				
				factory.toolAmountArray[i] -= worker.getRecipe().getToolAmount(Factory.toolStringArray[i]);
				worker.toolArray[i] += worker.getRecipe().getToolAmount(Factory.toolStringArray[i]);
				
			} catch (InterruptedException IE){
				IE.printStackTrace();
			}
		}
	}
	
	public void returnTool(WorkerObject worker, int i){
		if (worker.toolArray[i] != 0){
			toolSemaphoreArray[i].release(worker.toolArray[i]);
			
			factory.toolAmountArray[i] += worker.toolArray[i];
			worker.toolArray[i] = 0;
		}
	}
	
	public Vector<WorkerObject> getWorkerVector(){
		return workerVector;
	}
	
	public void startWorker(int ID){
		//start only if there are tasks
		if (recipeList.size() > 0){
			workerVector.get(ID).setIsWorking(true);
			workerThreadVector.get(ID).start();
		}
	}
	
	public void returnWorkarea(int workareaID){
		lock.lock();
		workareaAvailable.signalAll();
		Factory.allWorkareas.get(workareaID).setStatus(0);
		lock.unlock();
	}
	public int getWorkarea(String workareaName){
		int workareaID = -1;
		try{
			lock.lock(); 
			while (workareaID == -1){
				for (int i = 0; i < Factory.allWorkareas.size(); ++i){
					if (Factory.allWorkareas.get(i).getName().equalsIgnoreCase(workareaName) &&
							Factory.allWorkareas.get(i).getStatus() == 0){
						//the same name and is available
						//When you assign, change its status
						Factory.allWorkareas.get(i).setStatus(-1);
						workareaID = i;
						break;
					}
				}
				//end of for loop, if worker is still not available, means no worker available yet, await
				if (workareaID == -1){
					workareaAvailable.await();
				}
			}
		
		} catch (InterruptedException IE){
			IE.printStackTrace();
		} finally{
			lock.unlock();
		}
		
		return workareaID;
	}
	
	public void returnWorker(WorkerObject worker){
		lock.lock();
		worker.setIsWorking(false);
		workerAvailable.signal();
		lock.unlock();
	}
	
	public void addWorker(){
		WorkerObject newWorker = new WorkerObject(numOfWorkers++, this);
		workerVector.add(newWorker);
		workerThreadVector.add(new Thread(newWorker));
		factory.getGlass().add(newWorker);
		newWorker.setBounds(newWorker.x, newWorker.y, 50,50);
		startWorker(newWorker.getID());
	}
	
	class FireThread extends Thread{
		public FireThread(){

		}
		public void run(){
			boolean fired = false;
			try{				

				lock.lock();
				while(!fired){

					for (int i = 0; i < workerVector.size(); ++i){

						if (!workerVector.get(i).getIsWorking()){

							factory.getGlass().remove(workerVector.get(i));
							workerVector.remove(i);
							numOfWorkers--;
							fired = true;
							factory.totalWorkers--;
							factory.addMoney(15);
							break;
						}
					}
					if (!fired){
						//await to fire worker
						workerAvailable.await();
					}
				}
			} catch (InterruptedException IE){
				IE.printStackTrace();
			} finally{
				lock.unlock();
			}
		}
	}
	
	public void fireWorker(){
		Thread fire = new FireThread();
		fire.start();
	}
	
	public WorkerObject getWorker(){
		WorkerObject worker = null;
		try{
			lock.lock(); 
			while (worker == null){
				for (int i = 0; i < numOfWorkers; ++i){
					worker = workerVector.get(i);
					//see if worker is working or not
					if (!worker.getIsWorking()){
						//free worker, use him
						break;
					}
				}
				//end of for loop, if worker is still not available, means no worker available yet, await
				if (worker.getIsWorking()){
					worker = null;
					workerAvailable.await();
				}
			}
		
		} catch (InterruptedException IE){
			IE.printStackTrace();
		} finally{
			lock.unlock();
		}
		
		//worker assigned, set to isworking
		worker.setIsWorking(true);
		return worker;
	}
	
	public boolean existUnfinishedRecipe(){
		if (recipeCount < recipeList.size()){
			return true;
		} else{
			return false;
		}
	}

	public Recipe getRecipe(){
		Recipe nextRecipe = null;
		lock.lock();
		nextRecipe = recipeList.get(recipeCount++);
		lock.unlock();
		return nextRecipe;
	}
	
	public void run(){
		
		for (int i = 0; i < numOfWorkers; ++i){
			WorkerObject nextWorker = getWorker();
			try{
				sleep(500);
			} catch (InterruptedException IE){
				IE.printStackTrace();
			}
			startWorker(nextWorker.getID());
		}
	}
	
}