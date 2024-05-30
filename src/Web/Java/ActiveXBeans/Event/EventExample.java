//////////////////////////////////////////////////////////////////////////
//
//  EventExample.java
//
//      This example demonstrates how  a JavaBean that supports listeners
//      can be used with Microsoft's Internet Explorer. This object will
//      source an event called DoClick. The HTML page (Example.html) will
//      sink the event and display a message box.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

import java.awt.*;
import java.applet.*;
import java.util.*;

public class EventExample extends Applet
{
    private Vector m_listeners;

    /**
     *  Creates a new EventExample object. It will set the layout and
     *  add a button.
     */
    public EventExample()
    {
        m_listeners = new Vector();
        
        setLayout(new BorderLayout());
        add("Center", new Button("Fire DoClick"));
    }

    /**
     *  Add a listener to the list of objects that are listening
     *  for events.
     */
    public void addEventExampleListener(EventExampleListener listener)
    {
        if(m_listeners == null)
            m_listeners = new Vector();

        m_listeners.addElement(listener);
    }

    /**
     *  Remove the listener for list of objects that are listening
     *  for events.
     */
    public void removeEventExampleListener(EventExampleListener listener)
    {
        m_listeners.removeElement(listener);
    }

    /**
     *  When an action occurs that is an instance of a button,
     *  fire the event.
     */
    public boolean action(Event event, Object obj)
    {
        if (event.target instanceof Button)
        {
            fireEvent();
            return true;
        }

        return false;
    }

    /**
     *  Iterate through the list of listener objects and fire
     *  the DoClick event.
     */
    private void fireEvent()
    {
        EventExampleListener listener[];

        synchronized(m_listeners)
        {
            listener = new EventExampleListener[m_listeners.size()];
            m_listeners.copyInto(listener);
        }

        for (int i=0; i<listener.length; i++)
            listener[i].DoClick();
    }
}
