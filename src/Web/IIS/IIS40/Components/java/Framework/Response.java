/*  ********************************************************************************
    Response.java ******************************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.asp.*;
import com.ms.com.*;
import java.io.*;
import java.util.*;

/**
 * Cover class for the ASP Response intrinsic.
 */

public class Response extends OutputStream
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public Response(IResponse response) 
    {
        m_IResponse = response;
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private IResponse m_IResponse;


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public void addHeader(String name, String value) 
    {
        m_IResponse.AddHeader(name, value);
    }

    public boolean getBuffered() 
    {
        return m_IResponse.getBuffer();
    }

    public void setBuffered(boolean fIsBuffered) 
    {
        m_IResponse.putBuffer(fIsBuffered);
    }

    public int getExpires() 
    {
        return VariantToJava.getInt(m_IResponse.getExpires());
    }

    public void setExpires(int iExpirationMinutes) 
    {
        m_IResponse.putExpires(iExpirationMinutes);
    }

    public Date getExpiresAbsolute() 
    {
        return VariantToJava.getDate(m_IResponse.getExpiresAbsolute());
    }

    public void setExpiresAbsolute(Date dateExpire) 
    {
        m_IResponse.putExpiresAbsolute(JavaToVariant.dateToDouble(dateExpire));
    }

    public String getCharSet() 
    {
        return m_IResponse.getCharSet();
    }

    public void setCharSet(String strCharSet) 
    {
        m_IResponse.putCharSet(strCharSet);
    }

    public String getContentType() 
    {
        return m_IResponse.getContentType();
    }

    public void setContentType(String strContentType) 
    {
        m_IResponse.putContentType(strContentType);
    }

    public String getCacheControl() 
    {
        return m_IResponse.getCacheControl();
    }

    public void setCacheControl(String strCacheControl) 
    {
        m_IResponse.putCacheControl(strCacheControl);
    }

    public String getStatus() 
    {
        return m_IResponse.getStatus();
    }

    public void setStatus(String strStatus) 
    {
        m_IResponse.putStatus(strStatus);
    }

    public void appendToLog(String s) 
    {
        m_IResponse.AppendToLog(s);
    }

    public boolean isClientConnected() 
    {
        return m_IResponse.IsClientConnected();
    }

    public void end() 
    {
        m_IResponse.End();
    }

    public void clear() 
    {
        m_IResponse.Clear();
    }

//    public void flush() is covered below (overriding OutputStream.flush()).

    public void write(String str) 
    {
        m_IResponse.Write(new Variant(str));
    }

    public void pics(String str) 
    {
        m_IResponse.Pics(str);
    }

    public void redirect(String str) 
    {
        m_IResponse.Redirect(str);
    }

    public CookieDictionary getCookies()  
    {
        return new CookieDictionary(m_IResponse.getCookies());
    }


/*  ********************************************************************************
    External (Public) java.io.OutputStream Interface Methods ***********************
    ********************************************************************************  */

    public void write(int i) 
        throws IOException,
               NullPointerException,
                IndexOutOfBoundsException
    {
        byte [] b = new byte[1];
        b[0] = (byte) i;
        write(b, 0, 1);
    }

    public void write(byte[] b) 
        throws IOException,
               NullPointerException,
               IndexOutOfBoundsException
    {
        write(b, 0, b.length);
    }

    public void write(byte[] b, int off, int len) 
        throws IOException,
                NullPointerException,
                IndexOutOfBoundsException
    {
        SafeArray sa = new SafeArray(Variant.VariantByte, len);
        sa.setBytes(0, len, b, off);
        Variant v = new Variant(sa, true);
        m_IResponse.BinaryWrite(v);
    }

    public void close() 
        throws IOException
    {
        // Nothing to do here -- we don't have to close the ASP response stream
    }

    public void flush() 
        throws IOException
    {
        // Can only flush if ASP buffering is on
        if (getBuffered() == true)
        {
            m_IResponse.Flush();
        }
    }

}
