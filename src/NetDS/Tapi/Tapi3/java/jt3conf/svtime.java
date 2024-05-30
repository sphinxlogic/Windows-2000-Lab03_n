/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
        svtime.java
Abstract:

Author:

Notes:
Revision History:
--*/


import com.ms.dll.DllLib;
import com.ms.dll.*;

public class svtime
{

    /////////////////////////////////////////////////////////////////////
    // getSTime
    // convert the time data into double format 
    /////////////////////////////////////////////////////////////////////
    public static double getSTime(short yr, short mo, short dy, short hr, short mn)
    {
        SYSTEMTIME st = new SYSTEMTIME();
		double[] vt = {0};

		st.wYear = yr;
		st.wMonth = mo;
		st.wDay = dy;
		st.wHour = hr;
		st.wMinute = mn;
    	st.wDayOfWeek = 0;
    	st.wSecond = 0;
    	st.wMilliseconds = 0;

		SystemTimeToVariantTime(st, vt);
		System.out.println(vt[0]);
		return vt[0];
   }


    public static void getVTime (double vtime, short[] pYear, short[] pMonth, short[] pDay, short[] pHour, short[] pMin)
    {
        SYSTEMTIME st = new SYSTEMTIME();

		double[] vt = {0};
		vt[0] = vtime;

		VariantTimeToSystemTime (vt[0], st);
		pYear[0] = st.wYear;
		pMonth[0] = st.wMonth;
		pDay[0] = st.wDay;
		pHour[0] = st.wHour;
		pMin[0] = st.wMinute;

		System.out.println(st.wYear);
		System.out.println(st.wMonth);
		System.out.println(st.wDay);
		System.out.println(st.wHour);
		System.out.println(st.wMinute);
    }


    /** @dll.import("oleaut32", ole) */
    static native void SystemTimeToVariantTime(SYSTEMTIME lpst, double[] d);

    /** @dll.import("oleaut32", ole) */
    static native void VariantTimeToSystemTime(double d, SYSTEMTIME lpst);
}


/** @dll.struct() */
class SYSTEMTIME {
    public short wYear;
    public short wMonth;
    public short wDayOfWeek;
    public short wDay;
    public short wHour;
    public short wMinute;
    public short wSecond;
    public short wMilliseconds;
}

