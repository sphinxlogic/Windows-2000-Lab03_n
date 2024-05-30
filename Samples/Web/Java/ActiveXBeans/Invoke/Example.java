//////////////////////////////////////////////////////////////////////////
//
//  Example.java
//
//      This example demonstrates how to instantiate an AcitveX control
//      using the CLSID instead of using JActiveX tool to generate the
//      JavaBean wrappers for the control. Also, this example demonstrates
//      how to call methods, set properties, and get properties.
//
//      This example relies on the MS Calendar ActiveX control that
//      ships with Microsoft Office 97.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

import java.awt.*;
import java.awt.event.*;
import com.ms.activeX.*;
import com.ms.ui.*;
import com.ms.com.*;

public class Example extends Frame
{
    private ActiveXControl cal;

    /**
     *  The main entry point for the Example application. It will
     *  create a new Example object, set the bounds and make the
     *  app visible.
     *
     *  @param  args[]      Command line argument list.
     *
     *  @return             No return value.
     */
    public static void main(String args[])
    {
        Example app = new Example();
        
        app.setBounds(0, 0, 400, 400);
        app.setVisible(true);
    }

    /**
     *  Creates a new Example object. It will add the ActiveX
     *  control, and add buttons to control the application.
     */
    public Example()
    {
        enableEvents(AWTEvent.WINDOW_EVENT_MASK);
        setLayout(new BorderLayout());

        //
        //  create a new panel and add each button to the
        //  panel. the buttons are used to invoke methods,
        //  set properties and get property values
        //
        Panel p = new Panel();
        p.setLayout(new GridLayout(2, 1));
        p.add(new Button("Set the date to the 23rd"));
        p.add(new Button("Get the day"));
        add("West", p);

        //
        //  create the ActiveX control using the CLSID
        //
        cal = new ActiveXControl("{8E27C92B-1264-101C-8A2F-040224009C02}");
        add("Center", cal);        
    }

    /**
     *  This method is used to look for the WINDOW_CLOSING event.
     *  When the event is caught, exit the application.
     *
     *  @param  event   The event for processing.
     *
     *  @return         No return value.
     */
    public void processWindowEvent(WindowEvent event)
    {
        if (event.getID() == WindowEvent.WINDOW_CLOSING)
            System.exit(0);

        super.processWindowEvent(event);        
    }

    /**
     *  This method is called when a button is pressed.
     *
     *  @param  event   The event object.
     *  @param  obj     The object.
     *
     *  @return         True is we processed the event,
     *                  otherwise, false.
     */
    public boolean action(Event event, Object obj)
    {
        if (event.target instanceof Button)
        {
            Button b = (Button)event.target;

            //
            //  call setProperty to set the Day property
            //  on the ActiveX control.
            //
            if (b.getLabel() == "Set the date to the 23rd")
            {
                short date = 23;
                cal.setProperty("Day", date);
            }
            //
            //  this will ask the control for the value of the
            //  day property. the value of this property is the
            //  currently selected day.
            //
            else if (b.getLabel() == "Get the day")
            {
                Variant month = cal.getProperty("Day");
                String day = "You have selected " + month.getShort();

                // 
                //  display the day in an AFC message box.
                //
                UIMessageBox mbox = new UIMessageBox(new UIFrame(), "The Day Property", day, UIMessageBox.STOP, UIButtonBar.OK);
                mbox.doModal();
            }
        }

        return false;
    }
}
