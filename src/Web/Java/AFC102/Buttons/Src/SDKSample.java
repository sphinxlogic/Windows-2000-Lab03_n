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
		setBackground(java.awt.Color.lightGray);
		setLayout(new UIBorderLayout(0, 0));
		setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		add(new SDKCtrlPnl(null, this), "Center");
		setSize(520, 412);
		setVisible(true);
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
