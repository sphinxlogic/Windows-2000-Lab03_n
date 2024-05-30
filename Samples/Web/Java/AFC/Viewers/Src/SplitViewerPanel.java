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
import com.ms.object.*;
import com.ms.object.dragdrop.*;

public class SplitViewerPanel extends UIPanel implements SDKConsts, IFxGraphicsConstants
{
    static public Class clrClass;
    static { try { clrClass = Class.forName("com.ms.fx.FxColor"); } catch (Exception e) {} }

	public SplitViewerPanel()
	{
		DropPanel pnl1, pnl2, pnl3, pnl4, pnl5, pnl6, pnl7, pnl8;
		UISplitViewer spv1, spv2, spv3, spv4, spv5, spv6, spv7, spv8;

		setLayout(new UIBorderLayout(5,10));
		add(new UIText("Create your own Mondrian"), "North");

		pnl1 = new DropPanel(PURPLE);
		pnl2 = new DropPanel(DEEP_BLUE);
		pnl3 = new DropPanel(BR_RED);
		pnl4 = new DropPanel(TEAL);
		pnl5 = new DropPanel(KHAKI);
		pnl6 = new DropPanel(WHITE);
		pnl7 = new DropPanel(LIME);
		pnl8 = new DropPanel(FOREST_GRN);

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
		spv1.setBackground(new FxColor(0,0,0));
		add(new UIAwtHost(new ColorGrid()), "east");
	}

	public Insets getInsets() { return new Insets(10,5,5,5); }
}

class DropPanel extends UIPanel implements SDKConsts, DragHandler
{
	FxColor normal, hot;
	boolean dohot = false;

	public DropPanel(int idx)
	{
		super();
		normal = new FxColor(CLRS[idx][0], CLRS[idx][1], CLRS[idx][2]);
		setFxColor(normal);
	}

	private void setFxColor(FxColor c)
	{
		hot = HotColor.make(c);
		normal = c;
		hotTrack(dohot);
	}

	private void hotTrack(boolean set)
	{
		dohot = set;
		setBackground(dohot ? hot : normal);
		if (isVisible())
			repaint();
	}

	public int dragOver(DragSession session, int x, int y)
	{
		MetaObject data = session.getTransferData();
		if ((data != null) && data.hasObject(null, SplitViewerPanel.clrClass))
			return session.getAvailableEffects() & Transfer.COPY;
		return Transfer.NONE;
	}

	public void drop(DragSession session, int x, int y)
	{
		MetaObject data = session.getTransferData();
		if (data != null) {
			Object object = data.getObject(null, SplitViewerPanel.clrClass);
			if (object instanceof FxColor)
				setFxColor(HotColor.unmake((FxColor)object));
		}
	}

	// hot tracking serves to indicate drop target
	public void dragEnter(DragSession session) { hotTrack(true); }
	public void dragLeave() { hotTrack(false); }
}

class ColorGrid extends Panel implements SDKConsts, DragHandler
{
	public ColorGrid()
	{
		setLayout(new GridLayout(0,2, 2,2));

		for ( int i = 0; i < NUM_COLORS; i++)
			add(new AwtUIHost(new ColorPanel(i)));
	}

	//
	// Need to have an AWT component and have it be addNotify'd for DragnDrop to work
	//  that's why this panel is a java.awt.Panel and not a UIPanel, and that the 
	//  DragHandler methods below are NOPs.
	//
	public int dragOver(DragSession session, int x, int y) { return Transfer.NONE; }
	public void drop(DragSession session, int x, int y) { }
	public void dragEnter(DragSession session) { }
	public void dragLeave() { }
}

class ColorPanel extends UIPanel implements IFxGraphicsConstants
{
	public ColorPanel(int color)
	{
		setEdge(EDGE_SUNKEN);
		setLayout(new UIBorderLayout());
		add(new DragColor(color), "center");
	}

	public Insets getInsets() { return new Insets(3,4,3,3); }
}

class DragColor extends UIPanel implements SDKConsts
{
	FxColor normal, hot;
	boolean dohot = false;

	public DragColor(int idx)
	{
		super();
		normal = new FxColor(CLRS[idx][0], CLRS[idx][1], CLRS[idx][2]);
		setFxColor(normal);
	}

	private void setFxColor(FxColor c)
	{
		hot = HotColor.make(c);
		normal = c;
		hotTrack(dohot);
	}

	private void hotTrack(boolean set)
	{
		dohot = set;
		setBackground(dohot ? hot : normal);
		if (isVisible())
			repaint();
	}

	public boolean mouseDown(Event e, int x, int y)
	{
		ObjectBag data = new ObjectBag();
		data.addObject(null, null, hot);
		UIDragDrop.beginDrag(data, Transfer.COPY | Transfer.LINK);
		return true;
	}

	// hot tracking serves to indicate drag target
	public boolean mouseEnter(Event e, int x, int y) { hotTrack(true); return true; }
	public boolean mouseExit(Event e, int x, int y) { hotTrack(false); return true; }

	public Insets getInsets() { return new Insets(8,8,8,8); }
}

class HotColor
{
	public static FxColor make(FxColor c)
	{
		int r = c.getRed() - 25;	if ( r < 0 ) r = 0;
		int g = c.getGreen() - 25;	if ( g < 0 ) g = 0;
		int b = c.getBlue() - 25;	if ( b < 0 ) b = 0;
		return new FxColor(r,g,b);
	}

	public static FxColor unmake(FxColor c)
	{
		int r = c.getRed() + 25;	if ( r == 25 ) r = 0;
		int g = c.getGreen() + 25;	if ( g == 25 ) g = 0;
		int b = c.getBlue() + 25;	if ( b == 25 ) b = 0;
		return new FxColor(r,g,b);
	}
}
