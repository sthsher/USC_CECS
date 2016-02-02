package tsher_CSCI201_Assignment5;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

public class FactoryPanel extends JPanel{
	static final long serialVersionUID = 1;
	
	private Factory		factory;
	
	private JPanel		northPanel			= new JPanel();
	private JPanel		northSeparatorA		= new JPanel();
	private JPanel		northSeparatorB		= new JPanel();

	GridBagConstraints	gbc					= new GridBagConstraints();

	public JPanel 		glass;
	
	private JPanel		westPanel			= new JPanel();
	public JLabel		screwdriverLabel	= new JLabel(new ImageIcon(Factory.imageDirectory + "screwdriver.png"));
	public JLabel		hammerLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "hammer.png"));
	public JLabel		paintbrushLabel		= new JLabel(new ImageIcon(Factory.imageDirectory + "paintbrush.png"));
	public JLabel		pliersLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "pliers.png"));
	public JLabel		scissorsLabel		= new JLabel(new ImageIcon(Factory.imageDirectory + "scissors.png"));
	
	private JButton		storeButton			= new JButton(new ImageIcon(Factory.imageDirectory + "store.png"));
	
	private JLabel[]	toolLabelArray		= new JLabel[5];
	
	private JPanel		moneyPanel			= new JPanel();
	private JLabel		moneyTitle			= new JLabel("Money");
	private JLabel		moneyLabel			= new JLabel("$100");
	
	public JLabel		screwdriverTitle	= new JLabel("  Screwdriver  ");
	public JLabel		hammerTitle			= new JLabel("  Hammer  ");
	public JLabel		paintbrushTitle		= new JLabel("  Paintbrush  ");
	public JLabel		pliersTitle			= new JLabel("  Pliers  ");
	public JLabel		scissorsTitle		= new JLabel("  Scissors  ");
	
	private JPanel		factoryFillerA		= new JPanel();
	private JPanel		factoryFillerB		= new JPanel();
	
	private JPanel		centerPanel			= new JPanel();
	private JPanel		anvilPanel			= new JPanel();
	private JPanel		workbenchPanel		= new JPanel();
	private JPanel		furnacePanel		= new JPanel();
	private JPanel		tablesawPanel		= new JPanel();
	private JPanel		paintingStationPanel= new JPanel();
	private JPanel		pressPanel			= new JPanel();
	
	private JPanel		westSeparatorA		= new JPanel();
	private JPanel		westSeparatorB		= new JPanel();
	private JPanel		westSeparatorC		= new JPanel();
	private JPanel		westSeparatorD		= new JPanel();
	
	JComponent[] 		componentArray;
	
	private JLabel 		woodLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "wood.png"));
	private JLabel 		metalLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "metal.png"));
	private JLabel 		plasticLabel		= new JLabel(new ImageIcon(Factory.imageDirectory + "plastic.png"));
	private JLabel		woodTitle			= new JLabel("Wood");
	private JLabel		metalTitle			= new JLabel("Metal");
	private JLabel		plasticTitle		= new JLabel("Plastic");
	
	private String getToolCountString(int numLeft, String tool){
		if (tool.equalsIgnoreCase("hammers")){
			return ("" + numLeft + "/" + factory.totalToolArray[1]);
		} else if (tool.equalsIgnoreCase("screwdrivers")){
			return ("" + numLeft + "/" + factory.totalToolArray[0]);
		} else if (tool.equalsIgnoreCase("pliers")){
			return ("" + numLeft + "/" + factory.totalToolArray[3]);
		} else if (tool.equalsIgnoreCase("scissors")){
			return ("" + numLeft + "/" + factory.totalToolArray[4]);
		} else if (tool.equalsIgnoreCase("paintbrushes")){
			return ("" + numLeft + "/" + factory.totalToolArray[2]);
		} else {
			return "Wrong argument into getToolCountString";
		}
	}
	
	public FactoryPanel(Factory factory){
		super();
		this.factory = factory;
		glass = (JPanel)factory.getGlassPane();
		setSize(600,600);
		setLayout(new BorderLayout());
		setBackground(Color.WHITE);
		
		toolLabelArray[0] = screwdriverLabel;
		toolLabelArray[1] = hammerLabel;
		toolLabelArray[2] = paintbrushLabel;
		toolLabelArray[3] = pliersLabel;
		toolLabelArray[4] = scissorsLabel;
		
		woodLabel.setHorizontalTextPosition(JLabel.CENTER);
		metalLabel.setHorizontalTextPosition(JLabel.CENTER);
		plasticLabel.setHorizontalTextPosition(JLabel.CENTER);
		
		northPanel.setBackground(Color.WHITE);
		northPanel.setLayout(new GridBagLayout());
		
		//Setup moneyPanel
		moneyPanel.setBackground(Color.WHITE);
		moneyPanel.setLayout(new BorderLayout());
		moneyPanel.add(moneyTitle, BorderLayout.NORTH);
		moneyPanel.add(moneyLabel, BorderLayout.SOUTH);
		
		//Store button
		storeButton.setBorder(new LineBorder(Color.BLACK, 1));
		storeButton.addActionListener(new CardAction("storeCard", factory.cardPanel));
		storeButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				glass.setVisible(false);
			}
		});

		moneyTitle.setFont(new Font("Helvetica", Font.BOLD, 12));
		moneyLabel.setFont(new Font("Helvetica", Font.BOLD, 12));

		
		gbc.gridx = 0;
		gbc.gridy = 0;
		northPanel.add(moneyTitle, gbc);
		
		gbc.gridy = 1;
		northPanel.add(moneyLabel, gbc);
		
		gbc.gridx = 1;
		gbc.gridy = 1;
		gbc.insets.left = 20;
		gbc.insets.right = 0;
		northPanel.add(storeButton, gbc);
		
		gbc.insets.left = 10;
		gbc.insets.right = 50;
		
		gbc.gridx = 2;
		gbc.gridy = 0;
		northPanel.add(woodTitle, gbc);
		
		gbc.gridx = 2;
		gbc.gridy = 1;
		northPanel.add(woodLabel, gbc);
		
		gbc.insets.left = 50;
		gbc.insets.right = 50;
		
		gbc.gridx = 4;
		gbc.gridy = 0;
		northPanel.add(metalTitle, gbc);
		
		gbc.gridx = 4;
		gbc.gridy = 1;
		northPanel.add(metalLabel, gbc);
		
		gbc.gridx = 6;
		gbc.gridy = 0;
		northPanel.add(plasticTitle, gbc);
		
		gbc.gridx = 6;
		gbc.gridy = 1;
		northPanel.add(plasticLabel, gbc);
		
		gbc.insets.left = 0;
		gbc.insets.right = 0;
		
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
		
		//Now for workarea
		factoryFillerA.setPreferredSize(new Dimension(300,50));
		factoryFillerB.setPreferredSize(new Dimension(300,50));
		factoryFillerA.setBackground(Color.WHITE);
		factoryFillerB.setBackground(Color.WHITE);

		centerPanel.setLayout(new GridBagLayout());
		anvilPanel.setLayout(new GridBagLayout());
		workbenchPanel.setLayout(new GridBagLayout());
		furnacePanel.setLayout(new GridBagLayout());
		tablesawPanel.setLayout(new GridBagLayout());
		paintingStationPanel.setLayout(new GridBagLayout());
		pressPanel.setLayout(new GridBagLayout());
		
		centerPanel.setBackground(Color.WHITE);
		anvilPanel.setBackground(Color.WHITE);			
		workbenchPanel.setBackground(Color.WHITE);		
		furnacePanel.setBackground(Color.WHITE);		
		tablesawPanel.setBackground(Color.WHITE);		
		paintingStationPanel.setBackground(Color.WHITE);
		pressPanel.setBackground(Color.WHITE);			
		
		//Assumption: 	anvils and workbenches adds up to 5 units
		//				furnace and tablesaws adds up to 5 units
		//				painting stations and press adds up to 5 units
		
		int ID = 0;
		
		int xVal = 0;
		int yVal = 0;
		GridBagConstraints centerGBC = new GridBagConstraints();
		
		//Anvils
		centerGBC.ipadx = 20;
		centerGBC.gridwidth = 1;

		for (int i = 0; i < factory.anvilAmount; ++i){
			centerGBC.gridy = yVal;
			centerGBC.gridx = xVal++;
			WorkareaPanel workarea = new WorkareaPanel("anvil", ID++, factory);
			factory.allWorkareas.add(workarea);
			centerPanel.add(workarea, centerGBC);
		}

		centerGBC.ipadx = 0;
		centerGBC.ipady = 5;
		centerGBC.gridx = 0;
		centerGBC.gridy = yVal+1;
		centerGBC.gridwidth = factory.anvilAmount;
		centerPanel.add(new JLabel("Anvils"), centerGBC);
		

		//Workbenches
		centerGBC.ipadx = 20;
		centerGBC.gridwidth = 1;
		
		xVal += 0;
		for (int i = 0; i < factory.workbenchAmount; ++i){
			centerGBC.gridy = yVal;
			centerGBC.gridx = xVal++;
			WorkareaPanel workarea = new WorkareaPanel("workbench", ID++, factory);
			factory.allWorkareas.add(workarea);
			centerPanel.add(workarea, centerGBC);
		}

		centerGBC.ipadx = 0;
		centerGBC.ipady = 5;
		centerGBC.gridx = factory.anvilAmount;
		centerGBC.gridy = yVal+1;
		centerGBC.gridwidth = factory.workbenchAmount;
		centerPanel.add(new JLabel("Work Benches"), centerGBC);

		//Filler
		yVal += 2;			
		centerGBC.gridx = 0;
		centerGBC.gridy = yVal;
		centerGBC.gridwidth = factory.anvilAmount + factory.workbenchAmount;
		centerPanel.add(factoryFillerA, centerGBC);
		
		//set 2
		//Furnace
		yVal += 1;
		xVal = 0;
		centerGBC.ipadx = 20;
		centerGBC.gridwidth = 1;

		for (int i = 0; i < factory.furnaceAmount; ++i){
			centerGBC.gridy = yVal;
			centerGBC.gridx = xVal++;
			WorkareaPanel workarea = new WorkareaPanel("furnace", ID++, factory);
			factory.allWorkareas.add(workarea);
			centerPanel.add(workarea, centerGBC);
		}

		centerGBC.ipadx = 0;
		centerGBC.ipady = 5;
		centerGBC.gridx = 0;
		centerGBC.gridy = yVal+1;
		centerGBC.gridwidth = factory.furnaceAmount;
		centerPanel.add(new JLabel("Furnaces"), centerGBC);
		
		
		//Tablesaws
		centerGBC.ipadx = 20;
		centerGBC.gridwidth = 1;
		
		xVal += 0;
		for (int i = 0; i < factory.tablesawAmount; ++i){
			centerGBC.gridy = yVal;
			centerGBC.gridx = xVal++;
			WorkareaPanel workarea = new WorkareaPanel("Saw", ID++, factory);
			factory.allWorkareas.add(workarea);
			centerPanel.add(workarea, centerGBC);
		}

		centerGBC.ipadx = 0;
		centerGBC.ipady = 5;
		centerGBC.gridx = factory.furnaceAmount;
		centerGBC.gridy = yVal+1;
		centerGBC.gridwidth = factory.tablesawAmount;
		centerPanel.add(new JLabel("Tablesaws"), centerGBC);

		//Filler
		yVal += 2;			
		centerGBC.gridx = 0;
		centerGBC.gridy = yVal;
		centerGBC.gridwidth = factory.anvilAmount + factory.workbenchAmount;
		centerPanel.add(factoryFillerB, centerGBC);
		
		//set 3
		//Painting stations
		yVal += 1;
		xVal = 0;
		centerGBC.ipadx = 20;
		centerGBC.gridwidth = 1;

		for (int i = 0; i < factory.paintingAmount; ++i){
			centerGBC.gridy = yVal;
			centerGBC.gridx = xVal++;
			WorkareaPanel workarea = new WorkareaPanel("painting station", ID++, factory);
			factory.allWorkareas.add(workarea);
			centerPanel.add(workarea, centerGBC);
		}

		centerGBC.ipadx = 0;
		centerGBC.ipady = 5;
		centerGBC.gridx = 0;
		centerGBC.gridy = yVal+1;
		centerGBC.gridwidth = factory.paintingAmount;
		centerPanel.add(new JLabel("Painting Station"), centerGBC);
		
		
		//Workbenches
		centerGBC.ipadx = 20;
		centerGBC.gridwidth = 1;
		
		xVal += 0;
		for (int i = 0; i < factory.pressAmount; ++i){
			centerGBC.gridy = yVal;
			centerGBC.gridx = xVal++;
			WorkareaPanel workarea = new WorkareaPanel("press", ID++, factory);
			factory.allWorkareas.add(workarea);
			centerPanel.add(workarea, centerGBC);
		}

		centerGBC.ipadx = 0;
		centerGBC.ipady = 5;
		centerGBC.gridx = factory.paintingAmount;
		centerGBC.gridy = yVal+1;
		centerGBC.gridwidth = factory.pressAmount;
		centerPanel.add(new JLabel("Press"), centerGBC);
		

		add(centerPanel, BorderLayout.CENTER);
		add(northPanel, BorderLayout.NORTH);
		add(westPanel, BorderLayout.WEST);
		
		glass.setVisible(true);
		glass.setLayout(null);
		
		for (int i = 0; i < Factory.totalWorkers; ++i){
			WorkerObject tempWorker = factory.manager.getWorkerVector().get(i);
			glass.add(tempWorker);
			tempWorker.setBounds(tempWorker.x, tempWorker.y,50,50);
		}
		
	}
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		//North section: materials
		woodLabel.setText("" + factory.woodAmount);
		metalLabel.setText("" + factory.metalAmount);
		plasticLabel.setText("" + factory.plasticAmount);
		
		//Set the strings
		for (int i = 0; i < 5; ++i){
			toolLabelArray[i].setText(getToolCountString(factory.toolAmountArray[i],factory.toolStringArray[i]));
		}
		
		//Also update table
		for (int i = 0; i < factory.recipeList.size(); ++i){
			factory.model.setValueAt(factory.recipeList.get(i).getStatusMessage(), i, 0);
		}
	}
	
	void setMoneyLabel(int money){
		moneyLabel.setText("$" + money);
	}
}