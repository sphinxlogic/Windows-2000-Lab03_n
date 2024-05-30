/*  ********************************************************************************
    AspIOException.java ************************************************************
    ********************************************************************************  */

package aspcomp;

import java.io.IOException;

/**
 * Exception thrown if binary read/write through ASP fail
 */

public class AspIOException 
    extends IOException
{

/*  ********************************************************************************
    Constructors *******************************************************************
    ********************************************************************************  */

    public AspIOException() {}
    public AspIOException(String str) { super(str); }
}
