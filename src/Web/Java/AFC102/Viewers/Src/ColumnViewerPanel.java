//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;
import com.ms.fx.*;

public class ColumnViewerPanel extends UIPanel implements SDKConsts
{
	private static final int INDENT = 30;

	public UITree root;
	private int idx[] = { 0, 0, 0 };
	private GeoNode rtnode;

	public ColumnViewerPanel()
	{
		int widths[] = { 200, 140, 140 };
		setLayout(new UIBorderLayout(10,10));

		//
		// Create headings
		//
		String headings[] = { "Name", "Start", "End" };

		//
		// Create root node of UITree
		//
		rtnode = new GeoNode(idx, -1);

		//
		// Create UITree
		//
		root = buildTree(rtnode, 0);
		root.setExpanded(true);

		//
		// Create UIColumnViewer
		//
		UIColumnViewer cvtree = new UIColumnViewer(headings, root);
		// Set column widths
		cvtree.setWidths(widths);

		// Add to this panel
		add(cvtree, "center");
	}

	// *************************************************************************
	// buildTree - recursive method for building tree
	// *************************************************************************
	private UITree buildTree(GeoNode header, int depth)
	{
		UITree tree = null, subtree;
		GeoNode subnode;
		Object elements[] = new Object[3];
		int i;

		try {
			while ( true ) {
				// trigger AOOBE
				switch ( depth ) {
				case 0: i = GeoERA.IMAGE[idx[0]]; break;
				case 1: i = GeoPERIOD.IMAGE[idx[0]][idx[1]]; break;
				case 2: i = GeoEPOCH.IMAGE[idx[0]][idx[1]][idx[2]]; break;
				case 3: return null;
				}
				// If we get to here there is a subnode to header
				if ( idx[depth] == 0 ) {
					elements[0] = header;
					elements[1] = header.start;
					elements[2] = header.end;
					//
					// Create tree with UIRow as header
					//
					tree = new UITree(new UIRow(elements), INDENT);
				}

				subnode = new GeoNode(idx, depth);
				subtree = buildTree(subnode, depth+1);
				if ( subtree == null ) {
					elements[0] = subnode;
					elements[1] = subnode.start;
					elements[2] = subnode.end;
					// 
					// add UIRow branch to tree
					//
					tree.add(new UIRow(elements));
				}
				else
					tree.add(subtree);
				idx[depth]++;
			}
		}
		catch ( ArrayIndexOutOfBoundsException e ) {
			if ( idx[depth] != 0 ) { // Were there any nodes at this level?
				idx[depth] = 0; // Yes. Reset counter at this depth
				return tree;
			}
			else
				return null;
		}
	}
}

class GeoNode extends UIItem implements SDKConsts
{
	public String start;
	public String end;

	public GeoNode(int idx[], int depth)
	{
		switch ( depth ) {
		case -1:
			setImage(SDKImages.get(GeoROOT.IMAGE));
			setName(GeoROOT.NAME);
			setForeground(BaseColor.getColor(new FxColor(0,0,255)));
			start = GeoROOT.START;
			end = GeoROOT.END;
			break;
		case 0:
			setImage(SDKImages.get(GeoERA.IMAGE[idx[0]]));
			setName(GeoERA.NAME[idx[0]]);
			setForeground(BaseColor.getColor(new FxColor(255,0,0)));
			start = GeoERA.START[idx[0]];
			end = GeoERA.END[idx[0]];
			break;
		case 1:
			setImage(SDKImages.get(GeoPERIOD.IMAGE[idx[0]][idx[1]]));
			setName(GeoPERIOD.NAME[idx[0]][idx[1]]);
			setForeground(BaseColor.getColor(new FxColor(0,191,0)));
			start = GeoPERIOD.START[idx[0]][idx[1]];
			end = GeoPERIOD.END[idx[0]][idx[1]];
			break;
		case 2:
			setImage(SDKImages.get(GeoEPOCH.IMAGE[idx[0]][idx[1]][idx[2]]));
			setName(GeoEPOCH.NAME[idx[0]][idx[1]][idx[2]]);
			setForeground(BaseColor.getColor(new FxColor(255,255,0)));
			start = GeoEPOCH.START[idx[0]][idx[1]][idx[2]];
			end = GeoEPOCH.END[idx[0]][idx[1]][idx[2]];
			break;
		}
		setFlags(UIItem.LEFT);
		setFont(new FxFont("Helvetica", FxFont.PLAIN, 14));
	}
}
