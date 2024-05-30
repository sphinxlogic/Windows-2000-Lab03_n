//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.fx.*;
import java.awt.Insets;

public class WZValue extends UIWizardStep implements LCConsts
{
	public ValuePnl pnl;

	public WZValue()
	{
		super(new UIGraphic(LCImages.get(PVALUE)), new ValuePnl());
		pnl = (ValuePnl)getContent();
	}
}

class ValuePnl extends FocusUIPanel implements LCConsts, IFxTextConstants
{
	public UIEdit pv_e;

	public ValuePnl()
	{
		setLayout(new UIBorderLayout());

		// Main text
		UIDrawText intro = new UIDrawText(VALUE_TXT);
		intro.setWordWrap(IFxTextConstants.wwKeepWordIntact);

		// Amount label
		UIText pv_t = new UIText("Amount of Loan:", UIText.RIGHT);

		// Create Amount edit field
		pv_e = new UIEdit();
		pv_e.setValueText("" + INIT_PV);
		pv_e.setMaxBufferSize(7); pv_e.setBordered(true);
		pv_e.setVertAlign(IFxTextConstants.vtaCenter);
		pv_e.setHorizAlign(IFxTextConstants.htaCenter);
		pv_e.setMaskChars("0123456789"); pv_e.setMaskMode(UIEdit.INCLUDE);

		// add everything to this panel
		add(new HSL(intro, 
					new VSL(pv_t, 
							new BL(pv_e, 30,10,30,0),
							140),
					55),
			"center");
	}

	public void setFocus() { pv_e.requestFocus(); }

	public Insets getInsets() { return new Insets(10,0,0,0); }
}
