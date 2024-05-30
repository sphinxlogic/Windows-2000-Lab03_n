//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Image;
import java.awt.Insets;
import com.ms.ui.*;

public class SDKCtrlPnl extends UIPanel implements SDKConsts
{
	private TexturePnl texturepnl;
	private BtnPanel btns;

	public SDKCtrlPnl(UIApplet applet, UIFrame frame)
	{
		setLayout(new UIBorderLayout(0,0));

		// Initialized load on demand images
		SDKImages.init(applet, frame);

		// Create main UIGroup, add to this panel...
		SDKInsetGroup main = new SDKInsetGroup("This Fx has bold TEXTURES", 20,10,10,10);
		// ...and split it vertically.
		main.setLayout(new UISplitLayout(0, 130));

		// Create display panel
		texturepnl = new TexturePnl();
		UIGroup group = new UIGroup("Test Area");
		group.setLayout(new UIBorderLayout());
		group.add(texturepnl, "center");

		// Create btn panel
		btns = new BtnPanel(texturepnl);

		main.add(btns, "nw"); main.add(new SDKInsetPanelBL(group, 0,5,0,0), "se");
		add(main, "center");

		texturepnl.repaint();
	}

	public void setInitialFocus() { }

	public Insets getInsets() { return new Insets(5,5,5,5); }
}
