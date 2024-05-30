// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  JChartTitlesCustomizer.java
//
//  This provides editors for modifying the various titles displayed in the
//  chart.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

import com.ms.ui.*;
import com.ms.ui.event.*;
import java.beans.*;
import java.awt.*;

public class JChartTitlesCustomizer extends UIPanel implements Customizer, IUIKeyListener
{
    UIEdit captionEdit;                     // The editor for changing the caption of the chart
    UIEdit titleEdit;                       // The editor for the title
    UIEdit xTitleEdit;                      // The editor for x-axis title
    UIEdit yTitleEdit;                      // The editor for the y-axis title
    JChart bean;                             // the bean we are customizing
    PropertyChangeSupport helper;           // to help fire property change events.

    /**
     * Constructor for the Titles Customizer. It sets up the various
     * controls to be displayed in the customizer and then displays
     * them.
     * @param   JChartCustomizer The customizer which created this guy.
     */
    public JChartTitlesCustomizer()
    {
        // setup the property change listener support
        helper = new PropertyChangeSupport(this);

        setLayout( new UIGridLayout(4,2, 10, 10) );

        add( new UIDrawText("Caption") );
        add( new UIDrawText("Title") );

        captionEdit = new UIEdit("<blank>");
        captionEdit.setMaxBufferSize(20);
        captionEdit.setBackground(Color.white);
        captionEdit.addKeyListener(this);
        add( captionEdit );

        titleEdit = new UIEdit("<blank>");
        titleEdit.setMaxBufferSize(20);
        titleEdit.setBackground(Color.white);
        titleEdit.addKeyListener(this);
        add( titleEdit );

        add( new UIDrawText("X - Axis Title") );
        add( new UIDrawText("Y - Axis Title") );

        xTitleEdit= new UIEdit("<blank>");
        xTitleEdit.setBackground(Color.white);
        xTitleEdit.addKeyListener(this);
        add( xTitleEdit );

        yTitleEdit= new UIEdit("<blank>");
        yTitleEdit.setBackground(Color.white);
        yTitleEdit.addKeyListener(this);
        add( yTitleEdit );
    }

    /**
     * This function is called internally whenever some user input is given
     * to a UI and the new properties have to be calculated  based on this
     * input.
     * @param   Object  The UI object which received input
     */
    private void updateProperties(Object source)
    {
        if(source == titleEdit)
        {
            bean.setChartTitle( titleEdit.getValueText() );
        }

        else if(source == captionEdit)
        {
            bean.setCaption(captionEdit.getValueText() );
        }

        else if(source == xTitleEdit)
        {
            bean.setXAxisTitle(xTitleEdit.getValueText());
        }

        else if(source == yTitleEdit)
        {
            bean.setYAxisTitle(yTitleEdit.getValueText());
        }

        else
        {
            return;
        }

        helper.firePropertyChange(null, null, null);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Interface customizer requires the following procedures to be defined
    //
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * This function passes a reference to the chart bean we are customizing
     * @param   JChart   The chart bean to be customized
     */
    public void setObject(Object beanToCustomize)
    {
        bean = (JChart) beanToCustomize;

        captionEdit.setValueText( bean.getCaption() );
        
        titleEdit.setValueText( bean.getChartTitle() );

        yTitleEdit.setValueText( bean.getYAxisTitle() );

        xTitleEdit.setValueText( bean.getXAxisTitle() );
    }

    /**
     * Add a listener for changes to the bean
     * @param   PropertyChangeListener  The object which should be informed of a change
     */
    public void addPropertyChangeListener(PropertyChangeListener listener)
    {
        helper.addPropertyChangeListener(listener);
    }

    /**
     * Remove a listener of bean property changes
     * @param   PropertyChangeListener  The object who no longer wants to listen to changes
     */
    public void removePropertyChangeListener(PropertyChangeListener listener) 
    {
        helper.removePropertyChangeListener(listener);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Interface UIKeyListener requires the following methods.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    public void keyPressed(UIKeyEvent event)
    {        
        Object source = event.getSource();

        // now fugure out which property has to change
        updateProperties(source);
    }

    public void keyReleased(UIKeyEvent event)
    {
        Object source = event.getSource();

        // now fugure out which property has to change
        updateProperties(source);
    }

    public void keyTyped(UIKeyEvent event) 
    {
        Object source = event.getSource();

        // now fugure out which property has to change
        updateProperties(source);
    }


}

