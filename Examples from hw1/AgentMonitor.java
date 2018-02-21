import java.io.IOException;
import java.net.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class AgentMonitor implements Runnable {
	public AgentMonitor() throws IOException
	{
        // To-Do
	}


	@Override
	public void run() {
	    long timestamp;
		while (true)
        {
            System.out.println("AgentMoniter is checking agents...");
            try
            {
                Thread.sleep(60000);
            }
            catch (InterruptedException e)
            {
                Thread.currentThread().interrupt();
            }

            timestamp = System.currentTimeMillis();

            for(int i = 0; i < 20; i++)
            {
                if(Manager.agentList.size() != 0)
                {
                    int lastBeacon = Manager.getAgent(i).getTimeReceived();
                    if((int)timestamp - lastBeacon > 120000)
                    {
                        System.out.println("Error. Agent: "
                                + Manager.getAgent(i).getID() + " has died.");
                        Manager.getAgentList().remove(i);
                    }
                }
            }

        }
		
	}

}
