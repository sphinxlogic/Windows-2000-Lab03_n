//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Image;
import java.awt.Insets;
import com.ms.ui.*;

public class SDKCtrlPnl extends UIPanel implements SDKConsts, SDKCallbacks
{
	private SpinnerPnl spinner;
	private ScrollBarPnl scroll;
	private SpinnerEditPnl spinedit;
	private SliderPnl slider;
	private ProgressPnl progress;

	public SDKCtrlPnl(UIApplet applet, UIFrame frame)
	{
		setLayout(new UIBorderLayout(0,0));

		// Initialized load on demand images
		SDKImages.init(applet, frame);

		// Create a UIPanel for each demonstrated control
		spinner = new SpinnerPnl(); spinedit = new SpinnerEditPnl();
		scroll = new ScrollBarPnl();	slider = new SliderPnl();
		progress = new ProgressPnl();

		// Create main UIGroup, add to this panel...
		SDKInsetGroup main = new SDKInsetGroup("The dead c SCROLLS", 20, 10, 10, 10);
		// ...and split it vertically.
		main.setLayout(new UISplitLayout(0, 240));

		// Create panel for left side of main panel...
		SDKInsetPanel nwmain = new SDKInsetPanel();
		// ...and split it horizontally.
		nwmain.setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, 80));

		// Create panel for top half of nwmain panel...
		SDKInsetPanel nwnwmain = new SDKInsetPanel();
		// ... and split it vertically.
		nwnwmain.setLayout(new UISplitLayout(0, 115));

		// Create panel for bottom half of nwmain panel...
		SDKInsetPanel senwmain = new SDKInsetPanel();
		// ...and split it horizontally.
		senwmain.setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, 85));

		// add panels to desired locations
		add(main, "Center");
		main.add(nwmain, "nw"); main.add(slider, "se");
		nwmain.add(nwnwmain, "nw"); nwmain.add(senwmain, "se");
		nwnwmain.add(spinner, "nw"); nwnwmain.add(spinedit, "se");
		senwmain.add(scroll, "nw"); senwmain.add(progress, "se");
	}

	public void setInitialFocus()
	{
	}

	public boolean handleEvent(Event evt)
	{
		int pos, start, end;

		switch (evt.id)
		{
			case Event.SCROLL_LINE_UP:
			case Event.SCROLL_LINE_DOWN:
			case Event.SCROLL_PAGE_UP:
			case Event.SCROLL_PAGE_DOWN:
			case Event.SCROLL_ABSOLUTE:
				if ( evt.arg == spinner.ctrl ) {
					pos = spinner.ctrl.getScrollPos(); spinner.setImage(pos);
					spinedit.ctrl.setScrollPos(pos); scroll.ctrl.setScrollPos(pos);
					slider.ctrl.setScrollPos(MAX_SCROLL - pos);
					progress.ctrl.setPos(pos);
				}
				else if ( evt.arg == spinedit.ctrl ) {
					pos = spinedit.ctrl.getScrollPos();
					spinedit.ctrl.setScrollPos(pos);
					spinner.ctrl.setScrollPos(pos); spinner.setImage(pos);
					scroll.ctrl.setScrollPos(pos);
					slider.ctrl.setScrollPos(MAX_SCROLL-pos);
					progress.ctrl.setPos(pos);
				}
				else if ( evt.arg == scroll.ctrl ) {
					pos = scroll.ctrl.getScrollPos();
					spinner.ctrl.setScrollPos(pos); spinner.setImage(pos);
					spinedit.ctrl.setScrollPos(pos);
					slider.ctrl.setScrollPos(MAX_SCROLL-pos);
					progress.ctrl.setPos(pos);
				}
				else if ( evt.arg == slider.ctrl ) {
					pos = MAX_SCROLL - slider.ctrl.getScrollPos();
					spinner.ctrl.setScrollPos(pos); spinner.setImage(pos);
					spinedit.ctrl.setScrollPos(pos); scroll.ctrl.setScrollPos(pos);
					progress.ctrl.setPos(pos);
				}
				else if ( evt.arg == slider.start )
					slider.setSelectionStart();
				else if ( evt.arg == slider.end )
					slider.setSelectionEnd();
				break;
		}			 
		return super.handleEvent(evt);
	}

	public Insets getInsets() { return new Insets(5,5,5,5); }
}

class SDKInsetGroup extends UIGroup
{
	private int t, l, b, r;

	public SDKInsetGroup(String title, int t, int l, int b, int r)
	{
		super(title);
		this.t = t; this.l = l; this.b = b; this.r = r;
	}

	public Insets getInsets() { return new Insets(t, l, b, r); }
}