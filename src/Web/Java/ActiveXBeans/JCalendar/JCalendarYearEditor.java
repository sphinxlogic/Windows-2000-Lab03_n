///////////////////////////////////////////////////////////////////////////
//
//  JCalendarYearEditor.java
//
//  This class is an editor for editing the calendar year. It implements
//  PropertyEditor inerface required of all property editors.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////

import java.beans.*;
import java.awt.*;
import java.awt.event.*;

public class JCalendarYearEditor extends Panel implements PropertyEditor, ActionListener, KeyListener //, IUIAdjustmentListener
{
    private TextField text;                         // The text field for entering the year
    private Integer year = new Integer(1);          // the year which this class is out to modify
    private PropertyChangeSupport helper ;          // Helps to fire property change events.

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // The constructor of this editor
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    public JCalendarYearEditor() 
    {   
        helper = new PropertyChangeSupport(this);

        // I don't need a layout manger
        setLayout(null);

        // now create a text field
        text = new TextField("1",6);

        // now register myself as a listener on this text field
        text.addActionListener(this);
        text.addKeyListener(this);

        // add this text field
        add(text);
        text.setBounds(4,4, 100, 30);

        // now size myself correctly.
        setSize(128, 38);
        
    }

    /**
     * Returns the size of this component
     * @return  Dimension   the size
     */
    public Dimension getPreferredSize()
    {
        return new Dimension(108,72);
    }

    /**
     * Returns the size of this component
     * @return  Dimension   the size
     */
    public Dimension getMinimumSize()
    {
        return new Dimension(108,72);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Event handling
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Interface ActionListener requires the following methods.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    /**
     * Invoked by the text field when the user enters a new value
     * @param   ActionEvent The event object
     */
    public void actionPerformed(ActionEvent event) 
    {
	    Object source = event.getSource();
        if ( source == text)
        {
            try 
            {
                setAsText(text.getText());
            }
            catch(IllegalArgumentException e)
            {
                text.setText(getAsText());
            }
        }       
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Interface KeyListener requires the following methods.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    public void keyPressed(KeyEvent event)
    {        
        Object source = event.getSource();
        if ( source == text)
        {
            try 
            {
                setAsText(text.getText());
            }
            catch(IllegalArgumentException e)
            {
                text.setText(getAsText());
            }
        }
    }

    public void keyReleased(KeyEvent event)
    {
        Object source = event.getSource();
        if ( source == text)
        {
            try 
            {
                setAsText(text.getText());
            }
            catch(IllegalArgumentException e)
            {
                text.setText(getAsText());
            }
        }
    }

    public void keyTyped(KeyEvent event) 
    {
        Object source = event.getSource();
        if ( source == text)
        {
            try 
            {
                setAsText(text.getText());
            }
            catch(IllegalArgumentException e)
            {
                text.setText(getAsText());
            }
        }
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Interface PropertyEditor requires the following functions to be 
    // defined.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * Returns a string representation of the property suitable for
     * inclusion in java code. Note year being an int will be wrapped in an Integer.
     *
     * @return  String  The java representation of the year
     */
    public String getJavaInitializationString()
    {
       return getAsText();
    }


    /**
     * Sets the value of the year
     * @param   Object  The year wrapped in an Integer object.
     */
    public void setValue(Object yearObject)
    {
        // make a copy of the old year
        Integer oldYear = year;

        // now update the year
        year = (Integer) yearObject;

        // update the text box only if its different
        if( ! (text.getText()).equals(getAsText()))
            text.setText(getAsText());

        // now fire the property change event
        helper.firePropertyChange("year", oldYear, year);
    }

    /**
     * Get the value of the year
     * @return  Object  The year wrapped in an Integer object
     */
    public Object getValue()
    {
        return (Object) year;
    }

    /**
     * Tell the calling function that this property has a customized
     * editor.
     *
     * @return  boolean True
     */
    public boolean supportsCustomEditor()
    {
        return true;
    }

    /**
     * Returns the component which is responsible for editing this property
     *
     * @return  Component   The component which actually edits the property.
     */
    public Component getCustomEditor()
    {
        return this;
    }


     
    /**
     * This editor is capable of drawing itself 
     * 
     * @return  boolean true
     */
    public boolean isPaintable()
    {
        return true;
    }

    /**
     * Draws a representation of the year in a rectangle
     *
     * @param   Graphics    The graphics context
     * @param   Rectangle   The rectangle in which to draw itself
     */
    public void paintValue(Graphics gr, Rectangle rect)
    {
        // Get the font metrics to figure out the string widths
        FontMetrics fm = gr.getFontMetrics();

        // Center the year in the middle of the rectangle.
        gr.drawString(getAsText(), rect.x + rect.width/2 - fm.stringWidth(getAsText())/2, 
            rect.y + rect.height/2 + fm.getAscent()/2 );
    }

    /**
     * Return a string representation of the property suitable for display
     *
     * @return  String  The year
     */
    public String getAsText()
    {
        return ((Integer) getValue()).toString();
    }

    /**
     * Set the value of the year given as a string. Throws an Illegal Argument exception
     * if something is wrong with the provided string.
     *
     * @param   String  The month name
     */
    public void setAsText(String yearString) throws IllegalArgumentException
    {
        try
        {
            setValue( new Integer(Integer.parseInt(yearString)) );    
        }
        catch (Exception e)
        {
            throw new IllegalArgumentException(yearString);
        }
    }
 

    /**
     * Returns the possible string values supported with this property
     * @return  String[]    The array of possible string values supported.
     */
    public String[] getTags()
    {
        String s[] = {"10", "20"};
        return s;
           
    }

    /**
     * Add a listener for changes in this property
     * @param   PropertyChangeListener  The object which should be informed of a change
     */
    public void addPropertyChangeListener(PropertyChangeListener listener)
    {
        helper.addPropertyChangeListener(listener);
    }

    /**
     * Remove a listener of property changes
     * @param   PropertyChangeListener  The object who no longer wants to listen to changes
     */
    public void removePropertyChangeListener(PropertyChangeListener listener) 
    {
        helper.removePropertyChangeListener(listener);
    }

}
