/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example shows how to pass a pointer to a simple structure.
 * To declare a native structure in Java, use the "@dll.struct"
 * directive as shown the MEMORYSTATUS structure. 
 */


import com.ms.dll.DllLib;

public class Structs
{
    public static void main(String args[])
    {
        MEMORYSTATUS mstatus = new MEMORYSTATUS();
        GlobalMemoryStatus(mstatus);

        System.out.println("Total     physical memory = " +
                           Integer.toHexString(mstatus.dwTotalPhys));

        System.out.println("Available physical memory = " +
                           Integer.toHexString(mstatus.dwAvailPhys));

        System.out.println("Total     page file       = " +
                           Integer.toHexString(mstatus.dwTotalPageFile));

        System.out.println("Available page file       = " +
                           Integer.toHexString(mstatus.dwAvailPageFile));

        System.out.println("Total     virtual memory  = " +
                           Integer.toHexString(mstatus.dwTotalVirtual));

        System.out.println("Available virtual memory  = " +
                           Integer.toHexString(mstatus.dwAvailVirtual));


    }


    /** @dll.import("KERNEL32") */
    static native void GlobalMemoryStatus(MEMORYSTATUS lptMemStat);
}


/** @dll.struct() */
class MEMORYSTATUS {

    public int dwLength = DllLib.sizeOf(MEMORYSTATUS.class);
    public int dwMemoryLoad;
    public int dwTotalPhys;
    public int dwAvailPhys;
    public int dwTotalPageFile;
    public int dwAvailPageFile;
    public int dwTotalVirtual;
    public int dwAvailVirtual;


}

