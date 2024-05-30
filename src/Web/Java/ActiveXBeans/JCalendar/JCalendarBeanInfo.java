///////////////////////////////////////////////////////////////////////////
//
//  JCalendarBeanInfo.java
//
//  This contains information about the JCalendar bean for developers.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////

import java.beans.*;
import java.awt.*;
import java.io.*;


public class JCalendarBeanInfo extends SimpleBeanInfo implements Serializable
{
    /**
     * Return the icon for this bean
     * 
     * @param   int     whether 16x16 pixels or 32x32
     * @return  Image   The image icon for the calendar
     */
    public Image getIcon(int iconKind)
    {
        if(iconKind == BeanInfo.ICON_COLOR_16x16)        
            return loadImage("JCalendarIcon16.gif");
        
        if(iconKind == BeanInfo.ICON_COLOR_32x32)
            return loadImage("JCalendarIcon32.gif");

        return null;
    }


    /**
     * Returns the list of properties associated with the Calendar and
     * specifies their editors.
     */

    public PropertyDescriptor[] getPropertyDescriptors()
    {
        // watch out for IntrospectionException
        try
        { 
            // Create a property descriptor for each of the properties.
            PropertyDescriptor 
                circleActiveDate = new PropertyDescriptor("circleActiveDate", JCalendar.class),
                date = new PropertyDescriptor("date", JCalendar.class),
                month = new PropertyDescriptor("month", JCalendar.class),
                showHorizontalLines= new PropertyDescriptor("showHorizontalLines", JCalendar.class),
                showOutline = new PropertyDescriptor("showOutline", JCalendar.class),
                showVerticalLines = new PropertyDescriptor("showVerticalLines", JCalendar.class),
                year = new PropertyDescriptor("year", JCalendar.class),
                font = new PropertyDescriptor("font", JCalendar.class),
                foreground = new PropertyDescriptor("foreground", JCalendar.class),
                background = new PropertyDescriptor("background", JCalendar.class);


            // give a brief description of each of these properties.
            circleActiveDate.setShortDescription("Is the displayed date to be circled or not");
            date.setShortDescription("The day of the month which is to be displayed");
            month.setShortDescription("The month to be displayed");
            // TODO: add more descriptios here.
            
            // Define a new property editor for the month property
            month.setPropertyEditorClass(JCalendarMonthEditor.class);

            // define a new property editor for the year property
            year.setPropertyEditorClass(JCalendarYearEditor.class);

            // create an array of property descriptors.
            PropertyDescriptor[] pd = { circleActiveDate, date, month, 
                showHorizontalLines, showOutline, showVerticalLines, year,
                    font, foreground, background};

            return pd;
        }

        catch (IntrospectionException e)
        {
            throw new Error(e.toString() + "In getPropertydescriptor()");
        }
       
    }

}
