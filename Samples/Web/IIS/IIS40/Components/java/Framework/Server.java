/*  ********************************************************************************
    Server.java ********************************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.asp.*;

/**
 * Cover class for the ASP Session intrinsic.
 */

public class Server 
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public Server(IServer server) 
    {
        m_IServer = server;
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private IServer m_IServer;


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public String mapPath(String path) 
    {
        return m_IServer.MapPath(path);
    }

    public String URLEncode(String str) 
    {
        return m_IServer.URLEncode(str);
    }

    public String URLPathEncode(String str) 
    {
        return m_IServer.URLPathEncode(str);
    }

    public String HTMLEncode(String str) 
    {
        return m_IServer.HTMLEncode(str);
    }

    public int getScriptTimeout() 
    {
        return m_IServer.getScriptTimeout();
    }

    public void setScriptTimeout(int timeout) 
    {
        m_IServer.putScriptTimeout(timeout);
    }

    public Object createObject(String progID) 
    {
        return m_IServer.CreateObject(progID);
    }
}
