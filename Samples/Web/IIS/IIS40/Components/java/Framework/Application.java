/*  ********************************************************************************
    Application.java ***************************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.asp.*;

/**
 * Cover class for the ASP Application intrinsic.
 */

public class Application extends ObjectDictionary
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */
    
    public Application(IApplicationObject app) 
    {
        super(app.getContents());
        m_IApplication = app;
        staticObjects = new ObjectDictionary(app.getStaticObjects());
    }

/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private IApplicationObject m_IApplication;


/*  ********************************************************************************
    External (Public) Variables ****************************************************
    ********************************************************************************  */

    /**
     * Provide access to application-scoped objects created in global.asa
     */
    public ObjectDictionary staticObjects;
    

/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public void lock() 
    {
        m_IApplication.Lock();
    }

    public void unlock() 
    {
        m_IApplication.UnLock();
    }
}
