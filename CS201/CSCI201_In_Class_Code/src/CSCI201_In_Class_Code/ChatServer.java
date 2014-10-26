package CSCI201_In_Class_Code;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.Vector;


public class ChatServer {
	
	//Vector is synchronous, when we call a method on the vector, only one thread can call that method at one time
	//Array list is asynchronous, meaning multiple threads can access it at one time, meaning there will be different ordering of information
	//in each client
	private Vector<ChatThread> ctVector = new Vector<ChatThread>();
	
	public ChatServer(int port){
		try{
			//Open a socket
			ServerSocket ss = new ServerSocket(port);
			
			while(true){
				//Accept any clients connecting to the server
				Socket s = ss.accept();
				ChatThread ct = new ChatThread(s, this);
				ctVector.add(ct);
				ct.start();
			}
			
		} catch (IOException ioe){
			System.out.println("IOE: " + ioe.getMessage());
			ioe.printStackTrace();
		}
		
	}
	
	public void sendMessage(String message, ChatThread ct){
		for(ChatThread ctIter : ctVector){
			if (!ctIter.equals(ct)){
				ctIter.send(message);
			}
		}
	}
	
	public static void main (String [] args){
		Scanner scan = new Scanner(System.in);
		System.out.print("What port? ");
		int port = scan.nextInt();
		new ChatServer(port);
		
		
		
	}
}
