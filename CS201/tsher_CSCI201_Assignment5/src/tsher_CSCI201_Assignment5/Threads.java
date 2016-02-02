package tsher_CSCI201_Assignment5;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

class WorkareaRunThread extends Thread{
	private int destinationRow;
	private int workareaIndex;
	private int destinationRowY;
	private int workareaID;
	private WorkerObject worker;
	public WorkareaRunThread(WorkerObject worker, int workareaID){
		this.workareaID = workareaID;
		this.worker = worker;
	}
	
	public void setupNextDestination(String destination){
		if (destination.equalsIgnoreCase("Anvils") || destination.equalsIgnoreCase("Anvil") ||
				destination.equalsIgnoreCase("Workbenches") || destination.equalsIgnoreCase("Workbench")){
				destinationRowY = Factory.row1Walkway;
				destinationRow = 0;
				workareaIndex = 4;
			} else if (destination.equalsIgnoreCase("Furnaces") || destination.equalsIgnoreCase("Furnace") ||
					destination.equalsIgnoreCase("Tablesaw") || destination.equalsIgnoreCase("Tabelsaws") ||
					destination.equalsIgnoreCase("Saw") || destination.equalsIgnoreCase("Saws")){
				destinationRowY = Factory.row2Walkway;
				destinationRow = 1;
				workareaIndex = 9;
			} else if (destination.equalsIgnoreCase("Painting Station") || destination.equalsIgnoreCase("Painting Stations") ||
					destination.equalsIgnoreCase("Paintingstation") || destination.equalsIgnoreCase("Paintingstations") ||
					destination.equalsIgnoreCase("Press") || destination.equalsIgnoreCase("Presses")){
				destinationRow = 2;
				workareaIndex = 14;
				destinationRowY = Factory.bottomRow;
			} else{
				System.out.println("Unexpected destination name: " + destination);
			}
	}
	
	public void run(){
		
		//keep going until finish instructions
		setupNextDestination(worker.getRecipe().nextWorkarea());
		try{
			//move down to row first
			while(worker.y < destinationRowY){
				worker.setLocation(worker.x, worker.y);
				worker.y += 5;
				sleep(Global.speed);
			}
			
			int columnCheckIndex = 4;
			
			//now move to the left
			while (worker.x > Factory.leftColumn){
				//Check if at a slot
				if (worker.x == Factory.columnCoorArray[columnCheckIndex] && worker.getRecipe().getStatus() != 2){
					if (columnCheckIndex != 0)
						--columnCheckIndex;
					
					if (workareaID == Factory.allWorkareas.get(workareaIndex).getID()){

						int originalY = worker.y;
						while(worker.y >= Factory.rowCoorArray[destinationRow]){
							worker.setLocation(worker.x, worker.y);
							worker.y -= 5;
							sleep(Global.speed);
						}
						
						//Complete instruction
						//Assign instruction
						Factory.allWorkareas.get(workareaIndex).setInstruction(worker.getRecipe().getCurrentInstruction());
						Factory.allWorkareas.get(workareaIndex).setStatus(1);
						
						for (int i = 0; i < worker.getRecipe().getInstructionDuration(); ++i)
						{
							worker.getRecipe().getCurrentInstruction().decrementTimeLeft();
							Factory.allWorkareas.get(workareaIndex).repaint();
							sleep(1000);
						}
						
						Factory.manager.returnWorkarea(workareaID);
						worker.getRecipe().checkOffInstruction();
						
						while (worker.y < originalY){
							worker.setLocation(worker.x, worker.y);
							worker.y += 5;
							sleep(Global.speed);
						}	
						
					}
					--workareaIndex;
				}
				
				worker.setLocation(worker.x, worker.y);
				worker.x -= 5;
				sleep(Global.speed);
			}
			
			//up
			while (worker.y > Factory.workerStartY){
				worker.setLocation(worker.x, worker.y);
				worker.y -= 5;
				sleep(Global.speed);
			}
			
			while (worker.x < Factory.workerStartX){
				worker.setLocation(worker.x, worker.y);
				worker.x += 5;
				sleep(Global.speed);
			}
			
			worker.moveWorker();
			
		} catch (InterruptedException IE){
			IE.printStackTrace();
		}
	}
}

class MaterialRunThread extends Thread{
	private WorkerObject worker;
	public MaterialRunThread(WorkerObject worker, Condition workerAction, Lock workerLock){
		this.worker = worker;
	}
	
	public void run(){
		//go left
		
		boolean enoughMaterial = true;
		
		try{

			while (worker.x > Factory.leftColumn){
				//check materials
				
				if (worker.x == Factory.plasticX && worker.getRecipe().checkMaterial("plastic") && enoughMaterial){
					int originalY = worker.y;
					
					if (Factory.plasticImmediate > worker.getRecipe().getMaterialAmount("plastic")){
						Factory.plasticImmediate -= worker.getRecipe().getMaterialAmount("plastic");
						while(worker.y >= Factory.plasticY){
							worker.setLocation(worker.x, worker.y);
							worker.y -= 5;
							sleep(Global.speed);
						}
						//get the number required
						Factory.plasticAmount -= worker.getRecipe().getMaterialAmount("plastic");
							
						while (worker.y <= originalY){
							worker.setLocation(worker.x, worker.y);
							worker.y += 5;
							sleep(Global.speed);
						}		
					} else{
						enoughMaterial = false;
						worker.getRecipe().setStatus(-1);
					}
				}
				
			
				if (worker.x == Factory.metalX && worker.getRecipe().checkMaterial("metal") && enoughMaterial){
					int originalY = worker.y;
					
					if (Factory.metalImmediate >= worker.getRecipe().getMaterialAmount("metal")){
						Factory.metalImmediate -= worker.getRecipe().getMaterialAmount("metal");
						while(worker.y >= Factory.metalY){
							worker.setLocation(worker.x, worker.y);
							worker.y -= 5;
							sleep(Global.speed);
						}
						//get the number required
						Factory.metalAmount -= worker.getRecipe().getMaterialAmount("metal");
						while (worker.y <= originalY){
							worker.setLocation(worker.x, worker.y);
							worker.y += 5;
							sleep(Global.speed);
						}
					} else{
						enoughMaterial = false;
						worker.getRecipe().setStatus(-1);
					}
				}
				
				if (worker.x == Factory.woodX && worker.getRecipe().checkMaterial("wood") && enoughMaterial){
					int originalY = worker.y;
					
					if (Factory.woodImmediate > worker.getRecipe().getMaterialAmount("wood")){
						Factory.woodImmediate -= worker.getRecipe().getMaterialAmount("wood");
						while(worker.y >= Factory.woodY){
							worker.setLocation(worker.x, worker.y);
							worker.y -= 5;
							sleep(Global.speed);
						}
						//get the number required
						Factory.woodAmount -= worker.getRecipe().getMaterialAmount("wood");
						while (worker.y <= originalY){
							worker.setLocation(worker.x, worker.y);
							worker.y += 5;
							sleep(Global.speed);
						}				
					} else{
						enoughMaterial = false;
						worker.getRecipe().setStatus(-1);
					}
					
				}
					
				worker.setLocation(worker.x, worker.y);
				worker.x -= 5;
				sleep(Global.speed);
			}
			
			//Animation to get tool
			while (worker.y < Factory.bottomRow){
				worker.setLocation(worker.x, worker.y);
				worker.y += 5;
				sleep(Global.speed);
			}
			
			while (worker.x <= Factory.rightColumn){
				worker.setLocation(worker.x, worker.y);
				worker.x += 5;
				sleep(Global.speed);
			}
			while (worker.y >= Factory.topRow){
				worker.setLocation(worker.x, worker.y);
				worker.y -= 5;
				sleep(Global.speed);
			}
			
			worker.moveWorker();
			
			
		} catch (InterruptedException IE){
			IE.printStackTrace();
		}
	}
}

class ToolRunThread extends Thread{
	private WorkerObject worker;
	public ToolRunThread(WorkerObject worker){
		this.worker = worker;
	}
	
	public void run(){
		//go left
		try{
			while (worker.x > Factory.leftColumn){
				worker.setLocation(worker.x, worker.y);
				worker.x -= 5;
				sleep(Global.speed);
			}

			//Animation to get tool
			while (worker.y < Factory.bottomRow){
				for (int i = 0; i < 5; ++i){
					if (worker.y == Factory.toolCoordinateArrayY[i]){
						if (worker.getRecipe().checkTool(Factory.toolStringArray[i])){
							int originalX = worker.x;
							
							Factory.manager.getTool(worker, i);

							
							while (worker.x >= Factory.toolCoordinateArrayX[i]){
								worker.setLocation(worker.x, worker.y);
								worker.x -= 5;
								sleep(Global.speed);
							}
							
							while(worker.x <= originalX){
								worker.setLocation(worker.x, worker.y);
								worker.x += 5;
								sleep(Global.speed);
							}
						}
					}
				}
				
				worker.setLocation(worker.x, worker.y);
				worker.y += 5;
				sleep(Global.speed);
			}
			
			while (worker.x <= Factory.rightColumn){
				worker.setLocation(worker.x, worker.y);
				worker.x += 5;
				sleep(Global.speed);
			}
			while (worker.y >= Factory.topRow){
				worker.setLocation(worker.x, worker.y);
				worker.y -= 5;
				sleep(Global.speed);
			}
			
			worker.moveWorker();
			
			
		} catch (InterruptedException IE){
			IE.printStackTrace();
		}
	}
}

class ReturnToolThread extends Thread{
	private WorkerObject worker;
	public ReturnToolThread(WorkerObject worker){
		this.worker = worker;
	}
	
	public void run(){
		//go left
		try{
			
			while (worker.x > Factory.leftColumn){
				worker.setLocation(worker.x, worker.y);
				worker.x -= 5;
				sleep(Global.speed);
			}
			
			//Animation to get tool
			while (worker.y < Factory.bottomRow){
				for (int i = 0; i < 5; ++i){
					if (worker.y == Factory.toolCoordinateArrayY[i]){
						if (worker.toolArray[i] != 0){
							int originalX = worker.x;
							while (worker.x >= Factory.toolCoordinateArrayX[i]){
								worker.setLocation(worker.x, worker.y);
								worker.x -= 5;
								sleep(Global.speed);
							}
							
							Factory.manager.returnTool(worker, i);
							
							while(worker.x <= originalX){
								worker.setLocation(worker.x, worker.y);
								worker.x += 5;
								sleep(Global.speed);
							}
						}
					}
				}
				
				worker.setLocation(worker.x, worker.y);
				worker.y += 5;
				sleep(Global.speed);
			}
			
			while (worker.x <= Factory.rightColumn){
				worker.setLocation(worker.x, worker.y);
				worker.x += 5;
				sleep(Global.speed);
			}
			while (worker.y >= Factory.topRow){
				worker.setLocation(worker.x, worker.y);
				worker.y -= 5;
				sleep(Global.speed);
			}

			worker.moveWorker();
			
			
		} catch (InterruptedException IE){
			IE.printStackTrace();
		}
	}
}