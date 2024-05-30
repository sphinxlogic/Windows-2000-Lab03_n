/*  ********************************************************************************
    AspContext.java ****************************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.com.*;
import com.ms.asp.*;
import com.ms.mtx.*;

/**
 * The class from which a component gains access to the ASP intrinsic covers of the
 * framework. 
 * All the methods are static, to allow them to be called without creating an
 * instance of this class.
 */

public class AspContext
{

/*  ********************************************************************************
    Internal (Private) Constants ***************************************************
    ********************************************************************************  */
    
    private static final String REQUEST = "Request";
    private static final String RESPONSE = "Response";
    private static final String SERVER = "Server";
    private static final String SESSION = "Session";
    private static final String APPLICATION = "Application";


/*  ********************************************************************************
    Internal (Private) Access Methods **********************************************
    ********************************************************************************  */

    private static Object getIntrinsic(String strIntrinsic) 
        throws AspComponentException
    {
        Variant v;
        IGetContextProperties cp;

        try
        {
            cp = (IGetContextProperties) MTx.GetObjectContext();
        }

        catch(Exception e)
        {
            throw new AspComponentException(
                AspLocalizedStrings.ASP_E_FAIL_GET_CONTEXT);
        }
        
        if ( (strIntrinsic.equals(REQUEST))     ||
             (strIntrinsic.equals(RESPONSE))    ||
             (strIntrinsic.equals(SERVER))      ||
             (strIntrinsic.equals(SESSION))     ||
             (strIntrinsic.equals(APPLICATION)) )
        {
             v = cp.GetProperty(strIntrinsic);

             return v.getDispatch();
        }
        else 
        {
            throw new AspComponentException(
                AspLocalizedStrings.ASP_E_FAIL_GET_INTRINSIC);
        }
    }


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public static Request getRequest()
    {
        IRequest aspRequest = (IRequest) getIntrinsic(REQUEST);
        IResponse aspResponse = (IResponse) getIntrinsic(RESPONSE);
        return new Request(aspRequest, aspResponse);
    }

    public static Response getResponse()
    {
        IResponse aspResponse = (IResponse) getIntrinsic(RESPONSE);
        return new Response(aspResponse);
    }

    public static Server getServer()
    {
        IServer aspServer = (IServer) getIntrinsic(SERVER);
        return new Server(aspServer);
    }

    public static Session getSession()
    {
        ISessionObject aspSession = (ISessionObject) getIntrinsic(SESSION);
        return new Session(aspSession);
    }

    public static Application getApplication()
    {
        IApplicationObject aspApplication = 
            (IApplicationObject) getIntrinsic(APPLICATION);

        return new Application(aspApplication);
    }

    public static IObjectContext getObjectContext()
    {
        IObjectContext objContext;

        try
        {
            objContext = (IObjectContext) MTx.GetObjectContext(); 
        }

        catch(Exception e)
        {
             throw new AspComponentException(
                AspLocalizedStrings.ASP_E_FAIL_GET_CONTEXT);
        }

        return objContext;
    }
}
