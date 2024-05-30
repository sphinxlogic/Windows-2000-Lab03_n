/*  ********************************************************************************
    Request.java *******************************************************************
    ********************************************************************************  */

package aspcomp;

import java.io.*;
import com.ms.com.*;
import com.ms.asp.*;

/**
 * Cover class for the ASP Request intrinsic.
 */

public class Request 
    extends InputStream 
{

/*  ********************************************************************************
    Constructor ********************************************************************
    ********************************************************************************  */

    public Request(IRequest request, IResponse response) 
    {
        m_IRequest = request;
        m_IResponse = response;
        m_arrInput = null;
        m_iInputLength = 0;
        m_iInputPosition = 0;
        m_iMarkPosition = 0;
        m_iMarkReadLimit = 0;
        m_fMarked = false;
    }


/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private IRequest  m_IRequest;
    private IResponse m_IResponse;
    private byte []   m_arrInput;
    private int       m_iInputLength;
    private int       m_iInputPosition;
    private int       m_iMarkPosition;
    private int       m_iMarkReadLimit;
    private boolean   m_fMarked;


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public RequestDictionary getServerVariables() 
    {
        return new RequestDictionary(m_IRequest.getServerVariables());
    }

    public RequestDictionary getClientCertificate() 
    {
        return new RequestDictionary(m_IRequest.getClientCertificate());
    }

    public RequestDictionary getForm()  
    {
        return new RequestDictionary(m_IRequest.getForm());
    }

    public CookieDictionary getCookies()  
    {
        // Note: we pass the IResponse (not IRequest) cookie collection here, to 
        // allow read/write cookie access. 
        return new CookieDictionary(m_IResponse.getCookies());
    }

    public RequestDictionary getQueryString() 
    {
        return new RequestDictionary(m_IRequest.getQueryString());
    }

    public int getTotalBytes() 
    {
        return m_IRequest.getTotalBytes();
    }


/*  ********************************************************************************
    External (Public) java.io.InputStream Interface Methods ************************
    ********************************************************************************  */

    public int available()                
        throws IOException 
    {
        return getTotalBytes();
    }

    public void close()                    
        throws IOException 
    {
        // There is nothing to do here -- ASP streams do not need to be closed
    }

    public synchronized void mark(int iReadLimit) 
    {
        m_fMarked        = true;
        m_iMarkPosition  = m_iInputPosition;
        m_iMarkReadLimit = iReadLimit;
    }

    public boolean markSupported() 
    {
        return true;
    }

    public synchronized void reset()    
        throws IOException 
    {
        if (!m_fMarked) {
            throw new AspIOException(AspLocalizedStrings.ASP_E_UNMARKED_STREAM);
        }
        else {
            m_fMarked = false;
            m_iInputPosition = m_iMarkPosition;
        }
    }

    public long skip(long iNumToSkip)    
        throws IOException
    {
        long iProperNumberToSkip = Math.min(iNumToSkip, m_iInputLength - m_iInputPosition);

        // Conversion to int should be okay -- everything else
        // takes ints, so shouldn't ever be a problem.
        m_iInputPosition += (int) iProperNumberToSkip;
        
        if (m_fMarked) {
            m_iMarkReadLimit -= iProperNumberToSkip;
            if (m_iMarkReadLimit <= 0) {
                m_fMarked = false;
            }
        }

        return iProperNumberToSkip;
    }

    public int read()                    
        throws IOException,
               NullPointerException,
               IndexOutOfBoundsException
    {
        byte [] b = new byte[1];
        int iNumRead = read(b, 0, 1);
        if (iNumRead == -1) return -1;
        else return b[0];
    }

    public int read(byte[] b)            
        throws IOException,
               NullPointerException,
               IndexOutOfBoundsException
    {
        return read(b, 0, b.length);
    }

    public synchronized int read(byte[] b, int off, int len)    
        throws IOException,
               NullPointerException,
               IndexOutOfBoundsException
    {
        //
        // We want to read in all the data first, and then deal with it later.  We set
        // a reading position for the stream to deal with subsequent calls to the 
        // read() functions.
        //

        if (m_arrInput == null) 
        {
            Variant varInput = m_IRequest.BinaryRead(new Variant(getTotalBytes()));
            SafeArray sa = varInput.toSafeArray();
            m_iInputLength = sa.getUBound() - sa.getLBound() + 1;
            m_arrInput = new byte[m_iInputLength];
            sa.getBytes(0, m_iInputLength, m_arrInput, 0);
            m_iInputPosition = 0;
        }

        // If there isn't any data left, return -1.
        if (m_iInputPosition >= m_iInputLength) return -1;

        // Transfer the smallest number of bytes of (a) the number of bytes requested, 
        // or (b) the number of bytes left to be read.
        int iNumToTransfer = Math.min(len, m_iInputLength - m_iInputPosition);

        // If there isn't enough space in the passed in array for the transfer, throw!
        if ((b.length - off) < iNumToTransfer) 
        {
            // There won't be enough space in the passed in array.
            throw new ArrayIndexOutOfBoundsException();        
        }

        // Do the transfer of bytes, and update the current input position.
        System.arraycopy(m_arrInput, m_iInputPosition, b, off, iNumToTransfer);
        m_iInputPosition += iNumToTransfer;

        // Update the marking status, if necessary.
        if (m_fMarked) 
        {
            m_iMarkReadLimit -= iNumToTransfer;
            if (m_iMarkReadLimit <= 0) 
            {
                m_fMarked = false;
            }
        }

        // And return the number of bytes transferred.
        return iNumToTransfer;
    }
}
