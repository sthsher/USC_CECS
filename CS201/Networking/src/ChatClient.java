
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class ChatClient extends Thread {
	
	private PrintWriter pw;
	private BufferedReader br;
	public ChatClient(String hostname, int port, Scanner scan) {
		try {
			Socket s = new Socket(hostname, port);
			this.pw = new PrintWriter(s.getOutputStream());
			this.br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			this.start();
			while (true) {
				String line = scan.nextLine();
				System.out.println("YOUR LINE: " + line);
				pw.println(line);
				pw.flush();
			}
		} catch (IOException ioe) {
			System.out.println("ioe in ChatClient: " + ioe.getMessage());
		}
	}
	
	public void run() {
		try {
			while(true) {
				String line = br.readLine();
				System.out.println("FROM OTHER CLIENT: " + line);
			}
		} catch (IOException ioe) {
			System.out.println("ioe in run: " + ioe.getMessage());
		}
	}

	public static void main(String [] args) {
		Scanner scan = new Scanner(System.in);
		System.out.print("What is the name/IP of the server? ");
		String hostname = scan.nextLine();
		System.out.print("What is the port? ");
		int port = scan.nextInt();
		new ChatClient(hostname, port, scan);
	}
}
