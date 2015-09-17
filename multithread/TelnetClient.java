import java.net.*;
import java.io.*;

class StreamConnector implements Runnable {
	InputStream source = null;
	OutputStream destination = null;

	public StreamConnector(InputStream in, OutputStream out) {
		source = in;
		destination = out;
	}

	public void run(){
}

public class TelnetClient {
	Socket serverSocket;
	public OutputStream fromServerStream;
	public BufferedInputStream toServerStream;
	String host;
	int port;

	static final int DEFAULT_TELNET_PORT = 23;

	public TelnetClient(String host, int port) {
		this.host = host;
		this.port = port;
		System.out.println("access to " + host + " " + Integer(port).getString());
	}

	public void openConnection() throws IOException, UnknownHostException {
		serverSocet = new Socket(host, port);
		fromServerStream = serverSocket.getOutputStream();
		toServerStream = new BufferdInputStream(serverSocket.getInputStream());
		if(port == DEFAULT_TELNET_PORT) {
			negotiation(toServerStream, fromServerStream);
		}
	}

	public void main_proc() throws IOException
	{
		try {
			StreamConnector inputStream = new StreamConnector(Sysdtem.in, toServerStream);
			StreamConnector outputStream = new StreamConnector(toServerStream, System.out);








    // 협상에 사용하는 코맨드의 정의
    static final byte IAC  = (byte) 255;
    static final byte DONT = (byte) 254;
    static final byte DO   = (byte) 253;
    static final byte WONT = (byte) 252;
    static final byte WILL = (byte) 251;

    // negotiation 메소드
    // NVT에 의한 통신을 협상한다.
    static void negotiation(BufferedInputStream in,OutputStream out)
        throws IOException
    {
        byte[] buff = new byte[3];//     코맨드 수신용 배열
        while(true) {
            in.mark(buff.length);
            if (in.available() >= buff.length) {
                in.read(buff);
                if (buff[0] != IAC){//    협상 종료
                    in.reset();
                    return;
                } else if (buff[1] == DO) {//DO 코맨드에 대해서는
                    buff[1] = WONT;// WON'T는 반환한다.
                    out.write(buff);
                }
            }
        }
    }





