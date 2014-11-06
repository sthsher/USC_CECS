import java.util.concurrent.locks.ReentrantLock;




public class Lab11 {

	
	public static void main (String [] args){
		
		ReentrantLock globalLock = new ReentrantLock();
		
		SQLCommand.clearTable();
		
		for (int i = 0; i < 8; ++i){
			SQLCommand test = new AddHorseCommand(globalLock);
			test.run();
		}
		
//		SQLCommand test = new AddHorseCommand(globalLock);
//		test.run();
		
		for (int i = 0; i < 50; ++i){
			SQLCommand race = new RaceCommand(globalLock);
			race.run();
		}
		for (int i = 0; i < 8; ++i){
			SQLCommand results = new MostTimesPlacedCommand(globalLock, i);
			results.run();
		}
	
	}

	
}
