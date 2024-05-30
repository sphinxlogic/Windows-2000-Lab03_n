/*  ********************************************************************************
    CookieDictionary.java **********************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.com.*;
import com.ms.asp.*;
import java.util.*;

/**
 * Allows lookups in cookie collections.
 */

public class CookieDictionary 
    extends java.util.Dictionary
    implements aspcomp.Enumerator
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public CookieDictionary(IRequestDictionary reqDict) 
    {
        m_reqDict = reqDict;

        ve = new VariantEnumerator((IEnumVariant) m_reqDict.get_NewEnum());
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private IRequestDictionary m_reqDict;
    private VariantEnumerator ve;
    

/*  ********************************************************************************
    Internal (Private) Method ******************************************************
    ********************************************************************************  */

    private Variant getItem(String name)
    {
        return m_reqDict.getItem(new Variant(name));
    }


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public int getCount() 
    { 
        return m_reqDict.getCount();
    }
    
    public Cookie getCookie(String name) 
        throws ClassCastException 
    {
        Variant v = getItem(name);

        if (v.getvt() == v.VariantDispatch) {
            IReadCookie readCookie = (IReadCookie)v.getDispatch();
            return new Cookie(readCookie);
        }

        throw new ClassCastException();
    }

    
/*  ********************************************************************************
    External (Public) aspcomp.Enumerator Interface Methods *************************
    ********************************************************************************  */

    public void reset() 
    {
        ve.reset();
    }


/*  ********************************************************************************
    External (Public) java.util.Enumeration Interface Methods **********************
    ********************************************************************************  */

    public boolean hasMoreElements() 
    {
        return ve.hasMoreElements();
    }

    public Object nextElement() 
        throws NoSuchElementException,
               ClassCastException 
    {
        return ve.nextElement();
    }


/*  ********************************************************************************
    External (Public) java.lang.Cloneable Interface Methods ************************
    ********************************************************************************  */

    public Object clone() {
        return ve.clone();
    }


/*  ********************************************************************************
    External (Public) java.util.Dictionary Class Methods ***************************
    ********************************************************************************  */

    public int size()
    {
        return getCount();
    }

    public boolean isEmpty()
    {
        return (getCount() == 0);
    }

    public Enumeration keys()
    {
        return new VariantEnumerator((IEnumVariant) m_reqDict.get_NewEnum());
    }

    public Enumeration elements()
    {
        return new CookieEnumerator((IEnumVariant) m_reqDict.get_NewEnum(), this);
    }

    public Object get(Object key)
    {
        if (key instanceof String) {
            return getItem((String) key);
        }
        else if (key instanceof Variant) {
            Variant v = (Variant) key;
            if (v.getvt() == Variant.VariantString) {
                return getItem(v.getString());
            }
        }

        throw new AspComponentException(AspLocalizedStrings.ASP_E_NON_STRING_DICT_KEY);
    }

    public Object put(Object key, Object value)
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_COOKIE_PUT);
    }

    public Object remove(Object key)
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_DICT_REMOVE);
    }
}

