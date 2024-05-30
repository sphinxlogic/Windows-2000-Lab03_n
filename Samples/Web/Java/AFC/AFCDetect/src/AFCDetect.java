//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import java.applet.*;
import java.awt.*;

/**
 *	Small Java applet which detects whether AFC is installed on the machine or
 *	not. The function doesSupportAFC() returns 1 if AFC is installed and 0
 *	if not. Call this function from a piece of JavaScript and do the right
 *	thing in that piece of code.
 *
 *	@version	1.0, 8/1/97
 */

public class AFCDetect extends Applet
{
	public AFCDetect()
	{		
	}

	/**
	 *	Applet info.
	 *	@returns	String with information about the applet
	 */
	public String getAppletInfo()
	{
		return "Name: AFCDetect\r\n" +
		       "Microsoft Corp.\r\n";
	}


	/**
	 *	The init() method is called by AWT when an applet is first loaded or
	 *	reloaded. Resizes the applet to 0 by 0 pixels since we want this
	 *	applet to run very subtly.
	 */
	// 
    public void init()
	{
		// we don't want this applet taking up any space on the screen
     	resize(0, 0);
	}
		
	/**
	 *	Main function in the applet. Called by a piece of JavaScript and
	 *	returns whether AFC is supported on this machine or not. 
	 *	
	 *	@returns Return 0 if AFC is not installed, and 1 if it is
	 */
	public int doesSupportAFC()
	{
		// Does this by trying to load an AFC UIComponent dynamically. If this succeeds,
		// we have AFC. If not, we're out of luck.
	
		try
			{
				ClassLoader c = getClass().getClassLoader();

				if (c == null)
					{
						return 0;
					}

				// try to load a UIComponent. This must always exist for AFC to work.
				Object obj = c.loadClass("com.ms.ui.UIComponent");				
			}
		catch (ClassNotFoundException e)
			{
				// afc NOT installed
				return 0;
			}	
	
		// AFC installed
		return 1;	
	}
	
	/**
	 *	Obtain the full dot-separated version of AFC we're using in a string.
	 *	
	 *	@returns	Version of AFC; four fields, dot separated.
	 */
	public String getAFCVersionString()
		{
			return AFCVersionManager.getPackageVersionFull("com.ms.ui");
		}

	/**
	 *	Obtains the major version number of AFC.	
	 *	
	 *	@returns	AFC major version number
	 */
	public int getAFCMajorVersion()
		{
			return AFCVersionManager.getPackageVersionMajor("com.ms.ui");
		}	

	/**
	 *	Obtains the minor version number of AFC.	
	 *	
	 *	@returns	AFC minor version number
	 */
	public int getAFCMinorVersion()
		{
			return AFCVersionManager.getPackageVersionMinor("com.ms.ui");
		}	
	
}
