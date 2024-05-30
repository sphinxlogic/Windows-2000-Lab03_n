/*  ********************************************************************************
    ObjectEnumerator.java **********************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.com.*;
import java.util.*;

/**
 * Allows enumeration over object collections of variants. 
 */

public class ObjectEnumerator extends VariantEnumerator
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public ObjectEnumerator(IEnumVariant iev, Dictionary dict)
    {
        super(iev);
        m_dict = dict;
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private Dictionary m_dict;


/*  ********************************************************************************
    External (Public) Access Methods ***********************************************
    ********************************************************************************  */

    // This method overrides the definition in VariantEnumerator
    public Object nextElement() 
        throws NoSuchElementException,
               ClassCastException,
               AspComponentException
    {
        return m_dict.get(nextVariant());
    }
}
