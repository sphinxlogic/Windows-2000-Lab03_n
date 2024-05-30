//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Panel;
import java.awt.GridLayout;
import com.ms.ui.*;
import com.ms.fx.*;

public class SplitViewerPanel extends UIPanel implements SDKConsts, IFxGraphicsConstants
{
    static public Class clrClass;
    static { try { clrClass = Class.forName("com.ms.fx.FxColor"); } catch (Exception e) {} }

	public SplitViewerPanel()
	{
		ColorPanel pnl1, pnl2, pnl3, pnl4, pnl5, pnl6, pnl7, pnl8;
		UISplitViewer spv1, spv2, spv3, spv4, spv5, spv6, spv7, spv8;

		setLayout(new UIBorderLayout(5,10));
		add(new UIText("Create your own Mondrian"), "North");

		pnl1 = new ColorPanel(PURPLE);
		pnl2 = new ColorPanel(DEEP_BLUE);
		pnl3 = new ColorPanel(BR_RED);
		pnl4 = new ColorPanel(TEAL);
		pnl5 = new ColorPanel(KHAKI);
		pnl6 = new ColorPanel(WHITE);
		pnl7 = new ColorPanel(LIME);
		pnl8 = new ColorPanel(FOREST_GRN);

		spv1 = new UISplitViewer(null, null, 0, 100);
		spv2 = new UISplitViewer(null, null, UISplitViewer.HORIZONTAL, 150);
		spv3 = new UISplitViewer(null, null, 0, 60);
		spv4 = new UISplitViewer(null, null, 0, 95);
		spv5 = new UISplitViewer(null, null, UISplitViewer.HORIZONTAL, 40);
		spv6 = new UISplitViewer(null, null, UISplitViewer.HORIZONTAL, 100);
		spv7 = new UISplitViewer(null, null, 0, 60);

		spv1.add(pnl1, "nw"); spv1.add(spv2, "se");
		spv2.add(spv3, "nw"); spv2.add(spv4, "se");
		spv3.add(spv5, "nw"); spv3.add(spv6, "se");
		spv4.add(pnl2, "nw"); spv4.add(pnl3, "se");
		spv5.add(pnl4, "nw"); spv5.add(pnl5, "se");
		spv6.add(spv7, "nw"); spv6.add(pnl6, "se");
		spv7.add(pnl7, "nw"); spv7.add(pnl8, "se");

		add(spv1, "center");
		spv1.setEdge(EDGE_SUNKEN);
		spv1.setBackground(BaseColor.getColor(new FxColor(0,0,0)));
	}

	public Insets getInsets() { return new Insets(10,5,5,5); }
}

class ColorPanel extends UIPanel implements SDKConsts
{
	public ColorPanel(int idx)
	{
		setBackground(BaseColor.getColor(new FxColor(CLRS[idx][0], CLRS[idx][1], CLRS[idx][2])));
	}
}