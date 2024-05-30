//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.fx.*;

public class WZFinal extends UIWizardStep implements LCConsts
{
	public WZFinal()
	{
		super(new UIGraphic(LCImages.get(INTRO)), new FinalPnl(), true);
	}
}

class FinalPnl extends UIPanel implements LCConsts
{
	public FinalPnl()
	{
		UIDrawText dt;
		setLayout(new UIBorderLayout());
		dt = new UIDrawText(FINAL_TXT);
		dt.setWordWrap(IFxTextConstants.wwKeepWordIntact);
		add(dt, "center");
	}
}