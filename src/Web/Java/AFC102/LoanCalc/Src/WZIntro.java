//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.fx.*;

public class WZIntro extends UIWizardStep implements LCConsts
{
	public WZIntro()
	{
		super(new UIGraphic(LCImages.get(INTRO)), new IntroPnl());
	}
}

class IntroPnl extends UIPanel implements LCConsts
{
	public IntroPnl()
	{
		UIDrawText dt;
		setLayout(new UIBorderLayout());
		dt = new UIDrawText(INTRO_TXT);
		dt.setWordWrap(IFxTextConstants.wwKeepWordIntact);
		add(dt, "center");
	}
}