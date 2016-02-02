import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import SumApp.*;

public class SumClient {
	public static void main (String [] args) {
		try {
			ORB orb = ORB.init(args, null);
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
			SumServer ss = SumServerHelper.narrow(ncRef.resolve_str("SUM-SERVER"));
			int addSolution = ss.sum(100, 200);
			System.out.println ("100 + 200 = " + addSolution);
		} catch (Exception e) {
			System.out.println ("Exception: " + e.getMessage());
		}
	}
}