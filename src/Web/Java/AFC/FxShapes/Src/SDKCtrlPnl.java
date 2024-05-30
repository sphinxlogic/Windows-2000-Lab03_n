//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Image;
import java.awt.Insets;
import com.ms.ui.*;

public class SDKCtrlPnl extends UIPanel implements SDKConsts
{
	private PaintPnl pntpnl;
	private BtnPanel btns;

	public SDKCtrlPnl(UIApplet applet, UIFrame frame)
	{
		setLayout(new UIBorderLayout(0,0));

		// Initialize load on demand images
		SDKImages.init(applet, frame);

		// Create main UIGroup, add to this panel...
		SDKInsetGroup main = new SDKInsetGroup("We'll Fx you into SHAPES", 20,10,10,10);
		// ...and split it vertically.
		main.setLayout(new UISplitLayout(0, 130));

		// Create display panel
		pntpnl = new PaintPnl();
		UIGroup group = new UIGroup("Test Area");
		group.setLayout(new UIBorderLayout());
		group.add(pntpnl, "center");

		// Create btn panel
		btns = new BtnPanel(pntpnl);

		main.add(btns, "nw"); main.add(new SDKInsetPanelBL(group, 0,5,0,0), "se");
		add(main, "center");

		pntpnl.repaint();
	}

	public void setInitialFocus() { }

	public Insets getInsets() { return new Insets(5,5,5,5); }
}
