import java.net.*;
import java.io.*;
import java.util.ArrayList;

class DNSServerThread extends Thread{
	Socket socket;
	BufferedReader fromClientStream;
	PrintWriter toClientStream;

	public DNSServerThread(Socket socket) {
		super();
		this.socket = socket;
		try {
			fromClientStream = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			toClientStream = new PrintWriter(socket.getOutputStream());
		} catch(IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void run() {
		String clientMsg = "";
		String sndMsg = "";
		try {
			clientMsg = fromClientStream.readLine();
			try {
				InetAddress hostAddress = InetAddress.getByName(clientMsg);
				sndMsg = hostAddress.getHostAddress();
			} catch(UnknownHostException e) {
				sndMsg = "unknown host";
			}
			toClientStream.println(sndMsg);
			toClientStream.flush();
		} catch(IOException e) {
			String ip = socket.getInetAddress().getHostAddress();
			DNSServer.socketList.remove(socket);
			System.out.println("quit");
			return;
		}		
	}
}


public class DNSServer {
	static ArrayList<Socket> socketList = new ArrayList<Socket>();
	static int PORT = 6052;

	public static void main(String[] args) {
		ServerSocket serverSocket = null;
		PrintWriter toClientStream = null;
		BufferedReader fromClientStream = null;

		try {
			serverSocket = new ServerSocket(PORT);
			System.out.println("create server socket");

			while(true) {
				Socket socket = serverSocket.accept();
				socketList.add(socket);

				String clientHost = socket.getInetAddress().getHostAddress();
				System.out.println(clientHost+" : client accepted");

				new DNSServerThread(socket).start();
			}
		} catch(IOException e) {
			e.printStackTrace();
		}

		System.out.println("DNSServer close");
	}
}
