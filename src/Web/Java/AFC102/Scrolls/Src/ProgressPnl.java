//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import com.ms.ui.*;

public class ProgressPnl extends UIPanel implements SDKConsts
{
	public UIProgress ctrl;

	public ProgressPnl()
	{
		setLayout(new UIBorderLayout());

		ctrl = new UIProgress(MAX_SCROLL, INIT_POS);

		// Create UIGroup for progress
		UIGroup group = new UIGroup("UIProgress");
		group.setLayout(new UIBorderLayout());
		SDKInsetPanelBL ipnl = new SDKInsetPanelBL(15,10,15,10);
		ipnl.add(ctrl, "center"); group.add(ipnl, "center"); add(group, "center");
	}

	public Insets getInsets() { return new Insets(5,0,0,0); }
}
