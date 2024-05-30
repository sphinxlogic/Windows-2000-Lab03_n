//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;
import com.ms.fx.*;

public class TabViewerPanel extends UIPanel implements SDKConsts
{
	public TabViewerPanel()
	{
		SDKInsetPanelBL ipnl;

		setLayout(new UIBorderLayout(0,0));

		UITabViewer tbv1,tbv2,tbv3,tbv4,tbv5, tbv6;

		tbv1 = new UITabViewer(); tbv2 = new UITabViewer();
		tbv3 = new UITabViewer(); tbv4 = new UITabViewer();
		tbv5 = new UITabViewer(); tbv6 = new UITabViewer();

		tbv6.add("This better be it...", new UIText("You can smell it!"));
		tbv6.add("...for UITabViewer", new UIItem(SDKImages.get(RUSSIAN), "Yea!"));
		ipnl = new SDKInsetPanelBL(4,4,4,4);
		ipnl.add(tbv6);

		tbv5.add("Maybe the last...", new UIText("You can taste it!"));
		tbv5.add("...UITabViewer", ipnl);
		ipnl = new SDKInsetPanelBL(4,4,4,4);
		ipnl.add(tbv5);

		tbv4.add("Yet another...", new UIText("You're getting closer!"));
		tbv4.add("...UITabViewer", ipnl);
		ipnl = new SDKInsetPanelBL(4,4,4,4);
		ipnl.add(tbv4);

		tbv3.add("Still another...", new UIText("Almost there!"));
		tbv3.add("...UITabViewer", ipnl);
		ipnl = new SDKInsetPanelBL(4,4,4,4);
		ipnl.add(tbv3);

		tbv2.add("Another...", new UIText("Keep Looking!"));
		tbv2.add("...UITabViewer", ipnl);
		ipnl = new SDKInsetPanelBL(4,4,4,4);
		ipnl.add(tbv2);

		tbv1.add("All of these...", new UIText("Nope!"));
		tbv1.add("...tabs are...", new UIText("Nada!"));
		tbv1.add("...added to the...", new UIText("Naught!"));
		tbv1.add("...same UITabViewer.", new UIText("Zippo!"));
		tbv1.add("One of these...", new UIText("Not!"));
		tbv1.add("...tabs leads...", new UIText("Nothing!"));
		tbv1.add("...to something...", new UIText("Zero!"));
		tbv1.add("...other than...", ipnl);
		tbv1.add("...just text.", new UIText("Zilch!"));
		ipnl = new SDKInsetPanelBL(4,4,4,4);
		ipnl.add(tbv1);

		add(ipnl, "Center");
	}
}
