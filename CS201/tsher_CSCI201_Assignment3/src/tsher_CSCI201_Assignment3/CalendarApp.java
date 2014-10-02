package tsher_CSCI201_Assignment3;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.imageio.ImageIO;
import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.LineBorder;

public class CalendarApp extends JFrame{
	static final long serialVersionUID = 1;
	
	//GUI Variables
	static JPanel 							topPanel, monthPanel, menuPanel, eventsPanel, weekdayPanel, calendarPanel, eventManagerPanel, outerPanel, eventButtonsPanel, aboutPanel, picturePanel, namePanel;
	static JPanel							titlePanel, locationPanel, datePanel, startTimePanel, endTimePanel, dateWarningPanel, timeWarningPanel, buttonWarningPanel, eventChoicePanel, infoPanel;
	static JLabel 							topLabel, titleLabel, locationLabel, dateLabel, startTimeLabel, endTimeLabel, eventChoiceLabel, nameLabel, pictureLabel;
	static JLabel							dateWarningLabel, timeWarningLabel, buttonWarningLabel, titleWarningLabel, locWarningLabel;
	static JTextField						titleTextField, locationTextField;
	static JButton 							prevButton, nextButton, eventManagerTab, exportTab, aboutTab, backButton, saveButton, deleteButton;
	static JScrollPane						eventsScroller;
	static JComboBox<Integer>				yearBox, dateBox;
	static JComboBox<Integer>				startHourBox, startMinuteBox, endHourBox, endMinuteBox;
	static JComboBox<String>				monthBox, startAMPMBox, endAMPMBox, eventBox;
	static DefaultComboBoxModel<Integer>	yearChoices, dateChoices, startHourChoices, endHourChoices, startMinuteChoices, endMinuteChoices;
	static DefaultComboBoxModel<String>		monthChoices, startAMPMChoices, endAMPMChoices, eventChoices;
	static GridBagConstraints				gbc				= new GridBagConstraints();
	static ImageIcon						blueIcon, whiteIcon, grayIcon;
	
	//Export
	static BufferedWriter					writer;
	static JFileChooser						chooser;
	static File								saveFile;
	
	//Storage
	static ArrayList<DateButton>			dateButtonArray = new ArrayList<DateButton>();
	static ArrayList<Event>					eventArray		= new ArrayList<Event>();
	static ArrayList<Event>					eventsInDay		= new ArrayList<Event>(); 
	
	//Info Variables
	static Calendar calendar 				= new GregorianCalendar();
	static String[] monthArray 				= {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	static String[] monthArrayShort			= {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	static String[] weekdayArray			= {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	static int daysInMonth[] 				= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	static int currentYear 					= calendar.get(Calendar.YEAR);
	static int currentMonth 				= calendar.get(Calendar.MONTH);
	static int currentDate					= calendar.get(Calendar.DAY_OF_MONTH);
	static int selectedYear 				= calendar.get(Calendar.YEAR);
	static int selectedMonth				= calendar.get(Calendar.MONTH);
	static int selectedDate					= calendar.get(Calendar.DAY_OF_MONTH);

	
	static int chosenDatePosition;
	//Test
	
	static int tempNum = 0;
	
	//Constants
	static final float blueH 		= (float) 0.5947368;
	static final float blueS 		= (float) 0.8796296;
	static final float blueB 		= (float) 0.84705883;

	static final float lightBlueH 	= (float) 0.0947368;
	static final float lightBlueS 	= (float) 0.3796296;
	static final float lightBlueB 	= (float) 0.34705883;	
	
	public CalendarApp(){
		super("CS201_Calendar");
		
		//Create Objects
		topPanel 			= new JPanel();		menuPanel			= new JPanel();
		weekdayPanel 		= new JPanel();		eventsPanel			= new JPanel();
		calendarPanel		= new JPanel();		eventManagerPanel 	= new JPanel();
		outerPanel			= new JPanel();		titlePanel			= new JPanel();
		locationPanel		= new JPanel();		datePanel			= new JPanel();
		startTimePanel		= new JPanel();		endTimePanel		= new JPanel();
		eventButtonsPanel	= new JPanel();		dateWarningPanel	= new JPanel();
		timeWarningPanel	= new JPanel();		eventChoicePanel	= new JPanel();
		buttonWarningPanel	= new JPanel();		aboutPanel			= new JPanel();
		picturePanel		= new JPanel();		namePanel			= new JPanel();
		infoPanel			= new JPanel();
		titleLabel			= new JLabel("  Event Title");
		locationLabel		= new JLabel("  Event Location");
		dateLabel			= new JLabel("  Event Date");
		startTimeLabel		= new JLabel("  Event Start Time");
		endTimeLabel		= new JLabel("  Event End Time");
		dateWarningLabel	= new JLabel("");
		timeWarningLabel	= new JLabel("");
		topLabel 			= new JLabel(monthArray[currentMonth] + " " + currentYear);
		eventChoiceLabel	= new JLabel("  Choose an Event");
		buttonWarningLabel	= new JLabel("");
		titleWarningLabel	= new JLabel("");
		locWarningLabel		= new JLabel("");
		nameLabel			= new JLabel("Stephen Tsung-Han Sher");
		prevButton			= new JButton("<");
		nextButton			= new JButton(">");
		eventManagerTab		= new JButton("Event Manager ");
		exportTab			= new JButton("Export ");
		aboutTab			= new JButton("About ");
		backButton			= new JButton("Back");
		saveButton			= new JButton("Save");
		deleteButton		= new JButton("Delete");
		titleTextField		= new JTextField();
		locationTextField	= new JTextField();
		yearChoices			= new DefaultComboBoxModel<Integer>();
		monthChoices		= new DefaultComboBoxModel<String>();
		dateChoices			= new DefaultComboBoxModel<Integer>();
		startHourChoices	= new DefaultComboBoxModel<Integer>();
		startMinuteChoices	= new DefaultComboBoxModel<Integer>();
		startAMPMChoices 	= new DefaultComboBoxModel<String>();
		endHourChoices		= new DefaultComboBoxModel<Integer>();
		endMinuteChoices	= new DefaultComboBoxModel<Integer>();
		endAMPMChoices 		= new DefaultComboBoxModel<String>();
		eventChoices		= new DefaultComboBoxModel<String>();
		yearBox				= new JComboBox<Integer>(yearChoices);
		monthBox			= new JComboBox<String>(monthChoices);
		dateBox				= new JComboBox<Integer>(dateChoices);
		startHourBox		= new JComboBox<Integer>(startHourChoices);
		startMinuteBox		= new JComboBox<Integer>(startMinuteChoices);
		startAMPMBox		= new JComboBox<String>(startAMPMChoices);
		endHourBox			= new JComboBox<Integer>(endHourChoices);
		endMinuteBox		= new JComboBox<Integer>(endMinuteChoices);
		endAMPMBox			= new JComboBox<String>(endAMPMChoices);
		eventBox			= new JComboBox<String>(eventChoices);

		//set icons
		BufferedImage bi;
		Image scaled;
		
		try{
			bi = ImageIO.read(new File("white_event.jpg"));
			scaled = bi.getScaledInstance(60,60, Image.SCALE_SMOOTH);
			whiteIcon = new ImageIcon(scaled);
			
			bi = ImageIO.read(new File("blue_event.jpg"));
			scaled = bi.getScaledInstance(60, 60, Image.SCALE_SMOOTH);
			blueIcon = new ImageIcon(scaled);
			
			bi = ImageIO.read(new File("gray_event.jpg"));
			scaled = bi.getScaledInstance(60, 60,  Image.SCALE_SMOOTH);
			grayIcon = new ImageIcon(scaled);
			
		} catch (IOException IOE){
			System.out.println(IOE.getMessage());
		}
		
		//JFrame settings
		setSize(430,700);
		setLocation(400,100);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new FlowLayout());
		setBackground(Color.WHITE);

		
		//Set sizes for cards
		calendarPanel.		setPreferredSize(new Dimension(420,700));
		eventManagerPanel.	setPreferredSize(new Dimension(420,700));
		outerPanel.			setPreferredSize(new Dimension(430,700));
		calendarPanel.		setLayout(new FlowLayout(FlowLayout.LEFT));
		eventManagerPanel.	setLayout(new FlowLayout(FlowLayout.LEFT));
		outerPanel.			setLayout(new CardLayout());
		outerPanel.			setBackground(Color.WHITE);
		calendarPanel.		setBackground(Color.WHITE);
		
		//-----------------------------------------------------------------
		//							Calendar Panel
		//-----------------------------------------------------------------		
		//Menu bar
		eventManagerTab.	setBorder(null);
		exportTab.			setBorder(null);
		aboutTab.			setBorder(null);
		eventManagerTab.	addActionListener(new CardAction("emPanel", outerPanel));
		eventManagerTab.	addActionListener(new EventManagerAction());
		eventManagerTab.	setFont(new Font("Helvetica", Font.PLAIN, 12));
		exportTab.			setFont(new Font("Helvetica", Font.PLAIN, 12));
		aboutTab.			setFont(new Font("Helvetica", Font.PLAIN, 12));
		menuPanel.			setPreferredSize(new Dimension(420,20));
		menuPanel.			setLayout(new FlowLayout(FlowLayout.LEFT));
		menuPanel.			add(eventManagerTab);
		menuPanel.			add(exportTab);
		menuPanel.			add(aboutTab);
		menuPanel.			setBackground(Color.WHITE);
		
		//Next and Previous buttons
		prevButton.			setBorder(null);
		nextButton.			setBorder(null);
		nextButton.			setPreferredSize(new Dimension(60,60));
		prevButton.			setPreferredSize(new Dimension(60,60));
		prevButton.			setFont(new Font("Helvetica", Font.BOLD, 16));
		nextButton.			setFont(new Font("Helvetica", Font.BOLD, 16));
		prevButton.			setForeground(Color.GRAY);
		nextButton.			setForeground(Color.GRAY);
		
		//Add actions
		prevButton.			addActionListener(new PrevButtonAction());
		nextButton.			addActionListener(new NextButtonAction());
		exportTab.			addActionListener(new ExportAction(this));
		aboutTab.			addActionListener(new AboutAction(this));
				
		//Top bar
		topPanel.			setPreferredSize(new Dimension(420,30));
		topPanel.			setLayout(new BorderLayout());
		topLabel.			setHorizontalAlignment(SwingConstants.CENTER);	
		topLabel.			setFont(new Font("Helvetica", Font.BOLD, 20));
		topPanel.			setBackground(Color.WHITE);
		topPanel.			add(topLabel	, BorderLayout.CENTER);
		topPanel.			add(prevButton	, BorderLayout.WEST);
		topPanel.			add(nextButton	, BorderLayout.EAST);

		//Weekday bar
		weekdayPanel.		setPreferredSize(new Dimension(420,20));
		weekdayPanel.		setLayout(new GridLayout(1,7));
		weekdayPanel.		setBackground(Color.WHITE);

		for (int i = 0; i < 7; ++i){
			JLabel dayLabel = new JLabel(weekdayArray[i], SwingConstants.CENTER);
			dayLabel.setSize(60,30);
			weekdayPanel.add(dayLabel);
		}

		//Events Panel
		eventsScroller		= new JScrollPane(eventsPanel, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		eventsScroller.		setWheelScrollingEnabled(true);
		eventsScroller.		setBorder(null);
		eventsScroller.		setPreferredSize(new Dimension(420,220));
		eventsScroller.		setBackground(Color.WHITE);

		//-----------------------------------------------------------------
		//							Event Manager
		//-----------------------------------------------------------------
		eventManagerPanel.	setBackground(Color.WHITE);
		
		//Setup Panels
		eventChoicePanel.	setPreferredSize(new Dimension(420,60));
		titlePanel.			setPreferredSize(new Dimension(420,90));
		locationPanel.		setPreferredSize(new Dimension(420,90));
		datePanel.			setPreferredSize(new Dimension(420,60));
		startTimePanel.		setPreferredSize(new Dimension(420,90));
		endTimePanel.		setPreferredSize(new Dimension(420,60));
		dateWarningPanel.	setPreferredSize(new Dimension(420,30));
		timeWarningPanel.	setPreferredSize(new Dimension(420,30));
		buttonWarningPanel.	setPreferredSize(new Dimension(420,30));
		eventButtonsPanel.	setPreferredSize(new Dimension(420,60));

		eventChoicePanel.	setBorder(new LineBorder(Color.WHITE));
		titlePanel.			setBorder(new LineBorder(Color.WHITE));
		locationPanel.		setBorder(new LineBorder(Color.WHITE));
		datePanel.			setBorder(new LineBorder(Color.WHITE));
		startTimePanel.		setBorder(new LineBorder(Color.WHITE));
		endTimePanel.		setBorder(new LineBorder(Color.WHITE));
		dateWarningPanel.	setBorder(new LineBorder(Color.WHITE));
		timeWarningPanel.	setBorder(new LineBorder(Color.WHITE));
		buttonWarningPanel.	setBorder(new LineBorder(Color.WHITE));

		dateWarningPanel.	setLayout(new FlowLayout(FlowLayout.CENTER));
		timeWarningPanel.	setLayout(new FlowLayout(FlowLayout.CENTER));
		eventButtonsPanel.	setLayout(new FlowLayout(FlowLayout.CENTER));

		eventChoicePanel.	setBackground(Color.WHITE);
		titlePanel.			setBackground(Color.WHITE);
		locationPanel.		setBackground(Color.WHITE);
		datePanel.			setBackground(Color.WHITE);
		startTimePanel.		setBackground(Color.WHITE);
		endTimePanel.		setBackground(Color.WHITE);
		dateWarningPanel.	setBackground(Color.WHITE);
		timeWarningPanel.	setBackground(Color.WHITE);
		buttonWarningPanel.	setBackground(Color.WHITE);
		eventButtonsPanel.	setBackground(Color.WHITE);
		
		// titlePanel.		setBackground(Color.getHSBColor(lightBlueH, lightBlueS, lightBlueB));
		// locationPanel.	setBackground(Color.getHSBColor(lightBlueH, lightBlueS, lightBlueB));
		// datePanel.		setBackground(Color.getHSBColor(lightBlueH, lightBlueS, lightBlueB));
		// startTimePanel.	setBackground(Color.getHSBColor(lightBlueH, lightBlueS, lightBlueB));
		// endTimePanel.	setBackground(Color.getHSBColor(lightBlueH, lightBlueS, lightBlueB));

		//Setup Labels
		eventChoiceLabel.	setPreferredSize(new Dimension(420, 20));
		titleLabel.			setPreferredSize(new Dimension(420, 20));
		locationLabel.		setPreferredSize(new Dimension(420, 20));
		dateLabel.			setPreferredSize(new Dimension(420, 20));
		startTimeLabel.		setPreferredSize(new Dimension(420, 20));
		endTimeLabel.		setPreferredSize(new Dimension(420, 20));

		dateWarningLabel.	setForeground(Color.RED);
		timeWarningLabel.	setForeground(Color.RED);
		buttonWarningLabel.	setForeground(Color.RED);
		titleWarningLabel.	setForeground(Color.RED);
		locWarningLabel.	setForeground(Color.RED);

		eventChoiceLabel.	setBackground(Color.WHITE);
		titleLabel.			setBackground(Color.WHITE);
		locationLabel.		setBackground(Color.WHITE);
		dateLabel.			setBackground(Color.WHITE);
		startTimeLabel.		setBackground(Color.WHITE);
		endTimeLabel.		setBackground(Color.WHITE);

		eventChoiceLabel.	setFont(new Font("Helvetica", Font.BOLD, 16));
		titleLabel.			setFont(new Font("Helvetica", Font.BOLD, 16));
		locationLabel.		setFont(new Font("Helvetica", Font.BOLD, 16));
		dateLabel.			setFont(new Font("Helvetica", Font.BOLD, 16));
		startTimeLabel.		setFont(new Font("Helvetica", Font.BOLD, 16));
		endTimeLabel.		setFont(new Font("Helvetica", Font.BOLD, 16));
		dateWarningLabel.	setFont(new Font("Helvetica", Font.PLAIN, 12));
		timeWarningLabel.	setFont(new Font("Helvetica", Font.PLAIN, 12));
		buttonWarningLabel.	setFont(new Font("Helvetica", Font.PLAIN, 12));
		titleWarningLabel.	setFont(new Font("Helvetica", Font.PLAIN, 12));
		locWarningLabel.	setFont(new Font("Helvetica", Font.PLAIN, 12));

		
		//Setup TextFields
		titleTextField.		setPreferredSize(new Dimension(400,30));
		titleTextField.		setFont(new Font("Helvetica", Font.PLAIN, 16));
		locationTextField.	setPreferredSize(new Dimension(400,30));
		locationTextField.	setFont(new Font("Helvetica", Font.PLAIN, 16));

		//Initialize ComboBoxes
		for (int i = 0; i < 60; ++i){
			yearChoices.addElement((i+1990));
		}
		for (int i = 0; i < 12; ++i){
			monthChoices.addElement(monthArrayShort[i]);
		}
		for (int i = 1; i < 32; ++i){
			dateChoices.addElement(i);
		}
		for (int i = 1; i < 13; ++i){
			startHourChoices.addElement(i);
			endHourChoices.addElement(i);
		}
		for (int i = 0; i < 60; i = i+5){
			startMinuteChoices.addElement(i);
			endMinuteChoices.addElement(i);
		}
		startAMPMChoices.	addElement("AM");
		startAMPMChoices.	addElement("PM");
		endAMPMChoices.		addElement("AM");
		endAMPMChoices.		addElement("PM");

		//Initialize combo box values
		yearBox.			setSelectedIndex(currentYear-1990);
		monthBox.			setSelectedIndex(currentMonth);
		dateBox.			setSelectedIndex(currentDate-1);
		
		if (calendar.get(Calendar.HOUR_OF_DAY) > 12 ){
			//subtract 13 (extra 1 for index) and set to PM
			startHourBox.	setSelectedIndex(calendar.get(Calendar.HOUR_OF_DAY)-13);
			startAMPMBox.	setSelectedIndex(1);
			endHourBox.		setSelectedIndex(calendar.get(Calendar.HOUR_OF_DAY)-13);
			endAMPMBox.		setSelectedIndex(1);
		}
		else{
			startHourBox.	setSelectedIndex(calendar.get(Calendar.HOUR_OF_DAY)-1);
			endHourBox.		setSelectedIndex(calendar.get(Calendar.HOUR_OF_DAY)-1);
		}
		startMinuteBox.		setSelectedIndex(calendar.get(Calendar.MINUTE)/5);
		endMinuteBox.		setSelectedIndex(calendar.get(Calendar.MINUTE)/5);
		
		//Set Buttons
		backButton.			addActionListener(new CardAction("cPanel", outerPanel));
		deleteButton.		addActionListener(new DeleteAction());
		saveButton.			addActionListener(new SaveAction());
		backButton.			setFont(new Font("Helvetica", Font.PLAIN, 16));
		saveButton.			setFont(new Font("Helvetica", Font.PLAIN, 16));
		deleteButton.		setFont(new Font("Helvetica", Font.PLAIN, 16));

		//Add the buttons
		eventButtonsPanel.	add(backButton);
		eventButtonsPanel.	add(deleteButton);
		eventButtonsPanel.	add(saveButton);
		eventButtonsPanel.	add(buttonWarningPanel);

		//Add action to eventBox
		eventBox.addActionListener(new PopulateAction());
		
		//Add to Panels
		eventChoicePanel.	add(eventChoiceLabel);
		eventChoicePanel.	add(eventBox);
		
		titlePanel.			add(titleLabel);
		titlePanel.			add(titleTextField);
		titlePanel.			add(titleWarningLabel);

		locationPanel.		add(locationLabel);
		locationPanel.		add(locationTextField);
		locationPanel.		add(locWarningLabel);
		
		datePanel.			add(dateLabel);
		datePanel.			add(yearBox);
		datePanel.			add(monthBox);
		datePanel.			add(dateBox);
		datePanel.			add(dateWarningLabel);
		
		startTimePanel.		add(startTimeLabel);
		startTimePanel.		add(startHourBox);
		startTimePanel.		add(startMinuteBox);
		startTimePanel.		add(startAMPMBox);
			
		endTimePanel.		add(endTimeLabel);
		endTimePanel.		add(endHourBox);
		endTimePanel.		add(endMinuteBox);
		endTimePanel.		add(endAMPMBox);
		endTimePanel.		add(timeWarningLabel);
		
		dateWarningPanel.	add(dateWarningLabel);
		timeWarningPanel.	add(timeWarningLabel);
		buttonWarningPanel.	add(buttonWarningLabel);

		//Add the panels into eventManagerPanel
		eventManagerPanel.	add(eventChoicePanel);
		eventManagerPanel.	add(titlePanel);
		eventManagerPanel.	add(locationPanel);
		eventManagerPanel.	add(datePanel);
		eventManagerPanel.	add(dateWarningPanel);
		eventManagerPanel.	add(startTimePanel);
		eventManagerPanel.	add(endTimePanel);
		eventManagerPanel.	add(timeWarningPanel);
		eventManagerPanel.	add(eventButtonsPanel);
				
		//-----------------------------------------------------------------
		//							About Panel
		//-----------------------------------------------------------------
		aboutPanel.			setPreferredSize(new Dimension(500,500));
		picturePanel.		setPreferredSize(new Dimension(300,375));
		namePanel.			setPreferredSize(new Dimension(500,60));
		infoPanel.			setPreferredSize(new Dimension(300,65));
		
		aboutPanel.			setBorder(null);
		picturePanel.		setBorder(null);
		nameLabel.			setBorder(null);
		namePanel.			setBorder(null);
		infoPanel.			setBorder(null);
		
		aboutPanel.			setBackground(Color.WHITE);
		picturePanel.		setBackground(Color.WHITE);
		nameLabel.			setBackground(Color.WHITE);
		namePanel.			setBackground(Color.WHITE);
		infoPanel.			setBackground(Color.WHITE);
		
		namePanel.			setLayout(new FlowLayout(FlowLayout.CENTER));
		aboutPanel.			setLayout(new GridBagLayout());
		
		JLabel infoLabelA	= new JLabel("University of Southern California, Junior");
		JLabel infoLabelB	= new JLabel("Computer Engineering Computer Science");
		JLabel infoLabelC	= new JLabel("Prefers adding milk before cereal");
		
		nameLabel.			setFont(new Font("Helvetica", Font.PLAIN, 24));
		infoLabelA.			setFont(new Font("Helvetica", Font.PLAIN, 12));
		infoLabelB.			setFont(new Font("Helvetica", Font.PLAIN, 12));
		infoLabelC.			setFont(new Font("Helvetica", Font.PLAIN, 12));
		// infoLabelA.			setPreferredSize(new Dimension(450,15));
		// infoLabelB.			setPreferredSize(new Dimension(450,15));
		// infoLabelC.			setPreferredSize(new Dimension(450,15));


		namePanel.			add(nameLabel);
		infoPanel.			add(infoLabelA);
		infoPanel.			add(infoLabelB);
		infoPanel.			add(infoLabelC);
		
		//Add picture
		try{
			bi 					= ImageIO.read(new File("Sher_Tsung-Han.JPG"));
			scaled				= bi.getScaledInstance(300,375, Image.SCALE_SMOOTH);
			ImageIcon ii		= new ImageIcon(scaled);
			pictureLabel		= new JLabel(ii);
			picturePanel.		add(pictureLabel);
		} catch (IOException IOE){
			System.out.println(IOE.getMessage());
		}
		
		//Add components
		gbc.gridx = 0;
		gbc.gridy = 0;
		aboutPanel.add(namePanel, gbc);

		gbc.gridx = 0;
		gbc.gridy = 1;
		aboutPanel.add(picturePanel, gbc);
		
		gbc.gridx = 0;
		gbc.gridy = 2;
		aboutPanel.add(infoPanel, gbc);
		
		//Setup month panel
		createMonthPanel();
		createEventsPanel();

		//Add components
		calendarPanel.		add(menuPanel);
		calendarPanel.		add(topPanel);
		calendarPanel.		add(weekdayPanel);
		calendarPanel.		add(monthPanel);
		calendarPanel.		add(eventsScroller);
				
		//add the cards to outerPanel
		outerPanel.			add(calendarPanel, "cPanel");
		outerPanel.			add(eventManagerPanel, "emPanel");
		
		//add outerPanel
		add(outerPanel);
		
		
		setVisible(true);		
	}
	
	
	public static void main(String [] args){
		new CalendarApp();
	}
	
	
	//Helpers
	private static int convertTime(int hour, int minute, String AMPM){
		int time = hour;
		if (AMPM.equals("PM")){
				time += 12;
		}
		time *= 100;
		time += minute;
		
		return time;
	}
	
	private static boolean isValidTime(int startHour, int startMinute, String startAMPM, int endHour, int endMinute, String endAMPM){
		//convert time into an int
		int start	= convertTime(startHour, startMinute, startAMPM);
		int end		= convertTime(endHour, endMinute, endAMPM);
		if (start > end){
			return false;
		}
		return true;
		
	}
	
	private static boolean isValidDate(int year, String monthString, int date){
		//convert string month into int
		int month = -1;
		for (int i = 0; i < 12; ++i){
			if (monthString.equals(monthArrayShort[i])){
				month = i;
				break;
			}
		}
		
		if (month == -1){
			System.out.println("Stephen you're doing something wrong");
		}
				
		boolean isLeap		= false;
		
		//first determine if leap year
		if (year % 4 == 0){
			if (year % 100 == 0){
				if (year % 400 == 0)
					isLeap = true;
				else
					isLeap = false;
			}
			else{
				isLeap = true;
			}
		}
		else{
			isLeap = false;
		}

		if (daysInMonth[month] < date){
			//second test for February
			if (month == 1 && isLeap){
				if (date == 29)
					return true;
				else
					return false;
			}
			return false;
		}
		return true;
		
	}
	
	public static ArrayList<Event> getEventArray(){
		ArrayList<Event> returnList = new ArrayList<Event>();
		for (int i = 0; i < eventArray.size(); ++i){
			if (eventArray.get(i).getYear() == selectedYear && eventArray.get(i).getMonth() == selectedMonth && eventArray.get(i).getDate() == selectedDate){
				returnList.add(eventArray.get(i));
			}
		}
		//No events in this date, return null
		if (returnList.size() == 0){
			return null;
		}
		else{
			return returnList;
		}
	}
	
	public static void createEventsPanel(){
		eventsPanel = new JPanel();
		eventsPanel.setBorder(null);
		eventsPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
		eventsPanel.setBackground(Color.WHITE);

		
		if (chosenDatePosition == -1){
			eventsPanel.setPreferredSize(new Dimension(400,220));
			JLabel noDate = new JLabel("No Date Selected");
			noDate.setPreferredSize(new Dimension(420,25));
			noDate.setFont(new Font("Helvetica", Font.PLAIN, 16));
			eventsPanel.add(noDate);
		}
		else{
			//Add the events
			//See if there's events on this day

			ArrayList<Event> displayEvents = getEventArray();
			if (displayEvents != null){
				eventsPanel.setPreferredSize(new Dimension(400,30*displayEvents.size()));
				//If there are events on this day, get them
				for (int i = 0; i < displayEvents.size(); ++i){
					JLabel newEvent = new JLabel(displayEvents.get(i).getLabel());
					newEvent.setPreferredSize(new Dimension(420, 25));
					newEvent.setFont(new Font("Helvetica", Font.PLAIN, 16));
					eventsPanel.add(newEvent);
				}
			}
			else{
				eventsPanel.setPreferredSize(new Dimension(400,220));
				JLabel noEvent = new JLabel("No Events");
				noEvent.setPreferredSize(new Dimension(420,25));
				noEvent.setFont(new Font("Helvetica", Font.PLAIN, 16));
				eventsPanel.add(noEvent);
			}
			
		}
		eventsScroller.setViewportView(eventsPanel);
	}

	public static void createMonthPanel(){
		//PanelSetup
		monthPanel 		= new JPanel();
		
		//we need a grid 7 by 5
		monthPanel.setLayout(new GridLayout(6,7));
		monthPanel.setPreferredSize(new Dimension(420,360));

		//Figure out format for panel
		//Initialize information
		int numOfDays, startingDate;
		calendar.set(currentYear, currentMonth, 1);
		numOfDays 		= calendar.getActualMaximum(GregorianCalendar.DAY_OF_MONTH);
		startingDate	= calendar.get(GregorianCalendar.DAY_OF_WEEK);	//Sunday = 1, Saturday is 7
		
		//Need previous month's information
		int prevNumOfDays;
		calendar.set(currentYear, (currentMonth-1), 1);
		prevNumOfDays 		= calendar.getActualMaximum(GregorianCalendar.DAY_OF_MONTH);

		//for arrays, subtract 1
		--startingDate;
				
		//fill the buttons
		int dateCounter = 1;
		int nextMonthCounter = 1;
		int prevMonthCounter = prevNumOfDays-startingDate+1;
		
		for (int i = 0; i < 42; ++i){
			DateButton bt;
			if (i < startingDate){
				bt = new DateButton(("" + prevMonthCounter++));
				bt.setForeground(Color.GRAY);
				bt.inMonth = false;
				bt.addActionListener(new DateAction(i));
			}
			else if(i <= (numOfDays + startingDate-1)){
				bt = new DateButton(("" + dateCounter++));
				bt.setForeground(Color.BLACK);
				bt.inMonth = true;
				bt.addActionListener(new DateAction(i));
				//Only valid date has date info
				bt.year 	= currentYear;
				bt.month 	= currentMonth;
				bt.date 	= currentDate;
				
				//-----TEST add an event//-----//-----//-----//-----//-----
//				Event newEvent = new Event(currentYear, currentMonth, currentDate, 1, 1, "AM", 2, 2, "AM", ("Test Title" + i + " " + i), "Location");
//				eventArray.add(newEvent);
//				bt.numOfEvents++;
				//-----//-----//-----//-----//-----//-----//-----//-----//-----//-----
				
			}
			else{
				bt = new DateButton(("" + nextMonthCounter++));
				bt.setForeground(Color.GRAY);
				bt.inMonth = false;
				bt.addActionListener(new DateAction(i));

			}
			bt.setHorizontalTextPosition(SwingConstants.CENTER);

//			//try image
//			try{
//				ImageIcon ii;
//				BufferedImage bi = ImageIO.read(new File("white_event.jpg"));
//				Image scaled = bi.getScaledInstance(60,60, Image.SCALE_SMOOTH);
//				ii = new ImageIcon(scaled);
//				bt.setIcon(ii);
//
//			} catch (IOException IOE){
//				System.out.println(IOE.getMessage());
//			}
			bt.setBackground(Color.WHITE);
			bt.setOpaque(true);
			
			
			//if current date
			if (dateCounter-1 == currentDate){
				bt.setBackground(Color.getHSBColor(blueH, blueS, blueB));
				bt.setOpaque(true);
				bt.setForeground(Color.WHITE);
				chosenDatePosition = dateCounter-1;
				if (dateCounter-1 == daysInMonth[currentMonth] && currentDate == daysInMonth[currentMonth]){
					dateCounter = -1;		//get rid of dateCounter if last day of the month
				}
				
			}
			
			//Formatting for each panel
			bt.setFont(new Font("Helvetica", Font.BOLD, 24));
			bt.setBorder(new LineBorder(Color.WHITE));
			bt.setPreferredSize(new Dimension(60,60));
			bt.position = i;
			
			//Every button start off with no events
			bt.numOfEvents = 0;
			
			dateButtonArray.add(bt);
			monthPanel.add(bt);
		}

		
		
	}
	
	private static void colorButton(DateButton bt, String color){
		//color only in month
		if (!bt.inMonth)
			return;
		
		if (color.equals("GRAY")){
			if (bt.hasEvent){
				bt.setIcon(grayIcon);
			}
			else{
				bt.setIcon(null);
				bt.setBackground(Color.GRAY);
				bt.setOpaque(true);
			}
			bt.setForeground(Color.WHITE);
		}
		else if (color.equals("BLUE")){
			if (bt.hasEvent){
				bt.setIcon(blueIcon);
			}
			else{
				bt.setIcon(null);
				bt.setBackground(Color.getHSBColor(blueH, blueS, blueB));
				bt.setOpaque(true);
			}
			bt.setForeground(Color.WHITE);
		}
		else{
			//white
			if (bt.hasEvent){
				bt.setIcon(whiteIcon);
			}
			else{
				bt.setIcon(null);
				bt.setBackground(Color.WHITE);
				bt.setOpaque(true);
			}
			bt.setForeground(Color.BLACK);

		}
	}
	
	private static void refreshMonthPanel(int month, int year){
		//Update topPanel
		topLabel.setText(monthArray[month] + " " + year);

		//Figure out format for panel
		//Initialize information
		int numOfDays, startingDate;
		calendar.set(year, month, 1);
		numOfDays 		= calendar.getActualMaximum(GregorianCalendar.DAY_OF_MONTH);
		startingDate	= calendar.get(GregorianCalendar.DAY_OF_WEEK);	//Sunday = 1, Saturday is 7
		
		//Need previous month's information
		int prevNumOfDays;
		calendar.set(year, month-1, 1);
		prevNumOfDays 		= calendar.getActualMaximum(GregorianCalendar.DAY_OF_MONTH);

		//for arrays, subtract 1
		--startingDate;
				
		//fill the buttons
		int dateCounter = 1;
		int nextMonthCounter = 1;
		int prevMonthCounter = prevNumOfDays-startingDate+1;
		
		for (int i = 0; i < 42; ++i){
			if (i < startingDate){
				dateButtonArray.get(i).setText("" + prevMonthCounter++);
				dateButtonArray.get(i).inMonth = false;
				dateButtonArray.get(i).setForeground(Color.GRAY);
			}
			else if(i <= (numOfDays + startingDate-1)){
				dateButtonArray.get(i).setText("" + dateCounter);
				dateButtonArray.get(i).inMonth = true;
				dateButtonArray.get(i).setForeground(Color.BLACK);
				// Date info
				dateButtonArray.get(i).year = selectedYear;
				dateButtonArray.get(i).month = selectedMonth;
				dateButtonArray.get(i).date = dateCounter++;
				
				//see if button as event
				for (int j = 0; j < eventArray.size(); ++j){
					if (eventArray.get(j).getYear() 	== dateButtonArray.get(i).year &&
						eventArray.get(j).getMonth() 	== dateButtonArray.get(i).month &&
						eventArray.get(j).getDate()		== dateButtonArray.get(i).date){
						dateButtonArray.get(i).hasEvent = true;
					}
				}
			}
			else{
				dateButtonArray.get(i).setText("" + nextMonthCounter++);
				dateButtonArray.get(i).inMonth = false;
				dateButtonArray.get(i).setForeground(Color.GRAY);
			}
			

			//Color panels
			//priority: current Date
			if (dateCounter-1 == currentDate && month == currentMonth && year == currentYear){
				if (chosenDatePosition == -2){
					//if coming out of event manager
					chosenDatePosition = i;
				}
//				dateButtonArray.get(i).setForeground(Color.WHITE);
//				dateButtonArray.get(i).setBackground(Color.getHSBColor(blueH, blueS, blueB));
//				dateButtonArray.get(i).setOpaque(true);
				colorButton(dateButtonArray.get(i), "BLUE");
			}
			//other wise the selected date
			else if (dateCounter-1 == selectedDate && month == selectedMonth && year == selectedYear && chosenDatePosition == -2){
				chosenDatePosition = i;
//				dateButtonArray.get(i).setForeground(Color.WHITE);
//				dateButtonArray.get(i).setBackground(Color.GRAY);
//				dateButtonArray.get(i).setOpaque(true);
				colorButton(dateButtonArray.get(i), "GRAY");
			}
			else{
				colorButton(dateButtonArray.get(i), "WHITE");
			}

		}
		
		if (chosenDatePosition != -1){
			selectedDate = dateButtonArray.get(chosenDatePosition).date;
		}
		else{
			selectedDate = 0;
		}
		
		//Display the events
		createEventsPanel();

	}
	
	//Actions
	static class PrevButtonAction implements ActionListener{
		public void actionPerformed(ActionEvent ae){
			if (selectedMonth == 0){
				--selectedYear;
				selectedMonth = 11;
			}
			else{
				--selectedMonth;
			}
			
			chosenDatePosition = -1;
			refreshMonthPanel(selectedMonth, selectedYear);
		}
	}
	
	static class NextButtonAction implements ActionListener{
		public void actionPerformed(ActionEvent ae){
			if (selectedMonth == 11){
				++selectedYear;
				selectedMonth = 0;
			}
			else{
				++selectedMonth;
			}
			
			chosenDatePosition = -1;
			refreshMonthPanel(selectedMonth, selectedYear);
		}
	}
	
	static class PopulateAction implements ActionListener{
		public void actionPerformed(ActionEvent ae){
			
			//if it's a new event or if there's only new event, do nothing
			System.out.println("index: " + eventBox.getSelectedIndex());
			if (eventBox.getSelectedIndex() <= 0){
				return;
			}
			
			Event selectedEvent = null;
			
			//get the right event
			String eventName = (String)eventBox.getSelectedItem();
			for (int i = 0; i < eventsInDay.size(); ++i){
				if (eventsInDay.get(i).getTitle().equals(eventName)){
					selectedEvent = eventsInDay.get(i);
					break;
				}
			}
			
			//now populate the boxes
			titleTextField.		setText(selectedEvent.getTitle());
			locationTextField.	setText(selectedEvent.getLocation());
			
			yearBox.			setSelectedIndex(selectedEvent.getYear()-1990);
			monthBox.			setSelectedIndex(selectedEvent.getMonth());
			dateBox.			setSelectedIndex(selectedEvent.getDate()-1);
				
			startHourBox.		setSelectedIndex(selectedEvent.getStartHour()-1);
			startMinuteBox.		setSelectedIndex(selectedEvent.getStartMinute()/5);
			startAMPMBox.		setSelectedIndex(selectedEvent.getStartAMPM());
			endHourBox.			setSelectedIndex(selectedEvent.getEndHour()-1);
			endMinuteBox.		setSelectedIndex(selectedEvent.getEndMinute()/5);
			endAMPMBox.			setSelectedIndex(selectedEvent.getEndAMPM());
		}
	}
	
	static class EventManagerAction implements ActionListener{
		public void actionPerformed(ActionEvent ae){
			//clear all the warning labels and text fields
			dateWarningLabel.	setText("");
			timeWarningLabel.	setText("");
			buttonWarningLabel.	setText("");
			titleWarningLabel.	setText("");
			locWarningLabel.	setText("");
			titleTextField.		setText("");
			locationTextField.	setText("");
			
			//clear array
			System.out.println("Size: " + eventsInDay.size());
			eventsInDay.clear();
			//Add in all the events in the day
			for (int i = 0; i < eventArray.size(); ++i){
				if (eventArray.get(i).getYear() == selectedYear && eventArray.get(i).getMonth() == selectedMonth && eventArray.get(i).getDate() == selectedDate){
					eventsInDay.add(eventArray.get(i));
				}
			}
			
			//clear contents in box and re-add the contents in the box
			eventChoices.		removeAllElements();
			eventChoices.		addElement("New Event");
			eventBox.			setSelectedIndex(0);
			
			//Initialize combo box values
			yearBox.			setSelectedIndex(selectedYear-1990);
			monthBox.			setSelectedIndex(selectedMonth);
			dateBox.			setSelectedIndex(selectedDate-1);
			
			if (calendar.get(Calendar.HOUR_OF_DAY) > 12 ){
				//subtract 13 (extra 1 for index) and set to PM
				startHourBox.	setSelectedIndex(calendar.get(Calendar.HOUR_OF_DAY)-13);
				startAMPMBox.	setSelectedIndex(1);
				endHourBox.		setSelectedIndex(calendar.get(Calendar.HOUR_OF_DAY)-13);
				endAMPMBox.		setSelectedIndex(1);
			}
			else{
				startHourBox.	setSelectedIndex(calendar.get(Calendar.HOUR_OF_DAY)-1);
				endHourBox.		setSelectedIndex(calendar.get(Calendar.HOUR_OF_DAY)-1);
			}
			startMinuteBox.		setSelectedIndex(calendar.get(Calendar.MINUTE)/5);
			endMinuteBox.		setSelectedIndex(calendar.get(Calendar.MINUTE)/5);
			
			//Get events into box
			for (int i = 0; i < eventsInDay.size(); ++i){
				eventChoices.addElement(eventsInDay.get(i).getTitle());
			}
		}
	}
	
	static class ExportAction implements ActionListener{
		private JFrame parent;
		public ExportAction(JFrame parent){
			this.parent = parent;
		}
		public void actionPerformed(ActionEvent ae){
			//Choose a file
			chooser = new JFileChooser();
			chooser.setDialogTitle("Export Calendar Events");
			
			//Get action
			int userSelection = chooser.showSaveDialog(parent);
			
			//Valid file, make sure ends in csv
			if (userSelection == JFileChooser.APPROVE_OPTION){
				File saveFile = chooser.getSelectedFile();
				if (!saveFile.getAbsolutePath().contains(".csv")){
					saveFile = new File(saveFile.getAbsolutePath() + ".csv");
				}
				try{
					writer = new BufferedWriter(new FileWriter(saveFile));
					
					for (int i = 0; i < eventArray.size(); ++i){
						writer.append(eventArray.get(i).write());
					}
					writer.close();
					
				} catch (IOException IOE){
					System.out.println(IOE.getMessage());
				}
			}
		}
	}
	
	static class AboutAction implements ActionListener{
		JFrame parent;
		public AboutAction(JFrame parent){
			this.parent = parent;
		}
		public void actionPerformed(ActionEvent ae){
			System.out.println("About");


			JOptionPane.showMessageDialog(parent, aboutPanel, "About", JOptionPane.PLAIN_MESSAGE);
		}
	}
	
	static class DateAction implements ActionListener{
		private int position;
		public DateAction(int position){
			this.position 	= position;
		}
		public void actionPerformed(ActionEvent ae){
			if (dateButtonArray.get(position).inMonth){
				chosenDatePosition = position;
	
				//Reset all the colors			
				refreshMonthPanel(selectedMonth, selectedYear);
				
				//Change color of clicked one if not the current date
				if (selectedDate != currentDate || selectedMonth != currentMonth & selectedYear != currentYear){
//					dateButtonArray.get(position).setBackground(Color.GRAY);
//					dateButtonArray.get(position).setOpaque(true);
//					dateButtonArray.get(position).setForeground(Color.WHITE);
					colorButton(dateButtonArray.get(position), "GRAY");
					//dateButtonArray.get(position).setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
				}
			}
			
		}
	}
	
	static class CardAction implements ActionListener{
		private String cardString;
		private JPanel cardPanel;
		public CardAction(String cardString, JPanel cardPanel){
			this.cardString = cardString;
			this.cardPanel  = cardPanel;
		}
		public void actionPerformed(ActionEvent ae){
			CardLayout cl   = (CardLayout)cardPanel.getLayout();
			cl.show(cardPanel, cardString);		
		}
	}
	
	static class DeleteAction implements ActionListener{
		public void actionPerformed(ActionEvent ae){
			//Cannot delete new event
			if (eventBox.getSelectedIndex() == 0){
				buttonWarningLabel.setText("You cannot delete a New Event");
				//do nothing, afterwards
				return;
			}
			else{
				//delete the selected event
				eventArray.remove(eventsInDay.get(eventBox.getSelectedIndex()-1));
				eventBox.removeItemAt(eventBox.getSelectedIndex());
				
				//set hasEvent boolean
				if (eventBox.getItemCount() == 1){
					//no more events, except for new event
					System.out.println("Marker");
					System.out.println(dateButtonArray.get(chosenDatePosition).hasEvent);
					dateButtonArray.get(chosenDatePosition).hasEvent = false;
				}
				
				//refresh calendar
				//to highlight the date selected from before
				chosenDatePosition = -2;
				refreshMonthPanel(selectedMonth, selectedYear);
				
				//go back to calendar
				CardLayout cl   = (CardLayout)outerPanel.getLayout();
				cl.show(outerPanel, "cPanel");	
			}
		}
	}

	static class SaveAction implements ActionListener{
		public void actionPerformed(ActionEvent ae){
			
			boolean isWarning 	= false;

			//Test date
			if(!isValidDate((int)yearBox.getSelectedItem(), (String)monthBox.getSelectedItem(), (int)dateBox.getSelectedItem())){
				//This is NOT a valid date, don't continue
				//Show error message
				dateWarningLabel.setText("Invalid date. Please make check your date selection");
				isWarning 		= true;
			}
			else{
				dateWarningLabel.setText("");
			}
			//Test time
			if (!isValidTime(	(int)startHourBox.getSelectedItem(), 	(int)startMinuteBox.getSelectedItem(), 	(String)startAMPMBox.getSelectedItem(),
								(int)endHourBox.getSelectedItem(),		(int)endMinuteBox.getSelectedItem(),	(String)endAMPMBox.getSelectedItem())){
				//This is NOT a valid time, don't continue
				//show error message
				timeWarningLabel.setText("Invalid time. Your end time must be after your start time");
				isWarning 		= true;
			}
			else{
				timeWarningLabel.setText("");
			}
			if (titleTextField.getText().equals("")){
				titleWarningLabel.setText("Invalid title. You must have an event title");
				isWarning		= true;
			}
			else{
				titleWarningLabel.setText("");
			}
			if (locationTextField.getText().equals("")){
				locWarningLabel.setText("Invalid location. You must have an event location");
				isWarning 		= true;
			}
			else{
				locWarningLabel.setText("");
			}
			if (isWarning){
				return;
			}

			//get int equivalent of month
			int useMonth = -1;
			for (int i = 0; i < 12; ++i){
				if (monthArrayShort[i].equals((String)monthBox.getSelectedItem())){
					useMonth = i;
					break;
				}
			}
			
			//see if it's a new event, if it is, create a new event and add
			if (eventBox.getSelectedIndex() == 0){
				Event newEvent = new Event	((int)yearBox.getSelectedItem(),		useMonth, 								(int)dateBox.getSelectedItem(),
											(int)startHourBox.getSelectedItem(), 	(int)startMinuteBox.getSelectedItem(), 	(String)startAMPMBox.getSelectedItem(),
											(int)endHourBox.getSelectedItem(),		(int)endMinuteBox.getSelectedItem(),	(String)endAMPMBox.getSelectedItem(),
											titleTextField.getText(), 				locationTextField.getText());
				eventArray.add(newEvent);
			}
			else{
				//change the information of
				Event changeEvent = eventsInDay.get(eventBox.getSelectedIndex()-1);
				changeEvent.setInfo((int)yearBox.getSelectedItem(),			useMonth, 								(int)dateBox.getSelectedItem(),
									(int)startHourBox.getSelectedItem(), 	(int)startMinuteBox.getSelectedItem(), 	(String)startAMPMBox.getSelectedItem(),
									(int)endHourBox.getSelectedItem(),		(int)endMinuteBox.getSelectedItem(),	(String)endAMPMBox.getSelectedItem(),
									titleTextField.getText(), 				locationTextField.getText());
			}
			
			
			//Want to highlight month, set chosenDatePosition to -1
			chosenDatePosition = -2;
			refreshMonthPanel(selectedMonth, selectedYear);
			
			//go back to calendar
			CardLayout cl   = (CardLayout)outerPanel.getLayout();
			cl.show(outerPanel, "cPanel");			
		}
	}
	
}

class DateButton extends JButton{
	static final long serialVersionUID = 1;
	public boolean inMonth;
	public int position, year, month, date;
	public int numOfEvents;
	public boolean hasEvent = false;
	public DateButton(String name){
		super(name);
		year = month = date = 0;
	}
}

class Event{
	private int year, month, date, startHour, startMinute, endHour, endMinute;
	private String title, location, startAMPM, endAMPM;
	static String[] monthArray 				= {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	public Event(int year, int month, int date, int startHour, int startMinute, String sAMPM, int endHour, int endMinute, String eAMPM, String title, String location){
		this.year 				= year;
		this.month 				= month;
		this.date 				= date;
		this.startHour 			= startHour;
		this.startMinute 		= startMinute;
		this.startAMPM			= sAMPM;
		this.endHour 			= endHour;
		this.endMinute			= endMinute;
		this.endAMPM			= eAMPM;
		this.title				= title;
		this.location 			= location;
	}
	private String getTimeFormat(int num){
		if (num < 10)
			return ("0" + num);
		else
			return ("" + num);
	}
	public int getYear()		{ return this.year;}
	public int getMonth()		{ return this.month;}
	public int getDate()		{ return this.date;}
	public String getTitle()	{ return this.title;}
	public String getLocation()	{ return this.location;}
	public int getStartHour()	{ return this.startHour;}
	public int getStartMinute()	{ return this.startMinute;}
	public int getEndHour()		{ return this.endHour;}
	public int getEndMinute()	{ return this.endMinute;}
	public int getEndAMPM()		{
		if (this.endAMPM.equals("AM")){
			return 0;
		}
		else{
			return 1;
		}
	}
	public int getStartAMPM()	{
		if (this.startAMPM.equals("AM")){
			return 0;
		}
		else{
			return 1;
		}
	}
	
	public void setInfo(int year, int month, int date, int startHour, int startMinute, String sAMPM, int endHour, int endMinute, String eAMPM, String title, String location){
		this.year 				= year;
		this.month 				= month;
		this.date 				= date;
		this.startHour 			= startHour;
		this.startMinute 		= startMinute;
		this.startAMPM			= sAMPM;
		this.endHour 			= endHour;
		this.endMinute			= endMinute;
		this.endAMPM			= eAMPM;
		this.title				= title;
		this.location 			= location;
	}
	
	public String getLabel(){
		return (this.title + " at " + this.location + " from " + getTimeFormat(startHour) + ":" + getTimeFormat(startMinute) + startAMPM + " to " + getTimeFormat(endHour) + ":" + getTimeFormat(endMinute) + endAMPM);
	}
	
	public String write(){
		String returnString = "";
		
		//date first
		returnString		+= this.year + "," + monthArray[this.month] + "," + this.date + ",";
		//title and location
		returnString		+= this.title + "," + this.location + ",";
		//time
		returnString		+= getTimeFormat(startHour) + ":" + getTimeFormat(startMinute)+ startAMPM + ",";
		returnString		+= getTimeFormat(endHour) + ":" + getTimeFormat(endMinute) + endAMPM;
		//end line
		returnString		+= "\n";
		
		return returnString;
		
	}

}

