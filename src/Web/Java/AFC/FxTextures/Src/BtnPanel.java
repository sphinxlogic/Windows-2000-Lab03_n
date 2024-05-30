//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;

class BtnPanel extends UIPanel implements SDKConsts
{
	private UIRadioButton none, middle, outer, all, tile;
	private UICheckButton snapto;

	private TexturePnl tpnl;
	private UIRadioGroup stretch;
	private UICheckGroup features;

	public BtnPanel(TexturePnl tpnl)
	{
		this.tpnl = tpnl;

		setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL, 0));

		stretch = new UIRadioGroup("Stretch Mode"); add(stretch);
		features = new UICheckGroup("Texture Features"); add(features);

		none = (UIRadioButton)stretch.add("NONE"); none.setChecked(true);
		middle = (UIRadioButton)stretch.add("MIDDLE");
		outer = (UIRadioButton)stretch.add("OUTER");
		all = (UIRadioButton)stretch.add("ALL");
		tile = (UIRadioButton)stretch.add("Tile Texture");

		snapto = (UICheckButton)features.add("Partial Texture"); snapto.setChecked(true);
	}

	public boolean handleEvent(Event e)
	{
		if ( e.id == e.LIST_SELECT ) {
			if ( e.arg instanceof UIButton ) {
				if ( e.arg == none ) {
					tpnl.setMode(FxTexture.STRETCH_NONE);
					snapto.setEnabled(true);
				}
				else if ( e.arg == middle ) {
					tpnl.setMode(FxTexture.STRETCH_MIDDLE);
					snapto.setEnabled(true);
				}
				else if ( e.arg == outer ) {
					tpnl.setMode(FxTexture.STRETCH_OUTER);
					snapto.setEnabled(true);
				}
				else if ( e.arg == all ) {
					tpnl.setMode(FxTexture.STRETCH_ALL);
					snapto.setEnabled(false);
				}
				else if ( e.arg == tile ) {
					tpnl.setTile(true);
					snapto.setEnabled(false);
				}
				else if ( e.arg == snapto )
					tpnl.setSnapTo(false);
			}
		}
		else if ( e.id == e.LIST_DESELECT ) {
			if ( e.arg instanceof UIButton ) {
				if ( e.arg == tile )
					tpnl.setTile(false);
				else if ( e.arg == snapto )
					tpnl.setSnapTo(true);
			}
		}
		return(super.handleEvent(e));
	}
}
