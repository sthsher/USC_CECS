package tsher_CSCI201_Assignment4;

import javax.swing.table.DefaultTableModel;

public class GlobalData {
	static class Coor{
		public Coor(){
			x = 0;
			y = 0;
		}
		public int x;
		public int y;
	}
	static Tile[][]				tileData		= new Tile[9][9];
	static DefaultTableModel 	model 			= new DefaultTableModel();


}
