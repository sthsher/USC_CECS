package tsher_CSCI201_Assignment4;

import java.util.Random;

abstract class CarAI {
	abstract public int getDirection(Tile tile);
}

class CarAI1 extends CarAI{
	private int direction;
	private int prevTileLoc;
	
	public CarAI1(){
		direction = 3;
		prevTileLoc = -1;
	}
	private void increment(){
		if (this.direction != 3){
			++direction;
		} else{
			//direction is 3, wrap back to 0
			direction = 0;
		}
	}
	private int getPrev(int a){
		if (a == 0){
			return 2;
		} else if (a == 1){
			return 3;
		} else if (a == 2){
			return 0;
		} else{
			return 1;
		}
		
	}
	public int getDirection(Tile tile){
		increment();
		for (int i = 0; i < 4; ++i){
			//first check if it's previous location
			if (direction == prevTileLoc){
				//don't go anywhere, just increment
				increment();
			}
			else if (tile.checkOpen(this.direction)){
				//if is open, give the direction
					prevTileLoc = getPrev(direction);
					return direction;
			}
			else{
				increment();
			}
		}
		
		//Returns back forward, meaning go in original first direction
		System.out.println("ERROR! Dead end");
		return 0;
		
	}
}

class CarAI2 extends CarAI{
	boolean[][] visitedTiles	= new boolean[9][9];
	Random generate 			= new Random();
	
	public CarAI2(int x, int y){
		wipeClean();
		//Starting Tile
		this.visitedTiles[x][y] = true;
	}

	private void wipeClean(){
		for (int i = 0; i < 9; ++i){
			for (int j = 0; j < 9; ++j){
				if (GlobalData.tileData[i][j].getType().equalsIgnoreCase("blank")){
					//blank, so make it true
					this.visitedTiles[i][j] = true;
				} else{
					this.visitedTiles[i][j] = false;
				}
			}
		}
	}
	
	//Check if there are any other possible places to go
	private boolean isStuck(int x, int y, Tile tile){

		boolean[] adjacent = new boolean[4];
		
		if (x == 0){
			adjacent[3] = true;
		} else{
			adjacent[3] = visitedTiles[x-1][y];
		}
		if (x == 8){
			adjacent[1] = true;
		} else{
			adjacent[1] = visitedTiles[x+1][y];
		}
		if (y == 0){
			adjacent[0] = true;
		} else{
			adjacent[0] = visitedTiles[x][y-1];
		}
		if (y == 8){
			adjacent[2] = true;
		} else{
			adjacent[2] = visitedTiles[x][y+1];
		}
		
		for(int i = 0; i < 4; ++i){
			//if there is a path and if it hasn't been visited, return true
			if (!adjacent[i] && tile.checkOpen(i)){
				return false;
			}
		}
		
		return true;
	}
	
	public int getDirection(Tile tile){
		//Check if stuck
		if (isStuck(tile.getX(), tile.getY(), tile)){
			//set everything false
			wipeClean();
		}
		
		//Random number between 0 and 3
		int randomNum = generate.nextInt(4);
		
		//Check if already visited
		int nextX 		= tile.getX();
		int nextY 		= tile.getY();
		boolean loop 	= true;
		
		//Mark current tile as visited
		visitedTiles[nextX][nextY] = true;
		
		while(loop){
			
			if (isStuck(nextX, nextY, tile)){
				wipeClean();
			}
			
			if (randomNum == 0){
				--nextY;
			} else if (randomNum == 1){
				++nextX;
			} else if (randomNum == 2){
				++nextY;
			} else{
				--nextX;
			}
			

			
			//if there is a direction open and if it hasn't been visited yet
			if(tile.checkOpen(randomNum) && !visitedTiles[nextX][nextY]){
				return randomNum;
			}
			
			//not open, undo alteration to nextX or nextY and make a new number
			
			if (randomNum == 0){
				++nextY;
			} else if (randomNum == 1){
				--nextX;
			} else if (randomNum == 2){
				--nextY;
			} else{
				++nextX;
			}
			randomNum = generate.nextInt(4);
		}
		
		//Should never reach here
		return 0;
	}
}

class CarAI3 extends CarAI{
	Random generate 			= new Random();
	private boolean isWest 		= false;
	public int getDirection(Tile tile){
		//See if you can go in favored direction. If you can, go
		if (isWest && tile.checkOpen(3)){
			return 3;
		} else{
			isWest = false;
		}
		if (!isWest && tile.checkOpen(1)){
			return 1;
		} else{
			isWest = true;
		}
		while(true){
			//go in random direction
			int randomNum = generate.nextInt(4);
			//see if this direction is valid
			if (tile.checkOpen(randomNum)){
				return randomNum;
			}
			//otherwise loop and try again
		}
		
	}
}

class CarAI4 extends CarAI{
	private int[] directionValues = new int[4];
	private int direction = -1;

	public CarAI4(){
		for (int i = 0; i < 4; ++i){
			directionValues[i] = 0;
		}
	}
	
	private void updateCounter(int a){
		if (a == 0){
			directionValues[1] += 1;
			directionValues[2] += 1;
			directionValues[3] += 1;
		} else if (a == 1){
			directionValues[2] += 1;
			directionValues[3] += 1;
			directionValues[0] += 1;
		} else if (a == 2){
			directionValues[3] += 1;
			directionValues[0] += 1;
			directionValues[1] += 1;
		} else{
			directionValues[0] += 1;
			directionValues[1] += 1;
			directionValues[2] += 1;
		}
	}
	
	public int getDirection(Tile tile){
		//Initial direction chosen randomly
		if (direction == -1){
			Random generate = new Random();
			while (true){
				int randomNum = generate.nextInt(4);
				if (tile.checkOpen(randomNum)){
					updateCounter(randomNum);
					direction = randomNum;
					return randomNum;
				}
			}
		}
		
		//Find direction with greatest value
		int nextDirection = -1;
		for (int i = 0; i < 4; ++i){
			if (tile.checkOpen(i)){
				//opening in this direction, see if it's value is larger than the current one
				if (nextDirection == -1){
					//First one, 
					nextDirection = i;
				} else if (directionValues[i] > directionValues[nextDirection]){
					//Update the direction
					nextDirection = i;
				} else{
					//smaller value, nothing to do
				}
			}
		}
		
		//go in nextDirection
		updateCounter(nextDirection);
		directionValues[nextDirection] = 0;
		return nextDirection;
	}
}