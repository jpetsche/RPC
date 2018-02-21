import java.io.*;
import java.net.*;
import java.util.Collections;
import java.util.List;
import java.util.ArrayList;

public class Manager {

    public static List<Agent> agentList = Collections.synchronizedList(new ArrayList<Agent>());

	public static void main(String[] args) throws IOException
	{
		AgentMonitor monitor = new AgentMonitor();
		BeaconListener listener = new BeaconListener();
		
		Thread monThread = new Thread(monitor);
		Thread lisThread = new Thread(listener);
		
		monThread.start();
		lisThread.start();

	}

    public static List<Agent> getAgentList() {
        return agentList;
    }

    public static Agent getAgent(int index)
    {
        return agentList.get(index);
    }

    public static void setAgent(Agent agent, int index)
    {
        agentList.set(index, agent);
    }

    public static void addAgent(Agent agent)
    {
        for(int i = 0; i < agentList.size(); i++)
        {
            if(agentList.get(i) == null)
            {
                agentList.set(i, agent);
                break;
            }
        }
    }
}
