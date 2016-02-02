package test;


interface I{
	public void thing();
}

class C implements I{
	public void C(){
		
	}
	
	public void thing(){
		System.out.println("Hello");
	}
}

public class test1 {
	public static void main(String[] args ) {
		I i = new C();
		
		i.thing();
		
	}
}