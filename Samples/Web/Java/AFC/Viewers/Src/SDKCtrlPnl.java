//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;

public class SDKCtrlPnl extends UIPanel implements SDKConsts, SDKCallbacks
{
	public SDKCtrlPnl(UIApplet applet, UIFrame frame)
	{
		SDKImages.init(applet, frame);

		setLayout(new UIBorderLayout(0,0));

		// Create main UIGroup, add to this UIPanel
		UIGroup group = new UIGroup("These VIEWERS were made for watching");
		add(group, "Center");

		group.setLayout(new UIBorderLayout(0, 0));

		UITabViewer main = new UITabViewer();
		main.add("UISplitViewer", new SplitViewerPanel());
		main.add("UIColumnViewer", new ColumnViewerPanel());
		main.add("UIMarquee", new MarqueePanel());
		main.add("UITabViewer", new TabViewerPanel());

		group.add(main, "Center");
	}

	public void setInitialFocus()
	{
	}

	public Insets getInsets() { return new Insets(5,5,5,5); }
}
