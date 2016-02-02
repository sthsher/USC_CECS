package tsher_CSCI201_Assignment5;

import java.util.ArrayList;

class Recipe {
//	private int amount;
	private String name;
	private ArrayList<Material> materials;
	private ArrayList<Instruction> instructions = new ArrayList<Instruction>();
	private int currentInstructionIndex = 0;
	private int status = 0;
	
	//without amount
	public Recipe(String name, ArrayList<Material> materials, ArrayList<String> instructions){
		this.name = name;
		this.materials = materials;
		
		//Convert list of instructions
		for (int i = 0; i < instructions.size(); ++i){
			Instruction newInstruction = new Instruction(instructions.get(i));
			this.instructions.add(newInstruction);
		}
	}
	
	public void checkOffInstruction(){
		instructions.get(currentInstructionIndex).finish();
		++currentInstructionIndex;
		
		if (currentInstructionIndex == instructions.size()){
			status = 2;
		}
	}
	
	public String nextWorkarea(){
		return instructions.get(currentInstructionIndex).getWorkarea(); 
	}
	
	public int getToolAmount(String tool){
		return instructions.get(currentInstructionIndex).getToolAmount(tool);
	}
	
	public boolean checkTool(String tool){
		return instructions.get(currentInstructionIndex).checkTool(tool);
	}
	
	public boolean checkInstructionStatus(){
		return instructions.get(currentInstructionIndex).getIsFinished();
	}
	
	public int getInstructionDuration(){
		return instructions.get(currentInstructionIndex).getDuration();
	}
	
	public Instruction getCurrentInstruction(){
		return instructions.get(currentInstructionIndex);
	}
	
	public int getMaterialAmount(String material){
		for (int i = 0; i < materials.size(); ++i){
			if (materials.get(i).getName().equalsIgnoreCase(material)){
				return materials.get(i).getAmount();
			}
		}
		return -1;
	}
	
	public boolean checkMaterial(String material){
		for (int i = 0; i < materials.size(); ++i){
			if (materials.get(i).getName().equalsIgnoreCase(material)){
				return true;
			}
		}
		return false;
	}
	
	public void setStatus(int s){
		status = s;
	}
	public int getStatus(){
		return this.status;
	}
	public String getStatusMessage(){
		if (status == 0){
			return (name + " ... Not Built");
		} else if (status == 1){
			return (name + " ... In Progress");
		} else if (status == 2){
			return (name + " ... Complete");
		} else if (status == -1){
			return (name + " .. No Materials");
		} else{
			return (name + " ... Unidentified Status");
		}
	}
	
	public String getName() {
		return name;
	}
	public ArrayList<Material> getMaterials() {
		return materials;
	}
	public ArrayList<Instruction> getInstructions() {
		return instructions;
	}
	public void setName(String name) {
		this.name = name;
	}
	public void setMaterials(ArrayList<Material> materials) {
		this.materials = materials;
	}
	public void setInstructions(ArrayList<Instruction> instructions) {
		this.instructions = instructions;
	}
	
	public void printRecipe(){
		for (int i = 0; i < materials.size(); ++i){
			System.out.println("[" + materials.get(i).getName() + ":" + materials.get(i).getAmount() + "]");
		}
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
		System.out.println("-" + amount + "x " + name + "-");
	}
}

class Instruction{
	private String entireInstruction;
	
	private ArrayList<Tool> toolList = new ArrayList<Tool>();
	private String workarea;
	private int duration;
	private int timeLeft;
	private boolean isFinished = false;
	
	public boolean checkTool(String tool){
		for (int i = 0; i < toolList.size(); ++i){
			if (toolList.get(i).name.equalsIgnoreCase(tool)){
				return true;
			}
		}
		return false;
	}
	
	public int getTimeLeftAndDecrement(){
		return timeLeft--;
	}
	
	public int getTimeLeft(){
		return timeLeft;
	}
	
	public void decrementTimeLeft(){
		--timeLeft;
	}
	
	public int getToolAmount(String tool){
		for (int i = 0; i < toolList.size(); ++i){
			if (toolList.get(i).name.equalsIgnoreCase(tool)){
				return toolList.get(i).amount;
			}
		}
		return -1;
	}
	
	public boolean getIsFinished(){
		return isFinished;
	}
	public void finish(){
		isFinished = true;
	}
	
	public Instruction(String entireInstruction){
		this.entireInstruction = entireInstruction;
		String inst = entireInstruction;
		

		//test for all the possible tools, always capitalized
		if (inst.contains("Hammer") || inst.contains("Hammers")){
			Tool newTool = new Tool("Hammers", findPrevIntInString(inst.indexOf("Hammer")));
			toolList.add(newTool);
		}
		if (inst.contains("Screwdriver") || inst.contains("Screwdrivers")){
			Tool newTool = new Tool("Screwdrivers", findPrevIntInString(inst.indexOf("Screwdriver")));
			toolList.add(newTool);
		}
		if (inst.contains("Paintbrush") || inst.contains("Paintbrushes")){
			Tool newTool = new Tool("Paintbrushes", findPrevIntInString(inst.indexOf("Paintbrush")));
			toolList.add(newTool);
		}
		if (inst.contains("Plier") || inst.contains("Pliers")){
			Tool newTool = new Tool("Pliers", findPrevIntInString(inst.indexOf("Pliers")));
			toolList.add(newTool);
		}
		if (inst.contains("Scissor") || inst.contains("Scissors")){
			Tool newTool = new Tool("Scissors", findPrevIntInString(inst.indexOf("Scissor")));
			toolList.add(newTool);
		}
		
		//Now look for the workspace
		if (inst.contains("Furnace")){
			workarea = "Furnace";
		}
		else if (inst.contains("Saw")){
			workarea = "Saw";
		}
		else if (inst.contains("Painting Station") || inst.contains("Paintingstation")){
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
			System.out.println("Unexpected work area name in " + entireInstruction);
		}
		
		duration = timeLeft = findPrevIntInString(inst.indexOf("s]"));
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

class Material{
	private String name;
	private int amount;
	
	public Material(String name, int amount){
		this.name = name;
		this.amount = amount;
	}
	
	public String getName() {
		return name;
	}
	public int getAmount() {
		return amount;
	}
	public void setName(String name) {
		this.name = name;
	}
	public void setAmount(int amount) {
		this.amount = amount;
	}
	
	public boolean equals (Object obj){
		if (obj instanceof Material){
			Material otherMaterial = (Material) obj;
			if (this.name.equalsIgnoreCase(otherMaterial.getName())){
				return true;
			} else{
				return false;
			}
		} else{
			return false;
		}
	}
}


