//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import com.ms.ui.UIComponent;
import com.ms.fx.FxColor;

/**
 *	Interface for allowing user interface controls to receive feedback
 *	(i.e. enabling and disabling items). 
 *	This gives one a flexible and easy to use
 *	architecture for setting the state of components that generate user 
 *	commands. This works well when one uses this to enable and disable commands in all
 *	controls in the entire system. For example, this system
 *	is great for disabling the save button in a toolbar and the corresponding
 *	save option in a menu with one simple method call. See CommandFeature for
 *	an example of how this is done.
 *
 *	@version	1.0, 8/11/97
 *
 *	@see		IComponentFeature
 *	@see		CommandFeature
 *	@see		JNoteMenubar
 *	@see		JNoteToolbar
 */

public interface ICommandFeedback 
{
	public static final int COLORCHANGE_FOREGROUND = 0;
	public static final int COLORCHANGE_BACKGROUND = 1;
	
	/**
	 *	Called to enable or disable a command. 
	 *
	 *	@param	command	Name of command to enable or disable
	 *	@param	on	State to change to. False if command is to be disabled, true if
	 *				it is to be enabled.
	 */
	public void enableCommand(String command, boolean on);

	/**
	 *	Called to check or uncheck a command. This item must be a UICheckButton
	 *	or this call will have no effect. 
	 *
	 *	@param	command	Name of command to check or uncheck
	 *	@param	on	State to change to. True if button is to be checked, false
	 *					is button is to be unchecked.
	 */
	public void setChecked(String command, boolean on);

	/**
	 *	Returns whether a command is enabled. Returns true if it is, false if it
	 *	is disabled.
	 *
	 *	@param	command	Name of command to query
	 */
	public boolean isEnabled(String command);
	
	/**
	 *	Adds a file to the Most Recently Used (MRU) file list. 
	 *
	 *	@param	filename Name of file to add
	 */
	public void addToMRUList(String filename);

	public void notifyColorChange(Object comp,FxColor col,int i);

}

