package tsher_CSCI201_Assignment5;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class WorkareaPanel extends JPanel{
	static final long serialVersionUID = 1;
	
	private int ID;
	private JLabel iconLabel;
	private JLabel iconTitle = new JLabel();
	private int status = 0;
	private int completionTime = 0;
	private String name;
	private Instruction assignedInstruction;
	
	private Factory factory;
	
	private GridBagConstraints gbc = new GridBagConstraints();
	
	public void setInstruction(Instruction instruction){
		assignedInstruction = instruction;
	}
	
	public WorkareaPanel(String type, int ID, Factory factory){
		this.name = type;
		this.ID = ID;
		this.factory = factory;
		
		setLayout(new GridBagLayout());
		setBackground(Color.WHITE);
		
		if (type.equalsIgnoreCase("anvil") || type.equalsIgnoreCase("anvils")){
			iconLabel = new JLabel(new ImageIcon(Factory.imageDirectory + "anvil.png"));
		} else if (type.equalsIgnoreCase("workbench") || type.equalsIgnoreCase("workbenches")){
			iconLabel = new JLabel(new ImageIcon(Factory.imageDirectory + "workbench.png"));
		} else if (type.equalsIgnoreCase("furnace") || type.equalsIgnoreCase("furnaces")){
			iconLabel = new JLabel(new ImageIcon(Factory.imageDirectory + "furnace.png"));
		} else if (type.equalsIgnoreCase("saw") || type.equalsIgnoreCase("saws")){
			iconLabel = new JLabel(new ImageIcon(Factory.imageDirectory + "tablesaw.png"));
		} else if (type.equalsIgnoreCase("painting station") || type.equalsIgnoreCase("painting stations")){
			iconLabel = new JLabel(new ImageIcon(Factory.imageDirectory + "paintingstation.png"));
		} else if (type.equalsIgnoreCase("press") || type.equalsIgnoreCase("presses")){
			iconLabel = new JLabel(new ImageIcon(Factory.imageDirectory + "press.png"));
		} else{
			System.out.println("Unexpected workarea");
		}
		
		iconTitle.setText(getStatusString());
		
		gbc.gridx = 0;
		gbc.gridy = 0;
		add(iconTitle, gbc);
		
		gbc.gridx = 0;
		gbc.gridy = 1;
		add(iconLabel, gbc);
	}
	
	public int getID(){
		return ID;
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		iconTitle.setText(getStatusString());
	}
	
	public String getName(){
		return name;
	}
	
	public String getStatusString(){
		if (status == 0){
			iconTitle.setForeground(Color.GREEN);
			return "Open";
		} else if (status == 1){
			iconTitle.setForeground(Color.RED);
			return ("" + (assignedInstruction.getTimeLeft()+1) + "s");
		} else if (status == -1){
			iconTitle.setForeground(Color.GREEN);
			return "Open";
		} else{
			return "Unexpected status";
		}
	}
	
	public int getStatus(){
		return status;
	}
	
	public int getCompletionTime(){
		return completionTime;
	}
	
	public void setCompletionTime(int t){
		completionTime = t;
	}
	
	public void decrement(){
		--completionTime;
	}
	
	public void setStatus(int n){
		status = n;
	}
}