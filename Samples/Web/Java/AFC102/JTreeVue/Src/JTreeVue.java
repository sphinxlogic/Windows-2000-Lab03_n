//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.awt.image.*;
import java.io.*;
import java.net.URL;
import java.net.MalformedURLException;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;

import com.ms.ui.*;
import com.ms.fx.*;

// Awt wrapper for UIApplet
public class JTreeVue extends AwtUIApplet
{
	public JTreeVue() { super(new JTVApplet()); }

	// Application CODE
	public static void main(String args[])
	{
		try { new JTVFrame(); } catch (Exception e) { e.printStackTrace(); }
	}
}

// Applet CODE
class JTVApplet extends UIApplet
{
	private JTreeVuePanel jtree;

	public void init()
	{
		try {
		setLayout(new UIBorderLayout(0, 0));
		setFont(new FxFont("Dialog", FxFont.BOLD, 12));
		URL url = new URL(getCodeBase(), "tree.html");
		InputStream stream = url.openStream();
		jtree = new JTreeVuePanel(stream);
		add(jtree, "Center");
		} catch (Exception e) { e.printStackTrace(); }
	}

	public void start()
	{
		jtree.objroot.getHeader().requestFocus();
	}
}

// Application CODE
class JTVFrame extends UIFrame
{
	private JTreeVuePanel jtree;

	public JTVFrame()
	{
		super("Java Class Hierarchy Application");
		setBackground(java.awt.Color.lightGray);
		setLayout(new UIBorderLayout(0, 0));
		setFont(new FxFont("Dialog", FxFont.BOLD, 12));

		try {
			FileInputStream stream = new FileInputStream("tree.html");
			jtree = new JTreeVuePanel(stream);
			add(jtree, "Center");
			setSize(350, 400);
			setVisible(true);
			jtree.objroot.getHeader().requestFocus();
		} catch ( Exception e ) { e.printStackTrace(); }
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
