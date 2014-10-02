package test_GUI;

import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class Test_GUI extends JFrame{
	public Test_GUI(){
		super("CSCI 201 Window");
		setSize(500,100);
		setLocation(200,300);

		JPanel northPanel 		=	 new JPanel();
		JLabel nameLabel 		=	 new JLabel("Name");
		JTextField nameTF 		=	 new JTextField(25);
		JButton verifyButton 	=	 new JButton("Verify");

		northPanel.add(nameLabel);
		northPanel.add(nameTF);
		northPanel.add(verifyButton);
		add(northPanel, BorderLayout.NORTH);

		JPanel southPanel 		= 	new JPanel();
		JLabel emailLabel		=	new JLabel("Email");
		JTextField emailTF		=	new JTextField(25);
		JButton submitButton	=	new JButton("Submit");

		southPanel.add(emailLabel);
		southPanel.add(emailTF);
		southPanel.add(submitButton);
		add(southPanel, BorderLayout.SOUTH);

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}
	
	
	
	public static void main(String [] args){
		new Test_GUI();


	}
	
	
}

