import java.io.*;
import java.net.*;

public class SendtoPd{

	public static void main(String [] args){
		try{
			Socket s= new Socket(InetAddress.getByName("127.0.0.1"), 6969);
			BufferedOutputStream ros= new BufferedOutputStream(s.getOutputStream());

			String mot= "bonjour;\n";

			for(int i=0; i<mot.length() ; i++){
				System.out.println("Valeur envoié: " + (int) mot.charAt(i));
				ros.write((int) mot.charAt(i));
				Thread.sleep(1000);
			}

			ros.close();
			s.close();

		}
		catch(Exception e){
			e.printStackTrace();
		}
	}

}