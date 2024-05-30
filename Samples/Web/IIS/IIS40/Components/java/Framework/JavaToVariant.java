/*  ********************************************************************************
    JavaToVariant.java *************************************************************
    ********************************************************************************  */

package aspcomp;

import com.ms.com.*;
import java.util.*;

/**
 * Conversion routines.
 */

public class JavaToVariant {

/*  ********************************************************************************
    Internal (Private) Variables ***************************************************
    ********************************************************************************  */

    private static int rgMonthDays[] =
        {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};


/*  ********************************************************************************
    External (Public) Methods ******************************************************
    ********************************************************************************  */

    public static Variant fromBoolean(boolean b) 
    {
        return new Variant(b);
    }

    public static Variant fromByte(byte b) 
    {
        return new Variant(Variant.VariantByte, b);
    }

    public static Variant fromShort(short s) 
    {
        return new Variant(Variant.VariantShort, s);
    }
    
    public static Variant fromInt(int i) 
    {
        return new Variant(i);
    }

    public static Variant fromFloat(float f) 
    {
        return new Variant(Variant.VariantFloat, f);
    }

    public static Variant fromDouble(double d) 
    {
        return new Variant(d);
    }

    public static Variant fromString(String str) 
    {
        return new Variant(str);
    }

    public static Variant fromObject(Object o) 
    {
        return new Variant(Variant.VariantObject, o);
    }

    public static Variant fromDate(Date date) 
    {
        return new Variant(Variant.VariantDate, dateToDouble(date));
    }

    public static double dateToDouble(Date date) 
    {
        String[] ids = TimeZone.getAvailableIDs(-8 * 60 * 60 * 1000);
        if (ids.length == 0) throw new AspComponentException(AspLocalizedStrings.ASP_E_INTERNAL_FAILURE);
        SimpleTimeZone pdt = new SimpleTimeZone(-8 * 60 * 60 * 1000, ids[0]);
        pdt.setStartRule(Calendar.APRIL, 1, Calendar.SUNDAY, 2 * 60 * 60 * 1000);
        pdt.setEndRule  (Calendar.OCTOBER, -1, Calendar.SUNDAY, 2 * 60 * 60 * 1000);
        GregorianCalendar calendar = new GregorianCalendar(pdt);
        calendar.setTime(date);

        // source code copied from MFC 4.21 and modified.
        int wYear   = calendar.get(Calendar.YEAR);
        int wMonth  = calendar.get(Calendar.MONTH) + 1;
        int wDay    = calendar.get(Calendar.DAY_OF_MONTH);
        int wHour   = calendar.get(Calendar.HOUR_OF_DAY);
        int wMinute = calendar.get(Calendar.MINUTE);
        int wSecond = calendar.get(Calendar.SECOND);

        //  Check for leap year and set the number of days in the month
        boolean bLeapYear = ((wYear & 3) == 0) &&
                            ((wYear % 100) != 0 || (wYear % 400) == 0);

        int nDaysInMonth =
                          rgMonthDays[wMonth] - rgMonthDays[wMonth-1] +
                          ((bLeapYear && wDay == 29 && wMonth == 2) ? 1 : 0);

        // Cache the date in days and time in fractional days
        long nDate;
        double dblTime;

        //It is a valid date; make Jan 1, 1AD be 1
        nDate = wYear*365L + wYear/4 - wYear/100 + wYear/400 +
                rgMonthDays[wMonth-1] + wDay;

        //  If leap year and it's before March, subtract 1:
        if (wMonth <= 2 && bLeapYear)
            --nDate;

        //  Offset so that 12/30/1899 is 0
        nDate -= 693959L;

        dblTime = (((long)wHour * 3600L) +  // hrs in seconds
                   ((long)wMinute * 60L) +  // mins in seconds
                   ((long)wSecond)) / 86400.;

        double dtDest = (double) nDate + 
                        ((nDate >= 0) ? dblTime : -dblTime);

        return dtDest;
    }
}
