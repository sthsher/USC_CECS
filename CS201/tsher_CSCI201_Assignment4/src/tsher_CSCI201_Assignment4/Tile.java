package tsher_CSCI201_Assignment4;

class Tile {
	private int x;
	private int y;
	private String type;
	private int degree;
	private boolean[] openings = new boolean[4];
	
	public Tile(char r, int c, String t, int d){
		this.x = c-1;
		this.type	= t;
		this.degree = d;
		this.y	= ((int)r)-64-1;
		
		//mark openings
		for (int i = 0; i < 4; ++i){
			openings[i] = true;
		}
		
//		if (t.equals("+"))
//			all true, default
		
		if (t.equals("i")){
			if (d == 0 || d == 180){
				openings[1] = false;
				openings[3] = false;
			} else{
				openings[0] = false;
				openings[2] = false;
			}
		}
		else if (t.equals("l")){
			if (d == 0){
				openings[2] = false;
				openings[3] = false;
			} else if(d == 90){
				openings[1] = false;
				openings[2] = false;
			} else if (d == 180){
				openings[0] = false;
				openings[1] = false;
			} else if (d == 270){
				openings[0] = false;
				openings[3] = false;
			} else{
				System.out.println("Please check your XML File 1");
			}
		} else if (t.equals("t")){
			if (d == 0){
				openings[0] = false;
			} else if(d == 90){
				openings[3] = false;
			} else if (d == 180){
				openings[2] = false;
			} else if (d == 270){
				openings[1] = false;
			} else{
				System.out.println("Please check your XML File 2");
			}
		} else if (t.equals("blank")){
			for (int i = 0; i < 4; ++i){
				openings[i] = false;
			}
		} else if (t.equals("+")){
			//Already set, don't do anything
		} else{
			
			System.out.println("Please check your XML File 3 " + r + " " + c);
		}
		
	}
	public boolean checkOpen(int direction){
		return openings[direction];
	}
	
	public String getType(){
		return this.type;
	}
	public int getX(){
		return this.x;
	}
	public int getY(){
		return this.y;
	}
	public int getDegree(){
		return this.degree;
	}
}
