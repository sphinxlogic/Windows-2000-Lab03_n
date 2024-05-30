//
//  SieveDemo.java
//
//  Copyright (c) 1997, Microsoft Corporation.  All rights reserved.
//

import java.awt.*;
import java.applet.Applet;

//----------------------------------------------------------------------------
public class SieveDemo extends Applet
{
    byte[] mabFlags = new byte[32768*2];
    int mhBar = 10;
    int mhGap = 2;
    int mwGap = 2;
    int mx;
    int my;
    int mhBarMax;
    Rectangle mrect;
    int mc;
    int mhText;
    int mwTextMax;
    long mTTotal;
    long mtLast;
    
    public void init()
    {
        mrect = bounds();
        Graphics g = getGraphics();
        if (g != null)
        {
            FontMetrics fm = g.getFontMetrics();
            mhText = fm.getHeight();
            mwTextMax = fm.stringWidth("9999")+mwGap;
            g.dispose();
        }

        mhBarMax = Math.max(mhText, mhBar) + mhGap;
        mtLast = System.currentTimeMillis();
        
        repaint();
    }

    public void update(Graphics g)
    {
        // Calc bar.
        Sieve.CountPrimes(mabFlags);
        long t = System.currentTimeMillis()-mtLast;
        mtLast = System.currentTimeMillis();
        mTTotal += t;        
        // System.out.println(mt);

        // Scroll if needed.    
        if (my + mhBarMax > mrect.height)
        {            
            g.copyArea(0, mhBarMax, mrect.width, mrect.height-mhBarMax, 0, -mhBarMax);
            my -= mhBarMax;
        }   

        DrawBar(g, (int)t);

        // Update the position.
        mc++;
        my += mhBarMax;

        // Average on status bar.
        showStatus("Average: " + mTTotal/mc);
        
        // Do it again.
        repaint();
    }

    void DrawBar(Graphics g, int t)
    {
        int w = (int)((mrect.width-mwTextMax)*(1000-t))/1000;
        g.setColor(Color.lightGray);
        g.fillRect(mx, my, mrect.width, mhBarMax);
        g.setColor(Color.black);
        g.drawString(Integer.toString(mc), mx, mhText+my+((mhBarMax-mhText)/2)-1);
        g.setColor(Color.blue);
        g.fillRect(mx+mwTextMax, my+((mhBarMax-mhBar)/2), w, mhBar);
    }
}
