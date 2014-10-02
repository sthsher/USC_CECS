import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.BevelBorder;

public class Lab_5 extends JFrame {
	
	public static JPanel tab2(){
		JPanel panel = new JPanel();
		panel.setSize(500,500);
		panel.setLocation(200,300);
				
		try{
			BufferedImage bi = ImageIO.read(new File("doge.jpg"));
			Image scaled = bi.getScaledInstance(500, 500, Image.SCALE_SMOOTH);
			ImageIcon ii = new ImageIcon(scaled);

			JLabel dogeLabel = new JLabel(ii);
			
			panel.add(dogeLabel);
			
			
			
		} catch (IOException e){
			System.out.println(e.getMessage());
		}
		
		return panel;


		

	}
	
	public static JPanel tab1(){
		//First Tab
		JPanel panel = new JPanel();
		panel.setLayout(new BorderLayout());
		panel.setSize(500,500);
		panel.setLocation(200,300);
		
		JPanel northPanel 		=	new JPanel();
		northPanel.setBorder(BorderFactory.createLineBorder(Color.black));
		JButton button1			=	new JButton("Button 1");
		JButton button2			=	new JButton("Button 2");
		button2.setBackground(Color.RED);
		button2.setOpaque(true);
				
		northPanel.add(button1);
		northPanel.add(button2);
		panel.add(northPanel, BorderLayout.NORTH);
		
		
		JPanel southPanel		=	new JPanel();
		southPanel.setBorder(BorderFactory.createLineBorder(Color.RED));
		southPanel.setLayout(new BorderLayout());
		
		JPanel southWestPanel	=	new JPanel();
		JLabel westLabel		=	new JLabel("West");
		southWestPanel.add(westLabel);

		
		JPanel southCenterPanel = 	new JPanel();
		JLabel centerLabel		=	new JLabel("This is the south quadrant");
//		centerLabel.setHorizontalAlignment(SwingConstants.LEFT);
		//southCenterPanel.setPreferredSize(new Dimension(400,25));
		southCenterPanel.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
		southCenterPanel.add(centerLabel);
		
		JPanel southEastPanel	= 	new JPanel();
		JLabel eastLabel		=	new JLabel("East");
		southEastPanel.add(eastLabel);

		
		southPanel.add(southWestPanel, BorderLayout.WEST);
		southPanel.add(southCenterPanel, BorderLayout.CENTER);
		southPanel.add(southEastPanel, BorderLayout.EAST);
		
//		JPanel blankCenter = new JPanel();
//		blankCenter.setSize(new Dimension(500,300));
//		JLabel testLabel		=	new JLabel("Center");
//		blankCenter.add(testLabel);
//				
//		panel.add(blankCenter, BorderLayout.CENTER);
		
		panel.add(southPanel, BorderLayout.SOUTH);
		
		
		return panel;

	}
	
	public Lab_5(){
		super("CSCI201_Lab5");
		setSize(500,500);
		setLocation(200,200);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JTabbedPane tabbedPane 		= new JTabbedPane();
		JPanel panel1				= tab1();
		JPanel panel2				= tab2();
		
		tabbedPane.add("First", panel1);
		tabbedPane.add("Doge", panel2);
	
		add(tabbedPane);
		setVisible(true);
	
	}
	
	
	
	public static void main(String [] args){
//		new doge();
	try {
            // Set cross-platform Java L&F (also called "Metal")
	    	UIManager.setLookAndFeel(
            UIManager.getCrossPlatformLookAndFeelClassName());
	    	new Lab_5();

    } 
    catch (UnsupportedLookAndFeelException e) {
       // handle exception
    }
    catch (ClassNotFoundException e) {
       // handle exception
    }
    catch (InstantiationException e) {
       // handle exception
    }
    catch (IllegalAccessException e) {
       // handle exception
    }
        
	}
		
		
}
	

