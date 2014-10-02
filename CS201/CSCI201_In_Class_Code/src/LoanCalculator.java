import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class LoanCalculator extends JFrame{
	static final long serialVersionUID = 1;
	private JTextField principalTF, interestTF, yearsTF;
	private JLabel amountLabel;
	
	public LoanCalculator(){
		super("Loan Calculator");
		setSize(300,300);
		setLocation(500,100);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel centerPanel 		= new JPanel();
		centerPanel.setLayout(new BoxLayout(centerPanel, BoxLayout.Y_AXIS));;
		JLabel principalLabel 	= new JLabel("Principal");
		centerPanel.add(principalLabel);
		principalTF 			= new JTextField();
		centerPanel.add(principalTF);
		JLabel interestLabel 	= new JLabel("Annual Interest Rate");
		centerPanel.add(interestLabel);
		interestTF 				= new JTextField(15);
		centerPanel.add(interestTF);
		JLabel yearsLabel 		= new JLabel("Number of Years");
		centerPanel.add(yearsLabel);
		yearsTF 				= new JTextField();
		centerPanel.add(yearsTF);
		
		JButton calculateButton	= new JButton("Calculate");
		//add action
		calculateButton.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent ae){
				double principal 	= Double.parseDouble(principalTF.getText());
				double interest		= Double.parseDouble(interestTF.getText());
				double years		= Double.parseDouble(yearsTF.getText());
				double amountPaid	= (principal*interest*years) + principal;
				amountLabel.setText("Amount Paid" + amountPaid);
			}
		});
		
		JPanel bottomPanel		= new JPanel();
		bottomPanel.add(calculateButton);
		amountLabel				= new JLabel("Amount Paid: ");
		bottomPanel.add(amountLabel);
		centerPanel.add(bottomPanel);
		
		add(centerPanel);
	
		
		setVisible(true);
	}
	public static void main(String[] args){
		new LoanCalculator();
	}
	
	
}
