/*  ********************************************************************************
    CookieEnumerator.java **********************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.com.*;
import java.util.*;

/**
 * Enumeration of cookie collections.
 */

public class CookieEnumerator extends VariantEnumerator
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public CookieEnumerator(IEnumVariant iev, CookieDictionary dict)
    {
        super(iev);
        m_dict = dict;
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private CookieDictionary m_dict;


/*  ********************************************************************************
    External (Public) Access Methods ***********************************************
    ********************************************************************************  */

    // This method overrides the definition in VariantEnumerator
    public Object nextElement() 
        throws NoSuchElementException,
               ClassCastException,
               AspComponentException
    {
        Variant varName = nextVariant();
        String  strName = null;

        try 
        {
            strName = varName.toString();
        }

        catch (ClassCastException cce) 
        {
            throw new NoSuchElementException();
        }

        return m_dict.getCookie(strName);
    }
}
