//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.fx.*;
import java.awt.Event;
import java.awt.Insets;

public class WZNumPeriods extends UIWizardStep implements LCConsts
{
	public NumPerPnl pnl;

	public WZNumPeriods()
	{
		super(new UIGraphic(LCImages.get(NUMPERIODS)), new NumPerPnl());
		pnl = (NumPerPnl)getContent();
	}
}

class NumPerPnl extends FocusUIPanel implements LCConsts
{
	public UIEdit len_e;
	public boolean years;
	public UIChoice hz_c;
	public UIRadioButton btn_m, btn_y;

	public NumPerPnl()
	{
		setLayout(new UIBorderLayout());

		// Main text
		UIDrawText dt = new UIDrawText(PERIOD_TXT);
		dt.setWordWrap(IFxTextConstants.wwKeepWordIntact);

		// Create Length UIEdit
		len_e = new UIEdit();
		len_e.setValueText("" + INIT_LEN);
		len_e.setMaxBufferSize(3); len_e.setBordered(true);
		len_e.setVertAlign(IFxTextConstants.vtaCenter);
		len_e.setHorizAlign(IFxTextConstants.htaCenter);
		len_e.setMaskChars("0123456789"); len_e.setMaskMode(UIEdit.INCLUDE);

		// Create months/years UIGroup
		UIGroup len_unit = new UIGroup();
		len_unit.setLayout(new UIGridLayout(0, 1));
		btn_m = new UIRadioButton("month(s)"); btn_m.setID(ID_MONTHS);
		btn_y = new UIRadioButton("year(s)"); btn_y.setID(ID_YEARS);
		btn_y.setChecked(true); years = true;
		len_unit.add(btn_m); len_unit.add(btn_y);

		/* If months/years unit choice is done with UIRadioGroup use this code
		UIRadioGroup len_unit = new UIRadioGroup();
		btn_m = (UIRadioButton)len_unit.add("month(s)"); btn_m.setID(ID_MONTHS);
		btn_y = (UIRadioButton)len_unit.add("year(s)"); btn_y.setID(ID_YEARS);
		btn_y.setChecked(true); years = true;
		*/

		UIText hz_t = new UIText(FREQ_TXT, UIText.RIGHT);

		// Create frequency UIChoice
		hz_c = new UIChoice();
		for ( int i = 0; i < FREQ_STR.length; i++ )
			hz_c.addString(FREQ_STR[i]);
		hz_c.setSelectedIndex(INIT_FREQ);

		add(new HSL(new HSL(dt,
							new VSL(new BL(len_e, 0,30,1,0),
									new BL(len_unit, 0,0,0,30),
									115),
							38),
					new HSL(hz_t,
							new BL(hz_c, 0,0,6,0),
							32),
					82),
			"center");
	}

	public void setFocus() { len_e.requestFocus(); }

	public boolean action(Event e, Object arg)
	{
		if ( arg instanceof UIButton ) {
			if ( arg == btn_m ) {
				years = false;
				btn_m.setChecked(true);
				btn_y.setChecked(false);
			}
			else if ( arg == btn_y ) {
				years = true;
				btn_y.setChecked(true);
				btn_m.setChecked(false);
			}
			setFocus();
		}
		return super.action(e, arg);
	}	

	/* If months/years unit choice is done with UIRadioGroup use this code
	public boolean handleEvent(Event e)
	{
		switch ( e.id ) {
		case Event.LIST_SELECT:
			if ( e.arg instanceof UIButton ) {
				int id = ((UIButton)e.arg).getID();

				switch ( id ) {
				case ID_MONTHS: years = false; break;
				case ID_YEARS: years = true; break;
				}
			}
			setFocus();
			break;
		}
		return(super.handleEvent(e));
	}
	*/
}

