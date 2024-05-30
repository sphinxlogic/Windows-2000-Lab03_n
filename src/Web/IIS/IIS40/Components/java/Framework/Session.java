/*  ********************************************************************************
    Session.java *******************************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.asp.*;

/**
 * Cover class for the ASP Session intrinsic.
 */

public class Session extends ObjectDictionary
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public Session(ISessionObject session) 
    {
        super(session.getContents());
        m_ISession = session;
        staticObjects = new ObjectDictionary(session.getStaticObjects());
    }

    
/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private ISessionObject m_ISession;


/*  ********************************************************************************
    External (Public) Variables ****************************************************
    ********************************************************************************  */
    
    /**
     * Provide access to session-scoped objects created in global.asa
     */
    public ObjectDictionary staticObjects;


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public String getSessionID() 
    {
        return m_ISession.getSessionID();
    }

    public int getTimeout() 
    {
        return m_ISession.getTimeout();
    }

    public void setTimeout(int timeout) 
    {
        m_ISession.putTimeout(timeout);
    }

    public int getLCID() 
    {
        return m_ISession.getLCID();
    }

    public void setLCID(int lcid) 
    {
        m_ISession.putLCID(lcid);
    }

    public int getCodePage() 
    {
        return m_ISession.getCodePage();
    }

    public void setCodePage(int cp) 
    {
        m_ISession.putCodePage(cp);
    }

    public void abandon() 
    {
        m_ISession.Abandon();
    }
}
