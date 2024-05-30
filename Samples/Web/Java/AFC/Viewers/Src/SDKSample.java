//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;

// Awt wrapper for UIApplet
public class SDKSample extends AwtUIApplet
{
	public SDKSample() { super(new SDKSmplApplet()); }

	// Application CODE
	public static void main(String args[])
	{
		try { new SDKSmplFrame(); }	catch (Exception e) { e.printStackTrace(); }
	}
}

// Applet CODE
class SDKSmplApplet extends UIApplet
{
	public void init()
	{
		try {
		setLayout(new UIBorderLayout(0, 0));
		setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		add(new SDKCtrlPnl(this, null), "Center");
		} catch (Exception e) { e.printStackTrace(); }
	}
}

// Application CODE
class SDKSmplFrame extends UIFrame
{
	public SDKSmplFrame()
	{
		super("SDKSample Application");
		setBackground(FxColor.lightGray);
		setLayout(new UIBorderLayout(0, 0));
		setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		SDKCtrlPnl ctrl = new SDKCtrlPnl(null, this);
		add(ctrl, "Center");
		setSize(545, 405);
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
