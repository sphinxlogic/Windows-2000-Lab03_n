//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;

public class SDKCtrlPnl extends UIPanel implements SDKConsts, SDKCallbacks
{
	private int idx[] = { 0, 0, 0 };
	private UIDrawText info;

	public SDKCtrlPnl(UIApplet applet, UIFrame frame)
	{
		SDKImages.init(applet, frame);

		setLayout(new UIBorderLayout(0,0));

		// Create main UIGroup, add to this UIPanel
		UIGroup group = new UIGroup("BANDS & MENUS");
		add(group, "Center");

		// Get panel from main UIGroup
		group.setLayout(new UIBorderLayout(5, 5));

		UIBandBox box = new UIBandBox();
		group.add(box, "North");

		UIBand venus = new UIBand("Venus"); box.add(venus);
		UIBand earth = new UIBand("Earth"); box.add(earth);
		UIBand mars = new UIBand("Mars", UIBand.BREAK); box.add(mars);

		// Create Venus menu
		UIMenuList mnulst = new UIMenuList();
		UIMenuItem mnuitm = new UIMenuItem("Planet Information");
		mnuitm.setID(ID_VENUS); mnulst.add(mnuitm);
		UIMenuButton btn = new UIMenuButton(new UIGraphic(SDKImages.get(VENUS)), mnulst);
		venus.add(btn);

		// Create Earth menus
		mnulst = new UIMenuList();
		mnuitm = new UIMenuItem("Planet Information");
		mnuitm.setID(ID_EARTH); mnulst.add(mnuitm);
		btn = new UIMenuButton(new UIGraphic(SDKImages.get(EARTH)), mnulst);
		earth.add(btn);
		btn = new UIMenuButton(new UIText("Geology"), buildMenu(0));
		earth.add(btn);

		// Create Mars menu
		mnulst = new UIMenuList();
		mnuitm = new UIMenuItem("Planet Information");
		mnuitm.setID(ID_MARS); mnulst.add(mnuitm);
		btn = new UIMenuButton(new UIGraphic(SDKImages.get(MARS)), mnulst);
		mars.add(btn);

		// Initialize info panel to Venus info
		info = new UIDrawText(INFO[ID_VENUS-ID_BASE]);
		info.setWordWrap(UIDrawText.wwKeepWordIntact);

		// Create info UIGroup
		UIGroup infogrp = new UIGroup("Information");
		infogrp.setLayout(new UIBorderLayout());
		infogrp.add(new UIScrollViewer(info), "Center");
		group.add(infogrp, "Center");
	}

	private UIMenuList buildMenu(int depth)
	{
		UIMenuList sublist, list = null;
		UIMenuItem subitem;
		String str;

		try {
			while ( true ) {
				// trigger AIOOBE
				switch ( depth ) {
				case 0: str = GeoERA.NAME[idx[0]]; break;
				case 1: str = GeoPERIOD.NAME[idx[0]][idx[1]]; break;
				case 2: str = GeoEPOCH.NAME[idx[0]][idx[1]][idx[2]]; break;
				case 3: return null;
				}
				// If we get to here there is a subnode to header
				if ( idx[depth] == 0 )
					list = new UIMenuList();

				sublist = buildMenu(depth+1);
				subitem = makeMenuItem(depth, sublist);
				list.add(subitem);
				idx[depth]++;
			}
		}
		catch ( ArrayIndexOutOfBoundsException e ) {
			if ( idx[depth] != 0 ) { // Were there any nodes at this level?
				idx[depth] = 0; // Reset counter at this depth
				return list;
			}
			else
				return null;
		}
	}

	private UIMenuItem makeMenuItem(int depth, UIMenuList list)
	{
		UIMenuItem item;

		switch ( depth ) {
		case 0:
			item = new UIMenuItem(GeoERA.NAME[idx[0]], list);
			item.setID(GeoERA.ID[idx[0]]);
			return item;
		case 1:
			item = new UIMenuItem(GeoPERIOD.NAME[idx[0]][idx[1]], list);
			item.setID(GeoPERIOD.ID[idx[0]][idx[1]]);
			return item;
		case 2:
			item = new UIMenuItem(GeoEPOCH.NAME[idx[0]][idx[1]][idx[2]], list);
			item.setID(GeoEPOCH.ID[idx[0]][idx[1]][idx[2]]);
			return item;
		}
		return null;
	}

	public boolean action(Event e, Object arg)
	{
		if ( arg instanceof UIMenuItem )
		{
			int id = ((IUIComponent)arg).getID();

			if ( (id >= ID_BASE) && (id < ID_BASE+NUM_INFO) ) {
				info.setValueText(INFO[id - ID_BASE]);
				info.setValid(true);
				return true;
			}
		}
		return super.action(e, arg);
	}

	public void setInitialFocus() { }

	public Insets getInsets() { return new Insets(5,5,5,5); }
}
