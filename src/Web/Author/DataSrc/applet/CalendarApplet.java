import java.util.*;
import java.lang.Float;
import java.applet.*;
import java.awt.*;

// Run midl compiler on the idl files: simpdata.idl and
// dslisten.idl.  This generates .tlb files.  Then run
// the javatlb tool to generate the java classes for these
// interfaces (which are placed in the c:\winnt\java\trustlib
// folder).

import java.util.Calendar;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

import com.ms.osp.*;

//------------------------------------------------------------------
public class CalendarApplet extends Applet
{
    public  CalendarApplet()
    {
        locale = Locale.FRENCH; // getDefault();
        calendar = Calendar.getInstance(locale);
        // this causes the page to take several minutes to load.
        // available = Calendar.getAvailableLocales();
        available = new Locale[1];
        available[0] = locale;
        UpdateLocale(locale);
    }

    public String getDate()
    {
        String date = formatter.format(calendar.getTime());
        return date;
    }

    public void setLocale(String s)
    {
        int i = s.indexOf(".");
        String lang = s.substring(0,i);
        String country = s.substring(i+1);
        locale = new Locale(lang, country);
        UpdateLocale(locale);
    }

    private void UpdateLocale(Locale locale)
    {
        this.locale = locale;
        Date time = calendar.getTime(); // save current setting.
        calendar = Calendar.getInstance(locale);
        calendar.setTime(time); // restore current setting.
        myProvider = new CalendarProvider (this, calendar, locale);
        formatter = new SimpleDateFormat("MMMM yyyy", locale);
        labelformatter = new SimpleDateFormat("EEEE", locale);
        notifyListeners();
        repaint();
    }

    public String getDayLabel(int i)
    {
        Calendar c = (Calendar)calendar.clone(); 
        while (c.get(Calendar.DAY_OF_WEEK) != i + 1) {
            c.roll(Calendar.DATE,true);
            c.setTime(c.getTime()); // trigger recalc.
        }
        String result = labelformatter.format(c.getTime());
        return result;
    }

    public int getLocaleCount()
    {
        return available.length; 
    }

    public boolean isCurrentLocale(int i)
    {
        return (i >= 0 && i < available.length && available[i] == locale);
    }

    public String getLanguage(int i)
    {
        String result = "";
        if (i >= 0 && i < available.length)
            available[i].getDisplayName();
        return result;
    }

    public String getLocaleCode(int i)
    {
        String result = "";
        if (i >= 0 && i < available.length) {
            Locale locale = available[i];
            result = locale.getLanguage() + "." + locale.getCountry();
        }
        return result;
    }

    public void ChangeMonth(int iDelta)
    {
        calendar.add(Calendar.MONTH, iDelta);
        calendar.setTime(calendar.getTime()); // trigger re-calc.
        myProvider = new CalendarProvider (this, calendar, locale);
        notifyListeners();
        repaint();
        return;
    }

    // Function to provide the OLE-DB simple provider interface to callers.
    // The qualifier parameter is ignored at this point, but is available
    // to allow the applet to serve up more than one data set

    public OLEDBSimpleProvider  msDataSourceObject(String qualifier)
    {
        return myProvider;
    }

    public void addDataSourceListener(DataSourceListener  listener)
        throws java.util.TooManyListenersException
    {
        if (myDSL != null)
            com.ms.com.ComLib.release(myDSL);
        
        myDSL = listener;
    }

    public void removeDataSourceListener( DataSourceListener   listener)
    {

        com.ms.com.ComLib.release(myDSL);
        myDSL = null;
    }

    // This function should probably be private, but for
    // now leave public so script writer can call to test notifications

    public void notifyListeners()
    {
        if (myDSL != null)
            myDSL.dataMemberChanged("");
    }

    private CalendarProvider  myProvider;
    private DataSourceListener myDSL;
    private Calendar calendar;
    private Locale locale;
    private SimpleDateFormat formatter;
    private SimpleDateFormat labelformatter;
    private String localeName;
    private Locale available[];
}

//------------------------------------------------------------------
class CalendarProvider  implements OLEDBSimpleProvider  
{    
    public CalendarProvider (CalendarApplet parent, Calendar c, Locale locale)
    {
        myParent = parent;
        calendar = (Calendar)c.clone();
        int iCurrentMonth = calendar.get(Calendar.MONTH);
        // Set calendar to first day of month.
        calendar.set(calendar.get(Calendar.YEAR),calendar.get(Calendar.MONTH),
            calendar.getMinimum(Calendar.DAY_OF_MONTH));
        calendar.setTime(calendar.getTime()); // trigger re-calc of fields.
        firstDayOfMonthPosition = calendar.get(Calendar.DAY_OF_WEEK)-1;
        // This assumes first day of week is Sunday.
        // So now adjust this based on what the real first day of week is.
        firstDayOffset = calendar.getFirstDayOfWeek()-1;
        firstDayOfMonthPosition -= firstDayOffset;
        if (firstDayOfMonthPosition < 0)
            firstDayOfMonthPosition += 7;

        // roll back to last day of month
        calendar.roll(Calendar.DATE,false);
        daysInMonth = calendar.get( Calendar.DAY_OF_MONTH );
        dayformatter = new SimpleDateFormat("d", locale);
    }

    public int getRowCount()
    {
        int rowCount = ((firstDayOfMonthPosition + daysInMonth + 6) / 7);
        return rowCount;
    }

    public int getEstimatedRows()
    {
        return getRowCount();
    }

    public int getColumnCount()
    {
        return 7;  // 7 days in a week
    }

    public int getRWStatus(int iRow,int iColumn)
    {
        return 0;  // STDRW_READONLY
    }

    public void addOLEDBSimpleProviderListener(OLEDBSimpleProviderListener l)
    {
    }

    public void removeOLEDBSimpleProviderListener(OLEDBSimpleProviderListener l)
    {
    }

    public int find(int iStartRow, int iColumn, Object varSearchVal,
                    int findFlags, int compType)
    {
        return 0;
    }

    public int deleteRows(int iRow,int cRows)
    {
        return 0;
    }

    public int insertRows(int iRow,int cRows)
    {
        return 0;
    }

    private String stDayFromInt(int iDay)
    {
        // I think these have to match the table headings in the html file.
        String stDay = "";

        switch (iDay)
        {
            case 0:
                stDay = "1";
                break;
            case 1:   
                stDay = "2";
                break;
            case 2:   
                stDay = "3";
                break;
            case 3:   
                stDay = "4";
                break;
            case 4:   
                stDay = "5";
                break;
            case 5:   
                stDay = "6";
                break;
            case 6:   
                stDay = "7";
                break;
        }
        return stDay;
    }

    private int dayOfMonth(int dayOfWeek, int week)
    {
        if (dayOfWeek > firstDayOfMonthPosition)
            week--;
        return (dayOfWeek - firstDayOfMonthPosition) + (7 * week) + 1;
    }

    private String Holiday(int d)
    {
        String retVal = null;
        int iCurrentMonth = calendar.get(Calendar.MONTH);
        if (iCurrentMonth == 0 && d == 1)
            retVal = "New Years";

        if (iCurrentMonth == 6 && d == 4)
            retVal = "Independence Day";

        if (iCurrentMonth == 11 && d == 25)
            retVal = "Christmas";

        if (iCurrentMonth == 10 && dayOfMonth(4, 4) == d )
            retVal = "Thanksgiving";

        return retVal;
    }

    private String RemindersForDate(int d, int formatType)
    {
        String holiday = Holiday(d);
        if (holiday != null)
        {
            if (formatType == 1)
                holiday = "<font color=blue>" + holiday + "</font>";
            return holiday;
        }

        if (dayOfMonth(4, 4) == d)
            return "recycling pickup";
        
        if (dayOfMonth(1,1) == d || dayOfMonth(1,3) == d)
            return "staff mtg";
        return null;
    }

    public Object getVariant(int iRow, int iColumn,int formatType )
    {
        Object retVal = null;
        if (iRow == 0)
        {
            // return the column information
            retVal = stDayFromInt(iColumn-1);
        }
        else
        {
            int iDayOfMonth = ((iRow-1) * 7 + iColumn) - firstDayOfMonthPosition;

            if (iDayOfMonth <= 0 || iDayOfMonth > daysInMonth)
                // this row/column combination doesn't represent a valid day
                // i.e. before the 1st or after the last day of the month
                retVal = "";
            else
            {
                // return the day of the month plus any reminders
                int i = calendar.getMinimum(Calendar.DAY_OF_MONTH)-1;
                i += firstDayOffset;
                calendar.set(Calendar.DAY_OF_MONTH, iDayOfMonth - i);
                String string = dayformatter.format(calendar.getTime());
    
                String note = RemindersForDate(iDayOfMonth, formatType);

                if (formatType == 1)
                    string = "<div style=\"font-weight:bold\">" + string + "</div>";

                if ( note != null )
                    string = string + "<br>" + "<font color=red>" + note + "</font>";
                
                retVal = string;
            }
        }
        return retVal;
    }

    public void setVariant(int iRow,int iColumn, int formatType, Object var)
    {
        // do nothing since the data is readonly
    }

    public String getLocale()
    {
        // nothing special here. Return the default locale, ie. US

        return "";
    }

    public int isAsync()
    {
        return 0;
    }

    public void stopTransfer()
    {
    }

    private CalendarApplet myParent;
    private int firstDayOfMonthPosition;
    private int daysInMonth;
    private int firstDayOffset;
    private Calendar calendar;
    private SimpleDateFormat dayformatter;

}

