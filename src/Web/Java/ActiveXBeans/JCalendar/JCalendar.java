//////////////////////////////////////////////////////////////////////////
//
//  JCalendar.java
//
//      This example is a demonstration of a calendar object that can
//      be placed in a layout. This object is a complete bean in that
//      it fires events (JCalendarListener) and contains property
//      customizers for setting the year and month
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;
import java.io.*;


public class JCalendar extends Canvas implements Serializable
{
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // CONSTANT DEFINITION FOR THE CALENDAR
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    public static final int    DAYS_IN_WEEK      =   7;
    public static final int    MONTHS_IN_YEAR    =   12;


    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // PROPERTY DEFINITION FOR THE CALENDAR
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    // These are transient properties they should not be saved.
    transient private Vector listeners = new Vector();					// list of all event listeners

    // Not transient properties
    transient private Date activeDate;									// The date which has the active focus.
    private int firstDisplayedDay = 0;									// The first displayed day of the week 0-6 0=>sunday.
    private String weekdayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};                           
																		// The displayed string for the weekdays
    public static final String monthNames[] = {"January", "February", "March", "April", "May", "June", "July", 
    "August", "September", "October", "November", "December"};			// the displayed string for the month name.    
    private Rectangle rect;												// the bounding rectangle of the calendar.
    private int charHeight;									            // The height of a displayed character
    transient private FontMetrics fm;					                // The font metrics for the displayed font.
    private int monthYearLineHeight;									// The height of the line displaying month and year.
    private int dayLineHeight;											// The height of the line displaying the day.
    private int boxHeight;									            // A box houses one date. This is its height.
																		// Note: 6x7 boxes will be displayed.
    private int boxWidth;												// The width of a box
    private boolean showOutline = true;									// calendar outline ?
    private boolean showVerticalLines = true;							//show vertical grid lines
    private boolean showHorizontalLines = true;						    //show horizontal grid lines
    private boolean circleActiveDate = true;							// draw a circle around the active date

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // CONSTRUCTORS FOR THE CALENDAR.
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /** 
     * Default constructor for Calendar without any parameters.
     */
    public JCalendar()
    {
        this(true, true, true, true, new Date() );
    }

    /**
     * Full fledged constructor for the calendar
     *
     * @param   boolean Should the outline be drawn
     * @param   boolean Should the vertical grid lines be drawn
     * @param   boolean Should the horizontal grid lines be drawn
     * @param   boolean Should the active date be circled
     * @param   Date    The starting date
     */
    public JCalendar(boolean outline, boolean verticalLines, boolean horizontalLines, 
        boolean circleActiveDate, Date startDate)
	{
        // call the super class constructor to do its thing
        super();            

        // initialize the properties
       showOutline = outline;
       showVerticalLines = verticalLines;
       showHorizontalLines = horizontalLines;
       this.circleActiveDate = circleActiveDate;
       activeDate = startDate;

       // initalize the display variables
       initDisplayVars();

       // Enable events to be received by the Calendar
       // calendar listens for mouse clicks and arrow keys
       enableEvents(AWTEvent.MOUSE_EVENT_MASK | AWTEvent.KEY_EVENT_MASK);

    }


    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Reconstruct the class from an external storage
    // These functions writeObject and readObject are required because this
	// class needs special handling on de-serialization. The acitveDate has
	// to be recalculated from the current date.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * Write the properties of the calendar to an external object.
     *
     * @param   ObjectOutput    The object to write the calendar properties to
     */
	private void writeObject(ObjectOutputStream stream) throws IOException
	{
		stream.defaultWriteObject();
	}
	
    /**
     * read the properties of the calendar from an external object.
     *
     * @param   ObjectInput     The object to read the properties from
     */
	private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException
	{
		stream.defaultReadObject();
		activeDate = new Date();
	}

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // ACCESSOR METHODS FOR THE CUSTOMIZABLE PROPERTIES.
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    //
    // PROPERTY circleActiveDate   Decide whether to circle the active date or not.
    //

    /**
     * Tells whether the active date is being circled
     *
     * @return  boolean true => active date is being circled
     */
    public boolean getCircleActiveDate()
    {
        return circleActiveDate;
    }

    /**
     * Set the active date to be circled or not.
     *
     * @param   boolean true => circle the active date
     */
    public void setCircleActiveDate(boolean circleOrNotCircle)
    {
        circleActiveDate = circleOrNotCircle;

        // The calendar has to be redrawn
        repaint();
    }

    //
    // PROPERTY showOutline         Decide whether to outline the calendar or not
    //

    /**
     * will the outline have to be shown
     * 
     * @return  boolean Is outline shown ?
     */
    public boolean getShowOutline()
    {
        return showOutline;
    }

    /**
     * set the showOutline property
     *
     * @param   boolean Is the outline to be shown ?
     */
    public void setShowOutline(boolean outlineOrBlank)
    {
        showOutline = outlineOrBlank;

        // The calendar has to be redrawn
        repaint();
    }

    //
    // PROPERTY showVerticalLines       Decide whether to show the vertical grid lines which 
    //                                  separate the dates.

    /**
     * show the vertical grid lines
     *
     * @return  boolean Are the vertical grid lines showing
     */
    public boolean getShowVerticalLines()
    {
        return showVerticalLines;
    }
 
    /**
     * hide/show the vertical grid lines
     *
     * @param  boolean Should the vertical grid lines show ?
     */
    public void setShowVerticalLines(boolean toShowVerticalLines)
    {
        showVerticalLines = toShowVerticalLines;

        // Redraw the calendar with or without the vertical lines
        repaint();
    }

    //
    // PROPERTY showHorizontalLines         Decide whether to show the horizontal grid lines which 
    //                                      separate the dates.
    // 

    
    /**
     * show the horizontal grid lines
     *
     * @return  boolean Are the horizontal grid lines showing
     */
    public boolean getShowHorizontalLines()
    {
        return showHorizontalLines;
    }
 
    /**
     * hide/show the horizontal grid lines
     *
     * @param  boolean Should the horizontal grid lines show ?
     */
    public void setShowHorizontalLines(boolean toShowVerticalLines)
    {
        showHorizontalLines = toShowVerticalLines;

        // Redraw the calendar with or without the vertical lines
        repaint();
    }

    //
    // PROPERTY font    The calendar size has to be recalculated when the font changes thus this property
    //                  in the Component class has to be overridden.
    //

    /**
     * change the calendar font
     *
     * @param   Font    The new calendar font.
     */
    public void setFont(Font f)
    {
        super.setFont(f);

        // This will resize the calendar and draw it again based on the new preferred size.
        adjustSize();
    }


	//
	// PROPERTY Background. The calendar's background has to be repainted when this
	//						property chnages therefore this method must be over-ridden
	//
	/**
	 * change the calendar background
	 *
	 * @param	Color	The background color
	 */
	public void setBackground(Color c)
	{
		super.setBackground(c);

		// this will fill the background color
		repaint();
	}

	//
	// PROPERTY Foreground. The calendar's foreground has to be repainted when this
	//						property chnages therefore this method must be over-ridden
	//
	/**
	 * change the calendar foreground
	 *
	 * @param	Color	The foreground color
	 */
	public void setForeground(Color c)
	{
		super.setForeground(c);

		// this will fill the background color
		repaint();
	}

 
    //
    // PROPERTY date    The date which has the current focus and is currently highlighted.
    //

    /**
     * Returns the active date
     * @return  int    The date which is currently being displayed
     */
    public int getDate()
    {
        return activeDate.getDate();
    }

    /**
     * Change the active date
     * @param   int    The new date to be displayed
     */
    public void setDate(int date)
    {
        // don't do anything if nothing needs to be done.
        if(activeDate.getDate() == date )
        {
            return;
        }

        // First I un-highlight the currently highlighted date.

        // Erase the circle by drawing over it in the background color.
        drawActiveDateCircle(getBackground());

        int oldYear = activeDate.getYear();        // The previous value of year
        int oldMonth = activeDate.getMonth();      // The previous value of month
        int oldDate = activeDate.getDate();        // The previous value of the date
        
        // Now change the date
        activeDate.setDate(date);

        // I want to redraw the calendar only if the month or year change. Else I will only
        // redraw the circle highlighting the active (or highlighted) date.

        if( activeDate.getMonth() != oldMonth || activeDate.getYear() != oldYear )
        {
            // I have to redraw the whole calendar
            repaint();
        }

        else
        {
            // I only have to redraw the circle around the highlighted date.
            drawActiveDateCircle(getForeground());
        }
    
        // Now tell the whole world that the date has changed.
        if(activeDate.getYear() != oldYear)
            fireYearChanged(oldYear, activeDate.getYear());

        if(activeDate.getMonth() != oldMonth)
            fireMonthChanged(oldMonth, activeDate.getMonth());

        if(activeDate.getDate() != oldDate)
            fireDateChanged(oldDate, activeDate.getDate());
                
    }

    //
    // PROPERTY year    The currently displayed year. Note: this must be a positive integer (i.e. >= 1)
    //

    /**
     * Get the currently displayed year
     * @return  int     The year being displayed (e.g. 1997)
     */
    public int getYear()
    {
        return activeDate.getYear() + 1900;
    }

    /**
     * Change the year being displayed
     * @param   int     The year to be displayed
     */
    public void setYear(int year) throws PropertyVetoException
    {
        
        // Veto the property change if its not >= 1
        if(year <= 0)
            throw new PropertyVetoException("year has to be positive !",
                new PropertyChangeEvent(this, "year", new Integer(activeDate.getYear()), new Integer(year)));

        // First copy the old date
        Date oldDate = cloneDate(activeDate);

        // Now change the year.
        activeDate.setYear(year-1900);

        // The calendar will have to be redrawn
        repaint();

        // Tell the whole world about this marvellous event !
        fireJCalendarEvent(oldDate, activeDate);
    }

    //
    // PROPERTY month   The month being displayed in the calendar (0-11)
    //

    /**
     * Get the currently displayed month
     * @return  int     The month being displayed (0 - 11)
     */
    public int getMonth()
    {
        return activeDate.getMonth();
    }

    /**
     * Change the month being displayed
     * @param   int     The month to be displayed (e.g. january is 0)
     */
    public void setMonth(int month) throws PropertyVetoException
    {
        // Veto the change if its negative.
        if(month < 0)
            throw new PropertyVetoException("month can't be negative !",
                new PropertyChangeEvent(this, "month", new Integer(activeDate.getMonth()), new Integer(month)));

        // first copy the old date
        Date oldDate = cloneDate(activeDate);

        // Now change the month and year if necessary
        activeDate.setMonth( month );

        // Redraw the calendar
        repaint();

        // Tell everyone that the date has changed.
        fireJCalendarEvent(oldDate, activeDate);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // PUBLIC METHODS FOR PERFORMING ACTIONS ON THE CALENDAR
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * Increment year by one.
     *
     */
    public void nextYear()
    {
        try 
        {
            // increment the year
            setYear(getYear() + 1);
        }
        catch(PropertyVetoException e)
        {
            // Do nothing. This exception is not going to occur unless you go into B.C.
        }
    }

    /**
     * Decrement year by one.
     */
    public void previousYear()
    {
        try
        {
            // decrement the year
            setYear(getYear() - 1);
        }
        catch(PropertyVetoException e)
        {
            // Do nothing. This exception is not going to occur unless you go into B.C.
        }
    }

    /**
     * Increment month by one.
     */
    public void nextMonth()
    {
        try
        {
            // increment the month
            setMonth(getMonth() + 1);
        }
        catch (PropertyVetoException e)
        {
        }
    }

    /**
     * Decrement month by one.
     */
    public void previousMonth()
    {
        try
        {
            // decrement the month
            setMonth(getMonth() - 1);
        }
        catch (PropertyVetoException e)
        {
            // If you are trying to go back a month from january then set the month to december !
            if(getMonth() == 0) 
            {
                // First make a copy of the old date
                Date oldDate = cloneDate(activeDate);

                // Go back a year and set the month to December.
                activeDate = new Date(activeDate.getYear() - 1, 11, activeDate.getDate());

                // Redraw the calendar.
                repaint();

                // since setMonth()  failed we have to now notify the change in the calendar.
                fireJCalendarEvent(oldDate, activeDate);
            }
        }
    }

    /**
     * Increments the current date by one week
     */
    public void nextWeek()
    {
        setDate(activeDate.getDate() + DAYS_IN_WEEK);
    }

    /**
     * Decrement the date by one week
     */
    public void previousWeek()
    {
        setDate(activeDate.getDate() - DAYS_IN_WEEK);
    }        

    /**
     * Increments the date by one
     */
    public void nextDate()
    {
        setDate(activeDate.getDate() + 1);
    }

    /**
     * Decrements the date by one
     */
    public void previousDate()
    {
        setDate(activeDate.getDate() - 1);
    }

    /**
     * Changes the date to today
     */
    public void toToday()
    {
        // Assign today's date to activeDate.
        activeDate = new Date();

        // The calendar has to be redrawn now.
        repaint();
    }

    /**
     * Returns the first date of the month --> 1 !!
     *
     * @return  int the first date of the month
     */
    public int getFirstDate()
    {
        return 1;
    }

    /**
     * Returns the last date of the month
     *
     * @return  int The last date of the month
     */
    public int  getLastDate()
    {
        Date lastDate = new Date(activeDate.getYear(), activeDate.getMonth()+1, 0);

        return lastDate.getDate();
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // METHODS FOR DISPLAYING THE CALENDAR.
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    /**
     * Draw the calendar
     * @param   Graphics    The graphics device for drawing the calendar
     */
	public void paint  (Graphics g)
	{
        // calculate the display variables
        initDisplayVars();   

		// fill the nackground with the background color
		g.setColor(getBackground());
		g.fillRect(0,0,rect.width-1, rect.height-1);
		
		// restore the foreground color
		g.setColor(getForeground());

        // Draw the outline of the calendar if desired.
        if(showOutline)
            g.drawRect(0,0, rect.width-1, rect.height-1);

        // Draw all the horizontal lines of the calendar.
        drawHorizontalLines(g);

        // Draw all the vertical lines
        drawVerticalLines(g);

        // We need the font metrics to calculate string
        // widths and heights
        fm = g.getFontMetrics();

        charHeight = fm.getAscent();  // the height of the chars
     
        // Displat the month and the year
        displayMonthYear(g);

        // Display the days of the week
        displayWeekDays(g);

        // Display the dates
        displayDates(g);
        
    }

    //--------------------------------------------------------------------
    // Private methods for displaying the calendar.
    //--------------------------------------------------------------------

    /**
     * Initialize the variables corresponding to the screen display.
     */
    private void initDisplayVars()
    {
        // First figure out my dimensions.
        rect = getBounds();  // The bounding rectangle of this object
    
        // The calendar is 7 boxes wide. One for each day of the week.
        boxWidth = (rect.width - 1) / DAYS_IN_WEEK;

        // The calendar has 8 lines
        // 1 line for the month and the year
        monthYearLineHeight = (rect.height - 1)/8;

        // 1 line for the days of the week
        dayLineHeight = (rect.height - 1)/8;
            
        // and 6 lines for the dates.
        boxHeight = (rect.height - 1) / 8;
    }

    /**
     * Draws the horizontal lines in the calendar
     * @param   Graphics    The graphics context to draw to.
     */
    private void drawHorizontalLines(Graphics g)
    {
        // check to see if the horizontal lines have to be shown at all.
        if(showHorizontalLines)
        {
            // The line separating the month and year from the days of the week.
            g.drawLine(0, monthYearLineHeight, rect.width, monthYearLineHeight);

            // The line separating the days of the week from the calendar dates
            g.drawLine(0, monthYearLineHeight + dayLineHeight, rect.width, monthYearLineHeight + dayLineHeight);

            // The 5 lines separating the 6 rows of dates.
            for(int i=1; i<=5; i++)
                g.drawLine(0, monthYearLineHeight + dayLineHeight + i*boxHeight, 
                            rect.width, monthYearLineHeight + dayLineHeight + i*boxHeight);
        }
    }

    /**
     * Draws the vertical lines
     *
     * @param   Graphics    The graphics context to draw to.
     */
    private void drawVerticalLines(Graphics g)
    {
        // Draw the vertical lines if neccessary
        if(showVerticalLines)
        {
            // Draw a 6 vertical lines separating the 7 columns for the weekdays
            for(int i=1; i<DAYS_IN_WEEK; i++)
                g.drawLine(i*boxWidth, monthYearLineHeight, i*boxWidth, rect.height);
        }
    }


    /**
     * Display the month and the year
     *
     * @param   Graphics    The graphics context to write to
     */
    private void displayMonthYear(Graphics g)
    {
        int stringWidth;          // the width of a displayed string.

        // First write the month and the year.
        String line = new String(monthNames[activeDate.getMonth()] + " " + 
                                new Integer(activeDate.getYear() + 1900).toString());
            // This will hold the displayed line for the month and the year.

        // the width of this line.
        stringWidth = fm.stringWidth(line);

        // Display the centered month and year.
        g.drawString(line, rect.width/2 - stringWidth/2, monthYearLineHeight/2 + 
                                                        charHeight/2);
    }

    /**
     * Display the names of the week days
     *
     * @param   Graphics    The graphics context to write to
     */
    private void displayWeekDays(Graphics g)
    {
        int stringWidth;        // The width of a displayed string
        
        // Display the weekdays.
        for(int i=0; i<7; i++)
        {
            // find the width of the weekday
            stringWidth = fm.stringWidth(weekdayNames[i]);

            // draw the weekday centered
            g.drawString(weekdayNames[i], boxWidth*i + boxWidth/2 - stringWidth/2,
                monthYearLineHeight + dayLineHeight/2 + charHeight/2);
        }

    }

    /**
     * Fill in the dates in the calendar
     *
     * @param   Graphics    The graphics context to write in
     */
    private void displayDates(Graphics g)
    {
        int stringWidth;                  // the width of a displayed line.
        
        int firstWeekDay = new Date(activeDate.getYear(), activeDate.getMonth(),1).getDay();
                    // the weekday corresponding to the first of the month.

        // Display the days. currDate starts as the first date of the month and iterates
        // through each date until it reaches the next month.
        for(Date currDate= new Date(activeDate.getYear(), activeDate.getMonth(),1);
                currDate.getMonth() == activeDate.getMonth();
                    currDate.setDate(currDate.getDate() + 1) )
        {
            String str = new Integer(currDate.getDate()).toString();
                            // The string version of the next displayed number.

            // the width of this number
            stringWidth = fm.stringWidth(str);

            int x;  // The x coordinate of the box in which to display this day
            int y;  // The y coordinate of the same.

            // The x cood is the same as the day of the week for this date.
            x = currDate.getDay();

            // The  cood is the week number for this date.
            y = (currDate.getDate() - 1 + firstWeekDay) / DAYS_IN_WEEK;

            // Now just draw the date centered
            g.drawString(str, x*boxWidth + boxWidth/2 - stringWidth/2,
                monthYearLineHeight + dayLineHeight + boxHeight*y + boxHeight/2 + 
                    charHeight/2);
            
            // Draw a circle around the active date if desired
            if(circleActiveDate)
            {
                // Draw a circle around the current date if its the actual date we are looking for.
                if(currDate.getDate() == activeDate.getDate())
                {
                    // Draw an oval around this date.
                    g.drawOval(x*boxWidth+1, monthYearLineHeight + dayLineHeight + boxHeight*y+1,
                        boxWidth-2, boxHeight-2);
                }
            }
        }
    }

    /**
     * Draw the active date circle. Useful for erasing and redrawing the circle on the active date.
     *
     */
    private void drawActiveDateCircle(Color c)
    {
        // Only if the active date NEEDS to be circled
        if(circleActiveDate)
        {            
            int firstWeekDay = new Date(activeDate.getYear(), activeDate.getMonth(),1).getDay();
                        // The day of the week for the first of the month
            int x;      // The x coordinate of the box corresponding to the active date.
            int y;      // The y coordinate of the same.

            // the x cood is simply the day of the week
            x = activeDate.getDay();

            // the y cood is the week number
            y = (activeDate.getDate() - 1 + firstWeekDay) / DAYS_IN_WEEK;

            // Get the graphics context
            Graphics g = getGraphics();

            // set the color
            g.setColor(c);

            // Now draw the oval around the date highlighted.
            g.drawOval(x*boxWidth+1, monthYearLineHeight + dayLineHeight + boxHeight*y+1, 
                boxWidth-2, boxHeight-2);

        }       

    }

    /**
     * This will set the calendar to the right size given the current
     * properties
     */
    private void adjustSize()
    {
        // Get the preferred size of the calendar
        Dimension d = getPreferredSize();

        // Resize the calendar
        setSize(d.width, d.height);

        // Now find out who my parent is
        Component p = getParent();

        if(p != null)
        {
            // invalidate the current layout
            p.invalidate();

            // now layout the display again
            p.doLayout();
        }

    }

    /**
     * Get the desired size of the calendar
     *
     * @return  Dimension   The optimal size for the calendar
     */
    public Dimension getPreferredSize()
    {
        // Figure out the font metrics
        FontMetrics fm =  getFontMetrics(getFont());

        int width = 0;    // The temporary width
        int max_width = 0;      // the maximum width
        
        
        // Find maximum width of the day of the week line
        for(int i=0; i<DAYS_IN_WEEK; i++)
        {
            // Find out the maximum width of any given day of the week.
            // plus for comfort leave a space between weekday names
            width = Math.max(width,fm.stringWidth(" " + weekdayNames[i]));
        }

        // The max_width has to accomodate all the week of the same size
        max_width = DAYS_IN_WEEK * width;

        // Maximum width of the date lines
        // Each line may have upto 14 digits as fat as an 8.
        width = fm.stringWidth("88888888888888");

        // choose the maximum of these two widths.
        max_width = Math.max(width, max_width);

        // The height is 8 times the height of a character + space for
        // inter-character space (leading).
        return new Dimension(max_width, 8 * (fm.getHeight() + fm.getLeading()));
    }

    /**
     * Get the minimum size of the calendar
     *
     * @return  Dimension   The minimum size for the calendar
     */
    public Dimension getMinimumSize()
    {
        // The fontmetrics
        FontMetrics fm =  getFontMetrics(getFont());

        int width = 0;    // The temporary width
        int max_width = 0;      // the maximum width


        // Find maximum width of the day of the week line
        // since we want minimum possible width we simply add the weekday name widths
        for(int i=0; i<DAYS_IN_WEEK; i++)
            width += fm.stringWidth(weekdayNames[i]);
            

        max_width = Math.max(width, max_width);

        // Maximum width of the date lines
        // allow 14 digits (2 per day of the week
        width = fm.stringWidth("88888888888888");

        // choose max of these two.
        max_width = Math.max(width, max_width);

        // The total height is 8 times the height of a character
        return new Dimension(max_width, 8 * (fm.getHeight() + fm.getLeading()));
    }

            

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // EVENT HOOKS FOR THE CALENDAR
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * Add a calendar listener
     *
     * @param   JCalendarListener    The listener object
     */
    synchronized public void addJCalendarListener(JCalendarListener l)
    {
        /*
         * when the object is serialized the listeners vector is lost so
         * a new one has to be created on deserialization
         */
        if(listeners == null)
            listeners = new Vector();

        listeners.addElement(l);
    }

    /**
     * Remove a calendar listener
     *
     * @param   JCalendarListener    The listener object to remove
     */
    synchronized public void removeJCalendarListener(JCalendarListener l)
    {
        listeners.removeElement(l);
    }

    /**
     * Fires an year changed event whenever the year changes.
     *
     * @param   int, int    The old and the new year.
     */
    synchronized private void fireYearChanged(int oldYear, int newYear)
    {
        if(listeners == null)
            return;

        for(int i=0; i< listeners.size(); i++)
            ((JCalendarListener) listeners.elementAt(i)).yearChanged(oldYear, newYear);
    }

    /**
     * Fires a month changed event whenever the month changes.
     *
     * @param   int, int    The old and the new month.
     */
    synchronized private void fireMonthChanged(int oldMonth, int newMonth)
    {
        if(listeners == null)
            return;
            
        for(int i=0; i< listeners.size(); i++)
            ((JCalendarListener) listeners.elementAt(i)).monthChanged(
                monthNames[oldMonth], monthNames[newMonth]);
    }

    /**
     * Fires a date changed event whenever the date changes.
     *
     * @param   int the old date 
     * @param   int the new date
     */
    synchronized private void fireDateChanged(int oldDate, int newDate)
    {
        if(listeners == null)
            return;

        for(int i=0; i< listeners.size(); i++)
            ((JCalendarListener) listeners.elementAt(i)).dateChanged(oldDate, newDate);
    }


    /**
     * Fires a date, month or year change event appropriately
     *
     * @param   Date    The old value of the date
     * @param   Date    The new date
     */
    synchronized private void fireJCalendarEvent(Date oldDate, Date newDate)
    {
         
        if(oldDate.getYear() != newDate.getYear())
            fireYearChanged(oldDate.getYear(), newDate.getYear());
        
        if(oldDate.getMonth() != newDate.getMonth())
            fireMonthChanged(oldDate.getMonth(), newDate.getMonth());
       
        if(oldDate.getDate() != newDate.getDate())
            fireDateChanged(oldDate.getDate(), newDate.getDate());

    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // HANDLING USER INPUT TO THE CALENDAR
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * If the user clicks on a calendar date and it's not the currently active
     * date then make it the active date
     *
     * @param   MouseEvent  The event corresponding to the key click
     */
    protected void processMouseEvent(MouseEvent e)
    {

        if((e.getID()) == MouseEvent.MOUSE_PRESSED)
mouse_handler:
        {
            int y = e.getY() - dayLineHeight - monthYearLineHeight;
            // The y -cood of the box

            // The user clicked outside the date area and on the month or the weekday
            if(y < 0) 
                break mouse_handler;

            // Find out the y cood of the box
            y /= boxHeight;

            int x = e.getX() / boxWidth;    // The x - cood of the box
            
            // Now figure out the actual date.
            // Note: we need to know the day of the week for the first day of the month to make
            // calculation.
            Date firstDayOfMonth = new Date(activeDate.getYear(), activeDate.getMonth(), 1);
            int date = 1 + y * 7 + x - firstDayOfMonth.getDay();

            // Do nothing if this click was outside the valid dates for this month.
            if(date < getFirstDate() || date > getLastDate())
                break mouse_handler;

            // Now set this date.   
            setDate(date);
        }
        
        // Allow the super class (component) to continue delivery of event
        super.processMouseEvent(e);
    }

    /**
     * Processes keyboard input.
     *
     * Key          Action
     * ---          ------
     * up arrow     previous week
     * down arrow   next week
     * left arrow   previous day
     * right arrow  next day
     * PAGE UP      previous month
     * PAGE DOWN    next month
     *
     * @param   KeyEvent    The key event which occurred.
     */
    protected void processKeyEvent (KeyEvent e)
    {
        if(e.getID() == KeyEvent.KEY_PRESSED )
        {
            switch( e.getKeyCode() )
            {
            case KeyEvent.VK_UP:
                previousWeek();
                break;

            case KeyEvent.VK_LEFT:
                previousDate();
                break;

            case KeyEvent.VK_RIGHT:
                nextDate();
                break;

            case KeyEvent.VK_DOWN:
                nextWeek();
                break;

            case KeyEvent.VK_PAGE_UP:
                previousMonth();
                break;

            case KeyEvent.VK_PAGE_DOWN:
                nextMonth();
                break;
            }
        }

        // Let the super class continue delivery of key events.
        super.processKeyEvent(e);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //                                        
    // Miscellaneous utility functions
    //                                        
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * This funcion clones a date object. This is helpful because the
     * the Date class hasn't defined a clone method.
     *
     * @param   Date    The date to be duplicated
     * @return  Date    A "new" copy of the date object
     */
    public static Date cloneDate(Date date)
    {
        return new Date(date.getYear(), date.getMonth(), date.getDate());
    }
}
