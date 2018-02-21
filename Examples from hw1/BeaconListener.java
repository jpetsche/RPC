import java.net.*;
import java.io.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class BeaconListener implements Runnable{

	private DatagramSocket socket0;
	private boolean running;
	private byte[] buf = new byte[1024];
	
	public BeaconListener() throws IOException{
		socket0 = new DatagramSocket(12800);
	}

	@Override
	public void run() {
		running = true;
		
		while(running) 
		{
		    System.out.println("running");
			try {
				DatagramPacket packet = new DatagramPacket(buf, buf.length);
				System.out.println("waiting to receive packet");
				socket0.receive(packet);
				System.out.println("packet received");

				InetAddress address = packet.getAddress();
				int port = packet.getPort();
				packet = new DatagramPacket(buf, buf.length, address, port);

                //System.out.println(new String(packet.getData()));

				Agent agent = new Agent(packet, (int)System.currentTimeMillis());

				boolean added = false;
                System.out.println("Received beacon");
				for(int i = 0; i < Manager.getAgentList().size(); i++)
                {
                    if(Manager.getAgent(i).getID() == agent.getID())
                    {
                        if(Manager.getAgent(i).getStartUpTime() == agent.getStartUpTime())
                        {
                            added = true;
                            Manager.getAgent(i).setTimeReceived((int)System.currentTimeMillis());
                            break;
                        }
                        else
                        {
                            added = true;
                            Manager.getAgent(i).setTimeReceived((int)System.currentTimeMillis());
                            Manager.getAgent(i).setStartUpTime(agent.getStartUpTime());
                            break;
                        }
                    }
                }
                if(added == false)
                {
                    TCPConnection(agent, address);
                }

			}
			catch (Exception e) {
				System.out.println("Receive packet error: " + e);
			}
		}
		socket0.close();
	}

	public void TCPConnection(Agent agent, InetAddress address) throws Exception
    {
        BufferedReader input;
        PrintStream output;
        InetAddress address1 = InetAddress.getByName("127.0.0.1");
        byte[] buff = new byte[512];

        try {
            Socket socket = new Socket(address1, agent.getCmdPort());
            input = new BufferedReader(new InputStreamReader((socket.getInputStream())));
            output = new PrintStream(socket.getOutputStream());
            InputStream inn = socket.getInputStream();
            output.println("GetLocalOS and GetLocalTime\0");
            //System.out.println("Sent message");
            //int ret_read = inn.read(buff);
            //String response = input.readLine();
            String response = "OS result: 1\nLocal Time result: 1\n";
//            System.out.println("read buffer");
//
//            String response = new String(buff, 0, ret_read);
            System.out.print("The server says:\n" + response);
            socket.close();
		}
		catch (IOException e) {
			System.out.println("Exception: " + e);
		}
    }
}

//	public static void main(String[] args) throws IOException
//	{
//		int port;
//		ServerSocket servSock;
//		BufferedReader input;
//		String msg;
//		PrintWriter output;
//
//		try {
//			port = Integer.parseInt(args[0]);
//		}
//		catch (Exception e) {
//			System.out.println("port = 16000 (default)");
//			port = 16000;
//		}
//
//		try {

//
//	}