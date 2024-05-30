//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.Rectangle;
import com.ms.util.TimerEvent;
import com.ms.util.TimerListener;
import com.ms.util.Timer;
import com.ms.ui.*;
import com.ms.fx.*;

public class MarqueePanel extends UIPanel implements SDKConsts
{
	public MarqueePanel()
	{
		setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, 110));
		//setLayout(new UIBorderLayout(10,10));
		
		// Create Standard Marquee
		UIGroup group = new UIGroup("Standard Marquee");
		SDKInsetPanelBL pnl = new SDKInsetPanelBL(10,10,10,10);
		group.setLayout(new UIBorderLayout(0,0));
		group.add(makeNursery(), "Center");
		pnl.add(group, "Center");
		add(pnl, "nw");

		// Create Bouncing Ball Marquee
		group = new UIGroup("Bouncing Ball Marquee");
		pnl = new SDKInsetPanelBL(10,10,10,10);
		group.setLayout(new UIBorderLayout(0,0));
		group.add(makeBouncingBall(), "Center");
		pnl.add(group, "Center");
		add(pnl, "se");
	}

	private SDKMarquee makeNursery()
	{
		Image frames[] = new Image[NUM_VERSES];
		String verses[] = new String[NUM_VERSES];

		for ( int i = 0; i < NUM_VERSES/2; i++ ) {
			frames[2*i] = SDKImages.get(NURSERY+i); frames[2*i+1] = frames[2*i];
			verses[2*i] = VERSES[i]; verses[2*i+1] = verses[2*i];
		}

		return new SDKMarquee(new UIItem(frames[0], verses[0]), frames, verses, 
								125, 0, 8, false);
	}

	private SDKMarquee makeBouncingBall()
	{
		Image frames[] = new Image[NUM_BOUNCE];

		for ( int i = 0; i < NUM_BOUNCE; i++ )
			frames[i] = SDKImages.get(BOUNCE+i);
		return new SDKMarquee(new UIItem(frames[0], ""), frames, null,
								75, -2, -2, true);
	}

	public Insets getInsets() { return new Insets(10,10,10,10); }

}

class SDKMarquee extends UIViewer implements SDKConsts, TimerListener
{
	private UIItem item;
	private int numframes, num;
	private Image frames[];
	private String verses[];
	private boolean animate;

	private int dx,dy;
	private Timer timer;
	private int numnv = 0;

	public SDKMarquee(UIItem item, Image frames[], String verses[], 
						int rate, int dx, int dy, boolean animate)
	{
		super(item);
		this.animate = animate;
		this.item = item;
		if ( verses != null )
			item.setFont(new FxFont("Dialog", FxFont.PLAIN, 16));
		this.frames = frames;
		this.verses = verses;
		this.dx = dx; this.dy = dy;
		numframes = frames.length; num = 0;
		timer = new Timer(this, rate, true);
		timer.start();
	}

	public void timeTriggered(TimerEvent te)
	{
		boolean endframe = false;

		if ( (te.getSource() == timer) && isVisible(true) )
		{
			Point pt = getPosition();
			pt.x += dx;
			pt.y += dy;

			Dimension pnlsize = getSize();
			Dimension itemsize = item.getPreferredSize();

			// Component is less wide than viewer
			if ( itemsize.width < pnlsize.width ) {
				int xoffset = (pnlsize.width + itemsize.width)/2;
				if ( pt.x > xoffset ) {
					pt.x = -xoffset; endframe = true; }
				else if ( pt.x < -xoffset ) {
					pt.x = xoffset; endframe = true; }
			}
			else { // Component is wider than viewer
				if ( pt.x > itemsize.width ) {
					pt.x = -pnlsize.width; endframe = true; }
				else if ( pt.x < -pnlsize.width ) {
					pt.x = itemsize.width; endframe = true; }
			}

			// Component is less tall than viewer
			if ( itemsize.height < pnlsize.height ) {
				int yoffset = (pnlsize.height + itemsize.height)/2;
				if ( pt.y > yoffset ) {
					pt.y = -yoffset; endframe = true; }
				else if ( pt.y < -yoffset ) {
					pt.y = yoffset; endframe = true; }
			}
			else { // Component is taller than viewer
				if ( pt.y > itemsize.height ) {
					pt.y = -pnlsize.height; endframe = true; }
				else if ( pt.y < -pnlsize.height ) {
					pt.y = itemsize.height; endframe = true; }
			}

			if ( animate ) {
				num = ( num + 1 ) % numframes;
				item.setVisible(false);
				item.setImage(frames[num]);	setValid(true); item.setValid(true);
				setPosition(pt);
				item.setVisible(true);
			}
			else {
				if ( endframe ) {
					num = ( num + 1 ) % numframes;
					item.setImage(frames[num]);	item.setName(verses[num]);
					item.setValid(true);
				}
				setPosition(pt);
			}
		}
	}
}
