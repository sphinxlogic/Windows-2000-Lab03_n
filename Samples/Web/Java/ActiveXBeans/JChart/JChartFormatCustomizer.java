// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//  JChartFormatCustomizer.java
//
//  This provides editors for modifying the format of the chart
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

import com.ms.ui.*;
import com.ms.ui.event.*;
import java.beans.*;
import com.ms.fx.*;

public class JChartFormatCustomizer extends UIPanel implements Customizer, IUIItemListener
{
    private JChart bean;                                     // the bean which is to be customized
    private PropertyChangeSupport helper;                   // to listen to property change listeners
    private UIGroup chartType;                              // what type of a chart is it
    private UIRadioButton pieButton;                        // pie chart button
    private UIRadioButton barButton;                        // bar chart radio button
    private UIRadioButton lineButton;                       // a line graph button
    private UIRadioButton columnButton;                     // a column graph
    private UIGroup rowsOrColumns;                          // group data by rows or columns
    private UIRadioButton compareColumns;                   // compare columns in a row
    private UIRadioButton compareRows;                      // compare the rows in a columns

    public JChartFormatCustomizer()
    {
        // setup the property change listener support
        helper = new PropertyChangeSupport(this);

        //set the layout manager
        setLayout( new UIRowLayout(2) );

        // set the back ground
        setBackground(FxColor.lightGray);

        // create a group for the chart type
        chartType = new UIGroup("Chart Type");
        pieButton = new UIRadioButton("Pie chart", UIButton.TOGGLE);
        pieButton.addItemListener(this);
        barButton = new UIRadioButton("Bar chart", UIButton.TOGGLE);
        barButton.addItemListener(this);
        lineButton = new UIRadioButton("Line graph", UIButton.TOGGLE);
        lineButton.addItemListener(this);
        columnButton = new UIRadioButton("Column chart", UIButton.TOGGLE);
        columnButton.addItemListener(this);


        chartType.add(pieButton);
        chartType.add(barButton);
        chartType.add(lineButton);
        chartType.add(columnButton);

        add(chartType);

        // create a group for the rows vs columns
        rowsOrColumns = new UIGroup("Rows or columns");
        compareRows = new UIRadioButton("Compare rows", UIButton.TOGGLE);
        compareRows.addItemListener(this);
        compareColumns = new UIRadioButton("Compare columns", UIButton.TOGGLE);
        compareColumns.addItemListener(this);

        rowsOrColumns.add(compareRows);
        rowsOrColumns.add(compareColumns);

        add(rowsOrColumns);
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Interface Customizer requires the following methods to be defined
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * Set the bean object which is to be customized
     */
    public void setObject(Object beanToCustomize)
    {
        this.bean = (JChart) beanToCustomize;

        switch(bean.getChartType())
        {
        case JChart.BAR_CHART:
            barButton.setChecked(true);
            break;

        case JChart.PIE_CHART:
            pieButton.setChecked(true);
            break;

        case JChart.LINE_GRAPH:
            lineButton.setChecked(true);
            break;

        case JChart.COLUMN_CHART:
            columnButton.setChecked(true);
            break;

        default:
            // do nothing I don't know this chart type
            break;
        }


        if(bean.getCompareColumns() )
        {
            compareColumns.setChecked(true);
        }

        else
        {
            compareRows.setChecked(true);
        }

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
    // Interface IUIActionListener requires the following methods.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    public void itemStateChanged(UIItemEvent evt)
    {
        UIRadioButton source = (UIRadioButton) evt.getSource();

        // if this button is de- selected then do nothing
        if( !source.isChecked() )
        {
            source.setChecked(true);
            return;
        }

        if(source == compareRows)
        {
            compareColumns.setChecked(false);
            bean.setCompareColumns(false);
            helper.firePropertyChange("compareColumns", new Boolean(true), new Boolean(false) );
        }
        else if(source == compareColumns)
        {
            compareRows.setChecked(false);
            bean.setCompareColumns(true);
            helper.firePropertyChange("compareColumns", new Boolean(false), new Boolean(true) );            
        }

        else 
        {
            // the click has to be one of the chart types

            // de-select all
            pieButton.setChecked(false);
            barButton.setChecked(false);
            lineButton.setChecked(false);
            columnButton.setChecked(false);

            // now select the one which was clicked
            source.setChecked(true);

            try
            {
                // now update the bean property
                if( source == pieButton)
                {
                    bean.setChartType(JChart.PIE_CHART);
                }

                else if(source == lineButton)
                {
                    bean.setChartType(JChart.LINE_GRAPH);
                }

                else if(source == barButton)
                {
                    bean.setChartType(JChart.BAR_CHART);
                }

                else if(source == columnButton)
                {
                    bean.setChartType(JChart.COLUMN_CHART);
                }

                else // I don't know how I got this Event
                {
                    System.err.println("Unexpected Adjustment Event received");
                }
            
                helper.firePropertyChange(null, null, null);
            }
            catch( PropertyVetoException e)
            {
                System.err.println("Unexpected Property Veto Exception: "+e.toString() );
                e.printStackTrace();
            }
        }
        
    }
}
