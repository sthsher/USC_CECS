package test;

import java.awt.*;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.swing.*;
class test2
{
	static Calendar calendar = new GregorianCalendar();

	public static void main(String[] args)
	{
		System.out.println("Year:   " + calendar.get(Calendar.YEAR));
		System.out.println("Month:  " + calendar.get(Calendar.MONTH));
		System.out.println("Day:    " + calendar.get(Calendar.DAY_OF_MONTH));
		System.out.println("Hour:   " + calendar.get(Calendar.HOUR_OF_DAY));
		System.out.println("Minute: " + calendar.get(Calendar.MINUTE));
		System.out.println("Time:   " + calendar.get(Calendar.SHORT_FORMAT));
//		System.out.println("
//		System.out.println("
//		System.out.println("
//		System.out.println("
//		System.out.println("
//	
	}
}