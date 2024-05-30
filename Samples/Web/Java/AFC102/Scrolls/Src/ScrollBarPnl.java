//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import com.ms.ui.*;

public class ScrollBarPnl extends UIPanel implements SDKConsts
{
	public UIScrollBar ctrl;

	public ScrollBarPnl()
	{
		setLayout(new UIBorderLayout());

		ctrl = new UIScrollBar(0, 0, MAX_SCROLL+8, 9, 1, INIT_POS);

		// Create UIGroup for scrollbar
		UIGroup group = new UIGroup("UIScrollBar");
		group.setLayout(new UIBorderLayout());
		SDKInsetPanelBL ipnl = new SDKInsetPanelBL(15,10,15,10);
		ipnl.add(ctrl, "center"); group.add(ipnl, "center"); add(group, "center");
	}

	public Insets getInsets() { return new Insets(5,0,0,0); }
}
