//////////////////////////////////////////////////////////////////////////
//
//  AFCBean.java
//
//      This example demonstrates how one can write a 100% pure AFC
//      object and host it inside of an ActiveX container. When used in
//      development tool that has a design mode, when the PropertyViewer
//      for the bean is displayed, it will use a UIComponent for a 
//      customizer.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

import java.awt.*;
import com.ms.ui.*;
import com.ms.ui.event.*;
import com.ms.beans.*;
import java.util.Vector;

public class AFCBean extends AwtUIApplet
{
    AFCBeanImpl inner;                          // The inner UIApplet being hosted.

    public AFCBean()
    {
        super( new AFCBeanImpl());

        inner = (AFCBeanImpl) getUIApplet();
    }

    public void newItem(String str)
    {
        inner.newItem(str);
    }

    public String getSelecteditem()
    {
        return inner.getSelectedItem();
    }

    public void setSelectedItem(int itemNumber)
    {
        inner.setSelectedItem(itemNumber);
    }

    public void showPropertyViewer()
    {
        inner.showPropertyViewer();
    }

    public void addAFCBeanListener(AFCBeanListener l)
    {
        inner.addAFCBeanListener(l);
    }

    public void removeAFCBeanListener(AFCBeanListener l)
    {
        inner.removeAFCBeanListener(l);
    }
}

class AFCBeanImpl extends UIApplet
{
    private UIList              m_list;         // list of text strings
    private UIScrollViewer      m_scroll;       // scroll viewer
    private transient Vector    m_listeners;    // list of objects wanting events
    private transient PropertyViewer pv = null; // The property viewer for this java object

    public AFCBeanImpl()
    {
        m_listeners = new Vector();
        m_list      = new UIList();
        m_scroll    = new UIScrollViewer(m_list);

        m_list.setBackground(Color.white);
        m_scroll.setBackground(Color.lightGray);

        setLayout(new UIBorderLayout());
        add(m_scroll, "center");
    }

    /**
     *  Remove the property viewer when the applet is 
     *  is removed.
     */
    public void removeNotify()
    {
        if (pv != null)
        {
            pv.hide();
            pv = null;
        }

        super.removeNotify();
    }

    /**
     *  sets the color of the list.
     */
    public void setBackground(Color c)
    {
        super.setBackground(c);
        m_list.setBackground(c);
    }
    
    /**
     *  this property will retrieve the current selected item.
     */
    public String getSelectedItem()
    {
        IUIComponent c = m_list.getSelectedItem();
        return c.getName();
    }

    /**
     *  this property will set the selection based on the index.
     */
    public void setSelectedItem(int index)
    {
        m_list.setSelectedIndex(index);
    }

    /**
     *  adds a new item to the list.
     */
    public void newItem(String s)
    {
        m_list.add(s);
    }

    /**
     *  displays the propertyviewer for the object.
     */
    public void showPropertyViewer()
    {
        if( pv == null )
        {
            pv = new PropertyViewer(this);
        }

        pv.show();
    }

    /**
     * Close the property viewer when the applet is destroyed
     */
    public void destroy()
    {
        if( pv != null )
        {
            pv.hide();
        }
    }

    /**
     *  when a item is selected, an action is performed. the LIST_SELECT
     *  event is parsed and an event called itemSelected is fired.
     */
     public boolean handleEvent(Event e)
     {
        if ((e.target instanceof UIList) && (e.id == Event.LIST_SELECT))
        {
            AFCBeanListener listener[];

            synchronized (m_listeners)
            {
                listener = new AFCBeanListener[m_listeners.size()];
                m_listeners.copyInto(listener);
            }

            for (int i=0; i<listener.length; i++)
                listener[i].itemSelected();
        }

        return super.handleEvent(e);
    }

    /**
     *  add event sink.
     */
    public void addAFCBeanListener(AFCBeanListener listener)
    {
        m_listeners.addElement(listener);
    }

    /**
     *  remove event sink.
     */
    public void removeAFCBeanListener(AFCBeanListener listener)
    {
        m_listeners.removeElement(listener);
    }
}
