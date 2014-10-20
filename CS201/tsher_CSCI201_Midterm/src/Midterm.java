import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Midterm{

	
	public static void main(String [] args){
		
		//Variables
		boolean loop = true;
		ParentGUI frame;

		//Make a scanner
		Scanner scan = new Scanner(System.in);
		String input = "";
		
		
		while (loop){
			System.out.println("\nImage Editor [image]");
			System.out.println("Telephone [phone]");
			
			System.out.print("What application would you like to run? ");
			input = scan.nextLine();
		
			if (input.equals("image")){
				frame = new ImageFrame("CSCI 201 Midterm - Image Editor");
				loop = false;
			}
			else if (input.equals("phone")){
				frame = new PhoneFrame("CSCI 201 Midterm - Telephone");
				loop = false;
			}
			else{
				System.out.println("Please enter a valid selection");
			}
		}
	}
	

}




abstract class ParentGUI extends JFrame { 
	
	public ParentGUI(String title) {
			super(title);
			setSize(600, 400);
			setLocation(100, 100);
			setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			
			JPanel jp = createGUI();
			add(jp, BorderLayout.CENTER);
	}
	
	protected abstract void createMenuBar();
	protected abstract JPanel createGUI();
}

class PhoneFrame extends ParentGUI{
	JMenuBar	menuBar 	= new JMenuBar();
	JMenu		imageMenu	= new JMenu("Phone");
	JMenuItem	openItem	= new JMenuItem("Call");
	
	JTextField	phoneField;
	
	String		content		= "";
	
	public PhoneFrame(String name){
		super(name);
		
		createMenuBar();
		
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	protected void createMenuBar(){
		
		
		//Make menu
		imageMenu.add(openItem);
		
		openItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				phoneField.setText("");
			}
		});
		
		menuBar.add(imageMenu);
		
		//Add to JFrame
		setJMenuBar(menuBar);
	}

	
	protected JPanel createGUI(){
		JPanel phonePanel = new JPanel();
		phonePanel.setLayout(new FlowLayout());
		phonePanel.setPreferredSize(new Dimension(600,400));
		
		JPanel filler = new JPanel();
		filler.setPreferredSize(new Dimension(600,80));
		
		phonePanel.add(filler);
		
		//Need a textField
		phoneField	= new JTextField();
		phoneField.setPreferredSize(new Dimension(150,20));
		
		//Buttons
		JPanel buttonPanel = new JPanel();
		buttonPanel.setPreferredSize(new Dimension(150, 140));
		buttonPanel.add(phoneField);
		buttonPanel.setLayout(new FlowLayout());
		
		String[] array = {"7","8","9","4","5","6","1","2","3","*","0","+"};

		for (int i = 0; i < 12; ++i){
			PhoneButton newButton = new PhoneButton(array[i]);
			newButton.setPreferredSize(new Dimension(40,20));
			
			newButton.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent ae){
					content += "" + newButton.getC();
					phoneField.setText(content);
				}
			});
			
			buttonPanel.add(newButton);
		}


		
		phonePanel.add(buttonPanel, BorderLayout.CENTER);
		
		
		add(phonePanel, BorderLayout.CENTER);
		return phonePanel;
		
	}
	
	class PhoneButton extends JButton{
		String c;
		public PhoneButton(String name){
			super(name);
			this.c = name;
		}
		public String getC(){
			return this.c;
		}
	}

}

class ImageFrame extends ParentGUI{
	
	JMenuBar	menuBar 	= new JMenuBar();
	JMenu		imageMenu	= new JMenu("Image");
	JMenuItem	openItem	= new JMenuItem("Open Image");
	BufferedImage bi = null;
	ImagePanel	panel;
	
//	ImageIcon	picture		= new ImageIcon();
	
	public ImageFrame(String name){
		super(name);
		
		//make menu
		createMenuBar();
		
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	protected void createMenuBar(){
		//Add actions
//		openItem.addActionListener(new ImageListener(this));
		openItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				JFileChooser chooser = new JFileChooser();
				FileNameExtensionFilter imageFilter = new FileNameExtensionFilter("Images", "jpg", "png", "gif");
				chooser.setFileFilter(imageFilter);
				
				int userSelection = chooser.showOpenDialog(ImageFrame.this);
				
				//see if valid selection
				if (userSelection == JFileChooser.APPROVE_OPTION){
					File imageFile = chooser.getSelectedFile();
					try{
						
						bi = ImageIO.read(imageFile);
						panel.repaint();
						
					} catch (IOException e){
						System.out.println(e.getMessage());
					}
					
				}
				else if (userSelection == JFileChooser.CANCEL_OPTION){
					return;
				}
			}
		});
		
		
		//Make menu
		imageMenu.add(openItem);
		menuBar.add(imageMenu);
		
		//Add to JFrame
		setJMenuBar(menuBar);
	}
	
	protected JPanel createGUI(){
		panel = new ImagePanel(bi);
		
//		JLabel pictureLabel = new JLabel(picture);
//		panel.setLayout(new BorderLayout());
		
		return panel;
	}
	
	class ImagePanel extends JPanel{
		private BufferedImage image;
		public ImagePanel(BufferedImage im){
			this.image = im;
		}
		protected void paintComponent(Graphics g){
			super.paintComponent(g);
			if (bi != null){
			    int x = (this.getWidth() - bi.getWidth(null)) / 2;
				g.drawImage(bi, x,0,null);
			}
		}
	}
	
	

}









