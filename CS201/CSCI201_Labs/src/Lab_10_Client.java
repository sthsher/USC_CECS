import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;


public class Lab_10_Client extends Thread {
	private PrintWriter pw;
	private Socket s;
	private Lab_10_Server gs;
	private GameFrame gf;
	private BufferedReader br;
	
	public Lab_10_Client(String hostName, int port, int i, Scanner scan){

		try{
			
			//start a JFrame
			this.gf = new GameFrame("Player " + i, i);
			
			//reading from socket
			s = new Socket(hostName, port);
			this.pw = new PrintWriter(s.getOutputStream());
			
			gf.setpw(pw);
			
			this.br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			this.start();
			
//			while (true){
//				//Read from user
//				String line = scan.nextLine();
//				pw.println(line);
//				pw.flush();
//			}
		} catch (IOException IOE){
			
		}
		
	}
	
	public void run(){
		try{
			while (true){
				String line = br.readLine();
				if (line.equals("READY")){
					gf.markFullPlayers();
//					gf.setLabel("10/10 Health");
				} else if (line.equals("SWORD")){
					gf.deductHealth(2);
				} else if (line.contains("MAGIC")){
					gf.deductHealth(Integer.parseInt(line.charAt(5)+""));
				}
//				System.out.println(line);
			}
		} catch (IOException IOE){
			System.out.println("IOE");
		}
	}
	
	public static void main(String [] args){
		Scanner scan = new Scanner(System.in);

//

		int playerNum = scan.nextInt();
		
		new Lab_10_Client("localhost", 6789, playerNum, scan);
		
		
	
	}
	
}



class HealthThread extends Thread{
	private GameFrame gf;
	public HealthThread(GameFrame gf){
		this.gf = gf;
	}
	public void run(){
		while (true){
			if (!gf.isEnd){
				try{
					gf.infoLabel.setText(gf.returnHealthString(gf.health2));
					gf.healthLabel.setText(gf.returnHealthString(gf.health));
					sleep(1);
					gf.infoLabel.repaint();
					gf.healthLabel.repaint();
				} catch(InterruptedException IE){}
			}
			else{
				if (gf.health == 0){
					gf.infoLabel.setText("You Lost!");
				}
				else{
					gf.infoLabel.setText("You Win");
				}
			}
		}
	}
}

class ButtonThread extends Thread{
	private GameFrame gf;
	public ButtonThread(GameFrame gf){
		this.gf = gf;
	}
	public void run(){
		
		while(true){
			if (gf.isEnd){
				gf.isEnabled = false;
				gf.magicButton.setBackground(Color.GRAY);
				gf.magicButton.setForeground(Color.WHITE);
				gf.swordButton.setBackground(Color.GRAY);
				gf.swordButton.setForeground(Color.WHITE);
				
				if (gf.health == 0){
					gf.infoLabel.setText("You Lost!");
				}
				else{
					gf.infoLabel.setText("You Win");
				}
				try{
					sleep(1);
				}
				catch (InterruptedException IE){
				
				}
			}
			else{
				if (gf.isEnabled){
					try{
						sleep(1);
					}
					catch (InterruptedException IE){
					
					}
					//don't do anything
				} else{
					System.out.println("MARKER");

					try{
						//disable buttons
						sleep(3000);
						gf.isEnabled = true;
						gf.magicButton.setBackground(Color.WHITE);
						gf.magicButton.setForeground(Color.BLACK);
						gf.swordButton.setBackground(Color.WHITE);
						gf.swordButton.setForeground(Color.BLACK);
					} catch (InterruptedException IE){
						
					}
				}
			}
				
			
		}
	}
}

class GameFrame extends JFrame{
	private int playerNum;
	private PrintWriter pw;
	public int health = 2;
	public int health2 = 2;
	public JLabel healthLabel = new JLabel();
	public JLabel infoLabel = new JLabel();
	public boolean isEnabled;
	public JButton magicButton;
	public JButton swordButton;
	public boolean isEnd = false;
//	private String healthString;
	
	private Thread healthThread = new HealthThread(this);
	private Thread buttonThread = new ButtonThread(this);
	
	public boolean twoPlayers;
	
	public void deductHealth(int damage){
		health -= damage;
		if (health <= 0){
			isEnd = true;
			health = 0;
		}
	}
	
	public void deductHealth2(int damage){
		isEnabled = false;
		health2 -= damage;
		if (health2 <= 0){
			health2 = 0;
			isEnd = true;
		}
	}
	
	public void markFullPlayers(){
		this.twoPlayers = true;
		healthThread.start();
		buttonThread.start();
	}
	
	public void setLabel(String content){
		infoLabel.setText(content);
	}
	
	public String returnHealthString(int currentHealth){
		return ((currentHealth)+"/"+"10 Health");
	}
	
	public void changeText(String newText){
		infoLabel.setText(newText);
	}
	public void setpw(PrintWriter pw){
		this.pw = pw;
	}
	
	public GameFrame(String name, int i){
		super(name);
		this.setSize(300, 200);
		this.setLocation(400,300);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		this.playerNum = i;
		
		twoPlayers = false;
		isEnabled = true;
		
		this.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		JPanel healthPanel = new JPanel();
		JPanel infoPanel = new JPanel();
		JPanel buttonPanel = new JPanel();
		healthPanel.setPreferredSize(new Dimension(300, 20));
		infoPanel.setPreferredSize(new Dimension(300, 20));
		buttonPanel.setPreferredSize(new Dimension(75, 130));


		
		healthLabel.setText(returnHealthString(10));
		infoLabel.setText("Waiting for other player");
		
		swordButton = new JButton("Sword");
		magicButton = new JButton("Magic");
		
		swordButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				if(isEnabled){
					pw.flush();

					pw.println("SWORD" + i);
					pw.flush();
					deductHealth2(2);

					isEnabled = false;

					//make the button grey
					magicButton.setBackground(Color.GRAY);
					magicButton.setForeground(Color.WHITE);
					swordButton.setBackground(Color.GRAY);
					swordButton.setForeground(Color.WHITE);
				} else{

				}

			}
		});
		
		magicButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				if(isEnabled){
					Random generate = new Random();
					int randomNum = generate.nextInt(5)+1;
					pw.flush();

					pw.println("MAGIC" + i + " " + (randomNum));
					pw.flush();
					
					deductHealth2(randomNum);

					isEnabled = false;

					//make the button grey
					magicButton.setBackground(Color.GRAY);
					magicButton.setForeground(Color.WHITE);
					swordButton.setBackground(Color.GRAY);
					swordButton.setForeground(Color.WHITE);
				} else{

				}

			}
		});
		
		buttonPanel.add(swordButton);
		buttonPanel.add(magicButton);

		healthPanel.add(healthLabel);
		infoPanel.add(infoLabel);
		
		this.add(healthPanel);
		this.add(infoPanel);
		this.add(buttonPanel);
		
		this.setVisible(true);

	}
	

}

