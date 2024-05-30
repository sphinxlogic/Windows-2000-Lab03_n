//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import com.ms.ui.*;
import com.ms.fx.*;

class Pz15InfoPanel extends UIPanel implements Pz15Consts
{
	public UIText nummoves, minmoves, optmoves;
	public Pz15Marquee marquee;
	public UIText mrqtxt;
	public String mrqstr;

	public Pz15InfoPanel()
	{
		setLayout(new UIBorderLayout(0,0));
		setEdge(IFxGraphicsConstants.BDR_SUNKENOUTER | IFxGraphicsConstants.BDR_RAISEDINNER);
		mrqstr = " ";
		mrqtxt = new UIText(mrqstr);
		mrqtxt.setFont(new FxFont("Helvetica", FxFont.PLAIN, 14));
		marquee = new Pz15Marquee(mrqtxt, this);
		add(marquee, "north");
	
		UIGroup txtinfo = new UIGroup("Statistics");
		txtinfo.setLayout(new UISplitLayout(0,180));

		UIPanel pnl = new UIPanel();
		pnl.setLayout(new UIGridLayout(0,1,0,1));
	 	pnl.add(new UIText("Number of moves so far:", UIText.RIGHT));
		pnl.add(new UIText("Min number of moves to goal:", UIText.RIGHT));
		pnl.add(new UIText("Optimum solution:", UIText.RIGHT));
		txtinfo.add(pnl, "nw");

		// Create data side of info panel
		pnl = new UIPanel();
		pnl.setLayout(new UIGridLayout(0,1,0,1));

		nummoves = new UIText("0", UIText.LEFT);
		nummoves.setForeground(new FxColor(255,0,0));
		nummoves.setFont(new FxFont("Dialog", FxFont.BOLD, 12));

		minmoves = new UIText("" , UIText.LEFT);
		minmoves.setForeground(new FxColor(0,191,0));
		minmoves.setFont(new FxFont("Dialog", FxFont.BOLD, 12));

		optmoves = new UIText("", UIText.LEFT);
		optmoves.setForeground(new FxColor(0,0,255));
		optmoves.setFont(new FxFont("Dialog", FxFont.BOLD, 12));

		pnl.add(nummoves); pnl.add(minmoves); pnl.add(optmoves);
		txtinfo.add(pnl, "se");

		add(txtinfo, "south");
	}

	public Insets getInsets() { return(new Insets(10,10,10,10)); }

	//
	// override isKeyable() so that the info panel can never get focus, and focus
	//  will always be returned to the gamepanel through the UIApplet requestFocus().
	//  see Puzzle15.java
	//
	public boolean isKeyable() { return false; }
}
