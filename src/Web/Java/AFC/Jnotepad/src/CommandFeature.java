//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.ui.event.*;
import com.ms.fx.*;
import java.util.*;

/**
*	Application message mapping module. This module intercepts all menu commands, toolbar
*	commands, and accelerator key commands, identifies what command they are in one place,
*	and routes them to the appropriate place. This allows the developer to put all
*	code designed to identify user commands and put it in one spot. No need to duplicate
*	menu item command routing in different parts of the code.
*	<p>
*	This module also implements ICommandFeedback, which allows parts of the app to enable
*	and disable menu items/toolbar buttons. All the items which can send that command
*	are disabled, even if they are on totally different controls. One simple call
*	enables and disables all controls that can send a particular item.
*	<p>
*	This component is implemented as a plugin feature through the IComponentFeature
*	interface. Subclass this and do your command processing in actionPerformed.
*	<p>
*	@see	IFeature
*	@see	ICommandFeedback
*	@see	IComponentFeature
*
*	@version	1.0, 8/6/97
*/

public abstract class CommandFeature implements IComponentFeature, ICommandFeedback, IUIActionListener
{
	/**
	*	An object which handles text-related commands	
	*/
	ITextOperationTarget textTarget;
				
	/**
	*	An object which handles file-related commands
	*/
	IFileOperationTarget fileTarget;
	
	/**
	*	Vector of components which generate commands
	*/
	Vector talkerVector;
	
	
	/**
	*	Creates a new ComponentFeature.
	*/
	public CommandFeature()
	{
		talkerVector = new Vector(4);
	}
	
	/**
	*	Public init function. Part of the IFeature interface. Sets the objects
	*	which will receive the commands processed.
	*
	*	@param	tTarget	object to receive text-related commands
	*	@param	fTarget	object to receive file-related commands
	*/
	public void init(ITextOperationTarget tTarget, IFileOperationTarget fTarget)
	{
		textTarget = tTarget;
		fileTarget = fTarget;				
	}
				
	/**
	*	Adds a component to the list of objects that are listened to for
	*	command events. These objects are referred to as "talkers".
	*
	*	@param	talker	Object to listen to for command events.
	*/
	public void addTalker(IUIComponent talker)
	{
		if (talker != null)
		{
			talkerVector.addElement(talker);
		}
	}
	
	/**
	*	Called to activate the feature.
	*	Registers the feature as active and attaches listeners to the 
	*	components which have been added as talkers. Part of the IFeature interface. 
	*	Once this class has been registered, it is listening to the commands
	*	performed on all of the elements in talkerVector.
	*/
	public void register()
	{
		Enumeration enum = talkerVector.elements();
		
		while (enum.hasMoreElements())
		{
			Object comp = enum.nextElement();
			
			if (comp instanceof IUISelector)
			{
				((IUISelector)comp).addActionListener(this);
			}
			else if (comp instanceof IActionTalker)
			{
				((IActionTalker)comp).addActionListener(this);
			}
		}
	}
	
	/**
	*	Called when the feature is no longer
	*	active on the current objects. Removes listeners from the talkers. 
	*	Part of the IFeature interface. 
	*/
	public void unregister()
	{
		Enumeration enum = talkerVector.elements();
		
		while (enum.hasMoreElements())
		{
			Object comp = (Object)enum.nextElement();
			
			if (comp instanceof IUISelector)
			{
				((IUISelector)comp).removeActionListener(this);
			}
			else if (comp instanceof IActionTalker)
			{
				((IActionTalker)comp).removeActionListener(this);
			}
		}
	}
	
	/**
	*	Called to reset the state of the 
	*	feature after it is removed. There is no state to reset, so this
	*	method does nothing. Part of the IFeature interface. 
	*/
	public void reset()
	{
	}
	
	/**
	*	Enables or disables a command. All talker objects which support the 
	*	passed command will disable it (normally by graying it out).
	*
	*	@param	command	Name of command to disable or enable.
	*	@param	on	true if the control is to be enabled, false if it is to be disabled
	*/
	public void enableCommand(String command, boolean on)
	{
		Enumeration e = talkerVector.elements();
		while (e.hasMoreElements())
		{
			Object obj = (Object)e.nextElement();
			
			// if the element supports ICommandFeedback, try to enable/disable
			// this command
			if (obj instanceof ICommandFeedback)
			{
				((ICommandFeedback)obj).enableCommand(command, on);									
			}
		}
	}
	
	
	/**
	*	Checks whether a control is enabled or not.
	*
	*	@param	command	Name of command to check 
	*/
	public boolean isEnabled(String command)
	{
		Enumeration e = talkerVector.elements();
		while (e.hasMoreElements())
		{
			Object obj = (Object)e.nextElement();
			
			if (obj instanceof ICommandFeedback)
			{
				if (!((ICommandFeedback)obj).isEnabled(command))
				{
					return false;
				}
			}
		}
		
		return true;
	}
	
	/**
	*	Checks or unchecks a check menu item or a check box button. All talker
	*	controls will check or uncheck the item.
	*
	*	@param	command	Name of command to check or uncheck
	*	@param	on	true if the command is to be checked, false if it is to be unchecked
	*/
	public void setChecked(String command, boolean on)
	{
		Enumeration e = talkerVector.elements();
		while (e.hasMoreElements())
		{
			Object obj = (Object)e.nextElement();
			
			if (obj instanceof ICommandFeedback)
			{
				((ICommandFeedback)obj).setChecked(command, on);
			}
		}
	}
	
	
	/**
	*	Adds a file to the Most Recently Used (MRU) file list of all the
	*	talker components.
	*
	*	@param	filename	Name of file to add
	*/
	public void addToMRUList(String filename)
	{
		Enumeration e = talkerVector.elements();
		while (e.hasMoreElements())
		{
			Object obj = (Object)e.nextElement();
			
			if (obj instanceof ICommandFeedback)
			{
				((ICommandFeedback)obj).addToMRUList(filename);
			}
		}
	}
	
	/**
	*	Called when a control in the system changes color. Notifies all
	*	talker components of this change.
	*
	*	@param	comp	Component who had a color change
	*	@param	color	Color that the component was changed to
	*	@param	whichPart	Which part of the component had a color change. This can
	*						be either FOREGROUND or BACKGROUND.
	*/		
	public void	notifyColorChange(Object comp, FxColor color, int whichPart)
	{
		Enumeration e = talkerVector.elements();
		while (e.hasMoreElements())
		{
			Object obj = (Object)e.nextElement();
			
			if (obj instanceof ICommandFeedback)
			{
				((ICommandFeedback)obj).notifyColorChange(comp,color,whichPart);
			}
		}
	}
	
	/**
	*	Called whenever a command is performed. Override this in a subclass
	*	to perform custom command processing for your application.
	*
	*	@param	evt	Action that was performed.	
	*/
	public abstract void actionPerformed(UIActionEvent evt);
	
}

