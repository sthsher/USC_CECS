package tsher_CSCI201_Assignment5;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridBagConstraints;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class CookPanel extends JPanel{
	private GridBagConstraints 	gbc 		= new GridBagConstraints();
	private JTextArea			writeArea	= new JTextArea();
	private	JScrollPane			scroller	= new JScrollPane(writeArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
	
	
	public CookPanel(){
		setLayout(new BorderLayout());
		setPreferredSize(new Dimension(300,500));
		
//		scroller.setPreferredSize(new Dimension(300,500));
		
		add(scroller, BorderLayout.CENTER);
		
		
	}
}
