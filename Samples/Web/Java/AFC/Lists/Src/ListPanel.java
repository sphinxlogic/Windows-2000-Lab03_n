//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;
import com.ms.fx.*;

public class ListPanel extends UIPanel implements SDKConsts
{
	public UIList list;
	public int state = UISelector.SINGLESELECT;
	public UIScrollViewer scrollviewer;
	public UIStatus status;
	public SDKInsetPanelBL lstpanel;

	public ListPanel()
	{
		setLayout(new UIBorderLayout(5,5));
		add(new UIText("Animation Frames:", UIStatic.LEFT), "North");

		scrollviewer = new UIScrollViewer();
		list = new UIList(UIList.SINGLESELECT, UIVerticalFlowLayout.MULTICOLUMN);
		fillList();
		lstpanel = new SDKInsetPanelBL(2,2,2,2);
		lstpanel.setEdge(IFxGraphicsConstants.BDR_SUNKEN);
		lstpanel.add(list, "Center");
		add(lstpanel, "Center");
		status = new UIStatus("Frame 7 selected"); add(status, "South");
	}

	public void setSingleSelectMode()
	{
		int sel[] = list.getSelectedIndices();

		// Are there any selected items
		if ( (sel == null) || (sel.length == 0) )
			list.setSelectedIndex(0);
		else {
			list.removeSelectedIndices(sel);
			list.setSelectedIndex(sel[0]);
		}
		status.setName("Frame " + (list.getSelectedIndex()+1) + " selected");
		list.getSelectedItem().requestFocus();
	}

	public void setDisplay(boolean multi)
	{
		if ( multi ) {
			remove(scrollviewer);
			lstpanel.add(list, "Center");
			add(lstpanel, "Center");
			list.setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.MULTICOLUMN));
		}
		else {
			remove(lstpanel);
			scrollviewer.setContent(list);
			add(scrollviewer, "Center");
			list.setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL));
		}
		list.relayout();
		list.requestFocus();
	}

	private void fillList()
	{
		for ( int i = WORLD; i < WORLD + NUM_WORLDS; i++ ) {
			list.add(new UIItem(SDKImages.get(i), 
									"Frame " + (i - WORLD + 1),
									UIStatic.LEFT, UIItem.ONLEFT));
		}
		list.setSelectedIndex(6);
	}

	public boolean handleEvent(Event e)
	{
		if (e.id == Event.WINDOW_DESTROY)
			// handle the app exit event
			System.exit(0);
		else if ( (e.id == Event.LIST_SELECT) || (e.id == Event.LIST_DESELECT) ) {
			int sel[] = list.getSelectedIndices();
			if ( sel == null )
				status.setName("No frames selected");
			else if ( sel.length == 1 )
				status.setName("Frame " + (sel[0]+1) + " selected");
			else
				status.setName("" + sel.length + " frames selected");
		}
		return(super.handleEvent(e));
	}
}
