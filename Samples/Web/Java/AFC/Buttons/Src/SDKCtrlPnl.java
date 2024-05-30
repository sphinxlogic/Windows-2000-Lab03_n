//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import java.awt.Image;
import com.ms.ui.*;
import com.ms.fx.*;
import com.ms.util.*;

public class SDKCtrlPnl extends UIPanel implements SDKConsts, SDKCallbacks
{
	private UIPanel panel;
	private UIGroup main, stsgrp, btntst;
	private BtnPanel btns;
	private BtnTstPanel btntstpnl;
	private SDKInsetPanelBL ipanel;
	private UIText btntype, btnstyle, btnstate;

	public SDKCtrlPnl(UIApplet applet, UIFrame frame)
	{
		SDKImages.init(applet, frame);

		setLayout(new UIBorderLayout(0,0));

		// Create button UIPanel
		btns = new BtnPanel(this);

		// Create Button Test Panel
		btntst = new UIGroup("Button Test Area");
		btntst.setLayout(new UIBorderLayout(0,0));
		btntstpnl = new BtnTstPanel(this);
		btntst.add(btntstpnl, "Center");

		// Create UIPanel for btns and btntst
		panel = new UIPanel();
		panel.setLayout(new UISplitLayout(0, 135));
		panel.add(btns,"nw"); panel.add(btntst,"se");

		// Create UIGroup for displaying button status information
		stsgrp = new UIGroup("Button Status");
		stsgrp.setLayout(new UISplitLayout(0, 90));

		SDKInsetPanelGL ipnlgl;
		ipnlgl = new SDKInsetPanelGL(0,0,0,0);
		ipnlgl.add(new UIText( "Button TYPE:", UIStatic.RIGHT));
		ipnlgl.add(new UIText("Button STYLE:", UIStatic.RIGHT));
		ipnlgl.add(new UIText("Button STATE:", UIStatic.RIGHT));
		stsgrp.add(ipnlgl, "nw");

		ipnlgl = new SDKInsetPanelGL(0,5,0,0);
		btntype = new UIText("", UIStatic.LEFT);
		btnstyle = new UIText("", UIStatic.LEFT);
		btnstate = new UIText("", UIStatic.LEFT);
		btnstate.setFont(new FxFont("Dialog", FxFont.BOLD, 12));
		ipnlgl.add(btntype); ipnlgl.add(btnstyle); ipnlgl.add(btnstate);
		stsgrp.add(ipnlgl, "se");

		// Initialize Status panel w/ UIPushButton status (one button at a time
		//  is enabled, we start w/ UIPushButton
		displayTestBtn(B_PUSH); setStatusPush();

		// Create main UIGroup, add to this UIPanel
		main = new UIGroup("You don't wear these BUTTONS on your lapel");
		add(main, "Center");
		main.setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, 264));
		// Add button and button test panels on top and status panel on bottom.
		main.add(panel, "nw"); 
		ipanel = new SDKInsetPanelBL(3,0,0,0); ipanel.add(stsgrp, "Center");
		main.add(ipanel, "se");
	}

	public void setStatusPush()
	{
		int style = 0;
		String str = new String("");

		btntype.setName("UIPushButton");
		if ( btns.raised.isChecked() ) {
			str += "UIPushButton.RAISED";
			style |= UIPushButton.RAISED;
		}

		if ( btns.thick.isChecked() ) {
			if ( str.length() != 0 ) str += " | ";
			str += "UIPushButton.THICK";
			style |= UIPushButton.THICK;
		}
		if ( btns.ptgl.isChecked() ) {
			if ( str.length() != 0 ) str += " | ";
			str += "UIButton.TOGGLE";
			style |= UIButton.TOGGLE;
		}
		else { // If TOGGLE is turned off PushButton can't be checked
			if ( btntstpnl.pbtn.isChecked() )
				btntstpnl.pbtn.setChecked(false);
		}
		btntstpnl.pbtn.setStyle(style);
		btnstyle.setName(str);
		if ( btntstpnl.pbtn.isChecked() ) {
			btnstate.setName("Checked");
			btnstate.setForeground(new FxColor(255,0,0));
		}
		else {
			btnstate.setName("UNChecked");
			btnstate.setForeground(new FxColor(0,191,0));
		}
		// This will ensure pbtn repaints properly
		btntstpnl.pbtn.setVisible(false);
		btntstpnl.pbtn.setVisible(true);
		btnstate.setValid(true);
	}

	public void setStatusCheck()
	{
		int style = 0;
		String str = new String("");

		btntype.setName("UICheckButton");

		if ( btns.ctgl.isChecked() ) {
			str += "UIButton.TRITOGGLE";
			style = UIButton.TRITOGGLE;
		}
		else {
			str += "UIButton.TOGGLE";
			// if not TRITOGGLE can't be indeterminate
			if ( btntstpnl.cbtn.isIndeterminate() )
				btntstpnl.cbtn.setIndeterminate(false);
			style = UIButton.TOGGLE;
		}

		btntstpnl.cbtn.setStyle(style);
		btnstyle.setName(str);

		if ( btntstpnl.cbtn.isChecked() ) {
			btnstate.setName("Checked");
			btnstate.setForeground(new FxColor(255,0,0));
		}
		else {
			if ( btntstpnl.cbtn.isIndeterminate() ) {
				btnstate.setName("Indeterminate");
				btnstate.setForeground(new FxColor(255,255,0));
			}
			else {
				btnstate.setName("UNChecked");
				btnstate.setForeground(new FxColor(0,191,0));
			}
		}
		btnstate.setValid(true);
	}

	private void repaintAll(IUIComponent comp)
	{
		FxGraphics g = comp.getGraphics();
		if (g != null)
		{
			comp.paintAll(g);
			g.dispose();
		}
	}

	public void repaintCheck() { repaintAll(btntstpnl.cbtn); }

	public void setStatusRadio()
	{
		btntype.setName("UIRadioButton");
		btnstyle.setName("UIButton.TOGGLE");
		if ( btntstpnl.rbtn.isChecked() ) {
			btnstate.setName("Checked");
			btnstate.setForeground(new FxColor(255,0,0));
		}
		else {
			btnstate.setName("UNChecked");
			btnstate.setForeground(new FxColor(0,191,0));
		}
		btnstate.setValid(true);
	}

	public void setEnabledRadio() { btntstpnl.rbtn.setEnabled(!btns.rdis.isChecked()); }

	public void repaintRadio()
	{ 
		btntstpnl.rbtn.setValid(true);
		repaintAll(btntstpnl.rbtn);
	}

	public void setStatusRepeat()
	{
		btntype.setName("UIRepeatButton");
		btnstyle.setName("");
		btnstate.setName("UNChecked");
		btnstate.setForeground(new FxColor(0,191,0));
		btnstate.setValid(true);
	}

	public void setEnabledRepeat()
	{
		boolean enabled = !btns.rptdis.isChecked();
		btntstpnl.rptitem.setImage(enabled ? SDKImages.get(HOLDME) : 
											 SDKImages.get(HOLDME_DIS));
		btntstpnl.rptitem.setValid(true);
		btntstpnl.rptbtn.setEnabled(enabled);
	}

	public void displayTestBtn(int btn)
	{
		btntstpnl.removeAll();

		switch ( btn ) {
		case B_PUSH: btntstpnl.add(btntstpnl.ppanel,"nw"); break;
		case B_CHECK: btntstpnl.add(btntstpnl.cpanel,"nw"); break;
		case B_RADIO: btntstpnl.add(btntstpnl.rpanel,"nw"); break;
		case B_REPEAT: btntstpnl.add(btntstpnl.rptpnl,"nw"); break;
		}
		btntstpnl.add(btntstpnl.display, "se");
	}

	public boolean isCustomCheck() { return btns.ccstm.isChecked(); }

	public boolean isCustomRadio() { return btns.rcstm.isChecked(); }

	public Insets getInsets() { return new Insets(0,5,5,5); }
}

class BtnPanel extends UIPanel implements SDKConsts
{
	public UIRadioButton push, rpt, chk, rad;
	public UICheckButton raised, thick, ptgl, rcstm, ccstm, ctgl, bgnd;
	public UICheckButton rdis, rptdis;

	private SDKCallbacks ctrl;
	private UIGroup types; //, contnt;
	private SDKInsetPanelVFL ipnl1, ipnl2;

	public BtnPanel(SDKCallbacks ctrl)
	{
		this.ctrl = ctrl;

		setLayout(new UIBorderLayout(0,0));
		types = new UIGroup("Button Types");
		types.setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL, 0));

		add(types, "Center");

		push = new UIRadioButton("UIPushButton"); push.setChecked(true);
		raised = new UICheckButton("RAISED"); raised.setChecked(true);
		thick = new UICheckButton("THICK"); thick.setChecked(true);
		ptgl = new UICheckButton("TOGGLE"); ptgl.setChecked(true);
		
		chk = new UIRadioButton("UICheckButton"); 
		ctgl = new UICheckButton("TRITOGGLE"); ctgl.setChecked(true); ctgl.setEnabled(false);
		ccstm = new UICheckButton("Custom"); ccstm.setChecked(true); ccstm.setEnabled(false);

		rad = new UIRadioButton("UIRadioButton"); 
		rcstm = new UICheckButton("Custom"); rcstm.setChecked(true); rcstm.setEnabled(false);
		rdis = new UICheckButton("Disabled"); rdis.setEnabled(false);

		rpt = new UIRadioButton("UIRepeatButton"); 
		rptdis = new UICheckButton("Disabled");

		// Add UIPushButton option and sub-options
		ipnl1 = new SDKInsetPanelVFL(0,0,5,0); ipnl2 = new SDKInsetPanelVFL(0,20,0,0);
		ipnl1.add(push);
		ipnl2.add(raised); ipnl2.add(thick); ipnl2.add(ptgl);
		ipnl1.add(ipnl2); types.add(ipnl1);

		// Add UICheckButton option and sub-options
		ipnl1 = new SDKInsetPanelVFL(0,0,5,0);
		ipnl2 = new SDKInsetPanelVFL(0,20,0,0);
		ipnl1.add(chk);
		ipnl2.add(ctgl); ipnl2.add(ccstm);
		ipnl1.add(ipnl2); types.add(ipnl1);

		// Add UIRadioButton option and sub-options
		ipnl1 = new SDKInsetPanelVFL(0,0,5,0); ipnl2 = new SDKInsetPanelVFL(0,20,0,0);
		ipnl1.add(rad);
		ipnl2.add(rcstm); ipnl2.add(rdis);
		ipnl1.add(ipnl2); types.add(ipnl1);

		// Add UIRepeatButton option
		ipnl2 = new SDKInsetPanelVFL(0,20,0,0);
		ipnl2.add(rptdis);
		types.add(rpt); types.add(ipnl2);
	}

	public boolean action(Event e, Object arg)
	{
		if ( arg instanceof UIButton ) {
			if ( arg == push ) {
				push.setChecked(true); rpt.setChecked(false);
				chk.setChecked(false); rad.setChecked(false);
				raised.setEnabled(true); thick.setEnabled(true);
				ptgl.setEnabled(true);
				ctgl.setEnabled(false); ccstm.setEnabled(false);
				rcstm.setEnabled(false); rdis.setEnabled(false);
				rptdis.setEnabled(false);
				ctrl.displayTestBtn(B_PUSH); ctrl.setStatusPush();
			}
			else if ( (arg == raised) || (arg == thick) || (arg == ptgl) )
				ctrl.setStatusPush();
			else if ( arg == chk ) {
				push.setChecked(false); rpt.setChecked(false);
				chk.setChecked(true); rad.setChecked(false);
				raised.setEnabled(false); thick.setEnabled(false);
				ptgl.setEnabled(false);
				ctgl.setEnabled(true); ccstm.setEnabled(true);
				rcstm.setEnabled(false); rdis.setEnabled(false);
				rptdis.setEnabled(false);
				ctrl.displayTestBtn(B_CHECK); ctrl.setStatusCheck();
			}
			else if ( arg == ctgl )
				ctrl.setStatusCheck();
			else if ( arg == ccstm )
				ctrl.repaintCheck();
			else if ( arg == rad ) {
				push.setChecked(false); rpt.setChecked(false);
				chk.setChecked(false); rad.setChecked(true);
				raised.setEnabled(false); thick.setEnabled(false);
				ptgl.setEnabled(false);
				ctgl.setEnabled(false);	ccstm.setEnabled(false);
				if ( !rdis.isChecked() )
					rcstm.setEnabled(true); 
				if ( !rcstm.isChecked() )
					rdis.setEnabled(true);
				rptdis.setEnabled(false);
				ctrl.displayTestBtn(B_RADIO); ctrl.setStatusRadio();
			}
			else if ( arg == rcstm ) {
				ctrl.repaintRadio();
				if ( rcstm.isChecked() )
					rdis.setEnabled(false);
				else
					rdis.setEnabled(true);
			}
			else if ( arg == rdis ) {
				ctrl.setEnabledRadio();
				if ( rdis.isChecked() )
					rcstm.setEnabled(false);
				else
					rcstm.setEnabled(true);
			}
			else if ( arg == rpt ) {
				push.setChecked(false); rpt.setChecked(true);
				chk.setChecked(false); rad.setChecked(false);
				raised.setEnabled(false); thick.setEnabled(false);
				ptgl.setEnabled(false); 
				ctgl.setEnabled(false); ccstm.setEnabled(false);
				rcstm.setEnabled(false); rdis.setEnabled(false);
				rptdis.setEnabled(true);
				ctrl.displayTestBtn(B_REPEAT); ctrl.setStatusRepeat();
			}
			else if ( arg == rptdis )
				ctrl.setEnabledRepeat();
		}
	return super.action(e, arg);
	}	
}

class BtnTstPanel extends UIPanel implements SDKConsts, TimerListener
{
	public UIPushButton pbtn;
	public CustomCheckButton cbtn;
	public CustomRadioButton rbtn;
	public UIRepeatButton rptbtn;
	public DisplayPanel display; 
	public SDKInsetPanelBL ppanel, cpanel, rpanel, rptpnl;
	public UIGraphic anigrfc;
	public UIItem rptitem;

	private SDKCallbacks ctrl;
	private int imgindex, times;
	private Timer timer;

	public BtnTstPanel(SDKCallbacks ctrl)
	{
		super();
		this.ctrl = ctrl;

		imgindex = 0;
		timer = null;

		setLayout(new UISplitLayout(0, 135));

		// Make test UIPushButton
		UIItem item = new UIItem(SDKImages.get(PUSHME), "Press Me!", UIStatic.LEFT);
		item.setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		pbtn = new TTUIPushButton(item, 
								UIPushButton.TOGGLE | UIPushButton.RAISED | 
								UIPushButton.THICK);
		pbtn.setBackground(new FxTexture(SDKImages.get(TEXTURE), FxTexture.STRETCH_NONE, 
										0, 0, -1, -1, false, 185, 179, 202));
		ppanel = new SDKInsetPanelBL(0,5,175,10); ppanel.add(pbtn, "Center");

		UIText text;

		// Make test UICheckButton
		text = new UIText("Check Me!", UIStatic.LEFT);
		cbtn = new CustomCheckButton(text, UIButton.TRITOGGLE, ctrl);
		cpanel = new SDKInsetPanelBL(64,0,131,10); cpanel.add(cbtn, "Center");

		// Make test UIRadioButton
		text = new UIText("Turn Me On!", UIStatic.LEFT);
		rbtn = new CustomRadioButton(text, ctrl);
		rpanel = new SDKInsetPanelBL(123,0,72,10); rpanel.add(rbtn, "Center");

		// Make test UIRepeatButton
		rptitem = new UIItem(SDKImages.get(HOLDME), "Hold Me Down!", 0, UIItem.ABOVE);
		rptbtn = new TTUIRepeatButton(rptitem, UIPushButton.RAISED);
		rptpnl = new SDKInsetPanelBL(167,5,0,10); rptpnl.add(rptbtn, "Center");

		// Create Animation panel
		display = new DisplayPanel();
		anigrfc = new UIGraphic(SDKImages.get(ANIMATION));
		display.add(anigrfc, "Center");
	}

	public boolean action (Event evt, Object arg)
	{
		if ( arg instanceof UIButton ) {
			if ( arg == pbtn ) {
				animate();
				ctrl.setStatusPush(); 
			}
			else if ( arg == rptbtn ) {
				// Show next frame in animation
				imgindex = (imgindex + 1) % NUM_ANIMATE;
				anigrfc.setImage(SDKImages.get(ANIMATION+imgindex));
				anigrfc.setValid(true);
				ctrl.setStatusRepeat();
			}
			else if ( arg == cbtn ) {
				animate();
				ctrl.setStatusCheck();
			}
			else if ( arg == rbtn ) {
				animate();
				ctrl.setStatusRadio();
			}
		}
		return super.action(evt, arg);
	}

	public void animate()
	{
		if ( timer != null )
			timer.stop();

		times = 0;
		timer = new Timer(this, 65, true);
		timer.start();
	}

	public void timeTriggered(TimerEvent te)
	{
		if ( te.getSource() == timer ) {
			times++;
			imgindex++;
			if ( times == 4 )
				timer.stop();
			anigrfc.setImage(SDKImages.get(ANIMATION + (imgindex % NUM_ANIMATE)));
			anigrfc.setValid(true);
		}
	}
}

class DisplayPanel extends UIPanel implements SDKConsts
{
	public DisplayPanel()
	{
		setLayout(new UIBorderLayout(0,0));
		setBackground(new FxTexture(SDKImages.get(STARS), FxTexture.STRETCH_NONE, 
										0, 0, -1, -1, false, 210, 184, 155));
	}

	public Insets getInsets() { return new Insets(82,71,95,71); }
}

class TTUIPushButton extends UIPushButton
{
	public TTUIPushButton(IUIComponent comp, int style) { super(comp, style); }

	// This will implement ToolTips
	public String getHelp() {
		return "Pressing button will\nmake globe rotate\none quarter revolution.";
	}
}

class TTUIRepeatButton extends UIRepeatButton
{
	public TTUIRepeatButton(IUIComponent comp, int style) { super(comp, style); }

	// This will implement ToolTips
	public String getHelp() {
		return "Holding down button\nwill cause globe to\nrotate continuously.";
	}
}

class CustomCheckButton extends UICheckButton implements SDKConsts
{
	private SDKCallbacks ctrl;
	private Image on, off, ind;

	public CustomCheckButton(IUIComponent comp, int style, SDKCallbacks ctrl)
	{
		super(comp, style);
		this.ctrl = ctrl;
		on = SDKImages.get(CHECKBTN_ON); 
		off = SDKImages.get(CHECKBTN); 
		ind = SDKImages.get(CHECKBTN_IND);
	}

	public void paintCheck(FxGraphics g)
	{
		if ( ctrl.isCustomCheck() ) {
			if (g != null) {
				Image image;
				if ( isChecked() )
					image = on;
				else if ( isIndeterminate() )
					image = ind;
				else 
					image = off;
    			g.drawImage(image, 0, (getSize().height - 32) / 2, this);
			}    		
		}
		else
			super.paintCheck(g);
	}

	public Insets getInsets()
	{
		Insets insets = super.getInsets();
		if ( ctrl.isCustomCheck() )
			insets.left += 14;
		return(insets);
	}
}

class CustomRadioButton extends UIRadioButton implements SDKConsts
{
	private SDKCallbacks ctrl;
	private Image off, on;

	public CustomRadioButton(IUIComponent comp, SDKCallbacks ctrl)
	{
		super(comp);
		this.ctrl = ctrl;
		off = SDKImages.get(RADIOBTN); on = SDKImages.get(RADIOBTN_ON);
	}

	public void paintCheck(FxGraphics g)
	{
		if ( ctrl.isCustomRadio() ) {
			if (g != null) {
				Image image;
				if ( isChecked() )
					image = on;
				else 
					image = off;
				g.clearRect(0,0, 30,40);
    			g.drawImage(image, 0, (getSize().height - 32) / 2, this);
			}    		
		}
		else
			super.paintCheck(g);
	}

	public Insets getInsets()
	{
		Insets insets = super.getInsets();
		if ( ctrl.isCustomRadio() )
			insets.left += 16;
		return(insets);
	}
}
