//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.fx.*;
import java.awt.Insets;

public class WZPayment extends UIWizardStep implements LCConsts
{
	public PmntPnl pnl;

	public WZPayment()
	{
		super(new UIGraphic(LCImages.get(PAYMENT)), new PmntPnl());
		pnl = (PmntPnl)getContent();
	}
}

class PmntPnl extends FocusUIPanel implements LCConsts, IFxTextConstants
{
	public UIEdit pmnt_e;

	public PmntPnl()
	{
		setLayout(new UIBorderLayout());

		// Main text
		UIDrawText intro = new UIDrawText(PMNT_TXT);
		intro.setWordWrap(IFxTextConstants.wwKeepWordIntact);

		// Amount label
		UIText pmnt_t = new UIText("Amount of Payment:", UIText.RIGHT);

		// Create Amount edit field
		pmnt_e = new UIEdit();
		pmnt_e.setMaxBufferSize(7); pmnt_e.setBordered(true);
		pmnt_e.setVertAlign(IFxTextConstants.vtaCenter);
		pmnt_e.setHorizAlign(IFxTextConstants.htaCenter);
		pmnt_e.setMaskChars("0123456789."); pmnt_e.setMaskMode(UIEdit.INCLUDE);

		// add everything to this panel
		add(new HSL(intro, 
					new VSL(pmnt_t, 
							new BL(pmnt_e, 30,10,30,0),
							155),
					55),
			"center");
	}

	public Insets getInsets() { return new Insets(10,0,0,0); }

	public void setFocus() { pmnt_e.requestFocus(); }
}
