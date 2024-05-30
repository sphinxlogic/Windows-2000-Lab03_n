///////////////////////////////////////////////////////////////////////////
//
//  JChart.java
//
// This bean presents data to the user using a chart interface.
// It uses AFC (UI classes) internally to present data to the user.  
// It utilizes serialization to save and load chart information. 
// A special custom BeanInfo is provided to expose a set of properties, methods, and events. 
// Also, this bean uses a bean-customizer that uses the UITabViewer object
// This bean will be placed on a VB form. VB code will drive the bean to switch between chart types. 
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////

import java.awt.*;
import java.io.*;
import java.beans.*;
import java.util.*;


public class JChart extends Canvas implements Serializable
{
    // The chart properties
    private int chartType = BAR_CHART;              // the type of the chart being displayed
    private boolean showLegend = true;              // Should the legend be shown.
    private boolean compareColumns = true;          // Arrange the bars for the columns in a row together.
    private String chartTitle = "";                 // The title of the chart
    private String xAxisTitle = "";                 // The title of the x-axis
    private String yAxisTitle = "";                 // The title of the y-axis
    private String caption = "";                    // The caption of the chart ( a comment below the chart)
    private double [][] data;                       // The array of data values
    private int column;                             // The current column number for editing data.
    private int row;                                // The current row number for entering data.
    private int columnCount;                        // The number of columns
    private int rowCount;                           // The number of rows.
    private String[] columnLabel;                   // The array of column names
    private String[] rowLabel;                      // The array of row names.
    private Color[] chartColors = {Color.red, Color.green, Color.yellow, Color.cyan, Color.pink,
        Color.blue, Color.magenta, Color.orange};   // The colors to display for the chart
    private int rowGap = 0;                         // The gap between two rows
    private int columnGap = 0;                      // The gap between two columns
    private File dataFile = null;                   // The file which contains the Excel data

    // constant declaration

    // These are the possible values of the chart type
    public static final int BAR_CHART = 1;          // A regular bar chart
    public static final int COLUMN_CHART = 2;       // horizontal bars
    public static final int PIE_CHART = 3;          // A pie chart
    public static final int LINE_GRAPH = 4;         // A line graph

    // miscellaneous constants for drawing the charts
    private static final int NOTCH_WIDTH = 5;        // The width of the notches made on the Y-axis
    private static final int NOTCH_HEIGHT = 5;       // The height of the notches made on the X-axis
    private static final int CIRCLE_RADIUS = 3;      // The radius of the circle drawn around each point
    private static final int BAR_WIDTH = 10;         // the preferred widht of a bar
    private static final int BAR_HEIGHT = 200;       // the preferred maximum height of a bar
    private static final int COLUMN_HEIGHT = 10;     // the preferred height of a column
    private static final int COLUMN_WIDTH = 200;     // the preferred maximum width of a column
    private static final int PIE_CHART_RADIUS = 200; // the preferred radius of the pie chart    


    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Constructors for JChart and Main method for testing.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    /**
     * Null constructor for the chart.
     */
    public JChart()
    {
        super();

        // set the font
        setFont(new Font("Dialog", Font.PLAIN, 12) );
    }

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Reconstruct the class from an external storage
    // These functions writeObject and readObject are required because this
    // class needs special handling on de-serialization/serialization. 
    // The data file has to be written out to disk on serialization and read
    // from disk on de-serialization
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /**
     * Write the properties of the chart to an external object.
     *
     * @param   ObjectOutput    The object to write the calendar properties to
     */
	private void writeObject(ObjectOutputStream stream) throws IOException
	{
		stream.defaultWriteObject();
	}
	
    /**
     * read the properties of the chart from an external object.
     * If the dataFileName property is "good" then read in the values from
     * disk. Else set the dataFileName as "".
     *
     * @param   ObjectInput     The object to read the properties from
     */
	private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException
	{
		stream.defaultReadObject();

        File oldFile = dataFile;
        dataFile = null;

        if( oldFile != null)
        {
            try
            {
                setDataFileName(oldFile.getAbsolutePath() );
            }
            catch(Exception ex)
            {
                dataFile = null;
            }
        }
	}

    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Methods for drawing the chart based on its properties.
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    /**
     * Resizes the component if so desired. Called from within the bean if its felt
     * that a bigger size may be required. As a result of adding some columns for instance.
     */
    private void adjustSize()
    {
        // the current dimensions
        Dimension current = getSize();
        
        // the desired dimensions
        Dimension desired = getPreferredSize();

        // don't do anything if we have more size than we asked for
        if((desired.width <= current.width) && (desired.height <= current.height) )
        {
		}

		else
		{
			// first resize the bean
			setSize(desired.width, desired.height);
		}

        //now invalidate the parents layout and layout again.
        Component p = getParent();
        if(p != null)
        {
            p.invalidate();
            p.doLayout();
        }

		repaint();
    }

    /**
     * The preferred size of the chart bean
     * @return  Dimension   the preferred size
     */
    public Dimension getPreferredSize()
    {
        // the font metrics of this component
        FontMetrics fm = getFontMetrics(getFont());

        // the preferred width of the rectangle
        int width = 0;

        // the preferred height of the rectangle
        int height = 0;

        // add 4 lines for the title and caption
        height +=4*fm.getHeight();

        // add the width of the title and the caption
        width = Math.max(fm.stringWidth(caption), fm.stringWidth(chartTitle) );

        // the width of the graph
        int graph_width = 0;

        // the height of the graph
        int graph_height = 0;

        switch(chartType)
        {
        case LINE_GRAPH:
        case BAR_CHART:
            // the width from writing the title
            graph_width += fm.stringWidth(yAxisTitle) + NOTCH_WIDTH + 4 + 
                fm.stringWidth( new Double(getMax()).toString() );

            // the height of drawing the title
            graph_height += fm.getHeight() + NOTCH_HEIGHT + 4;

            // width of the graph bars
            if(compareColumns)
            {
                graph_width += rowCount* (columnCount*(BAR_WIDTH+columnGap) + rowGap);
            }
            else
            {
                graph_width += columnCount *(rowCount*(BAR_WIDTH+rowGap) + columnGap);
            }

            // height of the graph bars
            graph_height += BAR_HEIGHT;
            break;

        case COLUMN_CHART:
            // the width from writing the title
            graph_width = fm.stringWidth(yAxisTitle) + NOTCH_WIDTH + 4 +
                fm.stringWidth( new Double(getMax()).toString() );

            // the height of drawing the title
            graph_height = fm.getHeight() + NOTCH_HEIGHT + 4;

            // the height of the graph columns
            if(compareColumns)
            {
                graph_height += rowCount* (columnCount*(COLUMN_HEIGHT+columnGap) + rowGap);
            }
            else
            {
                graph_height += columnCount *(rowCount*(COLUMN_HEIGHT+rowGap) + columnGap);
            }

            // width of the graph columns
            graph_width += COLUMN_WIDTH;
            break;
        
        case PIE_CHART:
            // the height from writing the pie-chart label
            graph_height = fm.getHeight();

            // the width of the chart
            graph_width += PIE_CHART_RADIUS;

            // the height of the pie chart
            graph_height += PIE_CHART_RADIUS;
            break;
        }

        height += graph_height;

        width = Math.max(width, graph_width);

        // throw in an additional third of the width for the legend.
        if(showLegend)
        {
            width += width/3;
        }

        // the width should be atleast 200
        width = Math.max(200, width);

        return new Dimension(width, height);
    }

    /**
     * The minimum size of the chart bean
     * @return  Dimension   the minimum size
     */
    public Dimension getMinimumSize()
    {
        return new Dimension(200,200);
    }

    /**
     * The paint method draws the chart depending on its type. and displays other
     * useful information specified by the user like captions, titles and a legend.
     * @param   Graphics    The graphics context for draeing this image.
     */
    public void paint(Graphics g)
    {
        //set the color as black
        g.setColor(Color.black);

        // no point doing anything if the data hasn't been entered yet.
        if(columnCount == 0 || rowCount == 0)
        {
            g.drawString("Enter some data", 20,20);
            return;
        }

        // if a pie-chart has to be drawn then the x and the y-axis don't have to be drawn
        // but we still need to draw the legend, title and the caption.
        int x = 0;                          // The x cood of the leftmost point
        int y = 0;                          // The y cood of the topmost point.
        int width = getSize().width;           // The width of my drawable area
        int height = getSize().height;         // The height of my drawable area
        FontMetrics fm = g.getFontMetrics();// The font metrics of  my drawable area.
    
        // Draw the title centered at the top of the canvas
        drawCenteredText(g, x,y, width, fm.getHeight(), chartTitle);

        // Draw the caption at the bottom.
        drawCenteredText(g, x, y + height - fm.getHeight(), width, fm.getHeight(), caption);

        // we want one blank line below the title and and one blank line above the caption
        // the remaining drawing area has shrunk vertically so update y  and height
        height -= 4*fm.getHeight();
        y += 2*fm.getHeight();

        // clip out the remaining drawing area
        g.setClip(x, y, width,height);

        // Draw the legend if so desired.
        if(showLegend)
        {
            drawLegend(g);
        }

        // draw the appropriate chart
        switch(chartType)
        {
        case PIE_CHART:
            drawPieChart(g);
            break;

        case BAR_CHART:
            drawBarChart(g);
            break;

        case LINE_GRAPH:
            drawLineGraph(g);
            break;

        case COLUMN_CHART:
            drawColumnChart(g);
            break;

        default:
            g.drawString("Invalid chart type",20,20);
            break;
        }

 
    }

    /**
     * Draw a text message centered in the middle of the specified area
     * @param   Graphics    The graphics context to draw in
     * @param   int         The top left x cood
     * @param   int         The top left y cood
     * @param   int         The width of the rectangle.
     * @param   int         The height of the rectangle. (should be greater than the height of a character)
     * @param   String      The string to be drawn
     */
    private void drawCenteredText(Graphics g, int x, int y, int width, int height, String str)
    {
        int strWidth = (g.getFontMetrics()).stringWidth(str); // the width of the string
        int strDescent = (g.getFontMetrics()).getDescent();     // The amount which the string can descend
        int strHeight = (g.getFontMetrics()).getHeight();       // the height of a character

        g.drawString(str, x+width/2 - strWidth/2, y + height/2 + strHeight/2 - strDescent);
    }

    /**
     * Draw a legend in the provided graphics context.
     * <p>
     * The legend will be drawn in the right corner of the area. Using as much space is
     * needed to write the labels but no more than a quarter of the width.
     * @param   Graphics    The graphics context to draw in
     */
    private void drawLegend(Graphics g)
    {
        // the available drawing area
        Rectangle rect = g.getClipBounds();

        // get the current color
        Color oldColor = g.getColor();

        // the fontmetrics of this graphics object for calculating string widths and height.
        FontMetrics fm = g.getFontMetrics();

        int labelCount = compareColumns ? columnCount: rowCount;    // the number of labels to display
        String[] labelNames = compareColumns ? columnLabel : rowLabel;    // The names on the legend

        // the desired height of this rectangle.
        int height = fm.getHeight()*labelCount;

        // the size of the boxes painted in the legend
        int boxSize = fm.getAscent();

        // the padding between the boxes and the  text describing them
        int pad = 2 + fm.getLeading();

        // the desired width of this rectangle
        int width = 0;

        // first find the widest string
        for(int i=0; i<labelCount; i++)
        {
            width = Math.max(width, fm.stringWidth(labelNames[i]) );
        }

        // now add the width of the boxes and padding.
        width = pad + boxSize + pad +width + pad;

        // we must occupy no more than a quarter of the total width.
        width = Math.min(width, rect.width/4 );

        // the height ofcourse can't exceed the given height
        height = Math.min(height, rect.height);

        for(int i=0; i<labelCount; i++)
        {
            // draw the box of the appropriate color
            g.setColor(chartColors[i % chartColors.length]);
            g.fillRect( rect.x+rect.width-width+pad, rect.y + pad + i*fm.getHeight(), boxSize, boxSize);

            // Write the label corresponding to this color
            g.drawString(labelNames[i], rect.x+rect.width-width +pad+boxSize+pad,
                rect.y+pad+boxSize+i*fm.getHeight());
        }

        // draw a white rectangle around the legend
        g.setColor(Color.white);
        g.draw3DRect(rect.x+rect.width-width, rect.y, width-1, height-1, true);

        // now clip off this region so that noone else overwrites the legend
        g.setClip(rect.x, rect.y, rect.width-width-pad, rect.height);

        // and restore the color
        g.setColor(oldColor);
    }
    
    /**
     * Draws a pie chart for the current column or row.
     * @param   Graphics    The context for drawing the chart
     */
    public void drawPieChart(Graphics g)
    {
        Rectangle rect = g.getClipBounds();     // The available drawing area.

        String label;                           // The label of the row or column to
                                                // which the displayed data belongs.
        double[] dataArray;                      // The array of data :-)

        double total = 0;                        // the total of all the data.

        if(compareColumns)
        {
            // The "0" row doesn't have any value 
            if(row == 0)
                return;

            label = rowLabel[row-1];

            dataArray = data[row-1];
        }

        else    // compare rows
        {
            // The "0" column has no data
            if(column == 0)
                return;

            label = columnLabel[column-1];

            dataArray = new double[rowCount];
            
            for(int i=0; i<rowCount; i++)
            {
                dataArray[i] = data[i][column-1];
            }
        }

        // determine the height of a line
        int charHeight = (g.getFontMetrics()).getHeight();

        // write the label of this chart at the bottom of the drawing area.
        drawCenteredText(g,rect.x, rect.y + rect.height - charHeight, rect.width, charHeight, label);

        // the remaining drawing area shrinks in size
        rect.height -= charHeight;

        // calculate the total of the values
        for(int i=0; i<dataArray.length; i++)
        {
            total += dataArray[i];
        }

        // find the center of the piechart
        int centerX = rect.x + rect.width/2;
        int centerY = rect.y + rect.height/2;

        // we want the pie-chart to be a perfect circle
        int radius = Math.min(rect.width/2, rect.height/2);

        // the angle at which the next arc starts
        int startAngle = 0;

        // now draw a filled arc for each of the data items.
        for(int i=0; i<dataArray.length; i++)
        {   
            // calculate the arc angle for this data
            double arcAngle = 360.0 * dataArray[i] / total;

            // we round the arc angle to the nearest integer.
            int roundedArcAngle = (int)Math.rint(arcAngle);

            // set the color
            g.setColor(chartColors[i % chartColors.length]);

            // fill the arc
            g.fillArc(centerX-radius, centerY -radius, 2*radius, 2*radius, startAngle, roundedArcAngle);


            // now increment the starting angle for the next arc.
            startAngle += roundedArcAngle;
        }

    }


    /**
     * This method draws a bar chart
     * @param   Graphics    The graphics context to draw the chart
     */
    private void drawBarChart(Graphics g)
    {
        //draw the y axis title
        drawYAxisTitle(g);

        // draw the x-axis title
        drawXAxisTitle(g);

        // now draw the axis
        drawAxis(g);

        // get the bounds
        Rectangle rect = g.getClipBounds();

        // the number of rows or columns of data.
        int groupCount = compareColumns ? rowCount : columnCount;

        // the number of items within a group of data
        int groupSize = compareColumns ? columnCount : rowCount;

        // the width taken up by a group of data
        int groupWidth = rect.width / groupCount;

        // get the gaps within and between groups
        int interGroupGap = compareColumns ? getRowGap() : getColumnGap();
        int intraGroupGap = compareColumns ? getColumnGap() : getRowGap();

        // the width of each bar of datum
        int barWidth = (groupWidth - interGroupGap - groupSize*intraGroupGap) / groupSize;

        // get the maximum displayed value.
        double max = getMax();

        // now draw the groups of data one by one.
        for(int i=0; i<groupCount; i++)
        {
            //within each group a number of bars have to be drawn
            for(int j=0; j<groupSize; j++)
            {
                // this data value.
                double value;

                if(compareColumns)
                    value = data[i][j];
                else
                    value = data[j][i];

                // the height of this bar of datum
                int barHeight =(int) Math.rint( (rect.height * value ) / max);

                //now change the color to the appropriate one for this bar
                g.setColor(chartColors[ j % chartColors.length ]);

                //now draw this bar leaving appropriate widths between and within groups.
                g.fillRect(rect.x + i*groupWidth + j*(barWidth+intraGroupGap), rect.y+rect.height-barHeight,
                    barWidth, barHeight);
            }
        }
        
    }

    /**
     * This function will draw a line chart of the supplied data
     * @param Graphics  The graphics context for drawing the chart
     */
    private void drawLineGraph(Graphics g)
    {
        // write the name of the Y Axis
        drawYAxisTitle(g);

        // write the name of the X Axis
        drawXAxisTitle(g);

        // draw the axes.
        drawAxis(g);

        //the bounds this chart has to be drawn in
        Rectangle rect = g.getClipBounds();

        // the maximum data value
        double max = getMax();

        // the number of rows or columns of data.
        int groupCount = compareColumns ? rowCount : columnCount;

        // the number of items within a group of data
        int groupSize = compareColumns ? columnCount : rowCount;

        // the width taken up by a group of data
        int groupWidth = rect.width / groupCount;

        // for each item within a group a line has to be drawn across all the groups
        for(int j=0; j<groupSize; j++)
        {
            //set the color for this line
            g.setColor(chartColors[j% chartColors.length]);

            // a -ve value suggests that there was no point before this
            int last_height = -1;

            // draw a line for this data across each group
            for(int i=0; i<groupCount; i++)
            {
                // the data value
                double value = compareColumns ? data[i][j] : data[j][i];

                // the height of this data value.
                int height = (int) Math.rint( (rect.height * value) / max );

                // draw a circle around this value.
                g.drawOval(rect.x + i*groupWidth + (groupWidth/2) - CIRCLE_RADIUS, 
                    rect.y + rect.height - height - CIRCLE_RADIUS, 2*CIRCLE_RADIUS, 2 * CIRCLE_RADIUS);

                // if there was a data value before this then draw a line
                if(last_height >= 0)
                    g.drawLine(rect.x + i*groupWidth - (groupWidth/2), rect.y + rect.height - last_height, 
                        rect.x + i*groupWidth + (groupWidth/2), rect.y + rect.height - height);
                
                //update the last height for the next iteration.
                last_height = height;
            }
        }
    }

    /**
     * This function draws a column chart i.e. horizontal columns for each data value.
     * @param   Graphics    The graphics context for drawing this.
     */
    private void drawColumnChart(Graphics g)
    {
        // write the name of the Y Axis
        drawYAxisTitle(g);

        // write the name of the X Axis
        drawXAxisTitle(g);

        // draw the axis for the column graph
        drawInvertedAxis(g);

        // get the bounds
        Rectangle rect = g.getClipBounds();

        // the number of rows or columns of data.
        int groupCount = compareColumns ? rowCount : columnCount;

        // the number of items within a group of data
        int groupSize = compareColumns ? columnCount : rowCount;

        // the height taken up by a group of data
        int groupHeight = rect.height / groupCount;

        // get the gaps within and between groups
        int interGroupGap = compareColumns ? getRowGap() : getColumnGap();
        int intraGroupGap = compareColumns ? getColumnGap() : getRowGap();

        // the height of each column of datum
        int columnHeight = (groupHeight - interGroupGap - groupSize*intraGroupGap) / groupSize;

        // get the maximum displayed value.
        double max = getMax();

        // now draw the groups of data one by one.
        for(int i=0; i<groupCount; i++)
        {
            //within each group a number of columns have to be drawn
            for(int j=0; j<groupSize; j++)
            {
                // this data value.
                double value;

                if(compareColumns)
                    value = data[i][j];
                else
                    value = data[j][i];

                // the width of this column of datum
                int columnWidth =(int) Math.rint( (rect.width * value ) / max);

                //now change the color to the appropriate one for this bar
                g.setColor(chartColors[ j % chartColors.length ]);

                //now draw this bar leaving appropriate widths between and within groups.
                g.fillRect(rect.x, rect.y + i*groupHeight + j*(columnHeight+intraGroupGap),
                    columnWidth, columnHeight);                   
            }
        }


    }

    /**
     * This function draws the X-Axis title and
     * clips the remaining drawing area.
     * @param   Graphics    the graphics context of the calling chart
     */
    private void drawXAxisTitle(Graphics g)
    {
        Rectangle rect = g.getClipBounds();
    
        // the height of a text string
        int charHeight = (g.getFontMetrics()).getHeight();

        // Now write the text
        drawCenteredText(g, rect.x, rect.y + rect.height - charHeight, rect.width, charHeight, xAxisTitle);

        //now update the region which I can write to
        // give an extra 2 pixels of padding
        rect.height -= (2 + charHeight);

        //now clip off this region
        g.setClip(rect.x, rect.y, rect.width, rect.height);
    }

    /**
     * This function draws the Y-Axis title and
     * clips the remaining drawing area.
     * @param   Graphics    the graphics context of the calling chart
     */
    private void drawYAxisTitle(Graphics g)
    {
        Rectangle rect = g.getClipBounds();
    
        // the widht of the axis title
        int stringWidth = (g.getFontMetrics()).stringWidth(yAxisTitle);

        // write the text
        drawCenteredText(g, rect.x, rect.y, stringWidth, rect.height, yAxisTitle);

        //now update the region which I can write to
        // give an extra 2 pixels of padding
        rect.x += 2 + stringWidth;
        rect.width -= (2 + stringWidth);

        //now clip off the available region
        g.setClip(rect.x, rect.y, rect.width, rect.height);
    }

    /**
     * This routine draws the axis. The x-axis corresponds to the labels on the rows or columns
     * and the y-axis corresponds to the actual values.
     * <p>
     * This routine also marks the notches on the x-axis and puts numbers and labels.
     * @param   Graphics    The graphics context in which to draw the axis
     */
    private void drawAxis(Graphics g)
    {
        // Get the area I can draw in.
        Rectangle rect = g.getClipBounds();

        // get the font metrics
        FontMetrics fm = g.getFontMetrics();

        // Get the maximum value to display
        double max = getMax();

        // The extra padding to be given around the numbers
        int pad = 2;

        // the width occupied on the y-axis
        int width = pad + fm.stringWidth(new Double(max).toString()) + pad + NOTCH_WIDTH;

        // the height occupied on the x axis
        int height = pad + fm.getHeight();

        // now draw the lines (at last :-)

        // the y-axis
        g.drawLine(rect.x+width-1, rect.y, rect.x+width-1, rect.y + rect.height - height);
        
        // the x-axis
        g.drawLine(rect.x+width-1, rect.y + rect.height - height, rect.x+rect.width-1, rect.y + rect.height - height);


        // mark the notch on the y-axis.
        g.drawLine(rect.x+width-1, rect.y, rect.x+width-NOTCH_WIDTH, rect.y);

        //mark the max number on the y-axis
        drawCenteredText(g, rect.x, rect.y, width-NOTCH_WIDTH, fm.getHeight(), new Double(max).toString());

        // the number of groups of rows or columns (depending on compareColumns or compareRows)
        int groupCount = compareColumns ? rowCount : columnCount;

        // the width of a group of rows or columns.
        // i.e. the spacing between two notches on the x-axis
        int groupWidth = (rect.width - width)/ groupCount;

        // mark the notches on the x-axis and draw the labels as well while you are at it.
        for(int i=0; i<groupCount; i++)
        {
            // draw the notch
            g.drawLine(rect.x+width+ (i+1)*groupWidth-1, rect.y+rect.height-height, 
                       rect.x+width+ (i+1)*groupWidth-1, rect.y+rect.height-height + NOTCH_HEIGHT);

            // write the column or row name.
            drawCenteredText(g, rect.x+width + i*groupWidth, rect.y+rect.height - height,
                groupWidth, height, compareColumns ? rowLabel[i] : columnLabel[i]);
        }


        // now before quitting update the clipping rectangle so nobody else overwrites on this stuff
        g.setClip(rect.x+width, rect.y, rect.width-width, rect.height - height);


    }

    /**
     * This routine draws the inverted axis. The y-axis corresponds to the labels on the rows or columns
     * and the x-axis corresponds to the actual values.
     * <p>
     * This routine also marks the notches on the y-axis and puts numbers and labels.
     * @param   Graphics    The graphics context in which to draw the axis
     */
    private void drawInvertedAxis(Graphics g)
    {
        // Get the area I can draw in.
        Rectangle rect = g.getClipBounds();

        // get the font metrics
        FontMetrics fm = g.getFontMetrics();

        // The extra padding to be given around the numbers
        int pad = 2;

        // The height occupied on the x-axis
        int height = NOTCH_HEIGHT + pad + fm.getHeight() + pad;

        // the number of groups of rows or columns (depending on compareColumns or compareRows)
        int groupCount = compareColumns ? rowCount : columnCount;

        // the arrays of labels
        String[] labels = compareColumns ? rowLabel : columnLabel;

        // the height of a group of rows or columns.
        // i.e. the spacing between two notches on the y-axis
        int groupHeight = (rect.height - height)/ groupCount;

        // the maximum width of a label
        int maxLabelWidth = 0;

        // find the maximum label width by going over all labels
        for(int i=0; i<labels.length; i++)
        {
            maxLabelWidth = Math.max( maxLabelWidth, fm.stringWidth(labels[i]) );
        }

        // the width occupied on the y-axis
        int width = pad + maxLabelWidth + pad + NOTCH_WIDTH;

        // now draw the lines (at last :-)

        // the y-axis
        g.drawLine(rect.x+width-1, rect.y, rect.x+width-1, rect.y + rect.height - height);
        
        // the x-axis
        g.drawLine(rect.x+width-1, rect.y + rect.height - height, rect.x+rect.width-1, rect.y + rect.height - height);


        // mark the notch on the x-axis.
        g.drawLine(rect.x+rect.width-1, rect.y+rect.height-height, rect.x+rect.width-1, 
            rect.y+rect.height-height+NOTCH_HEIGHT);

        // the maximum datavalue in the form of a string
        String max = new Double(getMax()).toString();

        //mark the max number on the x-axis
        g.drawString(max, rect.x + rect.width - fm.stringWidth(max), rect.y + rect.height - pad);
        
        // mark the notches on the y-axis and draw the labels as well while you are at it.
        for(int i=0; i<groupCount; i++)
        {
            // draw the notch
            g.drawLine(rect.x+width-1, rect.y+i*groupHeight, rect.x+width-NOTCH_WIDTH, rect.y+i*groupHeight);

            // write the column or row name.
            drawCenteredText(g, rect.x, rect.y+i*groupHeight, width, groupHeight, labels[i]);
        }


        // now before quitting update the clipping rectangle so nobody else overwrites on this stuff
        g.setClip(rect.x+width, rect.y, rect.width-width, rect.height - height);

    }

    
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Event handlers
    //
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Accessor methods for the properties.
    //
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    //
    // chartType
    //
    /**
     * Get the type of the chart to be displayed.
     * @return  int The chart type
     */
    public int getChartType()
    {
        return chartType;
    }

    /**
     * Set the type of the chart to be displayed/
     * @param   int The chart type
     */
    public void setChartType(int chartType) throws PropertyVetoException
    {
        switch(chartType)
        {
        case BAR_CHART:
        case PIE_CHART:
        case LINE_GRAPH:
        case COLUMN_CHART:
            this.chartType = chartType;
            break;

        default:
            throw new PropertyVetoException("Unknown chart type",
                new PropertyChangeEvent(this, "chartType", new Integer(this.chartType), new Integer(chartType)));
            
        }

        // we need to resize
        adjustSize();
    }

    //
    // showLegend
    //

    /**
     * Get whether the legend is to be shown or not.
     * @return  boolean to show the legend or not.
     */
    public boolean getShowLegend()
    {
        return showLegend;
    }

    /**
     * Set whether or not the legend explaining the correspondence between chart colors and
     * columns/rows should be shown.
     * @param   boolean show the legend
     */
    public void setShowLegend(boolean showLegend)
    {
        this.showLegend = showLegend;

        // we need to resize
        adjustSize();
    }

    //
    // compareColumns
    //
    
    /**
     * Get whether the chart is comparing columns or rows
     * @return  boolean compares columns or rows.
     */
    public boolean getCompareColumns()
    {
        return compareColumns;
    }

    /**
     * Set whether the chart is comparing columns or rows
     * @param  boolean compares columns (true) or rows (false)
     */
    public void setCompareColumns(boolean compareColumns)
    {
        this.compareColumns = compareColumns;

        // we need to resize
        adjustSize();
    }

    //
    // chartTitle
    //

    /**
     * Gets the chart title
     * @return  String  The title of the chart
     */
    public String getChartTitle()
    {
        return chartTitle;
    }
    
    /**
     * Sets the chart title
     * @param   String  The title of the chart
     */
    public void setChartTitle(String title)
    {
        chartTitle = new String(title);

        // we need to resize
        adjustSize();
    }

    //
    // xAxisTitle
    //

    /**
     * Sets the x-axis title
     * @param   String  The x-axis label on the chart
     */
    public void setXAxisTitle(String title)
    {
        xAxisTitle = title;

        repaint();
    }


    /**
     * Gets the X-Axis title
     * @return  String  The x-axis of the chart
     */
    public String getXAxisTitle()
    {
        return xAxisTitle;
    }

    //
    // yAxisTitle
    //

    /**
     * Sets the Y-axis title
     * @param   String  The y-axis label on the chart
     */
    public void setYAxisTitle(String title)
    {
        yAxisTitle = new String(title);

        // we need to resize the chart
        adjustSize();
    }


    /**
     * Gets the Y-Axis title
     * @return  String  The y-axis of the chart
     */
    public String getYAxisTitle()
    {
        return yAxisTitle;
    }

    //
    // caption
    //

    /**
     * Gets the caption of the chart
     * @return   String  The caption of the chart
     */
    public String getCaption()
    {
        return caption;
    }

    /**
     * Sets the caption of the chart
     * @param   String  The caption of the chart
     */
    public void setCaption(String cap)
    {
        caption = new String(cap);

        // resize the chart
        adjustSize();
    }

    //
    // column
    //

    /**
     * Get the current column number being edited
     * @return  int the column number
     */
    public int getColumn()
    {
        return column;
    }

    /**
     * Set the current column number being edited
     * @param   int the new column number
     */
    public void setColumn(int new_col) throws PropertyVetoException
    {
        if(new_col > columnCount || new_col < 0)
            throw new PropertyVetoException("Column number out of range !",
                new PropertyChangeEvent(this, "column", new Integer(column), new Integer(new_col)));

        column = new_col;
    }

    //
    // row
    //

    /**
     * Get the current row number being edited
     * @return  int the row number
     */
    public int getRow()
    {
        return row;
    }

    /**
     * Set the current row number being edited
     * @param   int the new row number
     */
    public void setRow(int newRow) throws PropertyVetoException
    {
        if(newRow > rowCount || newRow < 0)
            throw new PropertyVetoException("Row number out of range !",
                new PropertyChangeEvent(this, "row", new Integer(row), new Integer(newRow)));

        row = newRow;
    }


    //
    // columnCount
    //

    /**
     * Get the number of columns
     * @return  int     The number of columns
     */
    public int getColumnCount()
    {
        return columnCount;
    }

    /**
     * Set the column count
     * @param   int the new number of columns
     */
    public void setColumnCount(int newCount) throws PropertyVetoException
    {
        // The number of columns has to be non-negative. It may be zero.
        if(newCount < 0)
            throw new PropertyVetoException("The number of columns can't be negative !",
                new PropertyChangeEvent(this, "columnCount", new Integer(columnCount), new Integer(newCount)));


        // the data array has to be updated row by row.
        for(int i=0; i<rowCount; i++)
        {
            // construct a new row of data containing the new number of columns
            double []newData = new double[newCount];

            // copy the original values into it.
            for(int j=0; j<columnCount && j<newCount; j++)
            {
                newData[j] = data[i][j];
            }

            // replace the old row of data
            data[i] = newData;
        }

        // now create new  column labels.
        String[] newColumnLabel = new String[newCount];

        // now initialize this list with the previous labels and put default names for new columns
        for(int i=0; i<newCount; i++)
        {
            if(i<columnCount)
                newColumnLabel[i] = columnLabel[i];

            else
                newColumnLabel[i] = "C" + new Integer(i+1).toString();
        }

        // now update the column labels
        columnLabel = newColumnLabel;
        
        // update the count
        columnCount = newCount;

        // we need to resize
        adjustSize();
    }
 
    //
    // rowCount
    //

    /**
     * Get the number of rows of data
     * @return  int the number of rows of data.
     */
    public int getRowCount()
    {
        return rowCount;
    }

    /**
     * Set the number of rows of data. This number should be non-negative.
     * If this is less than the original number of rows then last extra rows will be lost
     * If this is more, then additional rows containing null values will be introduced.
     * @param   int the number of rows of data.
     */
    public void setRowCount(int newCount) throws PropertyVetoException
    {
        // do nothing if nothing needs to be done.
        if(newCount == rowCount)
            return;

        // The number of rows has to be non-negative. It may be zero.
        if(newCount < 0)
            throw new PropertyVetoException("The number of rows can't be negative !",
                new PropertyChangeEvent(this, "rowCount", new Integer(rowCount), new Integer(newCount)));

        // The array of rows has to be reallocated. Though the rows themselves are not changed.
        double [][] newData = new double[newCount][];

        for(int i=0; i<newCount; i++)
        {
            // If this row of data already exists then just pick it up
            if(i<rowCount)
                newData[i] = data[i];

            // else create a row of null values
            else
                newData[i] = new double[columnCount];
        }
    
        // now update the data array
        data = newData;

        // now create new row labels.
        String[] newRowLabel = new String[newCount];

        // now initialize this list with the previous labels and put default names for new rows
        for(int i=0; i<newCount; i++)
        {
            if(i<rowCount)
                newRowLabel[i] = rowLabel[i];

            else
                newRowLabel[i] = "R" + new Integer(i+1).toString();
        }

        // now update the row labels
        rowLabel = newRowLabel;

        // and update the number of rows.
        rowCount = newCount;
        
        // we need to resize this chart
        adjustSize();
    }

    //
    // data
    //


    /**
     * Get the data entry corresponding to the current values of colum and row.
     * @return  double   the data value
     */
    public double getData()
    {
        // zero value of row or column is meaningless but allowed because
        // initially this value is possible.
        if(row == 0 || column == 0)
            return 0;

        return data[row-1][column-1];
    }

    /**
     * Set the value of the data element pointed to by the current value of row and column
     * @param   double   the new data value
     */
    public void setData(double newData)
    {
        // zero value of row or column is meaningless but allowed because
        // initially this value is possible.
         if(row == 0 || column == 0)
            return;
         
         data[row-1][column-1] = newData;

         repaint();
    }

    /**
     * Get the i,j th entry of the data i.e. i'th row j'th column
     * @param   int     the row number 1..
     * @param   int     the column number 1..
     * @return   double   the i,j th data entry
     */
    public double getData(int i, int j)
    {
        // zero value of row or column is meaningless but allowed because
        // initially this value is possible.
         if(i == 0 || j == 0)
            return 0;

        return data[i-1][j-1];
    }

    /**
     * Set the i,j th entry of the data.
     * @param   int     the row number
     * @param   int     the column number
     * @param   double   the new data value
     */
    public void setData(int i, int j, double newData)
    {
        // zero value of row or column is meaningless but allowed because
        // initially this value is possible.
        if(i == 0 || j == 0)
            return;

       data[i-1][j-1] = newData;

       repaint();
    }

    //
    // columnLabel
    //

    /**
     * Get the label of the column pointed to by the current column number.
     * @return   String The label of this column
     */
    public String getColumnLabel()
    {
        if(column == 0)
            return "";

        return columnLabel[column-1];
    }

    /**
     * Set the label of the column pointed to by the current column number.
     * @param   String  The column label
     */
    public void setColumnLabel(String newLabel)
    {
        if(column == 0)
            return ;

        columnLabel[column-1] = new String(newLabel);

        repaint();
    }

    /**
     * Get the label of the i'th column
     * @param   int The column number
     * @return  String The label of this column
     */
    public String getColumnLabel(int i)
    {
        if(i == 0)
            return "";

        return columnLabel[i-1];
    }

    /**
     * Set the label of the i'th column
     * @param   int     The column number
     * @param   String  The column label
     */
    public void setColumnLabel(int i, String newLabel)
    {
        if(i == 0)
            return ;

        columnLabel[i-1] = new String(newLabel);

        repaint();
    }

    //
    // rowLabel
    //

    /**
     * Get the label of the row pointed to by the current row number.
     * @return   String The label of this row
     */
    public String getRowLabel()
    {
        if(row == 0)
            return "";

        return rowLabel[row-1];
    }

    /**
     * Set the label of the row pointed to by the current row number.
     * @param   String  The row label
     */
    public void setRowLabel(String newLabel)
    {
        if(row == 0)
            return ;

        rowLabel[row-1] = new String(newLabel);

        repaint();
    }
 
    /**
     * Get the label of the i'th row.
     * @param   int The row number
     * @return  String The label of this row
     */
    public String getRowLabel(int i)
    {
        if(i == 0)
            return "";

        return rowLabel[i-1];
    }

    /**
     * Set the label of the i'th row
     * @param   int The row number
     * @param   String  The row label
     */
    public void setRowLabel(int i, String newLabel)
    {
        if(i == 0)
            return ;

        rowLabel[i-1] = new String(newLabel);

        repaint();
    }

    //
    // rowGap
    //

    /**
     * Set the gap between two rows of data
     * @param   int gap
     */
    public void setRowGap(int gap) throws PropertyVetoException
    {
        if(gap <0)
            throw new PropertyVetoException("The gap can't be negative !",
                new PropertyChangeEvent(this, "rowGap", new Integer(rowGap), new Integer(gap) ) );

        rowGap = gap;

        // resize the graph
        adjustSize();
    }

    /**
     * Get the gap between two rows of data
     * @param   int gap
     */
    public int getRowGap()
    {
        return rowGap;
    }

    //
    // columnGap
    //

    /**
     * Set the gap between two columns of data
     * @param   int gap
     */
    public void setColumnGap(int gap) throws PropertyVetoException
    {
        if(gap <0)
            throw new PropertyVetoException("The gap can't be negative !",
                new PropertyChangeEvent(this, "columnGap", new Integer(columnGap), new Integer(gap) ) );

        columnGap = gap;

        // we might need more space
        adjustSize();
    }

    /**
     * Get the gap between two columns of data
     * @param   int gap
     */
    public int getColumnGap()
    {
        return columnGap;
    }


    //
    // font
    //
    
    /**
     * Set the font of the chart.
     * <p>
     * This has to be overridden because if the font changes the chart has to
     * be resized
     * @param   Font    the new font
     */
    public void setFont(Font f)
    {
        super.setFont(f);

        // resize the chart
        adjustSize();
    }

    //
    // max
    //

    /**
     * The maximum data-value to be displayed. This is made as the nearest largest number which has 
     * one non-zero digit followed by all zeroes.
     * <p>
     * Example: If the maximum data value is 568 this returns 600
     *
     * @return  double  The largest value to be marked on the axis.
     */
    public double getMax()
    {
        // find the maximum value.
        double max = 0;

        for(int i=0; i<rowCount; i++)
        {
            for(int j=0; j<columnCount; j++)
            {
                max = Math.max(max, data[i][j]);
            }
        }

        if(max == 0)
            return 1;

        // The largest power of 10 which is less than max
        int powerOf10 = (int) Math.pow(10, (int)logBase10(max));

        // if max is of the desired form then return rigth away
        if( (max % powerOf10) == 0 )
            return max;

        // Now drop all but the leftmost digits in max
        max = (int) (max / powerOf10 );

        // add one to this unless max itself is of the desired form
        max ++;

        // and now blow it back to its original length
        max *= powerOf10;

        return max;

    }

    /**
     * The data file name specifies the name of an Excel data file in text format.
     * This file will be used to pick up the chart data.
     * @param   String  dataFileName
     */
    public void setDataFileName(String fileName) throws PropertyVetoException
    {
        if( fileName.equals("") )
        {
            return;
        }
        File testFile = new File(fileName);
        FileReader reader;

        try
        {
            reader = new FileReader(testFile);
        }
        catch(FileNotFoundException ex)
        {
            throw new PropertyVetoException("The specified file was not found",
                new PropertyChangeEvent(this, "dataFileName", getDataFileName(), fileName ) );
        }

        StreamTokenizer data = new StreamTokenizer( reader );

        data.eolIsSignificant(true);
        data.ordinaryChar('/');

        boolean EOFReached = false;
        int lastChar;

        int rowsRead = 0;
        int colsRead = 0;
        int maxCols = 0;
        Vector dataStore = new Vector();

        try
        {
            while( !EOFReached )
            {
                switch((lastChar = data.nextToken()))
                {
                case StreamTokenizer.TT_EOF:
                    EOFReached = true;
                    break;

                case StreamTokenizer.TT_EOL:
                    rowsRead ++;
                    
                    // this condition should occur only on the first line
                    if( maxCols == 0)
                    {
                        maxCols = colsRead;
                    }

                    if( colsRead != maxCols )
                    {
                        throw new PropertyVetoException("Wrong number of columns in row "+rowsRead,
                            new PropertyChangeEvent(this, "dataFileName", getDataFileName(), fileName ) );
                    }
                    colsRead = 0;
                    break;

                case StreamTokenizer.TT_NUMBER:
                    dataStore.addElement( new Double(data.nval) );
                    colsRead++;
                    break;

                default:
                    throw new PropertyVetoException("The file has a bad character "+lastChar,
                        new PropertyChangeEvent(this, "dataFileName", getDataFileName(), fileName ) );

                }
            }

            reader.close();
        }
        catch(IOException ex)
        {
            throw new PropertyVetoException("I/O Exception reading in file",
                new PropertyChangeEvent(this, "dataFileName", getDataFileName(), fileName ) );
        }


        // if there are not errors in this file then finally except it.

        // put the data values in the chart.        
        setColumnCount(maxCols);
        setRowCount(rowsRead);
        for(int i=0; i<rowsRead; i++)
        {
            for(int j=0; j<maxCols; j++)
            {
                setData(i+1, j+1, ((Double) dataStore.elementAt(j+i*maxCols)).doubleValue() );               
            }
        }
        
        dataFile = testFile;
    }

    /**
     * The data file name specifies the name of an Excel data file in text format.
     * @param   String  dataFileName
     */
     public String getDataFileName()
     {
         if( dataFile != null )
         {
             return dataFile.getAbsolutePath();
         }

         else
         {
             return "";
         }
     }
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Utility functions
    // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /** 
     * Calculate the logarithm of a number to the base 10
     * @param   double   number
     * @return  double   the log to base 10
     */
    private double logBase10(double number)
    {
        return  Math.log(number) / Math.log(10.0);
    }


}