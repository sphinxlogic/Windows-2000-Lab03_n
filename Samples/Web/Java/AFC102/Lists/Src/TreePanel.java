//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;
import com.ms.fx.*;

public class TreePanel extends UIPanel implements SDKConsts
{
	public int state = UISelector.SINGLESELECT;
	public UITree root;
	private static final int INDENT = 30;
	private UIStatus status;
	private int idx[] = { 0, 0, 0 };
	private GeoNode rtnode;
	private int numsel[] = { 0, 0, 0 };

	public TreePanel()
	{
		setLayout(new UIBorderLayout(5,5));
		makeTitle();
		rtnode = new GeoNode(idx, -1);
		root = buildTree(rtnode, 0); add(new UIScrollViewer(root), "Center");
		status = new UIStatus(); add(status, "South");
		setInfo();
	}

	public void setInfo()
	{
		root.setExpanded(true);
		root.setSelectedItem(root.getHeader());
		status.setName(rtnode.getName() + ": " + rtnode.duration);
	}

	public void setSingleSelectMode()
	{
		IUIComponent comp0, comps[] = root.getSelectedItems();

		// Are there any selected items
		if ( (comps == null) || (comps.length == 0) ) {
			root.setSelectedItem(rtnode);
			rtnode.requestFocus();
			status.setName(rtnode.getName() + ": " + rtnode.duration);
		}
		else {
			// Need to make copy of zeroth component since 
			//   removeSelectedItems will clobber component array
			comp0 = comps[0];
			root.removeSelectedItems(comps);
			root.setSelectedItem(comp0);
			comp0.requestFocus();
			GeoNode node = rtnode; // just so node != null if these tests fail;
			if ( comp0 instanceof UITree ) {
				IUIComponent comp = ((UITree)comp0).getHeader();
				if ( comp instanceof GeoNode )
					node = (GeoNode)comp;
			}
			else if ( comp0 instanceof GeoNode )
				node = (GeoNode)comp0;
			status.setName(node.getName() + ": " + node.duration);
		}
	}

	private UITree buildTree(GeoNode header, int depth)
	{
		UITree tree = null, subtree;
		GeoNode subnode;
		int i;

		try {
			while ( true ) {
				// trigger AIOOBE
				switch ( depth ) {
				case 0: i = GeoERA.IMAGE[idx[0]]; break;
				case 1: i = GeoPERIOD.IMAGE[idx[0]][idx[1]]; break;
				case 2: i = GeoEPOCH.IMAGE[idx[0]][idx[1]][idx[2]]; break;
				case 3: return null;
				}
				// If we get to here there is a subnode to header
				if ( idx[depth] == 0 )
					tree = new UITree(header, INDENT);

				subnode = new GeoNode(idx, depth);
				subtree = buildTree(subnode, depth+1);
				if ( subtree == null )
					tree.add(subnode);
				else
					tree.add(subtree);
				idx[depth]++;
			}
		}
		catch ( ArrayIndexOutOfBoundsException e ) {
			if ( idx[depth] != 0 ) { // Were there any nodes at this level?
				idx[depth] = 0; // Reset counter at this depth
				return tree;
			}
			else
				return null;
		}
	}

	public boolean handleEvent(Event e)
	{
		GeoNode node;

		if (e.id == Event.WINDOW_DESTROY)
			// handle the app exit event
			System.exit(0);
		else if ( (e.id == Event.LIST_SELECT) || (e.id == Event.LIST_DESELECT) ) {
			IUIComponent comps[] = root.getSelectedItems();
			String str = new String("");
			if ( comps != null ) {
				if ( comps.length == 0 ) 
					str = "No Items selected";
				else if ( comps.length > 1 )
					str = "" + comps.length + " Items selected";
				else {
					if (comps[0] instanceof GeoNode) {
						node = (GeoNode)comps[0];
						str = node.getName() + ": " + node.duration;
					}
					else if (comps[0] instanceof UITree)
					{
						IUIComponent comp = ((UITree)comps[0]).getHeader();
						if ( comp instanceof GeoNode ) {
							node = (GeoNode)comp;
							str = node.getName() + ": " + node.duration;
						}
					}
				}
			}
			else
				str = "No Items selected";
			status.setName(str);
		}
		return(super.handleEvent(e));
	}

	private void makeTitle()
	{
		UIPanel pnl = new UIPanel();
		pnl.setLayout(new UIFlowLayout(UIFlowLayout.LEFT, 0, 0));
		pnl.add(new UIText("Geological ", UIStatic.LEFT));
		UIText txt = new UIText("Eras", UIStatic.LEFT); txt.setForeground(BaseColor.getColor(new FxColor(255,0,0)));
		pnl.add(txt); pnl.add(new UIText(",", UIStatic.LEFT));
		txt = new UIText("Periods", UIStatic.LEFT); txt.setForeground(BaseColor.getColor(new FxColor(0,191,0)));
		pnl.add(txt); pnl.add(new UIText(",", UIStatic.LEFT));
		txt = new UIText("Epochs", UIStatic.LEFT); txt.setForeground(BaseColor.getColor(new FxColor(255,255,0)));
		pnl.add(txt); pnl.add(new UIText(":", UIStatic.LEFT));
		add(pnl, "North");
	}
}

class GeoNode extends UIItem implements SDKConsts
{
	public String duration;

	public GeoNode(int idx[], int depth)
	{
		//super();
		switch ( depth ) {
		case -1:
			setImage(SDKImages.get(GeoROOT.IMAGE)); setName(GeoROOT.NAME);
			duration = GeoROOT.DURATION; setForeground(BaseColor.getColor(new FxColor(0,0,255)));
			break;
		case 0:
			setImage(SDKImages.get(GeoERA.IMAGE[idx[0]])); setName(GeoERA.NAME[idx[0]]);
			duration = GeoERA.DURATION[idx[0]]; setForeground(BaseColor.getColor(new FxColor(255,0,0)));
			break;
		case 1:
			setImage(SDKImages.get(GeoPERIOD.IMAGE[idx[0]][idx[1]]));
			setName(GeoPERIOD.NAME[idx[0]][idx[1]]);
			duration = GeoPERIOD.DURATION[idx[0]][idx[1]];
			setForeground(BaseColor.getColor(new FxColor(0,191,0)));
			break;
		case 2:
			setImage(SDKImages.get(GeoEPOCH.IMAGE[idx[0]][idx[1]][idx[2]]));
			setName(GeoEPOCH.NAME[idx[0]][idx[1]][idx[2]]);
			duration = GeoEPOCH.DURATION[idx[0]][idx[1]][idx[2]];
			setForeground(BaseColor.getColor(new FxColor(255,255,0)));
			break;
		}
		setFont(new FxFont("Helvetica", FxFont.PLAIN, 18));
	}
}
