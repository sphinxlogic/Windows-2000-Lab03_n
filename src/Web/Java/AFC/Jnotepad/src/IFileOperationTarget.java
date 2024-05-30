//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import com.ms.ui.event.UIActionEvent;

/**
 *	Contains methods that support common file operations. Implement this interface
 *	if you'd like to receive notification that the user wants to
 *	do file-related stuff. This notification is usually sent from a toolbar or a menu.
 *	<p>
 *	An object which implements this interface can use a
 *	<a href="CommandFeature.html">CommandFeature</a> object to handle commands
 *	and have it call the right methods in this interface when necessary.
 *	This keeps command processing all in one place, where it can be easily
 *	reused and extended.
 *	<p>
 *	Several JNotepad classes support this interface:
 *	<ul>
 *	<li><a href="FileControl.html">FileControl</a>
 *	<li><a href="DiskFileControl.html">DiskFileControl</a>
 *	<li><a href="ClipboardControl.html">ClipboardControl</a>
 *	<li><a href="FeatureTabFileViewer.html">FeatureTabFileViewer</a>
 *	<li><a href="TabFileViewer.html">TabFileViewer</a>
 *	</ul>
 *
 *	@version	1.0, 7/14/97
 */

public interface IFileOperationTarget
{
	/**
	 *	Called when the user wants to create a new file.
	 */
	public void newFile();
	
	/**
	 *	Called when the user wants to open a new file.
	 */
	public boolean openFile();

	/**
	 *	Called when the user wants to save a file.
	 */
	public boolean saveFile();

	/**
	 *	Called when the user wants to save a file under a new name.
	 */
	public boolean saveFileAs();

	/**
	 *	Called when the user wants to close a file.	
	 */
	public boolean closeFile();

	/**
	 *	Called when the user wants to print a file.
	 */
	public void printFile();

	/**
	 *	Called when the user wants to perform a search and/or replace.
	 *
	 *	@param	isFind	true if the user wants to search for text, false if the 
	 *						user wants to replace text
	 */
	public void searchReplace(boolean isFind);	

	/**
	 *	Called when the user selects a command which is not a standard file
	 *	commands (i.e. one which does not have a matching method in this interface).
	 *
	 *	@param	command	Name of command which has been run
	 *	@param	evt	Event object associated with this command
	 *
	 *	@returns true if the command has been handled, and false if it has not.	 	 
	 */
	public boolean otherCommand(String command, UIActionEvent evt);
}

