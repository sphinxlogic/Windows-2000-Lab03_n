/******************************************************************************
 * simpleadoFrame.java
 * 
 * Copyright 1996-1999 Microsoft Corporation
 * 
 * This frame class acts as a top level window in which
 * the applet appears when it's run as a standalone
 * application in a browser.
 *
 ******************************************************************************
*/

import java.awt.*;

class simpleadoframe extends Frame
{
	// simpleadoFrame Constructor
	public simpleadoframe(String str)
	{
		// Additional construction code can be added here
		super (str);
	
		this.addWindowListener(new java.awt.event.WindowAdapter()
		{
			public void windowClosing(java.awt.event.WindowEvent e)
			{
			System.exit(0);
			}	
		});
	}
}
