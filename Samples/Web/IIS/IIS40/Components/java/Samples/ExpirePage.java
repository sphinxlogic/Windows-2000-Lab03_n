/**
 * ExpirePage: Java dates can now be easily used with ASP, in this case 
 * to set the page cache expiry date.
 */

package IISSample;

import java.util.*;
import aspcomp.*;


public class ExpirePage 
{

    public void expireAtYearEnd()
    {
        Response response = AspContext.getResponse();

        GregorianCalendar now = new GregorianCalendar();

        // Calculate the begining of next year
        GregorianCalendar nextYear = 
            new GregorianCalendar(now.get(Calendar.YEAR) + 1,   // next year
                                  0,                            // month
                                  1,                            // day
                                  0,                            // hours
                                  0,                            // minutes
                                  0);                           // seconds

        try
        {
            response.setExpiresAbsolute(nextYear.getTime());
        }
        catch(Exception e)
        {
            response.write(e.getMessage());
        }

        response.write("The Expires: header has been set to: " 
            + nextYear.getTime().toString() + "<P>");
    }

}
