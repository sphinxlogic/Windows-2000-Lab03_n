//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

/**
*	Static abstract wrapper class for the CommandFeature interfaces.
*	This class holds a static IComponentFeature and a static ICommandFeedback
*	and static methods to obtain either one of these. This allows any class
*	to get to one application-wide version of these interfaces. We avoid
*	having to pass the objects down and across class hierarchies. Since we
*	want only one central place to handle commands, having one static copy
*	that all classes can get to leads to simplicity and ease of use.
*	Subclass this to use your own classes that follow these interfaces.
*
*	@version	1.0, 8/18/97
*	@see		IComponentFeature
*	@see		ICommandFeedback
*/

public abstract class AppCommandFeature 
{
	/**
	*	The application-wide IComponentFeature object
	*/
	private static IComponentFeature compFeature;	
	
	/**
	*	The application-wide ICommandFeedback object
	*/
	private static ICommandFeedback commandFeedback;
	
	/**
	*	Protected init method. Called by subclasses to set the IComponentFeature
	*	and the ICommandFeedback interfaces.
	*
	*	@param	compfeature	The IComponentFeature object to set as the application-wide one.
	*	@param	commandfeedback The ICommandFeedback object to set as the application-wide one.
	*/
	protected static void init(IComponentFeature compfeature, ICommandFeedback commandfeedback)
	{
		compFeature = compfeature;
		commandFeedback = commandfeedback;			
	}
	
	/**
	*	Retrieves the application-wide IComponentFeature. This is a static method,
	*	so there is no need to create a local object.
	*/
	public static IComponentFeature getCompFeature()
	{
		return compFeature;
	}
	
	/**
	*	Retrieves the application-wide ICommandFeedback. This is a static method,
	*	so there is no need to create a local object.
	*/
	public static ICommandFeedback getCommandFeedback()
	{
		return commandFeedback;
	}
}



