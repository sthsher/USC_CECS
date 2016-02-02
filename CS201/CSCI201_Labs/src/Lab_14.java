import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URL;
import java.util.Scanner;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;


public class Lab_14 {
	public static void main(String [] args){
		try{
			URL url = new URL("http://gdata.youtube.com/feeds/api/standardfeeds/most_popular?v=2&alt=json");
			
			Scanner s = new Scanner(url.openStream());
			
			BufferedWriter writer = new BufferedWriter(new FileWriter("test.json"));
			writer.append(s.nextLine());
			writer.append("\n");

			writer.close();
			
			File jsonFile = new File("test.json");
			
			s = new Scanner(jsonFile);
			
			JSONObject json = new JSONObject(s.nextLine());
			
			JSONObject feed = (JSONObject)json.get("feed");
			JSONArray entry = (JSONArray)feed.get("entry");
			
			for (int i = 0; i < 10; ++i){
				JSONObject foo = (JSONObject)entry.get(i);
				JSONObject title = (JSONObject)foo.get("title");
				JSONObject statistic = (JSONObject)foo.get("yt$statistics");
				
				System.out.println(title.get("$t"));
				System.out.println("\thas " + statistic.getInt("viewCount") + " views!");
			}

			
		} catch (IOException IOE){
			IOE.printStackTrace();
		} catch (JSONException JE){
			JE.printStackTrace();
		}
	}
}
