/*  ********************************************************************************
    Cookie.java ********************************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.com.*;
import com.ms.asp.*;
import java.util.*;

/**
 * This class makes accessing Cookies from Java much simpler.  It combines the ASP
 * IReadCookie and IWriteCookie interfaces into one interface, thereby making the 
 * access less awkward.
 */

public class Cookie
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public Cookie(IReadCookie aspCookie) 
    {
        // Set up the IReadCookie interface, then query it for IWriteCookie
        m_rc = aspCookie;
        m_wc = (IWriteCookie) m_rc;
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private IReadCookie m_rc;
    private IWriteCookie m_wc;


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public boolean getHasKeys() 
    {
        return m_rc.getHasKeys();
    }

    public Enumerator getKeys() 
    {
        return new VariantEnumerator((IEnumVariant) m_rc.get_NewEnum());
    }

    public String getItem(String itemName) 
    {
        String strRetVal = null;

        try 
        {
            strRetVal = VariantToJava.getString(m_rc.getItem(new Variant(itemName)));
        }

        catch (ClassCastException cce) 
        {
            return "";
        }

        return strRetVal;
    }

    public String getValue() 
    {
        Variant p = new Variant();
        p.noParam();
        return VariantToJava.getString(m_rc.getItem(p));
    }

    public void    setDomain(String domainName) 
    {
        m_wc.putDomain(domainName);
    }

    public void setExpires(Date d) 
    {
        m_wc.putExpires(JavaToVariant.dateToDouble(d));
    }
    
    public void setItem(String name, String item) 
    {
        m_wc.putItem(new Variant(name), item);
    }

    public void setValue(String value) 
    {
        Variant v = new Variant();
        v.noParam();
        m_wc.putItem(v, value);
    }

    public void setPath(String path) 
    {
        m_wc.putPath(path);
    }
    
    public void setSecure(boolean secure) 
    {
        m_wc.putSecure(secure);
    }
}
