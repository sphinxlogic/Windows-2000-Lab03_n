//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;

/**
*	This object holds a static copy of the UIApplet in this system.
*	This is used by classes which need to have access to the UIApplet object
*	deep down in the hierarchy, mainly for compatibility with the different
*	security model applets use. This is set once, in the JNotePadFrame class,
*	and grabbed everywhere else.
*
*	@see	JNotePadFrame
*
*	@version	1.0, 8/22/97
*/

public class JNoteAppletObject 
{
	/**
	*	The UIApplet the application is running in. null if running as standalone
	*/
	private static UIApplet theApplet;
	
	/**
	*	Sets the application-wide UIApplet object. 
	*	
	*	@param	applet	The applet we are running in. null if we're a standalone app
	*/
	public static void setApplet(UIApplet applet)
	{
		theApplet = applet;			
	}
	
	/**
	*	Determines whether we're running in an applet or not.	
	*	
	*	@returns	true if we're running as an applet, false if we're running standalone.
	*/
	public static boolean isApplet()
	{
		return (theApplet != null);
	}
	
	/**
	*	Retrieves the applet object	
	*	
	*	@returns	The applet we're running in. Returns null if we're running standalone.
	*/
	public static UIApplet getApplet()
	{
		return theApplet;
	}
	
}

