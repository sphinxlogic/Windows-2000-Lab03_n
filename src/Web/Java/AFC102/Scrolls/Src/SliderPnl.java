//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import com.ms.ui.*;

public class SliderPnl extends UIPanel implements SDKConsts
{
	public UISlider ctrl, start, end;

	public SliderPnl()
	{
		setLayout(new UIBorderLayout());

		ctrl = new UISlider(UISlider.RANGESELECT | UISlider.VERTICAL,
								0, MAX_SCROLL, 16, 1, INIT_POS, 16);
		start = new UISlider(UISlider.POINTDOWN | UISlider.VERTICAL,
								0, MAX_SCROLL, 16, 1, SEL_START, 16);
		end = new UISlider(UISlider.POINTUP | UISlider.VERTICAL,
								0, MAX_SCROLL, 16, 1, SEL_END, 16);
		ctrl.setSelection(SEL_START, SEL_END);

		// Create UIGroup for sliders	
		UIGroup group = new UIGroup("UISlider"); group.setLayout(new UIBorderLayout());
		SDKInsetPanelBL ipnl = new SDKInsetPanelBL(8,10,8,10);
		ipnl.add(start, "west"); ipnl.add(ctrl, "center"); ipnl.add(end, "east");
		group.add(ipnl, "center"); add(group, "center");
	}

	public void setSelectionStart()
	{
		int startsel = start.getScrollPos();
		int endsel = end.getScrollPos();

		if ( startsel > endsel ) {
			end.setScrollPos(startsel);
			ctrl.setSelection(startsel, startsel);
		}
		else
			ctrl.setSelectionStart(startsel);
	}

	public void setSelectionEnd()
	{
		int startsel = start.getScrollPos();
		int endsel = end.getScrollPos();

		if ( startsel > endsel ) {
			start.setScrollPos(endsel);
			ctrl.setSelection(endsel, endsel);
		}
		else
			ctrl.setSelectionEnd(endsel);
	}

	public Insets getInsets() { return new Insets(0,10,0,0); }
}
