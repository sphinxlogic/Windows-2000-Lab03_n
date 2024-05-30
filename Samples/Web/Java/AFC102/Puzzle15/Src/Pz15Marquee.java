//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Point;
import java.awt.Dimension;
import com.ms.util.TimerEvent;
import com.ms.util.TimerListener;
import com.ms.util.Timer;
import com.ms.util.TaskManager;
import java.awt.Component;
import java.awt.Container;
import com.ms.ui.*;

class Pz15Marquee extends UIViewer implements Pz15Consts, TimerListener
{
	public boolean reset, is_on;
	public int state;

	private Pz15InfoPanel info;
	private Timer timer;
	TaskManager myTm = null ;

    private static AwtUIApplet findAwtUIAppletBelow(Component comp)
    {
        AwtUIApplet applet = null;

        if (comp instanceof AwtUIApplet)
        {
            applet = (AwtUIApplet)comp;
        }
        else if (comp instanceof Container)
        {
            Container cont = (Container)comp;
            int count = cont.countComponents();
            for (int i = 0; i < count; i++)
            {
                comp = cont.getComponent(i);
                if (comp instanceof AwtUIApplet)
                {
                    applet = (AwtUIApplet)comp;
                    break;
                }
            }
        }

        return applet;
    }

    private static AwtUIApplet findAwtUIApplet(Component comp)
    {
        AwtUIApplet applet = null;

        if (comp != null)
        {
            for (;;)
            {
                if (comp instanceof AwtUIApplet)
                {
                    applet = (AwtUIApplet)comp;
                    break;
                }

                Component parent = comp.getParent();
                if (parent == null)
                {
                    applet = findAwtUIAppletBelow(comp);
                    break;
                }

                comp = parent;
            }
        }

        return applet;
    }

    static TaskManager getTaskManager(Component comp)
    {
        AwtUIApplet found = findAwtUIAppletBelow(comp);

        if (found == null)
            found = findAwtUIApplet(comp);

        return (found != null)? found.getTaskManager() : null;
    }

	// This method is used to find what TaskManager should we use for the 
	// specefied IUIComponent.
    static TaskManager getTaskManager(IUIComponent uicomp)
    {
        TaskManager taskManager = null;

        if (uicomp != null)
        {
            IUIRootContainer root = uicomp.getRoot();
            if (root != null)
            {
                Component host = root.getHost();
                if (host != null)
                    taskManager = getTaskManager(host);
            }
        }

        return taskManager;
    }


	public Pz15Marquee(IUIComponent comp, Pz15InfoPanel info)
	{
		super(info.mrqtxt);
		this.info = info;
		reset = true; state = S_NORESET; is_on = false;
	}

	public void addNotify()
	{
		super.addNotify() ;
    	// Try to find the TaskManager used in the AwtUIApplet. This TaskManager
    	// will be passed to the constructor of com.ms.util.Timer.
    	// This is used to get around the security exception when running as an applet 
    	// in Nav3.			
    	if ( myTm == null )
        	myTm = getTaskManager( this ) ;
		timer = new Timer( myTm, this, 75, true);
		timer.start();		
	}

	public void timeTriggered(TimerEvent te)
	{
		if ((te.getSource() == timer) && isVisible(true) && is_on )
		{
			Dimension pnlsize = getSize();

			boolean endframe = false;

			if ( reset ) {
				setPosition(new Point(1000, 0));
				info.mrqtxt.setName(info.mrqstr);
				info.mrqtxt.setValid(true);
				reset = false;
			}

			Dimension itemsize = info.mrqtxt.getPreferredSize();

			Point pt = getPosition(); pt.x += 8;

			// Component is less wide than viewer
			if ( itemsize.width < pnlsize.width ) {
				int xoffset = (pnlsize.width + itemsize.width)/2;
				if ( pt.x > xoffset ) {
					pt.x = -xoffset; endframe = true; }
			}
			else { // Component is wider than viewer
				if ( pt.x > itemsize.width ) {
					pt.x = -pnlsize.width; endframe = true; }
			}
			
			setPosition(pt);

			if ( endframe ) {
				info.mrqtxt.setName(info.mrqstr);
				info.mrqtxt.setValid(true);
			}
		}
	}
}
