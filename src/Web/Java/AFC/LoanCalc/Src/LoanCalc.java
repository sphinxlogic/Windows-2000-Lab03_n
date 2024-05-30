//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;


// Awt wrapper for UIApplet
public class LoanCalc extends AwtUIApplet
{
	public LoanCalc() { super(new LCApplet()); }

	// Application CODE
	public static void main(String args[])
	{
		try { new LCFrame(); } catch (Exception e) { e.printStackTrace(); }
	}
}

// Applet CODE
class LCApplet extends UIApplet
{
	private LCCtrlPnl ctrl;

	public void init()
	{
		try {
		setLayout(new UIBorderLayout(0, 0));
		setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		ctrl = new LCCtrlPnl(this, null);
		add(ctrl, "Center");
		} catch (Exception e) { e.printStackTrace(); }
	}

	public void start() { ctrl.setInitialFocus(); }

	public void stop() { ctrl.hideWizard(); }
}

// Application CODE
class LCFrame extends UIFrame
{
	public LCFrame()
	{
		super("LoanCalc Application");
		setBackground(FxColor.lightGray);
		setLayout(new UIBorderLayout(0, 0));
		setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		LCCtrlPnl ctrl = new LCCtrlPnl(null, this);
		add(ctrl, "Center");
		setSize(556, 410);
		setVisible(true);
		ctrl.setInitialFocus();
	}

	public boolean handleEvent(Event evt)
	{
		switch (evt.id)
		{
			case Event.WINDOW_DESTROY: System.exit(0); return true;
			default: return super.handleEvent(evt);
		}			 
	}
}
