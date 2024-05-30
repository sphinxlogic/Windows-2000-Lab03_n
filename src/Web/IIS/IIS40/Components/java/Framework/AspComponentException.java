/*  ********************************************************************************
    AspComponentException.java *****************************************************
    ********************************************************************************  */

package aspcomp;

/**
 * Generic exception raised by the framework.
 */

public class AspComponentException 
    extends RuntimeException
{

/*  ********************************************************************************
    Constructors *******************************************************************
    ********************************************************************************  */

    public AspComponentException() {}
    public AspComponentException(String str) { super(str); }
}
