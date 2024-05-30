//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import java.awt.Image;
import com.ms.ui.*;
import com.ms.fx.*;

public class SDKCtrlPnl extends UIPanel implements SDKConsts, SDKCallbacks
{
	private UIGroup main, dspgroup, dtxtgroup;
	private UIPanel otherpnl, padding;
	private UIDrawText dtxt;
	private UIStatus status;
	private SDKInsetPanel display;
	private SDKInsetPanelBL stspnl;
	private ImagePanel imgpnl;
	private UIItem item;
	private String name;
	private Image image;
	private BtnPanel btns;
	private int position, imagepos, type;
	private boolean drawgrp, drawtxt;

	public SDKCtrlPnl(UIApplet applet, UIFrame frame)
	{
		SDKImages.init(applet, frame);

		setLayout(new UIBorderLayout(0,0));

		// Create main UIGroup, add to this UIPanel
		main = new UIGroup("Van de Graafics (STATICS)");
		add(main, "Center");

		// Create button UIPanel
		btns = new BtnPanel(this);

		// Create UIITem
		image = SDKImages.get(SHIP); name = "Santa Maria";	
		position = UIStatic.CENTERED;
		imagepos = UIItem.ABOVE; type = T_ITEM;
		item = new UIItem(image, name, position, imagepos);
		item.setFont(new FxFont("Helvetica", FxFont.BOLD, 16));
		item.setForeground(new FxColor(255,255,0));
		item.setBackground(new FxTexture(SDKImages.get(OCEAN), FxTexture.STRETCH_NONE, 
										0, 0, -1, -1, false, 210, 184, 155));

		// Create UIGroup for display and drawtext
		dspgroup = new UIGroup(STR_VOYAGE); dtxtgroup = new UIGroup(STR_TALE);
		dspgroup.setLayout(new UIBorderLayout(0,0));
		dtxtgroup.setLayout(new UIBorderLayout(0,0));

		// Create UIStatus for display
		status = new UIStatus("The ship is located in the center");

		// Create UIDrawText for display
		dtxt = new UIDrawText(STR_DRAWTEXT);
		dtxt.setWordWrap(IFxTextConstants.wwKeepWordIntact);
		dtxtgroup.add(dtxt, "Center");

		// Create UIPanel for UIDrawText and StatusPanel
		otherpnl = new UIPanel();
		otherpnl.setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, 75));

		// Create status and padding UIPanel for UIStatus
		stspnl = new SDKInsetPanelBL(8,0,0,0);
		stspnl.add(status, "Center");
		padding = new UIPanel();
		
		// Create display UIPanel
		display = new SDKInsetPanel(0,10,0,0);
		display.setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, 240));

		// Create image UIPanel
		imgpnl = new ImagePanel(this);
		imgpnl.setLayout(new UIBorderLayout(0,0));

		drawgrp = true; drawtxt = true;
		setDisplay(S_FIRSTTIME);

		main.setLayout(new UISplitLayout(0,150));
		// Add button panel on left and display panel on right.
		main.add(btns, "nw"); main.add(display, "se");
	}

	public void setDisplay(int state)
	{
		switch ( state ) {
		case S_FIRSTTIME:
			dspgroup.add(item, "Center"); 
			imgpnl.add(dspgroup, "Center");
			display.add(imgpnl, "nw"); 
			display.add(otherpnl, "se");
			otherpnl.add(dtxtgroup, "nw"); 
			otherpnl.add(stspnl, "se");
			break;
		case S_GRP:
			drawgrp = true; imgpnl.remove(item);
			dspgroup.add(item, "Center"); imgpnl.add(dspgroup, "Center");
			break;
		case S_NO_GRP:
			drawgrp = false;
			dspgroup.remove(item); imgpnl.remove(dspgroup);
			imgpnl.add(item, "Center");
			break;
		case S_DRAWTXT:
			drawtxt = true;
			display.removeAll();
			display.setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, 240));
			display.add(imgpnl, "nw"); display.add(otherpnl, "se");
			otherpnl.add(dtxtgroup, "nw"); 
			break;
		case S_NO_DRAWTXT:
			drawtxt = false;
			otherpnl.remove(dtxtgroup); display.removeAll();
			display.setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, 315));
			display.add(imgpnl, "nw"); display.add(otherpnl, "se");
			break;
		case S_STATUS:
			otherpnl.remove(padding);
			otherpnl.add(stspnl, "se");
			break;
		case S_NO_STATUS:
			otherpnl.remove(stspnl);
			otherpnl.add(padding, "se");
			break;
		}
	}
		
	public void setItemPosition(int pos)
	{
		if ( pos != position ) {
			item.setFlags( pos );
			position = pos;
			String str = new String("The ship is ");
			switch ( pos ) {
			case UIItem.TOPLEFT: str += "located in the top left corner"; break;
			case UIItem.BOTTOMLEFT: str += "located in the bottom left corner"; break;
			case UIItem.LEFT: str += "centered on the left"; break;
			case UIItem.TOPRIGHT: str += "located in the top right corner"; break;
			case UIItem.BOTTOMRIGHT: str += "located in the bottom right corner"; break;
			case UIItem.RIGHT: str += "centered on the right"; break;
			case UIItem.TOP: str += "centered at the top"; break;
			case UIItem.BOTTOM: str += "centered at the bottom"; break;
			case UIItem.CENTERED: str += "located in the center"; break;
			}
			status.setName(str);
		}
	}

	public void setItemType(int type)
	{
		if ( type != this.type ) {
			this.type = type;
			switch ( type ) {
			case T_TEXT: item.setName(name); item.setImage(null); break;
			case T_GRAPHIC: item.setName(""); item.setImage(image); break;
			case T_ITEM: item.setName(name); item.setImage(image); break;
			}
		}
	}

	public void setImagePos(int imagepos)
	{
		if ( imagepos != this.imagepos ) {
			this.imagepos = imagepos;
			item.setImagePos(imagepos);
		}
	}

	public boolean isDrawGrp() { return drawgrp; }
	public boolean isDrawTxt() { return drawtxt; }
	public Insets getInsets() { return new Insets(0,5,5,5); }
}

class BtnPanel extends UIPanel implements SDKConsts
{
	private UIRadioButton uit, uig, uii, above, onleft;
	private UICheckButton uigrp, uid, uis;

	private SDKCallbacks ctrl;
	private UIRadioGroup statics, style;
	private UIGroup align;
	private UICheckGroup other;
	private UIPanel panel;

	public BtnPanel(SDKCallbacks ctrl)
	{
		this.ctrl = ctrl;

		setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL, 0));
		statics = new UIRadioGroup("Static Components");
		style = new UIRadioGroup("Image Placement");
		align = new UIGroup("Alignment");
		other = new UICheckGroup("Other Statics");

		add(statics); add(style); add(align); add(other);

		uit = (UIRadioButton)statics.add("UIText");
		uig = (UIRadioButton)statics.add("UIGraphic");
		uii = (UIRadioButton)statics.add("UIItem"); uii.setChecked(true);

		above = (UIRadioButton)style.add("ABOVE"); above.setChecked(true);
		onleft = (UIRadioButton)style.add("ONLEFT");

		align.setLayout(new UIBorderLayout(0,0));
		align.add(new MyUIGraphic(SDKImages.get(COMPASS), ctrl), "Center");

		uigrp = (UICheckButton)other.add("UIGroup"); uigrp.setChecked(true);
		uid = (UICheckButton)other.add("UIDrawText"); uid.setChecked(true);
		uis = (UICheckButton)other.add("UIStatus");  uis.setChecked(true);
	}

	public boolean handleEvent(Event e)
	{
		if ( e.id == e.LIST_SELECT ) {
			// need to test radiobtn first since it extends checkbtn
			if ( e.arg instanceof UIRadioButton ) {
				if ( e.arg == uit ) {
					above.setEnabled(false); onleft.setEnabled(false); 
					ctrl.setItemType(T_TEXT);
				}
				else if ( e.arg == uig ) {
					above.setEnabled(false); onleft.setEnabled(false); 
					ctrl.setItemType(T_GRAPHIC);
				}
				else if ( e.arg == uii ) {
					above.setEnabled(true); onleft.setEnabled(true); 
					ctrl.setItemType(T_ITEM);
				}
				else if ( e.arg == above )
					ctrl.setImagePos(UIItem.ABOVE);
				else if ( e.arg == onleft )
					ctrl.setImagePos(UIItem.ONLEFT);
			}
			else if ( e.arg instanceof UICheckButton ) {
				if ( e.arg == uigrp )
					ctrl.setDisplay(S_GRP);
				else if ( e.arg == uid )
					ctrl.setDisplay(S_DRAWTXT);
				else if ( e.arg == uis )
					ctrl.setDisplay(S_STATUS);
			}
		}
		else if ( e.id == e.LIST_DESELECT ) {
			if ( e.arg instanceof UICheckButton ) {
				if ( e.arg == uigrp )
					ctrl.setDisplay(S_NO_GRP);
				else if ( e.arg == uid )
					ctrl.setDisplay(S_NO_DRAWTXT);
				else if ( e.arg == uis )
					ctrl.setDisplay(S_NO_STATUS);
			}
		}
		return(super.handleEvent(e));
	}
}

class MyUIGraphic extends UIGraphic
{
	private SDKCallbacks ctrl;

	public MyUIGraphic(Image img, SDKCallbacks ctrl)
	{
		super(img);
		this.ctrl = ctrl;
	}

	public boolean mouseDrag(Event evt, int x, int y)
	{
		setPos(x ,y);
		return super.mouseDrag(evt, x, y);
	}

	public boolean mouseDown(Event evt, int x, int y)
	{
		setPos(x ,y);
		return super.mouseDown(evt, x, y);
	}

	private void setPos(int x, int y)
	{
		if ( x < 40 ) {
			if ( y < 25 ) ctrl.setItemPosition(UIItem.TOPLEFT);
			else if ( y > 50) ctrl.setItemPosition(UIItem.BOTTOMLEFT);
			else ctrl.setItemPosition(UIItem.LEFT);
		}
		else if ( x > 80 ) {
			if ( y < 25 ) ctrl.setItemPosition(UIItem.TOPRIGHT);
			else if ( y > 50) ctrl.setItemPosition(UIItem.BOTTOMRIGHT);
			else ctrl.setItemPosition(UIItem.RIGHT);
		}
		else {
			if ( y < 25 ) ctrl.setItemPosition(UIItem.TOP);
			else if ( y > 50) ctrl.setItemPosition(UIItem.BOTTOM);
			else ctrl.setItemPosition(UIItem.CENTERED);
		}
	}
}

class ImagePanel extends UIPanel
{
	private SDKCallbacks ctrl;

	public ImagePanel(SDKCallbacks ctrl)
	{
		super();
		this.ctrl = ctrl;
	}

	public Insets getInsets()
	{
		if ( ctrl.isDrawGrp() ) {
			if ( ctrl.isDrawTxt() )
				return new Insets(0,0,0,0);
			else
				return new Insets(0,0,75,0);
		}
		else {
			if ( ctrl.isDrawTxt() )
				return new Insets(18,6,6,6);
			else
				return new Insets(18,6,81,6);
		}
	}
}
