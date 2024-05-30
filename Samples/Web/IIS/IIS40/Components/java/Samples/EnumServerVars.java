/**
 * EnumServerVars: Using the framework to access HTTP server variables.
 */

package IISSample;

import aspcomp.*;


public class EnumServerVars 
{

    public void enum()
    {
        Response response = AspContext.getResponse();

        response.write("<H2>Enumerating Server Variables</H2><P>");

        // Use the Java Component Framework to enumerate through the
        // server variables
        try 
        {
            Request request = AspContext.getRequest();
            RequestDictionary rd = request.getServerVariables();

            while (rd.hasMoreElements()) 
            {
                String str = (String)rd.nextElement();
                response.write("<B>" + str + " =</B>" + rd.getString(str) + "<P>");
            }    
        }

        catch (ClassCastException e) 
        {
            response.write("Oppps! It looks like it threw<P>");
        }

        response.write("<B>done</B><P>");
    }

}
