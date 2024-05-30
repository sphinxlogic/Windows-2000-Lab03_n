//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Point;
import java.awt.Dimension;
import com.ms.util.TimerEvent;
import com.ms.util.TimerListener;
import com.ms.util.Timer;
import com.ms.ui.*;

class Pz15Marquee extends UIViewer implements Pz15Consts, TimerListener
{
	public boolean reset, is_on;
	public int state;

	private Pz15InfoPanel info;
	private Timer timer;

	public Pz15Marquee(IUIComponent comp, Pz15InfoPanel info)
	{
		super(info.mrqtxt);
		this.info = info;
		reset = true; state = S_NORESET; is_on = false;
		timer = new Timer(this, 75, true);
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
