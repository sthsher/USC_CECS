package test_GUI;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class Test_GUI extends JFrame{
	public Test_GUI(){
		super("CSCI 201 Window");
		setSize(600,400);
		setLocation(200,300);

		JPanel phonePanel = new JPanel();
		phonePanel.setLayout(new FlowLayout());
		phonePanel.setPreferredSize(new Dimension(600,400));
		
		JPanel filler = new JPanel();
		filler.setPreferredSize(new Dimension(600,100));
		
		phonePanel.add(filler);
		
		//Need a textField
		JTextField 	phoneField 	= new JTextField();
		phoneField.setPreferredSize(new Dimension(150,20));
		
		//Buttons
		JPanel buttonPanel = new JPanel();
		buttonPanel.setPreferredSize(new Dimension(150, 140));
		buttonPanel.add(phoneField);
		buttonPanel.setLayout(new FlowLayout());
		
		String[] array = {"7","8","9","4","5","6","1","2","3","*","0","+"};

		for (int i = 0; i < 12; ++i){
			JButton newButton = new JButton(array[i]);
			newButton.setPreferredSize(new Dimension(40,20));
			buttonPanel.add(newButton);
		}


		
		phonePanel.add(buttonPanel, BorderLayout.CENTER);
		
		
		add(phonePanel, BorderLayout.CENTER);

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}
	
	
	
	public static void main(String [] args){
		new Test_GUI();


	}
	
	
}

