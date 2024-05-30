//
//  SampleBean.java
//
//  Copyright (c) 1996-1997, Microsoft Corporation.  All rights reserved.
//

import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import java.util.Date;

interface SampleBeanEventListener extends java.util.EventListener {
    void somethingHappened();
}

public class SampleBean extends Panel {

    public SampleBean()
    {
        enableEvents(AWTEvent.MOUSE_EVENT_MASK);
    }

    public void paint(Graphics g) {
        g.setColor(textColor);
        g.drawString(textToDraw, 20, 20);
    }

    //
    //  Examples of events using standard design patterns.
    //

    transient Vector listeners = new Vector();

    synchronized public void addSampleBeanEventListener(SampleBeanEventListener l) {

        if(listeners == null)
            listeners = new Vector();

        listeners.addElement(l);
    }

    synchronized public void removeSampleBeanEventListener(SampleBeanEventListener l) {        
        listeners.removeElement(l);
    }

    protected void processMouseEvent(MouseEvent e)
    {
        if((e.getID()) == MouseEvent.MOUSE_PRESSED)
fire_event:
        {
            synchronized(this)
            {
                if(listeners == null)
                    break fire_event;

                SampleBeanEventListener snapshot[];
                
                snapshot = new SampleBeanEventListener[listeners.size()];
                listeners.copyInto(snapshot);
            
                for (int i = 0; i < snapshot.length; i++)
                    snapshot[i].somethingHappened();

            }

        }

         super.processMouseEvent(e);
    }

    //
    //  Examples of properties using standard design patterns.
    //

    String textToDraw = "Some text...";

    public String getTextToDraw() {
        return textToDraw;
    }

    public void setTextToDraw(String textToDraw) {
        this.textToDraw = textToDraw;
        repaint();
    }

    Color textColor = Color.black;

    public Color getTextColor() {
        return textColor;
    }

    public void setTextColor(Color textColor) {
        this.textColor = textColor;
        repaint();
    }

    //
    //  Examples of methods using standard design patterns.
    //

    public String returnTheDate() {
        return (new Date()).toString();
    }
}
