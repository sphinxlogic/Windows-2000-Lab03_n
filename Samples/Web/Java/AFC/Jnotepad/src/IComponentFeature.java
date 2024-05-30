//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.ui.event.*;

/**
 *	Extends IFeature and IUIActionListener to provide a way for
 *	an object to attach itself to IUIComponents, intercept their action 
 *	events, interpret them, and send the results of what the user actually
 *	wants to do to another class. This has several benefits:
 *	<ul>
 *	<li>puts the user option control flow all in one class
 *	<li>prevents duplication if you have two classes which implement the
 *				same user commands (i.e. a toolbar and a menubar)
 *	<li>much easier to use - deal with command names rather than objects
 *				or ID numbers
 *	<li>easily extendable...subclass this class or use the otherCommand()
 *				method in your target object to implement nifty commands.
 *	<li><a href="#ICommandFeedback">ICommandFeedback</a> supports
 *				changing the state of user interface controls (i.e. disabling
 *				and enabling all buttons that do a certain command).
 *	</ul>
 *	@version	1.0, 8/6/97
 */

public interface IComponentFeature extends IFeature, IUIActionListener
{
	/**
	 *	Initializes the IComponentFeature object with a text target
	 *	(an object which handles text-related commands, such as cut or paste) and a
	 *	file target (an object which handles file-related commands). Part of the IFeature interface.
	 *
	 *	@param	tTarget	Object to handle text commands
	 *	@param	fTarget	Object to handle file commands
	 */
	public void init(ITextOperationTarget tTarget, IFileOperationTarget fTarget);

	/**
	 *	Adds a component to the list of components which are monitored for user
	 *	commands. Whenever a user selects a command in one of these components, 
	 *	the class that implements this interface intercepts it and handles it.
	 *
	 *	@param	comp	Component which generates user commands
	 */
	public void addTalker(IUIComponent comp);	
}
