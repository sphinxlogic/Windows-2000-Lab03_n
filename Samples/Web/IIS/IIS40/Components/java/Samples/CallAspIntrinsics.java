/**
 * CallAspIntrinsics: A Java class that calls ASP objects directly.
 */

package IISSample;

import com.ms.com.*;
import com.ms.mtx.*;
import com.ms.asp.*;


public class CallAspIntrinsics
{
    
    public void sayHello()
    {
        IGetContextProperties iConProps;
        Variant vResponse = new Variant();
        IResponse iResponseObject;
        Variant vMsg;

        // Get the Object Context
        iConProps = (IGetContextProperties)MTx.GetObjectContext();

        // Get the Response object
        vResponse = iConProps.GetProperty("Response");

        iResponseObject = (IResponse) vResponse.getDispatch();

        // Print HTML message
        vMsg = new Variant("Hello, World! (written from inside the Java component...)");

        iResponseObject.Write(vMsg);
    }

}
