import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;


public class Lab_10_GameThread extends Thread{
		private Socket s;
		private PrintWriter pw;
		private Lab_10_Server server;

		
		public Lab_10_GameThread(Socket s, Lab_10_Server server){
			this.s = s;
			this.server = server;
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
//				String line = br.readLine();
				String line;
				//Pass in the socket to make sure that you don't send message to same client. Comparing
				while (true){
					line = br.readLine(); //blocking
					server.sendAction(line);
				}
			} catch (IOException IOE){
				System.out.println("IOE: " + IOE.getMessage());
				IOE.printStackTrace();
				//Call a method in the server thread to remove this instance
			}
		}
}
