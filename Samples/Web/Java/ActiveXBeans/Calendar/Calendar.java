//////////////////////////////////////////////////////////////////////////
//
//  Calendar.java
//
//      This example demonstrates the hosting of ActiveX controls within
//      an applet.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

import java.awt.*;                          // standard java
import java.awt.event.*;
import java.applet.*;
import com.ms.ui.*;                         // afc controls
import com.ms.activeX.*;                    // used for our control host
import com.ms.com.*;                        // general com

public class Calendar extends Frame
{
    public static void main(String args[])
    {
        Calendar app = new Calendar();

        app.setSize(640, 480);
        app.setVisible(true);
    }

    Calendar()
    {
        ActiveXControl mscal = new ActiveXControl("{8E27C92B-1264-101C-8A2F-040224009C02}");
	    Button b          = new Button("Kung Foo Fighting");

        addWindowListener(new CalendarWindowListener() );

        this.setTitle("Calendar Example");
        this.setBackground(Color.lightGray);

    	setLayout(new BorderLayout());
        add("Center", mscal);
        add("North", b);
    }

    class CalendarWindowListener extends WindowAdapter
    {
        public void windowClosing(WindowEvent e)
        {
                System.exit(0);
        }
    }
}
