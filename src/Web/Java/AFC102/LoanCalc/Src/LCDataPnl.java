//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import java.awt.Insets;

public class LCDataPnl extends UIPanel
{
	private UIColumnViewer cvloan;
	private UIList list;

	public LCDataPnl(LCParams lp)
	{
		setLayout(new UIBorderLayout());

		UIText headings[] = { new UIText("Period #"), 
							  new UIText("Interest Pd"),
							  new UIText("Principal Pd"),
							  new UIText("Loan Balance") };

		// Create payment schedule list
		list = new UIList();
		fillList(lp, true);

		// Create column viewer
		cvloan = new UIColumnViewer(headings, list);
		int widths[] = { 60, 96, 96, 100 };
		cvloan.setWidths(widths);
		add(cvloan, "center");
	}

	// There is currently no way to just add rows to the UIList and have them
	//  be laid out correctly, so after the first time fillList is called
	//  the rows must be added directly to the UIColumnviewer ( although they need
	//  not be contained in a UIRow component, they can just be added as an array of
	//  IUIComponents).
	public void fillList(LCParams lp, boolean firsttime)
	{
		UIText row[] = new UIText[4];

		// This will allow us to remove/add without the columnviewer repainting
		//  before we are done.
		list.setInvalidating(false);

		if ( !firsttime )
			list.removeAll();

		int ipd, ppd;
		long balance = lp.pv * 100;

		for ( int i = 1; i <= lp.n; i++ ) {
			row[0] = new UIText("" + i);
			ipd = (int)(balance * lp.ip);
			row[1] = new UIText("" + new DNC(ipd));
			ppd = lp.pmnt - ipd;
			row[2] = new UIText("" + new DNC(ppd));
			balance -= ppd;
			row[3] = new UIText("" + new DNC(balance));
			if ( firsttime )
				list.add(new UIRow(row));
			else
				cvloan.add(row); // will pass on to list and layout correctly
		}
		list.setInvalidating(true);
	}

	public Insets getInsets() { return new Insets(12, 0, 5, 5); }
}
