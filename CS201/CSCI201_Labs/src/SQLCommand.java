
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

public abstract class SQLCommand implements Runnable
{
	public static final String DB_ADDRESS = "jdbc:mysql://localhost/CSCI201_Lab11";
	public static final String DB_NAME = "lab11";
	public static final String DRIVER = "com.mysql.jdbc.Driver";
	public static final String USER = "root";
	public static final String PASSWORD = "";
	protected ReentrantLock queryLock;
	public SQLCommand(ReentrantLock queryLock)
	{
		this.queryLock = queryLock;
	}
	
	@Override
	public void run() {
		try{
			queryLock.lock();
			System.out.print("Executing... ");
			execute();
			System.out.println("Done");
		}
		finally{
			queryLock.unlock();
		}
	}
	public abstract boolean execute();
	public static void clearTable(){
		try{
			Class.forName(DRIVER);
			
			java.sql.Connection conn = DriverManager.getConnection(DB_ADDRESS, USER, PASSWORD);
			
			//Clear table first
			Statement deleteStatement = conn.createStatement();
			deleteStatement.executeUpdate("TRUNCATE horse");
			deleteStatement.executeUpdate("TRUNCATE race_result");
			
			
		} catch (ClassNotFoundException CNFE){
			System.out.println("Class not found");
		} catch (Exception e){
			e.printStackTrace();
		}
	}
	
}

class AddHorseCommand extends SQLCommand{
//	private ReentrantLock lock = new ReentrantLock(); 
	public AddHorseCommand(ReentrantLock lock){
		super(lock);
	}
	
	public boolean execute(){
		//get two popular words
		String name = "";
		
		File popularWordsFile = new File("lab11/popularWords.txt");
		try{
			FileReader fr = new FileReader(popularWordsFile);
			BufferedReader br = new BufferedReader(fr);
			String line = "";
			
			int[] randomWords = new int[2];
			Random generator = new Random();
			
			int one = generator.nextInt(4458);
			int two = generator.nextInt(4458);
			
			String first = "";
			String second = "";
			
			Class.forName(DRIVER);
			
			java.sql.Connection conn = DriverManager.getConnection(DB_ADDRESS, USER, PASSWORD);
			
			java.sql.PreparedStatement statement = conn.prepareStatement("INSERT INTO horse (name) VALUES (?)");
			
//			Statement retrieveState = conn.createStatement();
//			ResultSet rs = retrieveState.executeQuery("SELECT * FROM words");
//			
			for (int i = 0; i < 4458; ++i){
				line = br.readLine();
				if (i == one){
					first = line.substring(1,line.length()-1);
				}
				if (i == two){
					second = line.substring(1,line.length()-1);
				}
			}
			
			name = first + " " + second;
//			System.out.println("Name: " + name);
			
//			Class.forName(DRIVER);
//			
//			java.sql.Connection conn = DriverManager.getConnection(DB_ADDRESS, USER, PASSWORD);
//			
//			java.sql.PreparedStatement statement = conn.prepareStatement("INSERT INTO horse (name) VALUES (?)");
			
//			System.out.println("Name: " + name);
			
			statement.setString(1,name);
			statement.execute();

			
			//To get results
//			Statement retrieveState = conn.createStatement();
//			ResultSet rs = retrieveState.executeQuery("SELECT * FROM horse");
//			
//			while(rs.next()){
//				System.out.println("Horse Name: " + rs.getString("name"));
//			}
			
		} catch (ClassNotFoundException CNFE){
			System.out.println("Class not found");
		} catch (Exception e){
			e.printStackTrace();
		}
		
		return true;

	}


}

class RaceCommand extends SQLCommand{
//	private ReentrantLock lock = new ReentrantLock(); 
	public RaceCommand(ReentrantLock lock){
		super(lock);
	}
	
	public boolean execute(){
		File popularWordsFile = new File("lab11/popularWords.txt");
		try{
			//get the max race number
			Class.forName(DRIVER);
			
			java.sql.Connection conn = DriverManager.getConnection(DB_ADDRESS, USER, PASSWORD);
			
//			java.sql.PreparedStatement statement = conn.prepareStatement("INSERT INTO race_result (race_number, horse_id, place) VALUES (?,?,?)");
////			
//			statement.setInt(1,2);
//			statement.setInt(2,1);
//			statement.setInt(3,1);
//			statement.execute();
			
			int currentRace = 0;
			
			//To get results
			Statement retrieveState = conn.createStatement();
			ResultSet rs = retrieveState.executeQuery("SELECT MAX(race_number) FROM race_result");
//			

			int nextRaceNum = 1;

			while(rs.next()){
				nextRaceNum += rs.getInt(1);
			}
			
//			System.out.println("Next race num: " + nextRaceNum);
			
//			To get results
			Statement hretrieveState = conn.createStatement();
			ResultSet hrs = retrieveState.executeQuery("SELECT MAX(horse_id) FROM horse");
			
			int[] randomHorses = new int[8];
			int maxID = 0;
			
			while (hrs.next()){
				maxID = hrs.getInt(1);
			}
			
			Random generate = new Random();
			
			for (int i = 0; i < 8; ++i){
				randomHorses[i] = -1;
			}
			
			int i = 0;
			boolean isRepeat = false;
			
			while (i < 8){
				int randomNum = generate.nextInt(maxID);
				//check for repeat
				for (int j = 0; j < 8; ++j){
					if (randomNum == randomHorses[j]){
						//match, break;
						isRepeat = true;
						break;
					}
				}
				if (!isRepeat){
					//no match, add it
					randomHorses[i++] = randomNum;
				} else{
					//don't do anything
				}
				isRepeat = false;
			}

//			Arrays.sort(randomHorses);
			
//			for (i = 0; i < 8; ++i){
//				System.out.println("Random horse: " + randomHorses[i]);
//			}
			
			hrs = retrieveState.executeQuery("SELECT * FROM horse");
			
			while(hrs.next()){
				for (int j = 0; j < 8; ++j){
					if (hrs.getInt("horse_id") == randomHorses[j]+1){
//						System.out.println("Name: " + hrs.getString("name"));
						java.sql.PreparedStatement statement = conn.prepareStatement("INSERT INTO race_result (race_number, horse_id, place) VALUES (?,?,?)");
						statement.setInt(1,nextRaceNum);
						statement.setInt(2,hrs.getInt("horse_id"));
						statement.setInt(3,j+1);
						statement.execute();
					}
				}
			}
			
		} catch (ClassNotFoundException CNFE){
			System.out.println("Class not found");
		} catch (Exception e){
			e.printStackTrace();
		}
		return true;
	}
}

class MostTimesPlacedCommand extends SQLCommand{
//	private ReentrantLock lock = new ReentrantLock(); 
	private int k;
	public MostTimesPlacedCommand(ReentrantLock lock, int k){
		super(lock);
		this.k = k;
	}
	
	public boolean execute(){
		File popularWordsFile = new File("lab11/popularWords.txt");
		try{
			//get the max race number
			Class.forName(DRIVER);
			
			java.sql.Connection conn = DriverManager.getConnection(DB_ADDRESS, USER, PASSWORD);
			
			//make an array of size of horses
			Statement retrieveState = conn.createStatement();
			ResultSet rs = retrieveState.executeQuery("SELECT MAX(horse_id) FROM horse");
			
			int maxID = 0;
			
			while (rs.next()){
				maxID = rs.getInt(1);
			}
			
			int[] horseArray = new int[maxID];

			for (int i = 0; i < maxID; ++i){
				horseArray[i] = 0;
			}
			
//			for (int k = 0; k < 8; ++k){
				//For each horse see how many times they placed first
				rs = retrieveState.executeQuery("SELECT * FROM race_result");
				while(rs.next()){
					if (rs.getInt(4) == k+1){
//						if (k == 1){
//							System.out.println(horseArray[rs.getInt(3)-1]+1);
//						}
						horseArray[rs.getInt(3)-1] += 1;
					}
				}
				
				//find the name of the horse who finished most for this place
				int max = 0;
				int maxVal = horseArray[0];
				for (int i = 1; i < 8; ++i){
					if (horseArray[i] > horseArray[max]){
						maxVal = horseArray[i];
						max = i;
					}
				}
				
				
				
				String name = "";
				
//				System.out.println("max: " + max);
//				System.out.println("val: " + maxVal);
				
				rs = retrieveState.executeQuery("SELECT * FROM horse");
				while (rs.next()){
					if (max+1 == rs.getInt(1)){
						name = rs.getString(2);
					}
				}
				
				System.out.println(name + " finished number " + (k+1) + " the most times at " + (maxVal+1) + " times");
//			}
			
		} catch (ClassNotFoundException CNFE){
			System.out.println("Class not found");
		} catch (Exception e){
			e.printStackTrace();
		}
		return true;
	}
}
