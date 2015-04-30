import java.io.*;
import java.net.*;

public class RecvfromPd{

	public static void main(String [] args){
		try{


			ServerSocket server= new ServerSocket(6969);
			Socket c= server.accept();
			System.out.println("Connect");
			Reader ris= new InputStreamReader(c.getInputStream());
			BufferedInputStream is= new BufferedInputStream(c.getInputStream());

			StringBuffer sb= new StringBuffer(); 

			int tmp;
			while( (tmp= is.read()) != -1){
				sb.append((char) tmp);
				System.out.print("r-");
			}
			System.out.println("");
			System.out.println("Msg: " + sb.toString());

			ris.close();
			c.close();

		}
		catch(Exception e){
			System.err.println("ERREUR");
			e.printStackTrace();
		}
	}

}