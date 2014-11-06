package tsher_CSCI201_Assignment4;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class RoadwaySim extends JFrame {
	static final long serialVersionUID = 1;

	JMenuBar 			menuBar 		= new JMenuBar();
	JMenuItem			openItem		= new JMenuItem("Open File...");
	MapPanel			mapPanel		= new MapPanel();
	JTable				dataTable;
	JScrollPane			tableScroller;
	

	
	Object[]			columnNames	= {"Car#", "X", "Y"};
	Object[][]			rowData		= {{"","",""}};
	GlobalData.Coor[][] tileLoc		= new GlobalData.Coor[9][9];
	ArrayList<Car>		carArray	= new ArrayList<Car>();
	boolean				isTile		= false;
	
	File		dataFile;
	boolean		fileExist = true;
	
	//Constants
	static final int tileSize = 50;
	static final float blueH 		= (float) 0.5947368;
	static final float blueS 		= (float) 0.8796296;
	static final float blueB 		= (float) 0.84705883;
	
	public RoadwaySim(){
		super("Creative Roadway Simulator");
		setSize(810,650);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBackground(Color.WHITE);
		setMinimumSize(new Dimension(700,550));
		
		//Set up mapPanel
		mapPanel.setPreferredSize(new Dimension(600,600));
		mapPanel.setBackground(Color.WHITE);
		
		//Set up JTable and scroller
		dataTable = new JTable(GlobalData.model);
		GlobalData.model.addColumn("Car #");
		GlobalData.model.addColumn("X");
		GlobalData.model.addColumn("Y");
		
		tableScroller = new JScrollPane(dataTable);
		tableScroller.setPreferredSize(new Dimension(200,600));
		
		//Actions
		//Add file choosing action
		openItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				JFileChooser chooser = new JFileChooser();
				FileNameExtensionFilter xmlFilter = new FileNameExtensionFilter("xml File", "xml");
				chooser.setFileFilter(xmlFilter);
				
				int userSelection = chooser.showOpenDialog(RoadwaySim.this);
				
				//see if valid selection
				if (userSelection == JFileChooser.APPROVE_OPTION){
					dataFile = chooser.getSelectedFile();
				}
				else if (userSelection == JFileChooser.CANCEL_OPTION){
					return;
				}
				
				//Once file is selected, get the grid information
				readXML();
				
				isTile = true;
				mapPanel.repaint();
				
				//Now that we have grid information, repaint panel
//				mapPanel.repaint();
			}
		});

		//Adding Components
		//Menu Bar
		menuBar.add(openItem);
		
		//Add to JFrame
		setJMenuBar(menuBar);
		add(mapPanel, BorderLayout.CENTER);
		add(tableScroller, BorderLayout.EAST);

		//run the panel thread
		MapThread mapThread = new MapThread(mapPanel);
		mapThread.start();
		
		setVisible(true);
	}
	
	public static void main(String args[]){
		new RoadwaySim();
	}

	//Helpers
	private void readXML(){
		try{
			//Open xml as a document
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(dataFile);
			
			doc.getDocumentElement().normalize();
			
			//Get list of row nodes
			NodeList rList = doc.getElementsByTagName("row");
			
			for (int i = 0; i < rList.getLength(); ++i){
				Node rNode = rList.item(i);
				if (rNode.getNodeType() == Node.ELEMENT_NODE){
					Element rElement = (Element)rNode;
//					char row 	= rElement.getAttribute("label").charAt(0);
					
					//get list of column nodes
					NodeList cList = rElement.getElementsByTagName("tile");
					for (int j = 0; j < cList.getLength(); ++j){
						Node cNode = cList.item(j);
						if (cNode.getNodeType() == Node.ELEMENT_NODE){
							Element cElement = (Element)cNode;
//							int column 		= Integer.parseInt(cElement.getAttribute("column"));
//							String type		= cElement.getAttribute("type");
//							int degree		= Integer.parseInt(cElement.getAttribute("degree"));
							
							//Now make a tile object
							Tile newTile 	= new Tile(	rElement.getAttribute("label").charAt(0),
														Integer.parseInt(cElement.getAttribute("column")),
														cElement.getAttribute("type"),
														Integer.parseInt(cElement.getAttribute("degree")));
							GlobalData.tileData[j][i] 	= newTile; 
						}
					}
					
				}
			}
			
			//Now read information for cars
			NodeList cList = doc.getElementsByTagName("car");
			for (int i = 0; i < cList.getLength(); ++i){
				Node cNode = cList.item(i);
				if (cNode.getNodeType()== Node.ELEMENT_NODE);
				Element cElement = (Element)cNode;
				
				//get location
				NodeList lList = cElement.getElementsByTagName("location");

				Car newCar = new Car(	i,
										cElement.getAttribute("color"),
										Integer.parseInt(cElement.getAttribute("ai")),
										Double.parseDouble(cElement.getAttribute("speed")),
										Integer.parseInt(((Element)lList.item(0)).getAttribute("x")),
										(int)(((Element)lList.item(0)).getAttribute("y").charAt(0))-64);
				carArray.add(newCar);
				
				newCar.start();
			}
			
			//Set up table
			for (int i = 0; i < carArray.size(); ++i){
				GlobalData.model.addRow(new Object[] {""+(i+1),carArray.get(i).getX()+1,(char)(carArray.get(i).getY()+1+64)});
			}
			
		} catch (ParserConfigurationException PCE){
			PCE.printStackTrace();
		} catch (Exception E){
			E.printStackTrace();
		}
		
	}
	
	class MapThread extends Thread{
		private MapPanel mp;
		public MapThread(MapPanel mp){
			this.mp = mp;
		}
		public void run(){
			while (true){
				mp.repaint();
				try{
					sleep((long)(20));
				} catch (InterruptedException IE){
					System.out.println("Error: Interrupted");
					return;
				}
			}
		}
	}
	
	class MapPanel extends JPanel{
		static final long serialVersionUID = 1;

		public MapPanel(){
			super();
		}
		
		private void drawRoad(int i, int j, Graphics g){
			g.setColor(Color.BLACK);
			String type 	= GlobalData.tileData[i][j].getType();
			int degree 		= GlobalData.tileData[i][j].getDegree();
			int x 			= tileLoc[i][j].x;
			int y 			= tileLoc[i][j].y;
			if (type.equals("blank")){
				//no roads
			}
			else if (type.equals("+")){
				//cross roads
				g.fillRect(x+20, y, 10, 50);
				g.fillRect(x, y+20, 50, 10);
			}
			else if (type.equals("i")){
				if (degree == 0 || degree == 180){
					g.fillRect(x+20, y, 10, 50);
				}
				else{
					g.fillRect(x, y+20, 50, 10);
				}
			}
			else if (type.equals("l")){
				if (degree == 0){
					g.fillRect(x+20, y, 10, 30);
					g.fillRect(x+20, y+20, 30, 10);
				}
				else if (degree == 90){
					g.fillRect(x+20, y, 10, 30);
					g.fillRect(x, y+20, 30, 10);
				}
				else if (degree == 180){
					g.fillRect(x,y+20, 30, 10);
					g.fillRect(x+20, y+20, 10, 30);
				}
				else if (degree == 270){
					g.fillRect(x+20, y+20, 30, 10);
					g.fillRect(x+20, y+20, 10, 30);
				}
			}
			else if (type.equals("t")){
				if (degree == 0){
					g.fillRect(x, y+20, 50, 10);
					g.fillRect(x+20, y+20, 10, 30);
				}
				else if (degree == 90){
					g.fillRect(x+20, y, 10, 50);
					g.fillRect(x+20, y+20, 30, 10);
				}
				else if (degree == 180){
					g.fillRect(x+20,y, 10, 30);
					g.fillRect(x, y+20, 50, 10);
				}
				else if (degree == 270){
					g.fillRect(x+20, y, 10, 50);
					g.fillRect(x, y+20, 30, 10);
				}
			}
			else{
				System.out.println("UNEXPECTED TILE TYPE");
			}
		}
		
		private void drawCar(Graphics g){
			for (int i = 0; i < carArray.size(); ++i){
//			int i = 1;
				Car tempCar = carArray.get(i);
				//only paint it if it is lighted
				if (tempCar.isLit()){
					int x = tempCar.getX();
					int y = tempCar.getY();
					
					//Set color
					g.setColor(tempCar.getColor());
					g.fillOval(tileLoc[x][y].x+10, tileLoc[x][y].y+10, 30, 30);
					g.setColor(Color.WHITE);
					g.setFont(new Font("Helvetica", Font.BOLD, 24));
					g.drawString(""+(i+1), tileLoc[x][y].x+18, tileLoc[x][y].y+33);
				}
			}
			
		}
		
		public void paintComponent(Graphics g){
			super.paintComponent(g);
			
			//get dimensions
			Dimension panelDimension 	= this.getSize();
			final double width			= panelDimension.getWidth();
			final double height			= panelDimension.getHeight();
			
			//get location information
			double xChange	= (width-450)/2;
			double yChange	= (height-450)/2;
			final double xStart = xChange;
			final double yStart	= yChange;
			final double xEnd	= xStart + 450;
			final double yEnd	= yStart + 450;
			
			//Draw roads before drawing grid
			if (isTile){
				//get coordinates
				xChange = xStart;
				yChange = yStart;
				
				//Create coordinates
				for (int i = 0; i < 9; ++i){
					for (int j = 0; j < 9; ++j){
						tileLoc[i][j] = new GlobalData.Coor();
					}
				}
				
				//get the top left coordinates of every tile
				for (int i = 0; i < 9; ++i){
					for (int j = 0; j < 9; ++j){
						tileLoc[i][j].x = (int)xChange;
						tileLoc[i][j].y = (int)yChange;
						yChange += tileSize;
					}
					xChange += tileSize;
					yChange = yStart;
				}
				
				//Paint the tiles and roads after the tile
				for (int i = 0; i < 9; ++i){
					for (int j = 0; j < 9; ++j){
						g.setColor(Color.getHSBColor(blueH, blueS, blueB));
						g.fillRect(tileLoc[i][j].x, tileLoc[i][j].y, tileSize, tileSize);
						drawRoad(i, j, g);
					}
				}
				
				//And now we can draw cars
				drawCar(g);
				
			}
			
			//grid should be black
			g.setColor(Color.BLACK);
			xChange = xStart;
			yChange = yStart;
			for (int i = 0; i < 10; ++i){
				g.drawLine((int)xChange, (int)yStart, (int)xChange, (int)yEnd);
				g.drawLine((int)xStart, (int)yChange, (int)xEnd, (int)yChange);
				//Update next coordinates
				xChange += tileSize;
				yChange += tileSize;
			}
			
			//Also draw string
			//Be above xStart and yStart
			g.setFont(new Font("Helvetica", Font.PLAIN, 12));
			String[] rowValues = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};

			xChange = xStart + 20;
			yChange = yStart + 30;
			for (int i = 0; i < 9; ++i){
				g.drawString((""+(i+1)), (int)xChange, (int)yStart-10);
				xChange += tileSize;
				g.drawString(rowValues[i], (int)xStart-20, (int)yChange);
				yChange += tileSize;
			}
			

		}
	}
}
