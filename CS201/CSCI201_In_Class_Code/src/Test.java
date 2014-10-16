
public class Test {
	public static void main(String [] args){
		System.out.println("First line");
		TestThread ta = new TestThread('a');
		TestThread tb = new TestThread('b');
		TestThread tc = new TestThread('c');
		ta.start();
		tb.start();
		tc.start();
		System.out.println("Last Line");
	}
}

class TestThread extends Thread{
	private char c;
	public TestThread(char c){
		this.c = c;
	}
	public void run(){
		for (int i = 0; i < 20; ++i){
			System.out.println(i + "" + c + " ");
			try{
				sleep(1000);
			}catch (InterruptedException ie){
				System.out.println("interrupted");
				return;
			}
		}
		System.out.println("");
	}
}
