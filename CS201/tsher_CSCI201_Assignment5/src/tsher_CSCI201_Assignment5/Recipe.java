package tsher_CSCI201_Assignment5;

import java.util.ArrayList;

class Recipe {
	private int amount;
	private String name;
	private ArrayList<Material> materials;
	private ArrayList<String> instructions;
	private int status = 0;
	
	public Recipe(String name, int amount, ArrayList<Material> materials, ArrayList<String> instructions){
		this.amount = amount;
		this.name = name;
		this.materials = materials;
		this.instructions = instructions;
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
		} else{
			return (name + " ... Unidentified Status");
		}
	}
	
	public int getAmount() {
		return amount;
	}
	public String getName() {
		return name;
	}
	public ArrayList<Material> getMaterials() {
		return materials;
	}
	public ArrayList<String> getInstructions() {
		return instructions;
	}
	public void setAmount(int amount) {
		this.amount = amount;
	}
	public void setName(String name) {
		this.name = name;
	}
	public void setMaterials(ArrayList<Material> materials) {
		this.materials = materials;
	}
	public void setInstructions(ArrayList<String> instructions) {
		this.instructions = instructions;
	}
	
	public void printRecipe(){
		System.out.println("[" + name + "] x" + amount);
		for (int i = 0; i < materials.size(); ++i){
			System.out.println("[" + materials.get(i).getName() + ":" + materials.get(i).getAmount() + "]");
		}
		
		for (int i = 0; i < instructions.size(); ++i){
			System.out.println(instructions.get(i));
		}
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
			if (this.name.equals(otherMaterial.getName())){
				return true;
			} else{
				return false;
			}
		} else{
			return false;
		}
	}
	
	
}
