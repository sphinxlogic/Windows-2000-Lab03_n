// CMyCOMObject.java
//
// Created 09/09/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

package comsamp;

import com.ms.com.*;


// jactivex-generated.
/** @com.class(classid=8EACC4B2-289A-11D1-BA1D-006008039BF0,DynamicCasts)
*/
class CMyCOMObjectImp implements IUnknown,com.ms.com.NoAutoScripting,IMyInterface
{
  /** @com.method() */
  public native void COMCheckedLoad(String filename, byte[] buffer, int[] bufsize);

  /** @com.method() */
  public native void JavaCheckedLoad(String filename, byte[] buffer, int[] bufsize);


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0x8eacc4b2, (short)0x289a, (short)0x11d1, (byte)0xba, (byte)0x1d, (byte)0x0, (byte)0x60, (byte)0x8, (byte)0x3, (byte)0x9b, (byte)0xf0);
}


/**
 * Wraps the COM implementation of CMyCOMObject and re-implements the
 * JavaCheckedLoad method to perform a security check before invoking
 * the existing COM implementation.
 * The implementation of COMCheckedLoad simply delegates to the COM
 * implementation.
 */
public class CMyCOMObject
{
    IMyInterface imp = new CMyCOMObjectImp();

    public void COMCheckedLoad(String filename, byte[] buffer, int[] bufsize)
    {
        imp.COMCheckedLoad(filename, buffer, bufsize);
    }

    public void JavaCheckedLoad (String filename, byte[] buffer, int[] bufsize)
    {
        SecurityManager security = System.getSecurityManager();
        if (security != null)
            security.checkRead(filename);
        imp.JavaCheckedLoad(filename, buffer, bufsize);
    }
}


/**
 * Used from COM to perform security checks.
 */
class CMyCOMObjectSecurity implements IMyCOMObjectSecurity
{
    public void CheckRead (String filename)
    {
        SecurityManager security = System.getSecurityManager();
        if (security != null)
            security.checkRead(filename);
    }
}


