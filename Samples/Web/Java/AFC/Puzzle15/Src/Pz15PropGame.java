//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.Dimension;
import com.ms.ui.*;
import com.ms.fx.*;

class Pz15PropGame extends UIPropertyPage implements Pz15Consts, IFxTextConstants
{
	private Pz15Options props;
	private UICheckButton cpu;
	private UISpinnerEdit scrambler;

	public Pz15PropGame(Pz15Options props)
	{
		super(props);
		this.props = props;
	}

	public boolean addContent()
	{
		scrambler = new UISpinnerEdit(UISpinner.RAISED, 
										UISpinnerEdit.BORDER | UISpinnerEdit.CENTER,
										MIN_SCRAMBLE,MAX_SCRAMBLE, 10,1, props.numscramble);
		// Get Buddy
		IUIComponent comp = scrambler.getLayoutComponent(UISpinner.BUDDY);
		UIEdit edit;
		if ( comp instanceof UIEdit ) { // it very well better be
			edit = (UIEdit)comp;
			edit.setMaxBufferSize(3); edit.setVertAlign(vtaCenter);
			edit.setFont(new FxFont("Dialog", FxFont.BOLD, 14));
		}

		UIGroup scramble = new UIGroup("Scrambling");
		scramble.setLayout(new UIBorderLayout());
		scramble.add(new SDKInsetPanelBL(scrambler, 14,60,14,60));

		addAt(scramble, 6, 10, new Dimension(189, 50));

		UIGroup cpugr = new UIGroup("Competition");
		cpu = new UICheckButton("Have computer determine an optimum solution");
		cpugr.setLayout(new UIBorderLayout()); cpugr.add(cpu, "center");
		if ( props.cpuactive )
			cpu.setChecked(true);

		addAt(cpugr, 6, 70, new Dimension(189, 50));

		return true;
	}

	public boolean action(Event e, Object arg)
	{
		if ( (arg instanceof UICheckButton) && (arg == cpu) )
			setApplyable(true);
		return super.action(e, arg);
	}	

	public boolean handleEvent(Event e)
	{
		switch ( e.id ) {
		case Event.SCROLL_ABSOLUTE:
			if ( e.arg instanceof UISpinnerEdit )
				scrambler.setScrollPos(scrambler.getScrollPos());
			// FALL THROUGH
		case Event.SCROLL_LINE_DOWN:
		case Event.SCROLL_LINE_UP:
			if ( e.arg instanceof UISpinnerEdit )
				setApplyable(true);
			break;
		}
		return(super.handleEvent(e));
	}
	
	public boolean doApplyAction()
	{
		props.numscramble = scrambler.getScrollPos();
		props.cpuactive = cpu.isChecked();
		return true;
	}
}
