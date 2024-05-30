//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import com.ms.ui.event.IUIKeyListener;
import com.ms.ui.event.UIActionEvent;
import com.ms.fx.FxFont;

/**
 *	Contains methods that support common text operations. Implement this interface
 *	if you'd like to receive notification that the user wants to
 *	do edit control text-related stuff. This notification is usually sent from 
 *	a toolbar or a menu.
 *	<p>
 *	An object which implements this interface can use a
 *	<a href="CommandFeature.html">CommandFeature</a> object to handle commands
 *	and have it call the right methods in this interface when necessary.
 *	This keeps command processing all in one place, where it can be easily
 *	reused and extended.
 *	<p>
 *	Several JNotepad classes support this interface:
 *	<ul>
 *	<li><a href="TabFileViewer">TabFileViewer</a>
 *	<li><a href="FeatureTabFileViewer.html">FeatureTabFileViewer</a>
 *	<li><a href="JNoteUIEdit.html">JNoteUIEdit</a>
 *	</ul>
 *
 *	@version	1.0, 7/15/97
 */

public interface ITextOperationTarget
{
	/**
	 *	Called when the user wishes to undo the previous action.
	 */
	public boolean undo();

	/**
	 *	Called when the user wishes to redo the previously undone action.
	 */
	public boolean redo();

	/**
	 *	Called when the user wishes to cut text.
	 */
	public void cut();

	/**
	 *	Called when the user wishes to copy text.
	 */	
	public void copy();

	/**
	 *	Called when the user wishes to paste text.
	 */	
	public void paste();

	/**
	 *	Called when the user wishes to delete text.
	 */	
	public void delete();

	/**
	 *	Called when the user wishes to select all text.
	 */	
	public void selectAll();


	/**
	 *	Called when the user wishes to change the foreground color.
	 */	
	public void changeTextColor();

	/**
	 *	Called when the user wishes to change the background color.
	 */	
	public void changeBackColor();

	/**
	 *	Called when the user wishes to change the current font.
	 */		
	public void changeFont();

	/**
	 *	Called when the user wishes to change the current font to a given font.
	 *
	 *	@param	font	Font the user wishes to change to.
	 */		
	public void changeFont(FxFont font);

	/**
	 *	Called when the user wishes to change the horizontal alignment.
	 *
	 *	@param	h	Horizontal alignment style, defined in the IFxTextConstants interface.
	 */		
	public void setHorizAlign(int h);

	/**
	 *	Causes the ITextOperationTarget to receive the input focus.
	 */
	public void requestFocus();

	/**
	 *	Queries if the ITextOperationTarget may receive the input focus.
	 */
	public boolean isKeyable();

	/**
	 *	Called when the user selects a command which is not a standard text
	 *	commands (i.e. one which does not have a matching method in this interface).
	 *
	 *	@param	command	Name of command which has been run
	 *	@param	evt	Event object associated with this command
	 *
	 *	@returns true if the command has been handled, and false if it has not.	 
	 */
	public boolean otherCommand(String command, UIActionEvent evt);

}
