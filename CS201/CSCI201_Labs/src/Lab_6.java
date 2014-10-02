import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;


public class Lab_6 extends JFrame{
		static JLabel 		titleLabel;
		static JPanel		titlePanel, gridPanel, resetPanel;
		static JButton		resetButton;
		static int 			player = 0;
		
		//button storage
		static ArrayList<GameButton> buttonArray = new ArrayList<GameButton>();
		
	public static int checkGrid(){
		//convert the buttonArray to an array from Lab4
		char[] board = new char[9];
		for (int i = 0; i < 9; ++i){
			if (buttonArray.get(i).player == 0){
				board[i] = 'o';
			}
			else if (buttonArray.get(i).player == 1){
				board[i] = 'x';
			}
			else{
				board[i] = '_';
			}
		}
		
//		for (int i = 0; i < 9; ++i){
//			System.out.print(board[i]);
//			if (i == 2 || i == 5 || i == 8){
//				System.out.println("");
//			}
//		}
//		System.out.println("");
		
		for (int i = 0; i < 3; ++i){
			if (board[3*i] == board[(3*i)+1] && board[i] == board[(3*i)+2]){
				if (board[3*i] != '_'){
					if(board[3*i] == 'x'){
						// System.out.println("Marker1, i = " + i);
						return 1;
					}
					else{
						// System.out.println("Marker1, i = " + i);
						return 0;
					}
				}
			}
		}
		
		for (int i = 0; i < 3; ++i){
			if (board[i] == board[i+3] && board[i] == board[6+i]){
				if (board[i] != '_'){
					if (board[i] == 'x'){
						// System.out.println("Marker2, i = " + i);
						return 1;
					}
					else{
						// System.out.println("Marker2, i = " + i);
						return 0;
					}
				}
			}
		}
		
		//check diagnoal
		if (board[0] == board[4] && board[0] == board[8]){
			if (board[0] != '_'){
				if (board[0] == 'x'){
					// System.out.println("Marker3");
					return 1;
				}
				else{
					// System.out.println("Marker3");
					return 0;
				}
			}
		}
		
		if (board[2] == board[4] && board[2] == board[6]){
			if (board[2] != '_'){
				if (board[2] == 'x'){
					System.out.println("Marker4");
					return 1;
				}
				else{
					System.out.println("Marker4");
					return 0;
				}
			}
		}
		
		boolean isDraw = true;
		
		//this means no winner, check if board is full
		for (int i = 0; i < 9; ++i){
			if (board[i] == '_'){
				isDraw = false;
			}
		}
		
		if (isDraw){
			return 2;
		}
		else{
			return -1;
		}
		
		
	}
		
	static void deactivateButtons(){
		for (int i = 0; i < 9; ++i){
			buttonArray.get(i).isPressed = true;
		}
	}
	
	
	public Lab_6(){
		//JFrame settings
		setSize(600,700);
		setLocation(400,100);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new FlowLayout(FlowLayout.CENTER));
		setBackground(Color.WHITE);
		
		//First add the JLabel to JPanel
		titleLabel 	= new JLabel("Current Player: 1");
		titlePanel	= new JPanel();
		titlePanel.setPreferredSize(new Dimension(600,30));
		titlePanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		titlePanel.add(titleLabel);
		add(titlePanel);
		
		//Make the grid
		gridPanel	= new JPanel();
		gridPanel.setPreferredSize(new Dimension(600,600));
		gridPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		for (int i = 0; i < 9; ++i){
			//make 9 buttons
			GameButton bt = new GameButton("");
			bt.setBorder(new LineBorder(Color.BLACK));
			bt.setPreferredSize(new Dimension(190,190));
			bt.setOpaque(true);
			bt.setBackground(Color.WHITE);
			bt.setFont(new Font("Helvetica", Font.BOLD, 36));
			
			//Add action
			bt.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent ae){
					//only perform action if not pressed
					if (!bt.isPressed){
						bt.isPressed = true;
						//set the player's marker
						if (player % 2 == 0){
							bt.setText("O");
							bt.player = 0;
						}
						else{
							bt.setText("X");
							bt.player = 1;
						}
						player++;
						bt.setBackground(Color.WHITE);
						
						//check board
						int result = checkGrid();
						if (result == 0){
							titleLabel.setText("Player 1 Won!");
							deactivateButtons();
						}
						else if (result == 1){
							titleLabel.setText("Player 2 Won!");
							deactivateButtons();
						}
						else if (result == 2){
							titleLabel.setText("Draw!");
							deactivateButtons();
						}
						else{
							//see who's turn it is
							if (player % 2 == 0){
								titleLabel.setText("Current Player: 1");
							}
							else{
								titleLabel.setText("Current Player: 2");
							}
						}
						
						
					}

				}
			});
			
			//add it to the panel and store it
			gridPanel.add(bt);
			buttonArray.add(bt);
			
		}
		add(gridPanel);
		
		//Reset Panel
		resetPanel	= new JPanel();
		resetPanel.setPreferredSize(new Dimension(600,30));
		resetButton	= new JButton("Reset Game");
		resetButton.setPreferredSize(new Dimension(600,30));
		//Action for reset
		resetButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				for (int i = 0; i < 9; ++i){
					//reset values
					buttonArray.get(i).isPressed = false;
					buttonArray.get(i).player = -1;
					buttonArray.get(i).setText("");
					buttonArray.get(i).setBackground(Color.WHITE);
					//reset title
					titleLabel.setText("");
				}
			}
		});
		
		
		resetPanel.add(resetButton);
		add(resetPanel);
		
		setVisible(true);
	}
	
	public class GameButton extends JButton{
		public boolean isPressed = false;
		public int player = -1;
		public GameButton(String name){
			super(name);			
		}
	}
		
		
	static public void main(String args []){
		new Lab_6();
	}
}
