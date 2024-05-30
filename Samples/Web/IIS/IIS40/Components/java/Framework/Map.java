/*  ********************************************************************************
    Map.java ***********************************************************************
    ********************************************************************************  */

package aspcomp;

import java.util.*;
import com.ms.com.*;

/**
 * Interface that defines common typed data access methods.
 */

public interface Map 
{

/*  ********************************************************************************
    External (Public) Interface Methods ********************************************
    ********************************************************************************  */

    int     getType(String name);

    Object  getObject(String name)                  throws ClassCastException;
    boolean getBoolean(String name)                 throws ClassCastException;
    byte    getByte(String name)                    throws ClassCastException;
    short   getShort(String name)                   throws ClassCastException;
    char    getChar(String name)                    throws ClassCastException;
    int     getInt(String name)                     throws ClassCastException;
    long    getLong(String name)                    throws ClassCastException;
    float   getFloat(String name)                   throws ClassCastException;
    double  getDouble(String name)                  throws ClassCastException;
    String  getString(String name)                  throws ClassCastException;
    Date    getDate(String name)                    throws ClassCastException;
    Variant getVariant(String name)                 throws ClassCastException;

    void    setObject(String name, Object o)        throws AspComponentException;
    void    setBoolean(String name,boolean b)       throws AspComponentException;
    void    setByte(String name,byte b)             throws AspComponentException;
    void    setShort(String name,short s)           throws AspComponentException;
    void    setInt(String name,int i)               throws AspComponentException;
    void    setFloat(String name,float f)           throws AspComponentException;
    void    setDouble(String name,double d)         throws AspComponentException;
    void    setString(String name,String str)       throws AspComponentException;
    void    setDate(String name, Date d)            throws AspComponentException;
    void    setVariant(String name, Variant var)    throws AspComponentException;
}
