package tsher_CSCI201_Assignment5;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

public class StoreCard extends JPanel {
	private Factory factory;
	private FactoryPanel fp;
	
	//Components
	//Money
		private JPanel 	moneyPanel		= new JPanel();
		private JLabel 	moneyTitle		= new JLabel("Money");
		private JLabel 	moneyLabel		= new JLabel();
	
	private JButton		backButton		= new JButton(new ImageIcon(Factory.imageDirectory + "back.png"));
		
	//Layout
		private GridBagConstraints gbc	= new GridBagConstraints();
		
	//Labels
	public JLabel		screwdriverLabel		= new JLabel(new ImageIcon(Factory.imageDirectory + "screwdriver.png"));
		private JLabel	screwdriverBuyLabel 	= new JLabel("$10");
		private JLabel	screwdriverSellLabel	= new JLabel("$7");
	public JLabel		hammerLabel				= new JLabel(new ImageIcon(Factory.imageDirectory + "hammer.png"));
		private JLabel	hammerBuyLabel 			= new JLabel("$12");
		private JLabel	hammerSellLabel			= new JLabel("$9");
	public JLabel		paintbrushLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "paintbrush.png"));
		private JLabel	paintbrushBuyLabel 		= new JLabel("$5");
		private JLabel	paintbrushSellLabel		= new JLabel("$3");
	public JLabel		pliersLabel				= new JLabel(new ImageIcon(Factory.imageDirectory + "pliers.png"));
		private JLabel	plierBuyLabel 			= new JLabel("$11");
		private JLabel	plierSellLabel			= new JLabel("$9");
	public JLabel		scissorsLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "scissors.png"));
		private JLabel	scissorBuyLabel 		= new JLabel("$9");
		private JLabel	scissorSellLabel		= new JLabel("$7");
	
	public JLabel		screwdriverTitle		= new JLabel("  Screwdriver  ");
	public JLabel		hammerTitle				= new JLabel("  Hammer  ");
	public JLabel		paintbrushTitle			= new JLabel("  Paintbrush  ");
	public JLabel		pliersTitle				= new JLabel("  Pliers  ");
	public JLabel		scissorsTitle			= new JLabel("  Scissors  ");
	public JLabel		woodTitle				= new JLabel("  Wood  ");
	public JLabel		metalTitle				= new JLabel("  Metal  ");
	public JLabel		plasticTitle			= new JLabel("  Plastic  ");
	public JLabel		workerTitle				= new JLabel("  Worker  ");
	public JLabel		 workerAmountLabel 		= new JLabel();

	
	public JLabel		woodLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "wood.png"));
		private JLabel	woodBuyLabel 		= new JLabel("$1");
		private JLabel	woodSellLabel		= new JLabel("$1");
	public JLabel		metalLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "metal.png"));
		private JLabel	metalBuyLabel 		= new JLabel("$3");
		private JLabel	metalSellLabel		= new JLabel("$2");	
	public JLabel		plasticLabel		= new JLabel(new ImageIcon(Factory.imageDirectory + "plastic.png"));
		private JLabel	plasticBuyLabel 	= new JLabel("$2");
		private JLabel	plasticSellLabel	= new JLabel("$1");		
	public JLabel		workerLabel			= new JLabel(new ImageIcon(Factory.imageDirectory + "worker.png"));
		private JLabel	workerBuyLabel	 	= new JLabel("$15");
		private JLabel	workerSellLabel		= new JLabel("$15");
		
		
	public StoreCard(Factory factory, FactoryPanel fp){
		this.factory = factory;
		this.fp = fp;
		
		//Money Panel
		moneyLabel.setText("$" + factory.getMoney());
		moneyPanel.setLayout(new BorderLayout());
		moneyPanel.add(moneyTitle, BorderLayout.NORTH);
		moneyPanel.add(moneyLabel, BorderLayout.SOUTH);
		
		//Back Button
		backButton.setBackground(null);
		backButton.setBorder(new LineBorder(Color.BLACK, 1));
		backButton.addActionListener(new CardAction("factoryCard", factory.cardPanel));
		backButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				factory.setGlassVisible();
			}
		});
		
		RepaintThread rt = new RepaintThread();
		rt.start();
		
		setLayout(new GridBagLayout());
		
		//Top row
		gbc.insets.left = 10;
		gbc.insets.right = 10;
		
		gbc.gridx = 0;
		gbc.gridy = 0;
		
		add(moneyPanel, gbc);
		
		gbc.gridx = 1;
		add(backButton, gbc);
		
		//Second row
		//Screwdriver
		gbc.gridwidth = 2;
		gbc.gridx = 0;
		gbc.gridy = 1;
		add(screwdriverTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 2;
		screwdriverLabel.setHorizontalTextPosition(JLabel.CENTER);
		add(screwdriverLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 2;
		gbc.gridy = 2;
		add(screwdriverBuyLabel, gbc);
		
		gbc.gridx = 3;
		add(new BuyButton(0, 10), gbc);
		
		gbc.gridx = 2;
		gbc.gridy = 3;
		add(screwdriverSellLabel, gbc);
		
		gbc.gridx = 3;
		add(new SellButton(0, 7), gbc);
		
		//Hammer
		gbc.gridwidth = 2;
		gbc.gridx = 0;
		gbc.gridy = 4;
		add(hammerTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 5;
		hammerLabel.setHorizontalTextPosition(JLabel.CENTER);
		add(hammerLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 2;
		gbc.gridy = 5;
		add(hammerBuyLabel, gbc);
		
		gbc.gridx = 3;
		add(new BuyButton(1, 12), gbc);
		
		gbc.gridx = 2;
		gbc.gridy = 6;
		add(hammerSellLabel, gbc);
		
		gbc.gridx = 3;
		add(new SellButton(1, 9), gbc);
		
		//Paintbrush
		gbc.gridwidth = 2;
		gbc.gridx = 0;
		gbc.gridy = 7;
		add(paintbrushTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 8;
		paintbrushLabel.setHorizontalTextPosition(JLabel.CENTER);
		add(paintbrushLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 2;
		gbc.gridy = 8;
		add(paintbrushBuyLabel, gbc);
		
		gbc.gridx = 3;
		add(new BuyButton(2, 5), gbc);
		
		gbc.gridx = 2;
		gbc.gridy = 9;
		add(paintbrushSellLabel, gbc);
		
		gbc.gridx = 3;
		add(new SellButton(2, 3), gbc);
		
		//Pliers
		gbc.gridwidth = 2;
		gbc.gridx = 0;
		gbc.gridy = 10;
		add(pliersTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 11;
		pliersLabel.setHorizontalTextPosition(JLabel.CENTER);
		add(pliersLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 2;
		gbc.gridy = 11;
		add(plierBuyLabel, gbc);
		
		gbc.gridx = 3;
		add(new BuyButton(3, 11), gbc);
		
		gbc.gridx = 2;
		gbc.gridy = 12;
		add(plierSellLabel, gbc);
		
		gbc.gridx = 3;
		add(new SellButton(3, 9), gbc);
		
		//Scissors
		gbc.gridwidth = 2;
		gbc.gridx = 0;
		gbc.gridy = 13;
		add(scissorsTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 14;
		scissorsLabel.setHorizontalTextPosition(JLabel.CENTER);
		add(scissorsLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 2;
		gbc.gridy = 14;
		add(scissorBuyLabel, gbc);
		
		gbc.gridx = 3;
		add(new BuyButton(4, 9), gbc);
		
		gbc.gridx = 2;
		gbc.gridy = 15;
		add(scissorSellLabel, gbc);
		
		gbc.gridx = 3;
		add(new SellButton(4, 7), gbc);
		
		//Wood
		gbc.gridwidth = 2;
		gbc.gridx = 4;
		gbc.gridy = 1;
		add(woodTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 2;
		woodLabel.setHorizontalTextPosition(JLabel.CENTER);
		add(woodLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 6;
		gbc.gridy = 2;
		add(woodBuyLabel, gbc);
		
		gbc.gridx = 7;
		add(new BuyButton(5, 1), gbc);
		
		gbc.gridx = 6;
		gbc.gridy = 3;
		add(woodSellLabel, gbc);
		
		gbc.gridx = 7;
		add(new SellButton(5, 1), gbc);
		
		//Metal
		gbc.gridwidth = 2;
		gbc.gridx = 4;
		gbc.gridy = 4;
		add(metalTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 5;
		metalLabel.setHorizontalTextPosition(JLabel.CENTER);
		add(metalLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 6;
		gbc.gridy = 5;
		add(metalBuyLabel, gbc);
		
		gbc.gridx = 7;
		add(new BuyButton(6, 3), gbc);
		
		gbc.gridx = 6;
		gbc.gridy = 6;
		add(metalSellLabel, gbc);
		
		gbc.gridx = 7;
		add(new SellButton(6, 2), gbc);
		
		//Plastic
		gbc.gridwidth = 2;
		gbc.gridx = 4;
		gbc.gridy = 7;
		add(plasticTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 8;
		plasticLabel.setHorizontalTextPosition(JLabel.CENTER);
		add(plasticLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 6;
		gbc.gridy = 8;
		add(plasticBuyLabel, gbc);
		
		gbc.gridx = 7;
		add(new BuyButton(7, 2), gbc);
		
		gbc.gridx = 6;
		gbc.gridy = 9;
		add(plasticSellLabel, gbc);
		
		gbc.gridx = 7;
		add(new SellButton(7, 1), gbc);
		
		//Worker
		workerAmountLabel.setText("" + Factory.totalWorkers);
		gbc.gridwidth = 2;
		gbc.gridx = 4;
		gbc.gridy = 12;
		add(workerTitle, gbc);
		
		gbc.gridheight = 2;
		gbc.gridy = 13;
		add(workerLabel, gbc);
		
		gbc.gridheight = 1;
		gbc.gridwidth = 1;
		gbc.gridx = 6;
		gbc.gridy = 13;
		add(workerBuyLabel, gbc);
		
		gbc.gridx = 7;
		add(new BuyButton(8, 15), gbc);
		
		gbc.gridx = 6;
		gbc.gridy = 14;
		add(workerSellLabel, gbc);
		
		gbc.gridx = 7;
		add(new SellButton(8, 15), gbc);
		
		gbc.gridx = 5;
		gbc.gridy++;
		add(workerAmountLabel, gbc);
		
		
	}

	class BuyButton extends JButton{
		private int toolID;
		private int price;
		//screwdriver
		//hammer
//		paintbrush
//		pliers
//		scissors
//		wood
//		metal
//		plastic
//		worker
		public BuyButton(int toolID, int price){
			super("Buy");
			this.price = price;
			this.toolID = toolID;
		
			this.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent ae){
					if (price < factory.getMoney()){
						if (toolID == 0){
							factory.toolAmountArray[0]++;
							factory.totalToolArray[0]++;
							Factory.manager.addTool(0);
							factory.deductMoney(price);
						} else if (toolID == 1){
							factory.toolAmountArray[1]++;
							factory.totalToolArray[1]++;
							Factory.manager.addTool(1);
							factory.deductMoney(price);						
						} else if (toolID == 2){
							factory.toolAmountArray[2]++;
							factory.totalToolArray[2]++;
							Factory.manager.addTool(2);
							factory.deductMoney(price);
						} else if (toolID == 3){
							factory.toolAmountArray[3]++;
							factory.totalToolArray[3]++;
							Factory.manager.addTool(3);
							factory.deductMoney(price);
						} else if (toolID == 4){
							factory.toolAmountArray[4]++;
							factory.totalToolArray[4]++;
							Factory.manager.addTool(4);
							factory.deductMoney(price);
						} else if (toolID == 5){
							Factory.woodAmount++;
							Factory.woodImmediate++;
							factory.deductMoney(price);
						} else if (toolID == 6){
							Factory.metalAmount++;
							Factory.metalImmediate++;
							factory.deductMoney(price);
						} else if (toolID == 7){
							Factory.plasticAmount++;
							Factory.plasticImmediate++;
							factory.deductMoney(price);
						} else if (toolID == 8){
							factory.addWorker();
						}
						moneyLabel.setText("$" + factory.getMoney());

					}
				}
			});
		
		}
		
	}
	
	class SellButton extends JButton{
		private int toolID;
		private int price;
		//screwdriver
		//hammer
//		paintbrush
//		pliers
//		scissors
//		wood
//		metal
//		plastic
//		worker
		public SellButton(int toolID, int price){
			super("Sell");
			this.price = price;
			this.toolID = toolID;
		
			this.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent ae){
					if (toolID == 0 && factory.toolAmountArray[0] > 0){
						factory.toolAmountArray[0]--;
						factory.totalToolArray[0]--;
						Factory.manager.removeTool(0);
						factory.addMoney(price);
					} else if (toolID == 1 && factory.toolAmountArray[1] > 0){
						factory.toolAmountArray[1]--;
						factory.totalToolArray[1]--;
						Factory.manager.removeTool(1);
						factory.addMoney(price);
					} else if (toolID == 2 && factory.toolAmountArray[2] > 0){
						factory.toolAmountArray[2]--;
						factory.totalToolArray[2]--;
						Factory.manager.removeTool(2);
						factory.addMoney(price);
					} else if (toolID == 3 && factory.toolAmountArray[3] > 0){
						factory.toolAmountArray[3]--;
						factory.totalToolArray[3]--;
						Factory.manager.removeTool(3);
						factory.addMoney(price);
					} else if (toolID == 4 && factory.toolAmountArray[4] > 0){
						factory.toolAmountArray[4]--;
						factory.totalToolArray[4]--;
						Factory.manager.removeTool(4);
						factory.addMoney(price);
					} else if (toolID == 5 && Factory.woodAmount > 0){
						Factory.woodAmount--;
						Factory.woodImmediate--;
						factory.addMoney(price);
					} else if (toolID == 6 && Factory.metalAmount > 0){
						Factory.metalAmount--;
						Factory.metalImmediate--;
						factory.addMoney(price);
					} else if (toolID == 7 && Factory.plasticAmount > 0){
						Factory.plasticAmount--;
						Factory.plasticImmediate--;
						factory.addMoney(price);
					} else if (toolID == 8 && Factory.totalWorkers > 0){
						factory.fireWorker();
					}
					moneyLabel.setText("$" + factory.getMoney());

				}
			});
		
		}
		
	}
	
	class RepaintThread extends Thread{
		
		public RepaintThread(){
			
		}
		
		public void run(){
			while (true){
				try{
					sleep(1000/24);
					woodLabel.setText("" + Factory.woodAmount);
					metalLabel.setText("" + Factory.metalAmount);
					plasticLabel.setText("" + Factory.plasticAmount);
					workerAmountLabel.setText("" + Factory.totalWorkers);
					screwdriverLabel.setText("" + factory.totalToolArray[0]);
					hammerLabel.setText("" + factory.totalToolArray[1]);
					paintbrushLabel.setText("" + factory.totalToolArray[2]);
					pliersLabel.setText("" + factory.totalToolArray[3]);
					scissorsLabel.setText("" + factory.totalToolArray[4]);

				} catch (InterruptedException IE){
					IE.printStackTrace();
				}
			}
		}
	}
	
}
