//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;

class BtnPanel extends UIPanel implements SDKConsts, IFxTextConstants
{
	private UIRadioButton ellipse, line, polygon, rect, roundrect, formattxt, lineoval;
	private UIRadioButton solid, dashed, dotted, textured;

	private PaintPnl pntpnl;
	private UIRadioGroup primitives, penstyle;
	private UISpinnerEdit numpoints, penwidth;
	private UIGroup numgrp, widgrp;

	public BtnPanel(PaintPnl pntpnl)
	{
		this.pntpnl = pntpnl;

		primitives = new UIRadioGroup("Primitive Types");
		ellipse = (UIRadioButton)primitives.add("Ellipse"); ellipse.setID(ID_ELLIPSE);
		line = (UIRadioButton)primitives.add("Line"); line.setID(ID_LINE);
		polygon = (UIRadioButton)primitives.add("Polygon");	polygon.setID(ID_POLY);
		rect = (UIRadioButton)primitives.add("Rectangle"); rect.setID(ID_RECT);
		roundrect = (UIRadioButton)primitives.add("Rounded Rect");	roundrect.setID(ID_ROUNDRECT);
		formattxt = (UIRadioButton)primitives.add("Formatted Text"); formattxt.setID(ID_FORMAT_TEXT);
		lineoval = (UIRadioButton)primitives.add("Lines on Ellipse"); lineoval.setID(ID_LINE_ELLIPSE);
		line.setChecked(true);

		// Create numpoints spinedit
		numpoints = new UISpinnerEdit(UISpinner.RAISED, 
									UISpinnerEdit.CENTER | UISpinnerEdit.BORDER,
									MIN_POINTS, MAX_POINTS, 0, 1, MAX_POINTS);
		UIEdit edit;
		IUIComponent comp = numpoints.getLayoutComponent(UISpinner.BUDDY);
		if ( comp instanceof UIEdit ) { // it very well better be
			edit = (UIEdit)comp;
			edit.setMaxBufferSize(2); edit.setVertAlign(vtaCenter);
			edit.setFont(new FxFont("Dialog", FxFont.BOLD, 14));
		}

		penstyle = new UIRadioGroup("Pen Styles");
		solid = (UIRadioButton)penstyle.add("Solid"); solid.setID(ID_SOLID);
		dashed = (UIRadioButton)penstyle.add("Dashed"); dashed.setID(ID_DASH);
		dotted = (UIRadioButton)penstyle.add("Dotted"); dotted.setID(ID_DOT);
		textured = (UIRadioButton)penstyle.add("Textured"); textured.setID(ID_TEXTURE);
		solid.setChecked(true);

		// Create penwidth spinedit
		penwidth = new UISpinnerEdit(UISpinner.RAISED, 
									UISpinnerEdit.CENTER | UISpinnerEdit.BORDER,
									MIN_WIDTH, MAX_WIDTH, 0, 1, INIT_WIDTH);
		comp = penwidth.getLayoutComponent(UISpinner.BUDDY);
		if ( comp instanceof UIEdit ) { // it very well better be
			edit = (UIEdit)comp;
			edit.setMaxBufferSize(2); edit.setVertAlign(vtaCenter);
			edit.setFont(new FxFont("Dialog", FxFont.BOLD, 14));
		}

		// Create UIGroup for numpoint
		numgrp = new UIGroup("Polygon #Points");
		numgrp.setEnabled(false);
		numgrp.setLayout(new UIBorderLayout());
		SDKInsetPanelBL ipnl = new SDKInsetPanelBL(2,10,2,10);
		ipnl.add(numpoints, "center"); numgrp.add(ipnl, "center");

		// Create UIGroup for penwitdh
		widgrp = new UIGroup("Pen Width");
		widgrp.setLayout(new UIBorderLayout());
		ipnl = new SDKInsetPanelBL(2,10,2,10);
		ipnl.add(penwidth, "center"); widgrp.add(ipnl, "center");

		setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL, 0));
		add(primitives); add(numgrp); add(penstyle); add(widgrp);
	}

	public boolean handleEvent(Event e)
	{
		switch ( e.id ) {
		case Event.LIST_SELECT:
			if ( e.arg instanceof UIButton ) {
				int id = ((UIButton)e.arg).getID();

				boolean isstyledpen = (dotted.isChecked() || dashed.isChecked());

				switch ( id ) {
				case ID_LINE: case ID_RECT:
					penstyle.setEnabled(true);
					solid.setEnabled(true); dashed.setEnabled(true);
					dotted.setEnabled(true); textured.setEnabled(true);
					numgrp.setEnabled(false);
					if ( !isstyledpen )
						widgrp.setEnabled(true);
					else
						widgrp.setEnabled(false);
					pntpnl.setDrawMode(id);
					break;

				case ID_POLY: case ID_ELLIPSE: case ID_ROUNDRECT:
					penstyle.setEnabled(true);
					if ( isstyledpen ) {
						dotted.setChecked(false); dashed.setChecked(false);
						solid.setChecked(true); pntpnl.setPenStyle(ID_SOLID, false);
					}
					widgrp.setEnabled(true);
					solid.setEnabled(true); dashed.setEnabled(false);
					dotted.setEnabled(false); textured.setEnabled(true);
					if ( id == ID_POLY )
						numgrp.setEnabled(true);
					else
						numgrp.setEnabled(false);
					pntpnl.setDrawMode(id);
					break;

				case ID_FORMAT_TEXT:
					penstyle.setEnabled(true);
					solid.setChecked(true); pntpnl.setPenStyle(ID_SOLID, false);
					dashed.setChecked(false);
					dotted.setChecked(false); textured.setChecked(false);
					solid.setEnabled(true); dashed.setEnabled(false);
					dotted.setEnabled(false); textured.setEnabled(false);
					numgrp.setEnabled(false); widgrp.setEnabled(false);
					pntpnl.setDrawMode(id);
					break;

				case ID_LINE_ELLIPSE:
					penstyle.setEnabled(false);
					numgrp.setEnabled(false); widgrp.setEnabled(false);
					pntpnl.setDrawMode(id);
					break;

				case ID_SOLID:
				case ID_TEXTURE:
					widgrp.setEnabled(true);
					pntpnl.setPenStyle(id, true);
					break;

				case ID_DASH:
				case ID_DOT:
					widgrp.setEnabled(false);
					pntpnl.setPenStyle(id, true);
					break;
				}
			}
			break;

		case Event.SCROLL_ABSOLUTE:
			if ( e.arg instanceof UISpinnerEdit ) {
				if ( e.arg == penwidth )
					penwidth.setScrollPos(penwidth.getScrollPos());
				else if ( e.arg == numpoints )
					numpoints.setScrollPos(numpoints.getScrollPos());
			}
			// FALL THROUGH
		case Event.SCROLL_LINE_DOWN:
		case Event.SCROLL_LINE_UP:
			if ( e.arg instanceof UISpinnerEdit ) {
				if ( e.arg == penwidth )
					pntpnl.setPenWidth(penwidth.getScrollPos());
				else if ( e.arg == numpoints )
					pntpnl.setNumPoints(numpoints.getScrollPos());
			}
			break;
		}
		return(super.handleEvent(e));
	}
}
