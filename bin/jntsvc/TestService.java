// TestService.java
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

import java.io.*;
import com.ms.service.*;

public
class TestService extends Service
{
    static
    {
        // Uncomment to disable the assassin.  The service will fail to respond 
        // in the time specified in the last waithint for the third pause
        // event received.  If the assassin is enabled (i.e. this line is commented
        // out, the default), then the service will be forcibly killed.
        
        //Service.disableassassin = true;
    }

    int pausecount;
    int intcount;

    public TestService (String[] args) throws IOException
    {
        System.out.println("Sending updated pending status");

        CheckPoint(1000);

        System.out.println("Sending running status with all controls");

        setRunning(ACCEPT_SHUTDOWN | ACCEPT_PAUSE_CONTINUE | ACCEPT_STOP);
        
        System.out.println("Started");
    }

    protected
    boolean handleStop ()
    {
        setStopping(5000);
        System.out.println("dying");
        return true;
    }

    protected
    boolean handlePause ()
    {
        pausecount++;
        if (pausecount == 3)
        {
            System.out.println("pause #3, sleeping for 30 seconds, should be killed in 2+5 seconds");
            setPausing(2000);
            try
            {
                Thread.sleep(30000);
            }
            catch (InterruptedException e)
            {
                System.out.println("interrupted");
            }
        }
        else
        {
            System.out.println("received pause #"+pausecount+", pausing for 2 seconds");
            setPausing(5000);
            try
            {
                Thread.sleep(2000);
            }
            catch (InterruptedException e)
            {
                System.out.println("interrupted");
            }
            System.out.println("sending paused");
            setPaused();
            System.out.println("sent paused");
        }

        return false;
    }

    protected
    boolean handleContinue ()
    {
        System.out.println("received continue, continuing after 2 seconds");
        setContinuing(5000);
        try
        {
            Thread.sleep(2000);
        }
        catch (InterruptedException e)
        {
            System.out.println("interrupted");
        }
        System.out.println("sending running");
        setRunning();
        System.out.println("sent running after continue");

        return false;
    }

    protected
    boolean handleShutdown ()
    {
        System.out.println("received shutdown, treating as stop");
        return handleStop();
    }

    protected
    boolean handleInterrogate ()
    {
        System.out.println("received interrogate");
        setServiceStatus(getServiceStatus());
        System.out.println("sent status for interrogate");
        
        intcount++;
        if (intcount == 3)
        {
            System.out.println("received 3rd interrogate, stopping self in 5 seconds");
            try
            {
                Thread.sleep(5000);
            }
            catch (InterruptedException iex)
            {
                System.out.println("interrupted");
            }
            System.out.println("stopping");
            StopServiceEventHandler(1000);
        }
        
        return false;
    }
}

