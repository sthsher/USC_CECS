package tsher_CSCI201_Assignment4;

class Tile {
	private int column;
	private int row;
	private String type;
	private int degree;
	
	public Tile(char r, int c, String t, int d){
		this.column = c;
		this.type	= t;
		this.degree = d;
		this.row	= ((int)r)-64;
	}
	public String getType(){
		return this.type;
	}
	public int getColumn(){
		return this.column;
	}
	public int getRow(){
		return this.row;
	}
	public int getDegree(){
		return this.degree;
	}
}
