///////////////////////////////////////////////////////////////////////////
//
//  JCalendarMonthEditor.java
//
//  This class is an editor for editing the calendar month. It uses
//  PropertyEditorSupport.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////

import java.beans.*;

public class JCalendarMonthEditor extends PropertyEditorSupport
{
    
    /**
     * Returns a string representation of the property suitable for
     * inclusion in java code. Note month being an int will be wrapped in Integer.
     *
     * @return  String  The java representation of the month.
     */
    public String getJavaInitializationString()
    {
        // start off with january
       return ((Integer) getValue()).toString();
    }

    /**
     * Get the list of valid values for the month
     *
     * @return  String[]    The array of month names
     */
    public String[] getTags()
    {
        return JCalendar.monthNames;
    }

    /**
     * Return a string representation of the property suitable for display
     *
     * @return  String  The month name.
     */
    public String getAsText()
    {
        int month = ((Integer) getValue()).intValue();  // the month number;

        return JCalendar.monthNames[month];
    }

    /**
     * Set the value of the month based on the month name given as a string
     *
     * @param   String  The month name
     */
    public void setAsText(String month) throws java.lang.IllegalArgumentException
    {
        for(int i=0; i< JCalendar.MONTHS_IN_YEAR; i++)
        {
            if( month.toLowerCase().equals(JCalendar.monthNames[i].toLowerCase()) )
            {
                setValue(new Integer(i));
                return;
            }
        }
     
        throw new java.lang.IllegalArgumentException("Unknown month: "+month);
    }
 
}