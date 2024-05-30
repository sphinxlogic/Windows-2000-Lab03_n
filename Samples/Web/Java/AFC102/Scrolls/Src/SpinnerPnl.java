//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import java.awt.Image;
import com.ms.ui.*;

public class SpinnerPnl extends UIPanel implements SDKConsts
{
	public UISpinner ctrl;

	private UIGraphic sunrise;
	private Image frames[] = new Image[NUM_FRAMES+1];

	public SpinnerPnl()
	{
		setLayout(new UIBorderLayout());

		// load images for animation
		for ( int i = 0; i < NUM_FRAMES; i++ )
			frames[i] = SDKImages.get(SUNRISE+i);
		frames[NUM_FRAMES] = frames[0];

		// Create UISpinner control
		ctrl = new UISpinner(UISpinner.RAISED | UISpinner.VERTICAL | UISpinner.CIRCULAR,
									0, MAX_SCROLL, 0, SPIN_INC, INIT_POS);

		// Create BUDDY associated w/ UISpinner
		sunrise = new UIGraphic(frames[INIT_POS/SPIN_INC], UIStatic.RIGHT);

		// Create inset panel for buddy and add to spinner
		SDKInsetPanelBL ipnl = new SDKInsetPanelBL(0,10,0,10);
		ipnl.add(sunrise, "center"); ctrl.add(UISpinner.BUDDY, ipnl);

		// Create UIGroup for spinner
		UIGroup group = new UIGroup("UISpinner"); group.setLayout(new UIBorderLayout());
		ipnl = new SDKInsetPanelBL(13,10,13,22);
		ipnl.add(ctrl, "center"); group.add(ipnl, "center"); add(group, "center");
	}

	public void setImage(int pos)
	{
		sunrise.setImage(frames[pos/SPIN_INC]);
		sunrise.setValid(true);
	}

	public Insets getInsets() { return new Insets(0,0,0,0); }
}
