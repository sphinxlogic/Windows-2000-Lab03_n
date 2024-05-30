//
// (c) 1997 Microsoft Corporation.	All rights reserved.
//
import java.awt.Insets;
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;

// Awt wrapper for UIApplet
public class Puzzle15 extends AwtUIApplet
{
	public Puzzle15() { super(new Pz15Applet()); }

	// Application CODE
	public static void main(String args[])
	{
		try { new Pz15Frame(); } catch (Exception e) { e.printStackTrace(); }
	}
}

// Applet CODE
class Pz15Applet extends UIApplet
{
	private Pz15ControlPanel ctrl;

	public void init()
	{
		try {
			setLayout(new UIBorderLayout(0, 0));
			setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
			ctrl = new Pz15ControlPanel(this, null);
			add(ctrl, "Center");
		} catch (Exception e) { e.printStackTrace(); }
	}

	public void start() { ctrl.initialize(); }

	public void stop() { ctrl.hideProperties(); }

	//
	// User may switch to another program running in his system, when he comes back,
	//	applet will get focus, need to give it to the gameboard.
	//
	public void requestFocus() { ctrl.requestFocus(); }
}

// Application CODE
class Pz15Frame extends UIFrame
{
	public Pz15Frame()
	{
		super("Puzzle15 Application");
		setBackground(java.awt.Color.lightGray);
		setLayout(new UIBorderLayout(0, 0));
		setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		Pz15ControlPanel ctrl = new Pz15ControlPanel(null, this);
		add(ctrl, "Center");
		setSize(360, 475);
		setVisible(true);
		ctrl.initialize();
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
