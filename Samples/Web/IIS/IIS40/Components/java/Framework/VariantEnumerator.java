/*  ********************************************************************************
    VariantEnumerator.java *********************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.com.*;
import java.util.*;

/**
 * The VariantEnumerator class is an implementation of an enumeration that works with 
 * variant objects.
 */

public class VariantEnumerator implements Enumerator 
{

/*  ********************************************************************************
    * Constructors *****************************************************************
    ******************************************************************************** */

    public VariantEnumerator(IEnumVariant enum) 
    {
        m_iev      = enum;
        m_nextObj  = new Variant[1];
        m_objCount = new int[1];
    }

    private VariantEnumerator(IEnumVariant enum, Variant nextObj) 
    {
        m_iev        = enum;
        m_nextObj    = new Variant[1];
        m_nextObj[0] = nextObj;
        m_objCount   = new int[1];
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ******************************************************************************** */

    private IEnumVariant m_iev;
    // The two members below need to be arrays for the IEnumVariant.Next() call
    private Variant[] m_nextObj;
    private int[] m_objCount;


/*  ********************************************************************************
    Package/SubClass (Protected) Methods *******************************************
    ******************************************************************************** */

    /**
     * This method returns the next Variant in the enumeration.
     */

    protected Variant nextVariant() 
        throws NoSuchElementException 
    {
        if (m_nextObj[0] == null) {
            try {
                m_iev.Next(1, m_nextObj, m_objCount);
                if (m_objCount[0] != 1) {
                    m_nextObj[0] = null;
                    throw new NoSuchElementException();
                }
            }
            catch (ComFailException cfe){
                m_nextObj[0] = null;
                throw new NoSuchElementException();
            }
        }
        Variant varRetVal = m_nextObj[0];
        m_nextObj[0] = null;
        return varRetVal;
    }


/*  ********************************************************************************
    External (Public) aspcomp.Enumerator Interface Methods *************************
    ******************************************************************************** */

    /**
     * Overrides Enumerator
     */

    public void reset() 
    {
        m_nextObj[0] = null;
        m_iev.Reset();
    }


/*  ********************************************************************************
    External (Public) java.util.Enumeration Interface Methods **********************
    ******************************************************************************** */

    /**
     * Test if this enumeration has more elements available.
     * Returns true if there are more elements available, false otherwise.
     */

    public boolean hasMoreElements() 
    {
        // If we have already prefetched an element, then there are more elements.
        if (m_nextObj[0] != null)
            return true;

        //
        // Otherwise, we'll have to try to get another element.  If we succeed in 
        // getting one, and there is no exception, go ahead and set it up in the 
        // prefetch area, and return true.  In all other (error) cases, return false
        // and make sure the prefetch area is set to null.
        //
        try 
        {
            m_iev.Next(1, m_nextObj, m_objCount);
            if (m_objCount[0] != 1) 
            {
                m_nextObj[0] = null;
                return false;
            }
            if (m_nextObj[0] != null)
                return true;
        }
        catch (ComFailException cfe) 
        {
            m_nextObj = null;
            return false;
        }
        return false;
    }

    /**
     * This method returns the next element available in the enumeration.
     */

    public Object nextElement() 
        throws NoSuchElementException,
               ClassCastException, 
               AspComponentException
    {
        Variant v = nextVariant();
        return VariantToJava.getObject(v);
    }


/*  ********************************************************************************
    External (Public) java.lang.Cloneable Interface Methods ************************
    ******************************************************************************** */

    /**
     * Overrides Cloneable
     */

    public Object clone() 
    {
        return new VariantEnumerator(m_iev.Clone(), m_nextObj[0]);
    }
}
