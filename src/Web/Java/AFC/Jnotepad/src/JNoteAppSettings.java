//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
/**
*	Static wrapper class for JNoteSettingsObject. If an application wants one
*	copy of a JNoteSettingsObject that will be shared by all classes in the 
*	application, they can use this class. AppSettings holds an instance
*	of a JNoteSettingsObject, and classes can use a static method to obtain
*	this object and manipulate it as necessary. This is an extension of
*	AppSettings and has identical functionality.
*
*	@version	1.0, 8/17/97
*	@see		SettingsObject
*	@see		JNoteSettings
*	@see		AppSettings
*/

public class JNoteAppSettings extends AppSettings
{	
/**
*	Initializes the AppSettings class. Sets the internal settingsObj
*	to an instance of JNoteSettings.
*	
*	@param	filename	Filename that the JNoteSettings object will load settings information from
	*/
	public static void init(String filename)
	{
		settingsObj = new JNoteSettings(filename);
	}
	
	/**
	*	Returns the application-wide JNoteSettings object.
	*/
	public static JNoteSettings getSettingsObj()
	{
		return (JNoteSettings)settingsObj;
	}
	
}


