package lab3;

/*
 * Evan Conley, Jacob Cromwell, Mike Coley
 * Prof. Nordquist
 * CS 459
 * Lab 3
 * */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class SystemCall extends Thread{
	ServerSocket server;
	String[] sharedData;
	public static int PORT = 6013;
	int port; //portNumber
	
	public SystemCall(int port, int fsize) throws IOException {
		server = new ServerSocket(port);
		sharedData = new String[fsize];
		for(int i = 0; i < fsize; i++){
			sharedData[i] = null;
		}
	}
	
	public void close() throws IOException {
		server.close();	
	}
	
	public int getServerPort() {
		return port;
	}
	
	public void run() {
		try {
			while (true) {
				Socket client = server.accept();
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				BufferedReader bin = new BufferedReader(new InputStreamReader(client.getInputStream()));
				String[] req = bin.readLine().split(" ");
				switch (req[0]) {	
				case "size":
					pout.println(sharedData.length);
					break;
				case "write":
					sharedData[(Integer.parseInt(req[1]))] = req[2];
					break;
				case "read":
					pout.println(sharedData[Integer.parseInt(req[1])]);
					break;
				}
				pout.close();
				bin.close();
				client.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
