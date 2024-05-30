//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;

public class ChoicePanel extends UIPanel implements SDKConsts
{
	public UIChoice choice;

	public ChoicePanel()
	{
		setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL,0));
		add(new UIText("Animation Start Frame:", UIStatic.LEFT));
		choice = new UIChoice(); add(choice);
		fillList();
	}

	private void fillList()
	{
		for ( int i = WORLD; i < WORLD + NUM_WORLDS; i++ ) {
			choice.add(new UIItem(SDKImages.get(i), 
									"Frame " + (i - WORLD + 1) + ": " + FRAME_STR[i-WORLD],
									UIStatic.LEFT, UIItem.ONLEFT));
		}
		choice.setSelectedIndex(11);
	}
}