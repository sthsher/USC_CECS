import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Polygon;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;


public class Lab_7 extends JFrame{
	JFrame mainFrame;
	JButton myButton;
	MyButton newButton;
	MyPanel	buttonPanel;
	public Lab_7(){
		super("Lab 7");
		setSize(500,500);
		setLocation(200,200);
		setLayout(new FlowLayout(FlowLayout.CENTER));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		newButton = new MyButton("Don't Click Me");
		newButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				JOptionPane.showMessageDialog(new JFrame(), "WHY DID YOU CLICK ME AGAIN?", "Message", JOptionPane.ERROR_MESSAGE);
			}
		});
		
		myButton = new JButton("Click Once");
		myButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				//hide the current button
				myButton.setVisible(false);
				buttonPanel.remove(myButton);
				buttonPanel.add(newButton);
			}
		});
		
		
		
		buttonPanel = new MyPanel();
		buttonPanel.add(myButton);
		buttonPanel.setPreferredSize(new Dimension(500,500));
		
//		buttonPanel.add(newButton);
		
		
		add(buttonPanel, BorderLayout.CENTER);
		
		setVisible(true);
		
	}
	
	public static void main(String args []){
		new Lab_7();
	}
}

class MyButton extends JButton{
	int h;
	int w;
	public MyButton(String name){
		super(name);

	}

	protected void paintComponent(Graphics g){
		super.paintComponent(g);
		Dimension thisSize = getSize();
		h = thisSize.height;
		w = thisSize.width;
		g.setColor(Color.RED);
		g.drawLine(0, 0, w, h);
		g.drawLine(w, 0, 0, h);
	}
	
	
}

class MyPanel extends JPanel{
	public MyPanel(){
		super();
	}
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		Polygon poly = new Polygon();
		g.setColor(Color.BLUE);
		int scale = 4;
		int x_off = 190;
		int y_off = 0;
		
		poly.addPoint((10*scale)+x_off,(10*scale)+y_off);
		poly.addPoint((20*scale)+x_off,(10*scale)+y_off);
		poly.addPoint((25*scale)+x_off,(20*scale)+y_off);
		poly.addPoint((25*scale)+x_off,(27*scale)+y_off);
		poly.addPoint((20*scale)+x_off,(37*scale)+y_off);
		poly.addPoint((10*scale)+x_off,(37*scale)+y_off);
		poly.addPoint((5*scale)+x_off,(27*scale)+y_off);
		poly.addPoint((5*scale)+x_off,(20*scale)+y_off);
		
		
		
		g.fillPolygon(poly);
	}
}