/*  ********************************************************************************
    VariantToJava.java *************************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.com.*;
import java.util.*;
import com.ms.asp.*;

/**
 * Conversion routines.
 */

public class VariantToJava 
{

/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    // Half a second, expressed in days
    private static double HALF_SECOND = (1.0/172800.0);
    private static int rgMonthDays[] =
        {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public static boolean getBoolean(Variant v)        
        throws ClassCastException 
    {
        return v.getBoolean();
    }

    public static byte getByte(Variant v)            
        throws ClassCastException 
    {
        return v.getByte();
    }

    public static short getShort(Variant v)            
        throws ClassCastException 
    {
        return v.getShort();
    }

    public static char getChar(Variant v)            
        throws ClassCastException 
    {
        return (char)v.getShort();
    }

    public static int getInt(Variant v)                
        throws ClassCastException 
    {
        return v.getInt();
    }

    public static long getLong(Variant v)            
        throws ClassCastException 
    {
        return (long)v.getInt();
    }

    public static float getFloat(Variant v)            
        throws ClassCastException 
    {
        return v.getFloat();
    }

    public static double getDouble(Variant v)        
        throws ClassCastException 
    {
        return v.getDouble();
    }

    public static String getString(Variant v)        
        throws ClassCastException 
    {
        if (v.getvt() != v.VariantString) 
        {
            if (v.getvt() == v.VariantDispatch) 
            {
                IStringList slist = (IStringList)v.getDispatch();
                Variant p = new Variant();
                p.noParam();
                v = slist.getItem(p);
                if (v.getvt() == v.VariantString)
                    return v.getString();
            }
            throw new ClassCastException();
        }
        return v.getString();
    }

    public static Object getObject(Variant v)        
        throws ClassCastException 
    {
        switch(v.getvt()) 
        {
        case Variant.VariantString:
            String s = v.getString();
            return s;
        case Variant.VariantObject:
            return v.getObject();
        default:
            break;
        }
        throw new ClassCastException();
    }

    public static Date getDate(Variant v)            
        throws ClassCastException 
    {
        // source code copied from MFC 4.21 and modified

        long nDays;                    // Number of days since Dec. 30, 1899
        long nDaysAbsolute;            // Number of days since 1/1/0
        long nSecsInDay;            // Time in seconds since midnight
        long nMinutesInDay;            // Minutes in day

        long n400Years;                // Number of 400 year increments since 1/1/0
        long n400Century;            // Century within 400 year block (0,1,2 or 3)
        long n4Years;                // Number of 4 year increments since 1/1/0
        long n4Day;                    // Day within 4 year block
                                    //  (0 is 1/1/yr1, 1460 is 12/31/yr4)
        long n4Yr;                    // Year within 4 year block (0,1,2 or 3)
        boolean bLeap4 = true;        // TRUE if 4 year block includes leap year

        // values in terms of year month date.
        int tm_sec;   
        int tm_min;   
        int tm_hour;  
        int tm_mday;  
        int tm_mon;   
        int tm_year;  
        int tm_wday;  
        int tm_yday;  

        if (v.getvt() != v.VariantDate)
            throw new ClassCastException();

        double dtSrc = v.getDate();
        double dblDate = dtSrc; // temporary serial date

        // If a valid date, then this conversion should not overflow
        nDays = (long)dblDate;

        // Round to the second
        dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

        // Add days from 1/1/0 to 12/30/1899
        nDaysAbsolute = (long)dblDate + 693959L; 

        dblDate = Math.abs(dblDate);
        nSecsInDay = (long)((dblDate - Math.floor(dblDate)) * 86400.);

        // Leap years every 4 yrs except centuries not multiples of 400.
        n400Years = (long)(nDaysAbsolute / 146097L);

        // Set nDaysAbsolute to day within 400-year block
        nDaysAbsolute %= 146097L;

        // -1 because first century has extra day
        n400Century = (long)((nDaysAbsolute - 1) / 36524L);

        // Non-leap century
        if (n400Century != 0)
        {
            // Set nDaysAbsolute to day within century
            nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

            // +1 because 1st 4 year increment has 1460 days
            n4Years = (long)((nDaysAbsolute + 1) / 1461L);

            if (n4Years != 0)
                n4Day = (long)((nDaysAbsolute + 1) % 1461L);
            else
            {
                bLeap4 = false;
                n4Day = (long)nDaysAbsolute;
            }
        }
        else
        {
            // Leap century - not special case!
            n4Years = (long)(nDaysAbsolute / 1461L);
            n4Day = (long)(nDaysAbsolute % 1461L);
        }

        if (bLeap4)
        {
            // -1 because first year has 366 days
            n4Yr = (n4Day - 1) / 365;

            if (n4Yr != 0)
                n4Day = (n4Day - 1) % 365;
        }
        else
        {
            n4Yr = n4Day / 365;
            n4Day %= 365;
        }

        tm_year = (int)(n400Years * 400 + n400Century * 100 + 
                        n4Years * 4 + n4Yr);

        // Handle leap year: before, on, and after Feb. 29.
        if (n4Yr == 0 && bLeap4 && n4Day == 59)
        {
            /* Feb. 29 */ 
            tm_mon = 2;
            tm_mday = 29;
        }
        else 
        {
            if (n4Yr == 0 && bLeap4 && n4Day >= 59)
                --n4Day;

            // Make n4DaY a 1-based day of non-leap year and compute
            //  month/day for everything but Feb. 29.
            ++n4Day;

            // Month number always >= n/32, so save some loop time */ 
            for (tm_mon = (int)((n4Day >> 5) + 1);
                 n4Day > rgMonthDays[tm_mon]; tm_mon++);

            tm_mday = (int)(n4Day - rgMonthDays[tm_mon-1]);
        }

        if (nSecsInDay == 0)
            tm_hour = tm_min = tm_sec = 0;
        else
        {
            tm_sec = (int)(nSecsInDay % 60L);
            nMinutesInDay = nSecsInDay / 60L;
            tm_min = (int)(nMinutesInDay % 60);
            tm_hour = (int)(nMinutesInDay / 60);
        }

        String[] ids = TimeZone.getAvailableIDs(-8 * 60 * 60 * 1000);
        if (ids.length == 0) throw new AspComponentException(AspLocalizedStrings.ASP_E_INTERNAL_FAILURE);
        SimpleTimeZone pdt = new SimpleTimeZone(-8 * 60 * 60 * 1000, ids[0]);
        pdt.setStartRule(Calendar.APRIL, 1, Calendar.SUNDAY, 2 * 60 * 60 * 1000);
        pdt.setEndRule  (Calendar.OCTOBER, -1, Calendar.SUNDAY, 2 * 60 * 60 * 1000);
        GregorianCalendar calendar = new GregorianCalendar(pdt);
        calendar.set(tm_year, tm_mon - 1, tm_mday, tm_hour, tm_min, tm_sec);
        return calendar.getTime();
    }
}
