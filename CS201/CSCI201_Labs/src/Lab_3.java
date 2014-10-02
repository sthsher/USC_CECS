
public class Lab_3 {
	static interface nameable_Interface{
		public abstract void setName(String newName);
		public abstract String getName();
	}
	
	static abstract class pet implements nameable_Interface{
		private String name;
		public void setName(String newName){
			this.name = newName;
		}
		public String getName(){
			return this.name;
		}
		public abstract String speak();
	}

	static class dragon extends pet{
		public String speak(){
			return ("I AM A FIRE BREATHING DRAGON NAMED " + this.getName() + ", RWARRRR!!!");
		}
	}

	static class clownfish extends pet{
		public String speak(){
			return ("Hello I am a clownfish. My name is " + this.getName() + ", have you seen my son, Nemo?");
		}
	}

	public static void main(String [] args){
		System.out.println("--- Program Start ---");		
		
		//Let's make some pets
		pet draco = new dragon();
		draco.setName("Draco");

		pet marlin = new clownfish();
		marlin.setName("Marlin"); 
		
		pet temp;
		String petName;
		
		for (int i = 0; i < 2; ++i){
			if (i == 0){
				temp = draco;
				System.out.println("\nDraco:");
				petName = "Draco";
			}
			else{
				temp = marlin;
				System.out.println("\nMarlin:");
				petName = "Marlin";
			}
				if (temp instanceof nameable_Interface){
					System.out.println(petName + " uses the nameable interface!");
				}
				if (temp instanceof pet){
					System.out.println(petName + " is a pet!");
				}
				if (temp instanceof dragon){
					System.out.println(petName + " is a dragon!");
				}
				System.out.println(temp.speak());		
			}
		
		System.out.println("\n--- Program End ---");		


	}
}
