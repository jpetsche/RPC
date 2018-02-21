import java.net.DatagramPacket;

public class Agent {

    private byte[] data;
    private int ID; //randomly generated during startup
    private int StartUpTime; //the time when the client starts
    private char[] IP = new char[4]; //the IP address of this client
    private int CmdPort; //the client listens to this port for manager cmd
    private int TimeReceived; //the time the listener received the most recent beacon
    public Agent(DatagramPacket packet, int time)
    {
        data = packet.getData();
        ID = fromByteArray(data, 0);
        StartUpTime = fromByteArray(data, 4);
        CmdPort = fromByteArray(data, 8);

        StringBuilder buff = new StringBuilder();
        buff.append(data[12]);
        buff.append(data[13]);
        buff.append(data[14]);
        buff.append(data[15]);
        buff.append(data[16]);
        buff.append(data[17]);
        IP = buff.toString().toCharArray();
        TimeReceived = time;
        System.out.println("Beacon ID: " + ID);
        System.out.println("Beacon Startup Time: " + StartUpTime);
        System.out.println("Beacon IP Address: " + IP[0] + "" + IP[1] + "" + IP[2] + "." + IP[3] + "." + IP[4] + "." + IP[5]);
        System.out.println("Beacon CmdPort: " + CmdPort);
        System.out.println("Beacon Arrival Time: " + TimeReceived);
        IP[0] = 127;
        IP[1] = 0;
        IP[2] = 0;
        IP[3] = 1;
    }

    public int fromByteArray(byte[] bytes, int index) {
        return bytes[index+0] << 24
                | (bytes[index+1] & 0xFF) << 16
                | (bytes[index+2] & 0xFF) << 8
                | (bytes[index+3] & 0xFF);
    }

    public int getID() {
        return ID;
    }

    public int getTimeReceived() {
        return TimeReceived;
    }

    public int getStartUpTime() {
        return StartUpTime;
    }

    public char[] getIP() {
        return IP;
    }

    public int getCmdPort() {
        return CmdPort;
    }

    public void setCmdPort(int cmdPort) {
        CmdPort = cmdPort;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public void setIP(char[] IP) {
        this.IP = IP;
    }

    public void setTimeReceived(int time) {
        TimeReceived = time;
    }

    public void setStartUpTime(int startUpTime) {
        StartUpTime = startUpTime;
    }
}
