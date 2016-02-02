package Restaurant;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class Restaurant extends JFrame {

	private static final long serialVersionUID = 1L;
	private static JTextArea jtaMessages;
	private JComboBox<Integer> jcbNumWaiters, jcbNumBusboys, jcbNumTables, jcbNumTablesPerWaiter, jcbNumTablesPerBusboy;
	private JButton jbRestaurant;
	private CustomerFactory customerFactory;
	public static BusboyFactory busboyFactory;
	private static WaiterFactory waiterFactory;
	private JPanel waitersPanel;
	private static JTextArea jtaWaiters[];
	
	//Lab 12
	public static int numOfBusboys;
	public static int numOfBusboysPerTable;
	
	private JLabel openTableLabel = new JLabel("Opened Tables");
	public static JLabel openTableContents = new JLabel("");
	
	private JLabel closeTableLabel = new JLabel("Closed Tables");
	public static JLabel closeTableContents = new JLabel("");

	
	public Restaurant() {
		super("CSCI 201 Synchronization");
		
		JPanel jp = new JPanel();
		jp.setLayout(new GridBagLayout());

		Integer [] numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
		jcbNumWaiters = new JComboBox<Integer>(numbers);
		jcbNumBusboys = new JComboBox<Integer>(numbers);
		jcbNumTables = new JComboBox<Integer>(numbers);
		jcbNumTablesPerWaiter = new JComboBox<Integer>(numbers);
		jcbNumTablesPerBusboy = new JComboBox<Integer>(numbers);
		
		JLabel jlNumWaiters = new JLabel("Number of Waiters");
		addComboBox(jp, jlNumWaiters, jcbNumWaiters, 0, 0);
		JLabel jlNumTablesPerWaiter = new JLabel("Number of Tables Per Waiter");
		addComboBox(jp, jlNumTablesPerWaiter, jcbNumTablesPerWaiter, 0, 1);
		JLabel jlNumBusboys = new JLabel("Number of Busboys");
		addComboBox(jp, jlNumBusboys, jcbNumBusboys, 2, 0);
		JLabel jlNumTablesPerBusboy = new JLabel("Number of Busboys Per Table");
		addComboBox(jp, jlNumTablesPerBusboy, jcbNumTablesPerBusboy, 2, 1);
		JLabel jlNumTables = new JLabel("Number of Tables");
		addComboBox(jp, jlNumTables, jcbNumTables, 0, 2);
		
		jbRestaurant = new JButton("Start Restaurant");
		addComponent(jp, jbRestaurant, 2, 2, GridBagConstraints.CENTER, 2, 1);
		
		addComponent(jp, openTableLabel, 0, 3, GridBagConstraints.CENTER, 2, 1);
		addComponent(jp, openTableContents, 0, 4, GridBagConstraints.CENTER, 2, 2);

		addComponent(jp, closeTableLabel, 1, 3, GridBagConstraints.CENTER, 2, 1);
		addComponent(jp, closeTableContents, 1, 4, GridBagConstraints.CENTER, 2, 2);

		
//		jp.add(openTableLabel, c);
		
		jbRestaurant.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				if (jbRestaurant.getText().equals("Start Restaurant")) {
					if (waitersPanel != null) {
						remove(waitersPanel);
					}
					addMessage("Number of tables: " + getNumTables());
					addMessage("Number of waiters: " + getNumWaiters());
					addMessage("Number of tables per waiter: " + getNumTablesPerWaiter());
					addMessage("Number of busboys: " + getNumBusboys());
					numOfBusboys = getNumBusboys();
					addMessage("Number of tables per busboy: " + getNumTablesPerBusboy());
					numOfBusboysPerTable = getNumTablesPerBusboy();
					addMessage("RESTAURANT STARTED");
					addMessage("***********************************");
					jbRestaurant.setText("Stop Restaurant");

					jtaWaiters = new JTextArea[getNumWaiters()];
					waitersPanel = new JPanel();
					waitersPanel.setLayout(new GridLayout(1, getNumWaiters()));
					for (int i=0; i < getNumWaiters(); i++) {
						jtaWaiters[i] = new JTextArea("", 10, 10);
						JScrollPane jsp = new JScrollPane(jtaWaiters[i]);
						waitersPanel.add(jsp);
					}
					add(waitersPanel, BorderLayout.SOUTH);

					
					// MULTI-THREADING PART OF CODE
					Hostess ht = new Hostess(getNumTables());
					waiterFactory = new WaiterFactory(ht, getNumWaiters(), getNumTablesPerWaiter());
					busboyFactory = new BusboyFactory(ht, getNumBusboys());
					
					customerFactory = new CustomerFactory(ht);

				}
				else if (jbRestaurant.getText().equals("Stop Restaurant")) {
					addMessage("RESTAURANT STOPPED");
					addMessage("***********************************");
					//remove(waitersPanel);
					customerFactory.interrupt();
					jbRestaurant.setText("Start Restaurant");
				}
			}
		});
		
		jtaMessages = new JTextArea("", 20, 40);
		jtaMessages.setLineWrap(false);
		jtaMessages.setFont(new Font("Arial",Font.PLAIN, 12));
		JScrollPane jsp = new JScrollPane(jtaMessages);
		
		
		add(jp, BorderLayout.NORTH);
		add(jsp, BorderLayout.CENTER);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(500, 500);
		setVisible(true);
		
	}
	
	public void addClosedTable(String appendString){
		closeTableContents.setText(closeTableContents.getText() + " " + appendString);
	}
	
	public static void addMessage(String msg) {
		String text = jtaMessages.getText();
		if (text == null || text.length() == 0) {
			jtaMessages.setText(msg);
		}
		else {
			jtaMessages.setText(jtaMessages.getText() + "\n" + msg);
		}
	}
	
	public static void addWaiterMessage(String msg, int waiterNumber) {
		String text = jtaWaiters[waiterNumber].getText();
		if (text == null || text.length() == 0) {
			jtaWaiters[waiterNumber].setText(msg);
		}
		else {
			jtaWaiters[waiterNumber].setText(jtaWaiters[waiterNumber].getText() + "\n" + msg);
		}
	}
	
	private void addComboBox(JPanel jp, JLabel jl, JComboBox<Integer> jcb, int gridx, int gridy) {
		addComponent(jp, jl, gridx, gridy, GridBagConstraints.EAST, 1, 1);
		addComponent(jp, jcb, gridx + 1, gridy, GridBagConstraints.WEST, 1, 1);
	}
	
	private void addComponent(JPanel jp, JComponent jc, int gridx, int gridy, int anchor, int gridwidth, int gridheight) {
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.ipadx = 3;
		gbc.ipady = 3;
		gbc.gridx = gridx;
		gbc.gridy = gridy;
		gbc.anchor = anchor;
		gbc.gridwidth = gridwidth;
		gbc.gridheight = gridheight;
		gbc.insets = new Insets(5, 5, 0, 0);
		jp.add(jc, gbc);
	}
	
	public static WaiterFactory getWaiterFactory() {
		return waiterFactory;
	}
	
	public int getNumWaiters() {
		return jcbNumWaiters.getItemAt(jcbNumWaiters.getSelectedIndex());
	}
	
	public int getNumBusboys() {
		return jcbNumBusboys.getItemAt(jcbNumBusboys.getSelectedIndex());
	}
	
	public int getNumTablesPerWaiter() {
		return jcbNumTablesPerWaiter.getItemAt(jcbNumTablesPerWaiter.getSelectedIndex());
	}
	
	public int getNumTablesPerBusboy() {
		return jcbNumTablesPerBusboy.getItemAt(jcbNumTablesPerBusboy.getSelectedIndex());
	}
	
	public int getNumTables() {
		return jcbNumTables.getItemAt(jcbNumTables.getSelectedIndex());
	}

	
	public static void main(String [] args) {
		new Restaurant();
	}
}