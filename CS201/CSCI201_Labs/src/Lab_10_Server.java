import java.awt.FlowLayout;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

import javax.swing.JFrame;
import javax.swing.JLabel;

public class Lab_10_Server {
	private int playerNum = 1;
	private Lab_10_GameThread thread1;
	private Lab_10_GameThread thread2;
	private static int num = 0;
	
	public Lab_10_Server(int port){
		try{
			ServerSocket ss = new ServerSocket(port);
			while(true){
				//accept any clients
				Socket s = ss.accept();
				if (playerNum == 1){
					thread1 = new Lab_10_GameThread(s, this);
					thread1.start();
					playerNum = 2;
				} else if (playerNum == 2){
					thread2 = new Lab_10_GameThread(s, this);
					thread2.start();
					playerNum = 1;
					
					//Now prepare
					thread1.send("READY");
					thread2.send("READY");
				} else{
					//only 2 players, don't do anything else
				}
				
			}
		} catch (IOException IOE){
			
		}
	}
	
	public void sendAction(String command){

		
		if (command.contains(("MAGIC1"))){
			thread2.send("MAGIC"+command.charAt(7));
		}
		else if (command.equals("SWORD1")){
			thread2.send("SWORD");
		}
		else if (command.contains("MAGIC2")){
			thread1.send("MAGIC"+command.charAt(7));
		}
		else if (command.equals("SWORD2")){
			thread1.send("SWORD");
		}
	}
	


	
	public static void main(String[] args){
//		Scanner scan = new Scanner(System.in);
//		System.out.print("What port? ");
//		int port = scan.nextInt();
//		new Lab_10_Server(port);
		
		System.out.println("Flag Server");
		
		new Lab_10_Server(6789);

	}
	
	
	
}





