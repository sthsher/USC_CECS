import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.Vector;

public class ChatServer {

	private Vector<ChatThread> ctVector = new Vector<ChatThread>();
	public ChatServer(int port) {
		try {
			ServerSocket ss = new ServerSocket(port);
			while(true) {
				System.out.println("Waiting for connections...");
				Socket s = ss.accept();
				System.out.println("Connection from " + s.getInetAddress());
				ChatThread ct = new ChatThread(s, this);
				ctVector.add(ct);
				ct.start();
			}
		} catch (IOException ioe) {
			System.out.println("ioe: " + ioe.getMessage());
		}
	}
	
	public void sendMessage(String message, ChatThread ct) {
		for(ChatThread c : ctVector) {
			if (!c.equals(ct)) {
				c.send(message);
			}
		}
	}
	
	public void removeChatThread(ChatThread ct) {
		ctVector.remove(ct);
	}
	
	public static void main(String [] args) {
		Scanner scan = new Scanner(System.in);
		System.out.print("What port? ");
		int port = scan.nextInt();
		new ChatServer(port);
	}
}
