/*  ********************************************************************************
    RequestDictionary.java *********************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.asp.*;
import com.ms.com.*;
import java.util.*;

/**
 * Used to access the subsidiary collections of the Request object.
 */

public class RequestDictionary 
    extends java.util.Dictionary
    implements aspcomp.Map, aspcomp.Enumerator
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public RequestDictionary(IRequestDictionary reqDic) 
    {
        m_irdDict = reqDic;
        enum = new VariantEnumerator((IEnumVariant) m_irdDict.get_NewEnum());
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private IRequestDictionary m_irdDict;
    private VariantEnumerator enum;


/*  ********************************************************************************
    Internal (Private) Methods *****************************************************
    ********************************************************************************  */

    private Variant getItem(String name) 
    {
        Variant vr = m_irdDict.getItem(new Variant(name));
        return vr;
    }


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public int getCount() 
    {
        return m_irdDict.getCount();
    }


/*  ********************************************************************************
    External (Public) aspcomp.Map Interface Methods ********************************
    ********************************************************************************  */

    public int getType(String name) 
    {
        Variant v = getItem(name);
        return v.getvt();
    }
    
    public boolean getBoolean(String name)        
        throws ClassCastException 
    {
        return VariantToJava.getBoolean(getItem(name));
    }

    public byte getByte(String name)            
        throws ClassCastException 
    {
        return VariantToJava.getByte(getItem(name));
    }

    public short getShort(String name)            
        throws ClassCastException 
    {
        return VariantToJava.getShort(getItem(name));
    }

    public char getChar(String name)            
        throws ClassCastException 
    {
        return VariantToJava.getChar(getItem(name));
    }

    public int getInt(String name)                
        throws ClassCastException 
    {
        return VariantToJava.getInt(getItem(name));
    }

    public long getLong(String name)            
        throws ClassCastException 
    {
        return VariantToJava.getLong(getItem(name));
    }

    public float getFloat(String name)            
        throws ClassCastException 
    {
        return VariantToJava.getFloat(getItem(name));
    }

    public double getDouble(String name)        
        throws ClassCastException 
    {
        return VariantToJava.getDouble(getItem(name));
    }

    public String getString(String name)        
        throws ClassCastException 
    {
        return VariantToJava.getString(getItem(name));
    }

    public Date getDate(String name)            
        throws ClassCastException 
    {
        return VariantToJava.getDate(getItem(name));
    }

    public Object getObject(String name)        
        throws ClassCastException 
    {
        return VariantToJava.getObject(getItem(name));
    }

    public Variant getVariant(String name)        
        throws ClassCastException 
    {
        return getItem(name);
    }

    //
    //    Request dictionaries are read-only dictionaries, so they
    //    should throw errors on an attempt to make a write.
    //

    public void setObject(String name, Object o)        
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setBoolean(String name,boolean b)        
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setByte(String name,byte b)                
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setShort(String name,short i)            
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setInt(String name, int i)                
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setFloat(String name,float f)            
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setDouble(String name,double d)            
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setString(String name,String str)        
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setDate(String name, Date d)            
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public void setVariant(String name, Variant v)        
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }


/*  ********************************************************************************
    External (Public) java.util.Dictionary Class Methods ***************************
    ********************************************************************************  */
    public Object get(Object key) 
        throws AspComponentException 
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
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
    }

    public int size() 
    {
        return getCount();
    }

    public boolean isEmpty() 
    {
        return (m_irdDict.getCount() == 0);
    }

    public Enumeration keys() 
    {
        return new VariantEnumerator((IEnumVariant) m_irdDict.get_NewEnum());
    }
    
    public Enumeration elements() 
    {
        return new ObjectEnumerator((IEnumVariant) m_irdDict.get_NewEnum(), this);
    }

    public Object remove(Object key) 
        throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_DICT_REMOVE);
    }


/*  ********************************************************************************
    External (Public) java.util.Enumeration Interface Methods **********************
    ********************************************************************************  */

    public boolean hasMoreElements() 
    {
        return enum.hasMoreElements();
    }

    public Object nextElement() 
        throws NoSuchElementException 
    {
        return enum.nextElement();
    }


/*  ********************************************************************************
    External (Public) java.lang.Cloneable Interface Methods ************************
    ********************************************************************************  */

    public Object clone() 
    {
        return enum.clone();
    }


/*  ********************************************************************************
    External (Public) aspcomp.Enumerator Interface Methods *************************
    ********************************************************************************  */

    public void reset() 
    {
        enum.reset();
    }
}

