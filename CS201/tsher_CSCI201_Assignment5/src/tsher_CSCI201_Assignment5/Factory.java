package tsher_CSCI201_Assignment5;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
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

import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

public class Factory extends JFrame{
	//Variables
	static final long serialVersionUID = 1;
	
	//Materials
	public static final int 	woodAmount 			= 1000;
	public static final int		metalAmount 		= 1000;
	public static final int		plasticAmount 		= 1000;
	public static final int		anvilAmount			= 2;
	public static final int		workbenchAmount		= 3;
	public static final int		furnaceAmount		= 2;
	public static final int		tablesawAmount		= 3;
	public static final int		paintingAmount		= 4;
	public static final int		pressAmount			= 1;
	public static final String	imageDirectory		= "assignment5images/";
	
	private int					hammersTotal, currentHammers;
	private int					screwdriversTotal, currentScrewdrivers;
	private int 				pliersTotal, currentPliers;
	private int					scissorsTotal, currentScissors;
	private int					paintbrushesTotal, currentPaintbrushes;
	private int					workersTotal, currentWorkers;

	private JMenuBar 			menuBar 			= new JMenuBar();
	private JMenuItem			openItem			= new JMenuItem("Open File...");
	
	private File 				factoryDirectory;
	private File 				factoryFile;
	
	private JScrollPane			taskScroller;
	private JTable 				taskTable;
	private DefaultTableModel 	model 				= new DefaultTableModel();
	
	//For factoryPanel
	private FactoryPanel		factoryPanel;
	RepaintThread rt;
	
	private ArrayList<Recipe> 	recipeList 			= new ArrayList<Recipe>();
	private ArrayList<Material> allMaterials 		= new ArrayList<Material>();
	
	private static GridBagConstraints 	gbc 		= new GridBagConstraints();
	
	Factory(String name){
		super(name);

		setSize(800,600);
		setLocation(200,100);
		
		//Task Board
		//Set up JTable
		taskTable = new JTable(model);
		model.addColumn("TASKBOARD");
		
		taskScroller = new JScrollPane(taskTable);
		taskScroller.setPreferredSize(new Dimension(200,600));
		
		openItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				
				//DEBUG
				factoryDirectory = new File("/Users/StephenTHSher/git_eclipse/tsher_CSCI201_Assignment5/FactoryInfo");
				
//				//Once file is selected, read the information
				if (readFiles()){
					//have file information, make factoryPanel
			 		factoryPanel = new FactoryPanel();
					add(factoryPanel, BorderLayout.CENTER);
					rt = new RepaintThread(factoryPanel);
					rt.start();

					//pass
				} else{
					System.out.println("Please check your factory directory");
				}
			}
		});
		
		menuBar.add(openItem);
		
		//Add to Frame
		setJMenuBar(menuBar);
		add(taskScroller, BorderLayout.EAST);
		
		setResizable(false);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
//	private addComponent(int x, int y, )
	
	private void setToolAmount(int amount, String tool){
		if (tool.equalsIgnoreCase("worker") || tool.equalsIgnoreCase("workers")){
			currentWorkers = workersTotal = amount;
		} else if (tool.equalsIgnoreCase("hammer") || tool.equalsIgnoreCase("hammers")){
			currentHammers = hammersTotal = amount;
		} else if (tool.equalsIgnoreCase("screwdrivers") || tool.equalsIgnoreCase("screwdriver")){
			currentScrewdrivers = screwdriversTotal = amount;
		} else if (tool.equalsIgnoreCase("pliers") || tool.equalsIgnoreCase("plier")){
			currentPliers = pliersTotal = amount;
		} else if (tool.equalsIgnoreCase("scissors") || tool.equalsIgnoreCase("scissor")){
			currentScissors = scissorsTotal = amount;
		} else if (tool.equalsIgnoreCase("paintbrushes") || tool.equalsIgnoreCase("paintbrush")){
			currentPaintbrushes = paintbrushesTotal = amount;
		} else{
			System.out.println("Unexpected tool in factory file");
		}
	}
	
	private boolean readFiles(){
		boolean existFactoryFile	= false;
		boolean existRecipeFile 	= false;
		for (File bufferFile: factoryDirectory.listFiles()){
			if (bufferFile.getName().contains(".factory")){
				if (!existFactoryFile){
					factoryFile = bufferFile;
					
					try{
						FileReader fr = new FileReader(bufferFile);
						BufferedReader br = new BufferedReader(fr);
						
						String line = "";
						
						//first line is worker amount
						for (int i = 0; i < 6; ++i){
							line = br.readLine();
							setToolAmount(Integer.parseInt((line.substring(line.indexOf(':')+1, line.indexOf(']')))), line.substring(1,line.indexOf(":")));
						}
						
					} catch (IOException IOE){
						IOE.printStackTrace();
					}
					//now read and parse the factory file
					
					existFactoryFile = true;
				} else{
					System.out.println("Can only have one .factory file");
					return false;
				}
			} else if (bufferFile.getName().contains(".rcp")){
				
				System.out.println("File: " + bufferFile.getName());
				
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
							System.out.println("Empty line");
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
								System.out.println("Already contains " + materialString);
							} else{
								allMaterials.add(newMaterial);
							}
							
							recipeMaterials.add(newMaterial);
						}
					}
					
					//Make new recipe and add it to list
					Recipe newRecipe = new Recipe(recipeName, recipeAmount, recipeMaterials, recipeInstructions);
					
					//add recipe number of times to be made, also populate table
					for (int i = 0; i < newRecipe.getAmount(); ++i){
						recipeList.add(newRecipe);
						model.addRow(new Object[] {newRecipe.getStatusMessage()});
					}
//					newRecipe.printRecipe();
					
						
				} catch (IOException IOE){
					IOE.printStackTrace();
				}
			}
		}
		
		if (!existFactoryFile || !existRecipeFile){
			System.out.println("You must have one .factory file and at least one .rcp file");
			return false;
		}
		
		return true;
	}
	
	
	public static void main(String[] args) {
		new Factory("Creative Factory");
	}

	class FactoryPanel extends JPanel{
		private JPanel		northPanel			= new JPanel();
		private JPanel		northSeparatorA		= new JPanel();
		private JPanel		northSeparatorB		= new JPanel();

		private ImageIcon	woodIcon, metalIcon, plasticIcon;
		
		private JPanel		westPanel			= new JPanel();
		private JLabel		screwdriverLabel	= new JLabel(new ImageIcon("assignment5images/screwdriver.png"));
		private JLabel		hammerLabel			= new JLabel(new ImageIcon("assignment5images/hammer.png"));
		private JLabel		paintbrushLabel		= new JLabel(new ImageIcon("assignment5images/paintbrush.png"));
		private JLabel		pliersLabel			= new JLabel(new ImageIcon("assignment5images/pliers.png"));
		private JLabel		scissorsLabel		= new JLabel(new ImageIcon("assignment5images/scissors.png"));
		private JLabel		screwdriverTitle	= new JLabel("  Screwdriver  ");
		private JLabel		hammerTitle			= new JLabel("  Hammer  ");
		private JLabel		paintbrushTitle		= new JLabel("  Paintbrush  ");
		private JLabel		pliersTitle			= new JLabel("  Pliers  ");
		private JLabel		scissorsTitle		= new JLabel("  Scissors  ");
		
		private JPanel		westSeparatorA		= new JPanel();
		private JPanel		westSeparatorB		= new JPanel();
		private JPanel		westSeparatorC		= new JPanel();
		private JPanel		westSeparatorD		= new JPanel();
		
		JComponent[] 		componentArray;
		
		private JLabel 		woodLabel			= new JLabel(new ImageIcon("assignment5images/wood.png"));
		private JLabel 		metalLabel			= new JLabel(new ImageIcon("assignment5images/metal.png"));
		private JLabel 		plasticLabel		= new JLabel(new ImageIcon("assignment5images/plastic.png"));
		private JLabel		woodTitle			= new JLabel("Wood");
		private JLabel		metalTitle			= new JLabel("Metal");
		private JLabel		plasticTitle		= new JLabel("Plastic");
		
		private String getToolCountString(int numLeft, String tool){
			if (tool.equalsIgnoreCase("hammers")){
				return ("" + numLeft + "/" + hammersTotal);
			} else if (tool.equalsIgnoreCase("screwdrivers")){
				return ("" + numLeft + "/" + screwdriversTotal);
			} else if (tool.equalsIgnoreCase("pliers")){
				return ("" + numLeft + "/" + pliersTotal);
			} else if (tool.equalsIgnoreCase("scissors")){
				return ("" + numLeft + "/" + scissorsTotal);
			} else if (tool.equalsIgnoreCase("paintbrushes")){
				return ("" + numLeft + "/" + paintbrushesTotal);
			} else {
				return "Wrong argument into getToolCountString";
			}
		}
		
		public FactoryPanel(){
			super();
			setSize(600,600);
			setLayout(new BorderLayout());
			setBackground(Color.WHITE);
			
			woodLabel.setHorizontalTextPosition(JLabel.CENTER);
			metalLabel.setHorizontalTextPosition(JLabel.CENTER);
			plasticLabel.setHorizontalTextPosition(JLabel.CENTER);
			
			northPanel.setBackground(Color.WHITE);
			northPanel.setLayout(new GridBagLayout());
			
			//Separators, each icon is 50 x 50
			northSeparatorA.setPreferredSize(new Dimension(75,50));
			northSeparatorB.setPreferredSize(new Dimension(75,50));
			northSeparatorA.setBackground(Color.WHITE);
			northSeparatorB.setBackground(Color.WHITE);
			
			gbc.gridx = 0;
			gbc.gridy = 0;
			northPanel.add(woodTitle, gbc);
			
			gbc.gridx = 2;
			gbc.gridy = 0;
			northPanel.add(metalTitle, gbc);
			
			gbc.gridx = 4;
			gbc.gridy = 0;
			northPanel.add(plasticTitle, gbc);
			
			gbc.gridx = 0;
			gbc.gridy = 1;
			northPanel.add(woodLabel, gbc);
			
			gbc.gridx = 1;
			gbc.gridy = 1;
			northPanel.add(northSeparatorA, gbc);
		
			gbc.gridx = 2;
			gbc.gridy = 1;
			northPanel.add(metalLabel, gbc);
			
			gbc.gridx = 3;
			gbc.gridy = 1;
			northPanel.add(northSeparatorB, gbc);
			
			gbc.gridx = 4;
			gbc.gridy = 1;
			northPanel.add(plasticLabel, gbc);
			
			//West section: Tools
			screwdriverLabel.setHorizontalTextPosition(JLabel.CENTER);
			hammerLabel.setHorizontalTextPosition(JLabel.CENTER);
			paintbrushLabel.setHorizontalTextPosition(JLabel.CENTER);
			pliersLabel.setHorizontalTextPosition(JLabel.CENTER);
			scissorsLabel.setHorizontalTextPosition(JLabel.CENTER);
			
			westSeparatorA.setBackground(Color.WHITE);
			westSeparatorB.setBackground(Color.WHITE);
			westSeparatorC.setBackground(Color.WHITE);
			westSeparatorD.setBackground(Color.WHITE);
			westSeparatorA.setPreferredSize(new Dimension(75, 25));
			westSeparatorB.setPreferredSize(new Dimension(75, 25));
			westSeparatorC.setPreferredSize(new Dimension(75, 25));
			westSeparatorD.setPreferredSize(new Dimension(75, 25));
			
			componentArray = new JComponent[] {	screwdriverTitle, 	screwdriverLabel, 	westSeparatorA,
												hammerTitle,		hammerLabel,		westSeparatorB,
												paintbrushTitle,	paintbrushLabel,	westSeparatorC,
												pliersTitle,		pliersLabel,		westSeparatorD,
												scissorsTitle,		scissorsLabel};
			
			westPanel.setBackground(Color.WHITE);
			westPanel.setLayout(new GridBagLayout());
			
			for (int i = 0; i < 14; ++i){
				gbc.gridx = 0;
				gbc.gridy = i;
				westPanel.add(componentArray[i], gbc);
			}
			
			add(northPanel, BorderLayout.NORTH);
			add(westPanel, BorderLayout.WEST);
			
		}
		public void paintComponent(Graphics g){
			super.paintComponent(g);
			//North section: materials
			woodLabel.setText("" + woodAmount);
			metalLabel.setText("" + metalAmount);
			plasticLabel.setText("" + plasticAmount);
			
			//Set the strings
			screwdriverLabel.setText(getToolCountString(currentScrewdrivers,"screwdrivers"));
			hammerLabel.setText(getToolCountString(currentHammers,"hammers"));
			paintbrushLabel.setText(getToolCountString(currentPaintbrushes,"paintbrushes"));
			pliersLabel.setText(getToolCountString(currentScrewdrivers,"screwdrivers"));
			scissorsLabel.setText(getToolCountString(currentScissors,"scissors"));

		}
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
					fp.repaint();
				} catch (InterruptedException IE){
					IE.printStackTrace();
				}
			}
		}
	}
	
	class WorkareaPanel extends JPanel{
		private JLabel iconLabel;
		private JLabel iconTitle;
		private int status = 0;
		public WorkareaPanel(String type){
			if (type.equalsIgnoreCase("anvil") || type.equalsIgnoreCase("anvils")){
				iconLabel = new JLabel(new ImageIcon("assignment5images/anvil.png"));
			} else if (type.equalsIgnoreCase("workbench") || type.equalsIgnoreCase("workbenches")){
				
			} else if (type.equalsIgnoreCase("furnace") || type.equalsIgnoreCase("furnaces")){
				
			} else if (type.equalsIgnoreCase("tablesaw") || type.equalsIgnoreCase("tablesaws")){
				
			} else if (type.equalsIgnoreCase("paintingstation") || type.equalsIgnoreCase("paintingstations")){
				
			} else if (type.equalsIgnoreCase("press") || type.equalsIgnoreCase("presses")){
				
			} else{
				System.out.println("Unexpected workarea");
			}
}


