package test;

import java.awt.*;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.swing.*;
class test2
{
	static Calendar calendar = new GregorianCalendar();

	public static void main(String[] args)
	{
		Instruction test = new Instruction("[Use 10x Hammer and 2x Screwdrivers at Workbench for 2s]");
	
	}
}

class Tool{
	public String name;
	public int amount;
	
	public Tool(String name, int amount){
		this.name = name;
		this.amount = amount;
	}
	
	public void print(){
		System.out.println(amount + "x " + name);
	}
}

class Instruction{
	private String entireInstruction;
	private ArrayList<Tool> toolList = new ArrayList<Tool>();
	private String workarea;
	private int duration;
	
	public Instruction(String entireInstruction){
		this.entireInstruction = entireInstruction;
		String inst = entireInstruction;

		//test for all the possible tools, always capitalized
		if (inst.contains("Hammer") || inst.contains("Hammers")){
			//get the number of instances of the tool
			Tool newTool = new Tool("Hammer", findPrevIntInString(inst.indexOf("Hammer")));
			toolList.add(newTool);
		}
		if (inst.contains("Screwdriver") || inst.contains("Screwdrivers")){
			//get the number of instances of the tool
			Tool newTool = new Tool("Screwdriver", findPrevIntInString(inst.indexOf("Screwdriver")));
			toolList.add(newTool);
		}
		if (inst.contains("Paintbrush") || inst.contains("Paintbrushes")){
			//get the number of instances of the tool
			Tool newTool = new Tool("Paintbrush", findPrevIntInString(inst.indexOf("Paintbrush")));
			toolList.add(newTool);
		}
		if (inst.contains("Plier") || inst.contains("Pliers")){
			//get the number of instances of the tool
			Tool newTool = new Tool("Pliers", findPrevIntInString(inst.indexOf("Pliers")));
			toolList.add(newTool);
		}
		if (inst.contains("Scissor") || inst.contains("Scissors")){
			//get the number of instances of the tool
			Tool newTool = new Tool("Scissor", findPrevIntInString(inst.indexOf("Scissor")));
			toolList.add(newTool);
		}
		
		//Now look for the workspace
		if (inst.contains("Furnace")){
			workarea = "Furnace";
		}
		else if (inst.contains("Saw")){
			workarea = "Saw";
		}
		else if (inst.contains("Painting Station")){
			workarea = "Painting Station";
		}
		else if (inst.contains("Workbench")){
			workarea = "Workbench";
		}
		else if (inst.contains("Anvil")){
			workarea = "Anvil";
		}
		else if (inst.contains("Press")){
			workarea = "Press";
		}
		else{
			System.out.println("Unexpected works area name");
		}
		
		duration = findPrevIntInString(inst.indexOf("s]"));
		
//		for (int i = 0; i < toolList.size(); ++i){
//			toolList.get(i).print();
//		}
//		System.out.println(workarea);
//		System.out.println(duration);
		
	}
	
	private int findPrevIntInString(int start){
		//now count back until you've got a number, and then the end of the number
		int endIndex = 0;
		int startIndex = 0;
		boolean isFirstIntegerEncounter = true;
		
		for (int i = start; i > 0; --i){
			if (Character.isDigit(entireInstruction.charAt(i)) && isFirstIntegerEncounter){
				endIndex = i+1;
				isFirstIntegerEncounter = false;
			}
			if (entireInstruction.charAt(i) == ' ' && !isFirstIntegerEncounter){
				//end of integer
				startIndex = i+1;
				break;
			}
		}
		
		return Integer.parseInt(entireInstruction.substring(startIndex, endIndex));
	}

	public String getEntireInstruction() {
		return entireInstruction;
	}

	public ArrayList<Tool> getToolList() {
		return toolList;
	}

	public String getWorkarea() {
		return workarea;
	}

	public int getDuration() {
		return duration;
	}

	public void setEntireInstruction(String entireInstruction) {
		this.entireInstruction = entireInstruction;
	}

	public void setToolList(ArrayList<Tool> toolList) {
		this.toolList = toolList;
	}

	public void setWorkarea(String workarea) {
		this.workarea = workarea;
	}

	public void setDuration(int duration) {
		this.duration = duration;
	}
	
}