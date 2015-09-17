import java.net.*;
import java.util.Scanner;
import java.io.*;


public class DNSClient {
	public static void main(String[] args) {
		int PORT = 6052;
		Socket socket = null;
		BufferedReader fromServerStream = null;
		PrintWriter toServerStream = null;
		BufferedReader fromInputStream = null;

		try {
			socket = new Socket("localHost", PORT);
			System.out.println("server access");

			toServerStream = new PrintWriter(socket.getOutputStream());
			fromInputStream = new BufferedReader(new InputStreamReader(System.in));
			String input = fromInputStream.readLine();

			toServerStream.println(input);
			toServerStream.flush();

			fromServerStream = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			String svrMsg = fromServerStream.readLine();
			System.out.println("message from server : " + svrMsg);



		} catch(UnknownHostException e){
			e.printStackTrace();
		} catch(IOException e){
			e.printStackTrace();
		}
		System.out.println("client close");
	}
}
