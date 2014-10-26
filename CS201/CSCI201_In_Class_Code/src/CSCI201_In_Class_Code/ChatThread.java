package CSCI201_In_Class_Code;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ChatThread extends Thread{
	private Socket s;
	private ChatServer cs;
	private PrintWriter pw;
	public ChatThread(Socket s, ChatServer cs){
		this.s = s;
		this.cs = cs;
		try{
			this.pw = new PrintWriter(s.getOutputStream());
		} catch (IOException IOE){
			System.out.println("IOE: " + IOE.getMessage());
			IOE.printStackTrace();
		}
	}
	
	public void send(String message){
		pw.println(message);
		pw.flush();
	}
	
	public void run(){
		//a client has connected to the server
		try{
			BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			String line = br.readLine();
			//Pass in the socket to make sure that you don't send message to same client. Comparing
			while (true){
				cs.sendMessage(line, this);
				line = br.readLine(); //blocking
			}
		} catch (IOException IOE){
			System.out.println("IOE: " + IOE.getMessage());
			IOE.printStackTrace();
			//Call a method in the server thread to remove this instance
		}
	}
}
