//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

/**
*	Static abstract wrapper class for SettingsObject. If an application wants one
*	copy of a SettingsObject that will be shared by all classes in the 
*	application, they can use this class. AppSettings holds an instance
*	of a SettingsObject, and classes can use a static method to obtain
*	this object and manipulate it as necessary. Subclass this to return and
*	manipulate whatever SettingsObject is appropriate for your application.
*
*	@version	1.0, 8/17/97
*	@see		SettingsObject
*/

public abstract class AppSettings 
{
    /**
    *	The application-wide SettingsObject
	*/
	protected static SettingsObject settingsObj;
	
	
	// NOTE: All classes that inherit from AppSettings should provide
	// a getSettings() method that returns the right subclass of SettingsObject.
	
	/**
	*	Public init function. Run this to have the SettingsObject created.
	*	Override this in your subclass and create whatever subclass of SettingsObject
	*	you need and assign it to settingsObj.
	*	
	*	@param	filename	Name of file to pass to the SettingsObject.
	*/
	public static void init(String filename)
	{
		settingsObj = new SettingsObject(filename);
	}
	
	/**
	*	Loads the SettingsObject from disk. The file it loads from is the one
	*	pass in init(). Calls the load() method in SettingsObject.
	*
	*	@see	SettingsObject#load
	*/
	public static boolean load()
	{
		return settingsObj.load();				
	}
	
	/**
	*	Saves the SettingsObject to disk. The file it loads from is the one
	*	pass in init().  Calls the save() method in SettingsObject.
	*
	*	@see	SettingsObject#save	 
	*/
	public static void save()
	{
		settingsObj.save();
	}
	
	/**
	*	Loads the default settings for the SettingsObject. Calls the loadDefaults()
	*	method in SettingsObject.
	*
	*	@see	SettingsObject#loadDefaults	 
	*/
	public static void loadDefaults()
	{
		settingsObj.loadDefaults();
	}
}

