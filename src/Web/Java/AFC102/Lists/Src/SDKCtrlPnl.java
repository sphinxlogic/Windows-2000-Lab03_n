//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;

public class SDKCtrlPnl extends UIPanel implements SDKConsts, SDKCallbacks
{
	private ChoicePanel cpanel; private ListPanel lpanel; private TreePanel tpanel;
	private UIGroup sample;

	public SDKCtrlPnl(UIApplet applet, UIFrame frame)
	{
		SDKImages.init(applet, frame);

		setLayout(new UIBorderLayout(0,0));

		// Create main UIGroup, add to this UIPanel
		UIGroup main = new UIGroup("Making LISTS, checking them twice");
		add(main, "Center");
		main.setLayout(new UISplitLayout(0, 135));

		// Add button and display panels on top and status panel on bottom.
		main.add(new BtnPanel(this), "nw");

		sample = new UIGroup(); sample.setLayout(new UIBorderLayout(0,0));
		SDKInsetPanelBL ipanel = new SDKInsetPanelBL(0,10,0,0);
		ipanel.add(sample, "Center"); main.add(ipanel, "se");

		// Create panels
		cpanel = new ChoicePanel(); lpanel = new ListPanel(); tpanel = new TreePanel();
	}

	public void setSelStateAndMode(int control, int state)
	{
		if ( control == S_LIST ) {
			if ( lpanel.state != state ) {
				lpanel.state = state;
				// If list is becoming SINGLE_SELECT remove all selections
				//   but first one, and give it focus.
				if ( state == UISelector.SINGLESELECT )
					lpanel.setSingleSelectMode();
				lpanel.list.setSelectionMode(state);
			}
			lpanel.list.getSelectedItem().requestFocus();
		}
		else if ( control == S_TREE ) {
			if ( tpanel.state != state ) {
				tpanel.state = state;
				// If tree is becoming SINGLE_SELECT remove all selections
				//   but first one, and give it focus.
				if ( state == UISelector.SINGLESELECT )
					tpanel.setSingleSelectMode();
				tpanel.root.setSelectionMode(state);
			}
			tpanel.root.getHeader().requestFocus();
		}
	}

	public void setDisplay(int state, boolean redraw)
	{
		switch ( state ) {
		case S_CHOICE:
			if ( redraw ) {
				sample.removeAll();
				sample.setName("UIChoice Sample");
				sample.add(cpanel, "Center");
			}
			cpanel.choice.requestFocus();
			break;
		case S_LIST:
			if ( redraw ) {
				sample.setName("UIList Sample");
				sample.removeAllChildren();
				sample.add(lpanel, "Center");
			}
			lpanel.list.getSelectedItem().requestFocus();
			break;
		case S_TREE:
			if ( redraw ) {
				sample.removeAll();
				sample.setName("UITree Sample");
				sample.add(tpanel, "Center");
			}
			tpanel.root.requestFocus();
			break;
		}
	}

	public void setDisplay(boolean multi) { lpanel.setDisplay(multi); }

	public int getListSelState() { return lpanel.list.getSelectionMode(); }

	public int getTreeSelState() { return tpanel.root.getSelectionMode(); }

	public Insets getInsets() { return new Insets(5,5,5,5); }
}

class BtnPanel extends UIPanel implements SDKConsts
{
	private UIRadioButton choice, list, tree, single, multi, extend;
	private UICheckButton multicol;

	private SDKCallbacks ctrl;
	private SDKInsetPanelVFL ipnl1, ipnl2;
	private int ctrlstate = S_LIST;

	public BtnPanel(SDKCallbacks ctrl)
	{
		this.ctrl = ctrl;

		setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL, 0));

		// Create "List Types" groupbox
		UIGroup group = new UIGroup("List Types");
		group.setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL, 0));

		// Create UIList option
		list = new UIRadioButton("UIList"); list.setChecked(true);
		multicol = new UICheckButton("Multi Column"); multicol.setChecked(true);
		ipnl1 = new SDKInsetPanelVFL(0,0,5,0); ipnl2 = new SDKInsetPanelVFL(0,20,0,0);
		ipnl1.add(list); ipnl2.add(multicol); ipnl1.add(ipnl2); group.add(ipnl1);

		// Create UIChoice option
		choice = new UIRadioButton("UIChoice");
		ipnl1 = new SDKInsetPanelVFL(0,0,5,0); ipnl1.add(choice); group.add(ipnl1);
		
		// Create UITree option
		tree = new UIRadioButton("UITree"); group.add(tree);

		// Add "List Types" groupbox to this panel
		add(group);

		// Create "Selection Types" groupbox
		UIRadioGroup rgroup = new UIRadioGroup("Selection Types");
		single = (UIRadioButton)rgroup.add("SINGLE"); single.setChecked(true);
		multi = (UIRadioButton)rgroup.add("MULTI");
		extend = (UIRadioButton)rgroup.add("EXTEND");

		// Add "Selection Types" groupbox to this panel
		add(rgroup);
	}

	public boolean handleEvent(Event e)
	{
		if ( e.id == e.LIST_SELECT ) {
			if ( e.arg instanceof UIRadioButton ) {
				if ( e.arg == single )
					ctrl.setSelStateAndMode(ctrlstate, UISelector.SINGLESELECT);
				else if ( e.arg == multi )
					ctrl.setSelStateAndMode(ctrlstate, UISelector.MULTISELECT);
				else if ( e.arg == extend )
					ctrl.setSelStateAndMode(ctrlstate, UISelector.EXTENDSELECT);
			}
		}
		return(super.handleEvent(e));
	}

	public boolean action(Event e, Object arg)
	{
		if ( arg instanceof UIButton ) {
			if ( arg == choice ) {
				choice.setChecked(true); list.setChecked(false); tree.setChecked(false);
				single.setChecked(true); multi.setChecked(false); extend.setChecked(false);
				multi.setEnabled(false); extend.setEnabled(false);
				multicol.setEnabled(false);
				if ( ctrlstate != S_CHOICE ) {
					ctrlstate = S_CHOICE;
					ctrl.setDisplay(S_CHOICE, true);
				}
				else 
					ctrl.setDisplay(S_CHOICE, false);
			}
			else if ( arg == list ) {
				choice.setChecked(false); list.setChecked(true); tree.setChecked(false);
				multi.setEnabled(true); extend.setEnabled(true);
				multicol.setEnabled(true);
				setModeButton(ctrl.getListSelState());
				if ( ctrlstate != S_LIST ) {
					ctrlstate = S_LIST;
					ctrl.setDisplay(S_LIST, true);
				}
				else 
					ctrl.setDisplay(S_LIST, false);
			}
			else if ( arg == multicol )
				ctrl.setDisplay(multicol.isChecked());
			else if ( arg == tree ) {
				choice.setChecked(false); list.setChecked(false); tree.setChecked(true);
				multi.setEnabled(true); extend.setEnabled(true);
				multicol.setEnabled(false);
				setModeButton(ctrl.getTreeSelState());
				if ( ctrlstate != S_TREE ) {
					ctrlstate = S_TREE;
					ctrl.setDisplay(S_TREE, true);
				}
				else 
					ctrl.setDisplay(S_TREE, false);
			}
		}
		return super.action(e, arg);
	}	

	private void setModeButton(int mode)
	{
		switch ( mode ) {
		case UISelector.SINGLESELECT:
			single.setChecked(true);
			multi.setChecked(false);
			extend.setChecked(false);
			break;
		case UISelector.MULTISELECT:
			single.setChecked(false);
			multi.setChecked(true);
			extend.setChecked(false);
			break;
		case UISelector.EXTENDSELECT:
			single.setChecked(false);
			multi.setChecked(false);
			extend.setChecked(true);
			break;
		}
	}
}
