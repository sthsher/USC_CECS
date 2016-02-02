package tsher_CSCI201_Assignment5;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Vector;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableModel;

public class Factory extends JFrame{
	static final long serialVersionUID = 1;
	
	//Money
	public int 					money				= 100;
	
	//Materials
	public static int 			woodAmount 			= 0;
	public static int			metalAmount 		= 0;
	public static int			plasticAmount 		= 0;
	public static int			woodImmediate 		= woodAmount;
	public static int			metalImmediate		= metalAmount;
	public static int			plasticImmediate	= plasticAmount;
	public static final int		anvilAmount			= 2;
	public static final int		workbenchAmount		= 3;
	public static final int		furnaceAmount		= 2;
	public static final int		tablesawAmount		= 3;
	public static final int		paintingAmount		= 4;
	public static final int		pressAmount			= 1;
	public static final String	imageDirectory		= "assignment5images/";
	
	//Coordinates
	public static final int		workerStartX		= 525;
	public static final int		workerStartY		= 90;
	public static final int		plasticX			= 510;
	public static final int		plasticY			= 35;
	public static final int		metalX				= 360;
	public static final int		metalY				= 35;
	public static final int		woodX				= 210;
	public static final int		woodY				= 35;
	
	public static final int		screwdriverX		= 75;
	public static final int		screwdriverY		= 135;
	public static final int		hammerX				= 75;
	public static final int		hammerY				= 225;
	public static final int		paintbrushX			= 75;
	public static final int		paintbrushY			= 315;
	public static final int		plierX				= 75;
	public static final int		plierY				= 405;
	public static final int		scissorX			= 75;
	public static final int		scissorY			= 495;
	
	public static final int		leftColumn			= 100;
	public static final int		bottomRow			= 525;
	public static final int		rightColumn			= 525;
	public static final int		topRow				= 85;
	
	public static final int		row1Walkway			= 235;
	public static final int		row2Walkway			= 380;
	public static final int		row1				= 160;
	public static final int		row2				= 305;
	public static final int 	row3				= 450;
	public static final int		column1				= 180;
	public static final int		column2				= 250;
	public static final int		column3				= 320;
	public static final int		column4				= 390;
	public static final int		column5				= 460;
	
	public static final int[]	columnCoorArray		= new int[] {column1, column2, column3, column4, column5};
	public static final int[]	rowCoorArray		= new int[] {row1, row2, row3};

	public int[] 				toolAmountArray		= new int[5];
	public int[]				totalToolArray		= new int[5];
	public static final String[]toolStringArray		= new String[]{"Screwdrivers", "Hammers", "Paintbrushes", "Pliers", "Scissors"};
	public static final int[]	toolCoordinateArrayX= new int[] {screwdriverX, hammerX, paintbrushX, plierX, scissorX};
	public static final int[]	toolCoordinateArrayY= new int[] {screwdriverY, hammerY, paintbrushY, plierY, scissorY};	
	
//	public static int			totalHammers;
//	public static int			totalScrewdrivers;
//	public static int 			totalPliers;
//	public static int			totalScissors;
//	public static int			totalPaintbrushes;
	public static int			totalWorkers;
	
	private JMenuBar 			menuBar 			= new JMenuBar();
	private JMenuItem			openItem			= new JMenuItem("Open File...");
	
	private File 				factoryDirectory;
	
	private JScrollPane			taskScroller;
	private JTable 				taskTable;
	DefaultTableModel 	model 				= new DefaultTableModel();

	//Card Layout
	public JPanel				cardPanel			= new JPanel();
	
	//For factoryPanel
	private JPanel				factoryCard			= new JPanel();
	private FactoryPanel		factoryPanel;
	private RepaintThread 		rt;
	
	//For storeCard
	private JPanel				storeCard;

	ArrayList<Recipe> 	recipeList 			= new ArrayList<Recipe>();
	private ArrayList<Material> allMaterials 		= new ArrayList<Material>();
	public static Vector<WorkareaPanel> allWorkareas= new Vector<WorkareaPanel>();
	
	private GridBagConstraints 	gbc 		= new GridBagConstraints();
	
	public static Manager manager;
	
	private Factory factory;
	
	//TEST
	public static Lock lock = new ReentrantLock();
	public static Condition GUIFinished = lock.newCondition();
	
	Factory(String name){
		super(name);
		factory = this;
		
		setSize(800,600);
		setLocation(200,100);
		
		//Initialize constants
		toolCoordinateArrayX[0] = screwdriverX;
		toolCoordinateArrayX[1] = hammerX;
		toolCoordinateArrayX[2] = paintbrushX;
		toolCoordinateArrayX[3] = plierX;
		toolCoordinateArrayX[4] = scissorX;
			
		toolCoordinateArrayY[0] = screwdriverY;
		toolCoordinateArrayY[1] = hammerY;
		toolCoordinateArrayY[2] = paintbrushY;
		toolCoordinateArrayY[3] = plierY;
		toolCoordinateArrayY[4] = scissorY;


		
		//Task Board
		//Set up JTable
		taskTable = new JTable(model);
		model.addColumn("TASKBOARD");
		
		taskScroller = new JScrollPane(taskTable);
		taskScroller.setPreferredSize(new Dimension(200,600));
		
		openItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
//				JFileChooser chooser = new JFileChooser();
//				chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
//				
//				int userSelection = chooser.showOpenDialog(Factory.this);
//				
//				if (userSelection == JFileChooser.APPROVE_OPTION){
//					factoryDirectory = chooser.getSelectedFile();
//				} else if (userSelection == JFileChooser.CANCEL_OPTION){
//					return;
//				}
				//DEBUG
				factoryDirectory = new File("/Users/StephenTHSher/git_eclipse/tsher_CSCI201_Assignment5/FactoryInfo");
				
//				//Once file is selected, read the information
				if (readFiles()){
					//Read all the files, make manager
					manager = new Manager(totalWorkers, recipeList, factory);

					
					//have file information, make factoryPanel
			 		factoryPanel = new FactoryPanel(factory);
			 		
			 		storeCard = new StoreCard(factory, factoryPanel);
					cardPanel.add(storeCard, "storeCard");

					factoryCard.add(factoryPanel, BorderLayout.CENTER);
					
					//Wait until factoryPanel is finished adding components
					rt = new RepaintThread(factoryPanel);
					rt.start();
					
					//Start assigning jobs
					manager.start();
					
					
				} else{
					System.out.println("Please check your factory directory");
				}
			}
		});
		
		menuBar.add(openItem);
		
 		cardPanel.setLayout(new CardLayout());
		
		//Add to Frame
		setJMenuBar(menuBar);
		factoryCard.setLayout(new BorderLayout());
		factoryCard.add(taskScroller, BorderLayout.EAST);
		
		cardPanel.add(factoryCard, "factoryCard");
		
		add(cardPanel, BorderLayout.CENTER);
		
		setResizable(false);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	private void setToolAmount(int amount, String tool){
		if (tool.equalsIgnoreCase("worker") || tool.equalsIgnoreCase("workers")){
			totalWorkers = amount;
		} else if (tool.equalsIgnoreCase("screwdrivers") || tool.equalsIgnoreCase("screwdriver")){
//			totalScrewdrivers = amount;
			toolAmountArray[0] = amount;
			totalToolArray[0] = amount;
		} else if (tool.equalsIgnoreCase("hammer") || tool.equalsIgnoreCase("hammers")){
//			totalHammers = amount;
			toolAmountArray[1] = amount;
			totalToolArray[1] = amount;
		} else if (tool.equalsIgnoreCase("paintbrushes") || tool.equalsIgnoreCase("paintbrush")){
//			totalPaintbrushes = amount;
			toolAmountArray[2] = amount;
			totalToolArray[2] = amount;
		}else if (tool.equalsIgnoreCase("pliers") || tool.equalsIgnoreCase("plier")){
//			totalPliers = amount;
			toolAmountArray[3] = amount;
			totalToolArray[3] = amount;
		} else if (tool.equalsIgnoreCase("scissors") || tool.equalsIgnoreCase("scissor")){
//			totalScissors = amount;
			toolAmountArray[4] = amount;
			totalToolArray[4] = amount;
		} else{
			System.out.println("Unexpected tool in factory file");
		}
	}
	
	private boolean readFiles(){
		boolean existFactoryFile	= false;
		boolean existRecipeFile 	= false;
		
		//No factory file, initialize all values
		int initialAmount = 0;
		totalWorkers = initialAmount;
//		totalScrewdrivers = initialAmount;
//		totalHammers = initialAmount;
//		totalPaintbrushes = initialAmount;
//		totalPliers = initialAmount;
//		totalScissors = initialAmount;
		
		for (int i = 0; i < 5; ++i){
			toolAmountArray[i] = initialAmount;
			totalToolArray[i] = initialAmount;
		}
		
		for (File bufferFile: factoryDirectory.listFiles()){
//			if (bufferFile.getName().contains(".factory")){
//				if (!existFactoryFile){
//					
//					try{
//						FileReader fr = new FileReader(bufferFile);
//						BufferedReader br = new BufferedReader(fr);
//						
//						String line = "";
//						
//						//first line is worker amount
//						for (int i = 0; i < 6; ++i){
//							line = br.readLine();
//							setToolAmount(Integer.parseInt((line.substring(line.indexOf(':')+1, line.indexOf(']')))), line.substring(1,line.indexOf(":")));
//						}
//						br.close();
//					} catch (IOException IOE){
//						IOE.printStackTrace();
//					}
//					//now read and parse the factory file
//					
//					existFactoryFile = true;
//				} else{
//					System.out.println("Can only have one .factory file");
//					return false;
//				}
//			}
			if (bufferFile.getName().contains(".rcp")){
				
				existRecipeFile = true;
				//Read in recipe
				try{
					FileReader fr = new FileReader(bufferFile);
					BufferedReader br = new BufferedReader(fr);
					String line = "";
					line = br.readLine();
					
					//Read the lines
					//First line is always name and amount
					String amountString = (line.substring(line.indexOf(']')+3, line.length()));
					String modifiedAmountString = "";
					for (int i = 0; i < amountString.length(); ++i){
						if (amountString.charAt(i) != ' '){
							//add it
							modifiedAmountString += amountString.charAt(i);
						} else{
							break;
						}
					}
					int recipeAmount = Integer.parseInt(modifiedAmountString);
					
					int beginIndex = line.indexOf('[')+1;
					int endIndex = line.indexOf(']');
					String recipeName = line.substring(beginIndex, endIndex);
					
					ArrayList<Material> recipeMaterials = new ArrayList<Material>();
					ArrayList<String> recipeInstructions = new ArrayList<String>();

					
					while ((line = br.readLine()) != null){
						if (line.contains("[Use")){
							//Instruction line;
							recipeInstructions.add(line);
						} else if (line.equals("")){

						} else{
							//Material line
							beginIndex = line.indexOf('[')+1;
							endIndex = line.indexOf(':');
							int materialAmount = Integer.parseInt(line.substring(endIndex+1, line.indexOf(']')));
							String materialString = line.substring(beginIndex, endIndex);
							
							//make new material
							Material newMaterial = new Material(materialString, materialAmount);
							
							//add to allMaterials and recipeMaterials
							if(allMaterials.contains(newMaterial)){
								//already contains, don't add
							} else{
								allMaterials.add(newMaterial);
							}
							
							recipeMaterials.add(newMaterial);
						}
					}
					
					br.close();
					
					//add recipe number of times to be made, also populate table
					for (int i = 0; i < recipeAmount; ++i){
						Recipe newRecipe = new Recipe(recipeName, recipeMaterials, recipeInstructions);
						recipeList.add(newRecipe);
						model.addRow(new Object[] {newRecipe.getStatusMessage()});
					}
						
				} catch (IOException IOE){
					IOE.printStackTrace();
				}
			}
		}
		
		if (!existRecipeFile){
			System.out.println("You must have least one .rcp file");
			return false;
		}
		
		return true;
	}
	
	public void setMoney(int money){
		this.money = money;
		factoryPanel.setMoneyLabel(money);
	}
	
	public void deductMoney(int deduct){
		this.money -= deduct;
		factoryPanel.setMoneyLabel(this.money);
	}

	public void addMoney(int add){
		this.money += add;
		factoryPanel.setMoneyLabel(this.money);
	}
	
	public int getMoney(){
		return money;
	}
	
	public JPanel getGlass(){
		return factoryPanel.glass;
	}
	
	public void setGlassVisible(){
		factoryPanel.glass.setVisible(true);
	}
	
	public static void main(String[] args) {
		new Factory("Creative Factory");
	}

	public void addWorker(){
		totalWorkers++;
		deductMoney(15);
		manager.addWorker();
	}
	
	public void fireWorker(){
		manager.fireWorker();
	}
	
	class RepaintThread extends Thread{
		private FactoryPanel fp;
		
		public RepaintThread(FactoryPanel fp){
			this.fp = fp;
		}
		
		public void run(){
			while (true){
				try{
					sleep(1000/24);
					int size = recipeList.size();
					for (int i = 0; i < size; ++i){
						if (recipeList.get(i).getStatus() == 2){
							recipeList.remove(i);
							model.removeRow(i);
							--size;
							manager.recipeCount--;
						}
					}
					fp.repaint();
				} catch (InterruptedException IE){
					IE.printStackTrace();
				}
			}
		}
	}
	
}

class CardAction implements ActionListener{
	private String cardString;
	private JPanel panel;
	public CardAction(String cardString, JPanel panel){
		this.cardString = cardString;
		this.panel = panel;
	}
	public void actionPerformed(ActionEvent ae){
		CardLayout cl = (CardLayout)panel.getLayout();
		cl.show(panel, cardString);
	}
}

