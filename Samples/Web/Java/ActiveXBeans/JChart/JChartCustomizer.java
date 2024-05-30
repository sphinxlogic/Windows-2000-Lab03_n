///////////////////////////////////////////////////////////////////////////
//
//  JChartCustomizer.java
//
//  This is the customizer for the JChart class. It provides editors for all the
//  chart properties.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////

import java.beans.*;
import java.awt.*;
import java.awt.event.*;
import com.ms.ui.*;

public class JChartCustomizer extends Panel implements Customizer
{
    private UITabViewer tabViewer;                  // The tab viewer which contains all the property editors
    private JChartTitlesCustomizer titles;           // This view will customize all the titles
    private JChartFormatCustomizer format;           // this view will customize the format of data presentation
    

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // The constructor of this customizer
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    public JChartCustomizer() 
    {   
        setBackground(Color.lightGray);

        // create the tab viewer
        tabViewer = new UITabViewer();

        // I have to host the UI objects before I can add them
        AwtUIHost tabHost = new AwtUIHost(tabViewer);

        setLayout(null);

        // add the tab viewer to the customizer
        add(tabHost);
        setSize(500,400);
        tabHost.setBounds(40,40, 400,200);

        // add the panel containing all the titles
        titles = new JChartTitlesCustomizer();
        tabViewer.add("Titles", titles);

        // add the panel containing the format customizer
        format = new JChartFormatCustomizer();
        tabViewer.add("Format", format );

    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Interface Customizer requires the following methods to be defined
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * Set the bean object which is to be customized
     */
    public void setObject(Object bean)
    {

        // inform the other sub-customizers about this bean
        titles.setObject(bean);
        format.setObject(bean);
    }

    /**
     * Add a listener for changes to the bean
     * @param   PropertyChangeListener  The object which should be informed of a change
     */
    public void addPropertyChangeListener(PropertyChangeListener listener)
    {
        // add this listener to the each of the view which are going to edit the properties
        titles.addPropertyChangeListener(listener);
        format.addPropertyChangeListener(listener);
    }

    /**
     * Remove a listener of bean property changes
     * @param   PropertyChangeListener  The object who no longer wants to listen to changes
     */
    public void removePropertyChangeListener(PropertyChangeListener listener) 
    {
        // remove this listener from each of the views
        titles.removePropertyChangeListener(listener);
        format.removePropertyChangeListener(listener);
    }

}
