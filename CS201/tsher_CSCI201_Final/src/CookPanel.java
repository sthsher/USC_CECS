

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
		writeArea.setEditable(false);
//		scroller.setPreferredSize(new Dimension(300,500));
		
		add(scroller, BorderLayout.CENTER);
		
		
	}
	
	public void addCookMessage(String message){
//		writeArea.setText(writeArea.getText() + "\n" + message);
		if (!writeArea.getText().equals(""))
			writeArea.append("\n" + message);
		else
			writeArea.append(message);
	}
	
}
