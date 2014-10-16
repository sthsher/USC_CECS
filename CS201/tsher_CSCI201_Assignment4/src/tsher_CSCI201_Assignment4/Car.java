package tsher_CSCI201_Assignment4;

import java.awt.Color;

class Car extends Thread{
	private String 	color;
	private int 	ai;
	private double	speed;
	private double	blinkSpeed;
	private int		x;
	private int		y;
	private boolean isLighted = true;
	public Car(String c, int a, double s, int x, int y){
		this.color = c;
		this.ai 	= a;
		this.speed 	= s;
		this.x		= x;
		this.y		= y;
		this.blinkSpeed = s*3;
	}
	
	public void run(){
		//blink speeds
		while (true){
			this.toggle();
			try{
				sleep((long)(1000/this.blinkSpeed));
			} catch (InterruptedException IE){
				System.out.println("Error: Interrupted");
				return;
			}
		}
	}
	
	public void toggle(){
		if (this.isLighted == true){
			this.isLighted = false;
		} else{
			this.isLighted = true;
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
	public int getAI(){
		return this.ai;
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
