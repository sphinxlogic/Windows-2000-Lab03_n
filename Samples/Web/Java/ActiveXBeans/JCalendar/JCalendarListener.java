//////////////////////////////////////////////////////////////////////////
//
//  JCalendarListener.java
//
//      This example is the listener interface for the calendar bean.
//      It defines the events that arbitrary objects will want to sink.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

public interface JCalendarListener extends java.util.EventListener
{
    // fired whenever the year changes.
    public void yearChanged(int oldyear, int newyear);

    //fired whenever the month changes.
    public void monthChanged(String oldmonth, String newmonth);

    //fired wheneve the date changes.
    public void dateChanged(int olddate, int newdate);
}
