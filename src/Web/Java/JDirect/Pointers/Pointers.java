/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example shows several different ways of dealing with pointers
 * in Java. This sample simply prints out the version string of
 * KERNEL32.DLL using the Win32 version apis. This seemingly straightforward
 * task requires parsing data through a double-indirected pointer.
 *
 * A one-element int[] array is used to simulate a pointer to a return buffer,
 * in the "pValBuffer" argument to VerQueryValue.
 *
 * A byte[] array is used to simulate a generic buffer in the "pVerBuffer"
 * arguments to getFileVersionInfo and VerQueryValue.
 *
 * An "int" is used to simulate the LPVOID pointer received from
 * VerQueryValue.
 *
 * DllLib.ptrToStruct() is used to parse the data addressed by
 * an LPVOID pointer.
 *
 * DllLib.ptrToString() is used to extract a string addressed by
 * an LPVOID pointer.
 *
 * (Note: This is intended to be an example of how to deal with particularly
 * difficult DLL functions. The specific task of getting version information
 * for a file can be done much more easily using the FileVersionInformation
 * class in com.ms.util.)
 */


import com.ms.dll.*;

/** @dll.import(auto) */
public class Pointers
{
  
  public static void main(String args[])
  {
    String sVersion;
    
    sVersion = FileInfo.getVersion(getSystemDirectory() + "\\KERNEL32.DLL");
    
    if(sVersion.length() > 0)
    { System.out.println("KERNEL32.DLL version is " + sVersion);
    }
    else
    { System.out.println("Couldn't get version information for KERNEL32.DLL");
    }
  }



  /** @dll.import("KERNEL32") */
  private static native int GetSystemDirectory(StringBuffer sysPath, int cch);

  private static String getSystemDirectory()
  {
      int MAXPATH=260;
      StringBuffer sysPath = new StringBuffer(MAXPATH-1);
      int cb = GetSystemDirectory(sysPath, MAXPATH);
      if (cb == 0 || cb > MAXPATH) {
          throw new RuntimeException("GetSystemDirectory() failed.");
      }
      return sysPath.toString();
  }

}



//==========================================================================//
// This structure allows us to extract a value from a pointer returned by
// the Win32 VerQueryValue routine.

/** @dll.struct() */
class PP_INTEGER 
{ public int iVal;
}


//==========================================================================//

/** @dll.import(auto) */
class FileInfo
{

  /** @dll.import("VERSION") */
  private static native int GetFileVersionInfoSize(String sFileName,
                                                   int    pHandle[]);

  /** @dll.import("VERSION") */
  private static native boolean GetFileVersionInfo(String sFileName,
                                                   int    iHandle,
                                                   int    iSize,
                                                   byte   pVerBuffer[]);

  /** @dll.import("VERSION") */
  private static native boolean VerQueryValue(byte   pVerBuffer[],
                                              String sSubBlock,
                                              int    pValBuffer[],
                                              int    piSize[]);



//--------------------------------------------------------------------------//

  public static String getVersion(String sFileName)
  {    
    PP_INTEGER ppInt;
    boolean bStat;
    int pValBuffer[] = {0};
    int pHandle[] = {0};
    int piSize[] = {0};
    int iSize;

    // See if the module has version info.  If not, return an empty string.
      iSize = GetFileVersionInfoSize(sFileName, pHandle);
      if(iSize < 1) return "";

    // Create enough space to hold the version information data block.
    byte[] pVerBuffer = new byte[iSize + 32];

    // Try to get the version info.  If we can't, return an empty string.
      bStat = GetFileVersionInfo(sFileName, pHandle[0], iSize, pVerBuffer);
    if(bStat == false) return "";

    // Get the language entry array data for the target file.
    // If we can't get it, return an empty string.
    bStat = VerQueryValue(pVerBuffer,
                          "\\VarFileInfo\\Translation",
                          pValBuffer,
                          piSize);
    if(bStat == false || piSize[0] < 1) return "";

    // Use the default (first) language entry in the array to 
    // generate the query string for the file version. 
    ppInt = (PP_INTEGER)DllLib.ptrToStruct(PP_INTEGER.class, pValBuffer[0]);
    String sLCID = intToHexString(ppInt.iVal);
    String sFileVersion = "\\StringFileInfo\\" +
                          sLCID.substring(4) +
                          sLCID.substring(0, 4) +
                          "\\FileVersion";
    
    // Query for version string. Return an empty string if we don't get it.
    bStat = VerQueryValue(pVerBuffer, sFileVersion, pValBuffer, piSize);
    if(bStat == false || piSize[0] < 1) return "";
    
    // Return the version string.
    return DllLib.ptrToString(pValBuffer[0]);
  }

//-----------------------------------------------------------------------//
// This routine generates an eight-character hexadecimal string that
// represents the integer value passed in.  The string is padded with
// leading zeros as needed to make it eight characters long.

  static String intToHexString(int iVal)
  {
    String sTemp = new String("00000000" + Integer.toHexString(iVal));
    sTemp = sTemp.toUpperCase();
    return sTemp.substring(sTemp.length() - 8);    
  }

}  // End of public class FileInfo.

//==========================================================================//
//                               - EOF -                                    // 
//==========================================================================//





