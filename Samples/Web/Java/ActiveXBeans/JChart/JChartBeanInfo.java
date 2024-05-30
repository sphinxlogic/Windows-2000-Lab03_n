///////////////////////////////////////////////////////////////////////////
//
//  JChartBeanInfo.java
//
// This provides the information about the chart beans properties and
// custom property editors.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////

import java.beans.*;
import java.awt.*;

//
//
// JChartBeanInfo
//
//
public class JChartBeanInfo extends SimpleBeanInfo
{
    /**
     * Return the icon for this bean
     * 
     * @param   int     whether 16x16 pixels or 32x32
     * @return  Image   The image icon for the calendar
     */
    public Image getIcon(int iconKind)
    {
        if(iconKind == BeanInfo.ICON_COLOR_16x16)        
            return loadImage("JChartIcon16.gif");
        
        if(iconKind == BeanInfo.ICON_COLOR_32x32)
            return loadImage("JChartIcon32.gif");

        return null;
    }


    /**
     * The Bean descriptor is used for specifying the customizer for the bean
     * @return  BeanDescriptor  The descriptor of the chart bean
     */
    public BeanDescriptor getBeanDescriptor()
    {
        return new BeanDescriptor(JChart.class, JChartCustomizer.class);
    }

}

