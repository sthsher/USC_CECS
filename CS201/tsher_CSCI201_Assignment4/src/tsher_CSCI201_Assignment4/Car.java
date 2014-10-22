package tsher_CSCI201_Assignment4;

import java.awt.Color;

class Car extends Thread{
	private int		carNum;
	private String 	color;
	private int 	aiNum;
	private double	speed;
	private double	blinkSpeed;
	private int		x;
	private int		y;
	private boolean isLighted = true;
	private int		lightCounter;

	private CarAI	ai;
	
	public Car(int num, String c, int a, double s, int x, int y){
		this.carNum			= num;
		this.color 			= c;
		this.aiNum 			= a;
		this.speed 			= s;
		this.x				= x-1;
		this.y				= y-1;
		this.blinkSpeed 	= s*3;
		this.lightCounter 	= 0;
		
		//DEBUG
		if (this.aiNum == 1){
			this.ai = new CarAI1();
		} else if (this.aiNum == 2){
			this.ai = new CarAI2(x, y);
		} else if (this.aiNum == 3){
			this.ai = new CarAI3();
		} else{
			this.ai = new CarAI4();
		}
	}
	
	private void move(int direction){
		if (direction == 0){
			--this.y;
		} else if (direction == 1){
			++this.x;
		} else if (direction == 2){
			++this.y;
		} else if (direction == 3){
			--this.x;
		} else{
			System.out.println("Unexpected direction");
		}
		
		//update information in JTable
		//y change
		if (direction % 2 == 0){
			GlobalData.model.setValueAt((char)(this.getY()+65), this.getCarNum(), 2);
		} else{
			GlobalData.model.setValueAt(""+(this.getX()+1), this.getCarNum(), 1);
		}
	}
	
	public void run(){
		//blink speeds
		while (true){
			toggle();
			try{
				sleep((long)(1000/this.blinkSpeed));
			} catch (InterruptedException IE){
				System.out.println("Error: Interrupted");
				return;
			}
			if (this.lightCounter == 0 && this.isLighted == true){
				move(this.ai.getDirection(GlobalData.tileData[this.x][this.y]));
			}
		}
	}
	
	private void increment(){
		if (this.lightCounter != 2){
			++lightCounter;
		} else{
			lightCounter = 0;
		}
	}
	
	private void toggle(){
		if (this.isLighted == true){
			this.isLighted = false;
		} else{
			this.isLighted = true;
			//back to true, increment counter
			increment();
		}
		
	}
	
	public boolean isLighted(){
		return this.isLighted;
	}
	
	public Color getColor(){
		switch(color){
			case "white": 		return Color.WHITE;
			case "light_gray":	return Color.LIGHT_GRAY;
			case "gray":		return Color.GRAY;
			case "dark_gray":	return Color.DARK_GRAY;
			case "black":		return Color.BLACK;
			case "red":			return Color.RED;
			case "pink":		return Color.PINK;
			case "orange":		return Color.ORANGE;
			case "yellow":		return Color.YELLOW;
			case "green":		return Color.GREEN;
			case "magenta":		return Color.MAGENTA;
			case "cyan":		return Color.CYAN;
			case "blue":		return Color.BLUE;
			default:			return Color.WHITE;
		}
		
	}
	public int getCarNum(){
		return this.carNum;
	}
	public int getAI(){
		return this.aiNum;
	}
	public double getSpeed(){
		return this.speed;
	}
	public int getX(){
		return this.x;
	}
	public int getY(){
		return this.y;
	}
}
