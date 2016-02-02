import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import SumApp.*;

public class SumServerImpl extends SumServerPOA {
	public int sum(int a, int b) {
		System.out.println("adding " + a + " and " + b + " together");
		return a+b;
	}

	public static void main (String [] args) {
		try {
			ORB orb = ORB.init(args, null);
			POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
			rootpoa.the_POAManager().activate();
			SumServerImpl ssi = new SumServerImpl();
			org.omg.CORBA.Object ref = rootpoa.servant_to_reference(ssi);
			SumServer ss = SumServerHelper.narrow(ref);
			org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
			NameComponent path[] = ncRef.to_name("SUM-SERVER");
			ncRef.rebind(path, ss);
			System.out.println ("Sum Server is running . . . ");
			orb.run();
		} catch (Exception e) {
			System.out.println ("Exception: " + e.getMessage());
		}
	}
}