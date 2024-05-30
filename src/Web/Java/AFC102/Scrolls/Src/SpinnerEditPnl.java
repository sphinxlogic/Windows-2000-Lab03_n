//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import com.ms.ui.*;
import com.ms.fx.*;

public class SpinnerEditPnl extends UIPanel implements SDKConsts, IFxTextConstants
{
	public UISpinnerEdit ctrl;

	public SpinnerEditPnl()
	{
		setLayout(new UIBorderLayout());

		ctrl = new UISpinnerEdit(UISpinner.RAISED, 
									UISpinnerEdit.CENTER | UISpinnerEdit.BORDER,
									0, MAX_SCROLL, 16, 1, INIT_POS);
		IUIComponent comp = ctrl.getLayoutComponent(UISpinner.BUDDY);
		UIEdit edit;
		if ( comp instanceof UIEdit ) { // it very well better be
			edit = (UIEdit)comp;
			edit.setMaxBufferSize(3); edit.setVertAlign(vtaCenter);
			edit.setFont(new FxFont("Dialog", FxFont.BOLD, 14));
		}

		// Create UIGroup for spinneredit
		UIGroup group = new UIGroup("UISpinnerEdit");
		group.setLayout(new UIBorderLayout());
		SDKInsetPanelBL ipnl = new SDKInsetPanelBL(13,10,13,10);
		ipnl.add(ctrl, "center"); group.add(ipnl, "center"); add(group, "center");
	}

	public Insets getInsets() { return new Insets(0,10,0,0); }
}
