package CSCI201_In_Class_Code;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;


//Each client has 2 threads: 1 for sending, 1 for recieving

public class ChatClient extends Thread{
	private PrintWriter pw;
	private BufferedReader br;
	public ChatClient(String hostName, int port, Scanner scan){
		try{
			Socket s = new Socket(hostName, port);
			this.pw = new PrintWriter(s.getOutputStream());
			this.br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			this.start();
			while (true){
				String line = scan.nextLine();
				pw.println(line);
				pw.flush();
			}
			
			
		} catch (IOException IOE){
			System.out.println("IOE: " + IOE.getMessage());
			IOE.printStackTrace();
		}
	}
	
	public void run(){
		try{
			while (true){
				String line = br.readLine();
				System.out.println(line);
			}
		} catch (IOException IOE){
			System.out.println("IOE");
		}
	}
	
	public static void main(String [] args){
		Scanner scan = new Scanner(System.in);

		System.out.print("What is the name/IP of the server? ");
		String hostName = scan.next();
		System.out.print("What is the port? ");
		int port = scan.nextInt();
		new ChatClient(hostName, port, scan);
		
		
	}
}
