/*  ********************************************************************************
    ObjectDictionary.java **********************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.asp.*;
import com.ms.com.*;
import java.util.*;

/**
 * Supports lookup of items in a collection of variants. 
 * Used by Session and Applcation. 
 */

public class ObjectDictionary 
    extends java.util.Dictionary
    implements aspcomp.Enumerator, aspcomp.Map
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public ObjectDictionary(IVariantDictionary ivd)
    {
        m_ivdDict = ivd;
        enum = new VariantEnumerator((IEnumVariant)m_ivdDict.get_NewEnum());
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private IVariantDictionary m_ivdDict;
    private VariantEnumerator enum;


/*  ********************************************************************************
    Internal (Private) Methods *****************************************************
    ********************************************************************************  */

    private Variant getItem(String name) 
    {
        Variant vr = m_ivdDict.getItem(new Variant(name));
        return vr;
    }

    private void putItem(String name, Variant value) 
    {
        m_ivdDict.putItem(new Variant(name), value);
    }


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public int getCount() 
    {
        return m_ivdDict.getCount();
    }


/*  ********************************************************************************
    External (Public) java.util.Dictionary Class Methods ***************************
    ********************************************************************************  */

    public Object get(Object key) throws AspComponentException 
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

    public Object put(Object key, Object value) throws AspComponentException 
    {
        String strKey = null;
        if (key instanceof String) {
            strKey = (String) key;
        }
        else if (key instanceof Variant) {
            Variant v = (Variant) key;
            if (v.getvt() == Variant.VariantString) {
                strKey = v.getString();
            }
        }
        else throw new AspComponentException(AspLocalizedStrings.ASP_E_NON_STRING_DICT_KEY);
        
        Object objPrevious = getObject(strKey);
        setObject(strKey, value);
        return objPrevious;
    }

    public int size() 
    {
        return m_ivdDict.getCount();
    }

    public boolean isEmpty() 
    {
        if (m_ivdDict.getCount() == 0) return true;
        else return false;
    }

    public Enumeration keys() 
    {
        return new VariantEnumerator((IEnumVariant) m_ivdDict.get_NewEnum());
    }
    
    public Enumeration elements() 
    {
        return new ObjectEnumerator((IEnumVariant) m_ivdDict.get_NewEnum(), this);
    }

    public Object remove(Object key) throws AspComponentException 
    {
        throw new AspComponentException(AspLocalizedStrings.ASP_E_DICT_REMOVE);
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

    public void setObject(String name, Object o)        
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromObject(o));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setBoolean(String name,boolean b)        
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromBoolean(b));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setByte(String name,byte b)                
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromByte(b));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setShort(String name,short v)            
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromShort(v));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setInt(String name, int v)                
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromInt(v));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setFloat(String name,float v)            
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromFloat(v));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setDouble(String name,double v)            
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromDouble(v));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setString(String name,String v)            
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromString(v));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setDate(String name, Date v)            
        throws AspComponentException 
    {
        try {
            putItem(name, JavaToVariant.fromDate(v));
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
    }

    public void setVariant(String name, Variant var)    
        throws AspComponentException 
    {
        try {
            putItem(name, var);
        }
        catch (Throwable t) {
            throw new AspComponentException(AspLocalizedStrings.ASP_E_READ_ONLY_DICT);
        }
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
