import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.util.Scanner;
import java.util.jar.Attributes;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.io.File;
 


public class Lab_8 {
	public static void main(String [] args){
		
		System.out.println(args[0]);
//		String argument = "AAPL";
		
		
		try{
//			URL url = new URL("http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20yahoo.finance.quotes%20where%20symbol%20in%20(%22" + argument + "%22)&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");
			URL url = new URL("http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20yahoo.finance.quotes%20where%20symbol%20in%20(%22" + args[0] + "%22)&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");
			InputStream in = url.openStream();
			
			
			Scanner s = new Scanner(url.openStream());

			BufferedWriter writer = new BufferedWriter(new FileWriter("test.xml"));
			writer.append(s.nextLine());
			writer.append("\n");
			writer.append(s.nextLine());
			writer.append("\n");
			writer.append(s.nextLine());

			writer.close();

			File fXmlFile = new File("test.xml");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			
			doc.getDocumentElement().normalize();
			
			NodeList nList = doc.getElementsByTagName("results");
			
			for (int i = 0; i < nList.getLength(); ++i){
				Node nNode = nList.item(i);
				if (nNode.getNodeType() == Node.ELEMENT_NODE){
					Element eElement = (Element)nNode;
					String NAME = eElement.getElementsByTagName("Name").item(0).getTextContent();
					String YEARLOW = eElement.getElementsByTagName("YearLow").item(0).getTextContent();
					String YEARHIGH = eElement.getElementsByTagName("YearHigh").item(0).getTextContent();
					String MARKET = eElement.getElementsByTagName("MarketCapitalization").item(0).getTextContent();
					
					System.out.println(NAME + " has a year low of: " + YEARLOW + " and a year high of: " + YEARHIGH + ". \nIts current market capitalization is " + MARKET);
				}
			}
			
			
		} catch (IOException IOE){
			System.out.println(IOE.getMessage());
		} catch (Exception e){
			System.out.println(e.getMessage());
		}
		
	}
	
}
