//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.ui.event.*;
import java.util.*;

/**
*	JNotepad specific extension of CommandFeature. Using the ICommandFeature
*	and ICommandFeedback interfaces, this module allows a program to handle
*	command processing and routing quickly and easily, as well as command item 
*	enabling and disabling. 
*
*	@see	IFeature
*	@see	ICommandFeedback
*	@see	IComponentFeature
*	@see	CommandFeature
*
*	@version	1.0, 8/6/97
*/

public class JNoteCommandFeature extends CommandFeature
{		
		
	/**
	*	Creates a new JNoteCommandFeature.
	*/
	public JNoteCommandFeature()
	{
		super();
	}
	
	
	/**
	*	Private function. Goes through all of the known general file commands
	*	(those defined in the IFileOperationTarget
	*	interface) and calls appropriate methods in that interface
	*	if the command is found. If none of these are found, it calls the
	*	otherCommand() method to see if the command is an application-specific one.
	*
	*	@param	name	Name of command
	*	@param	evt		Event object which generated this command
	*	@returns	true if the command was handled, false if not
	*/
	private boolean checkFileCommands(String name, UIActionEvent evt)
	{
		IUIComponent comp=evt.getActionItem();
		switch( comp.getID() )
		{
		case ResourceIDs.ID_FILE_NEW:
			return doFileNew();
		case ResourceIDs.ID_FILE_OPEN:
			return doFileOpen();
		case ResourceIDs.ID_FILE_SAVE:
			return doFileSave();
		case ResourceIDs.ID_FILE_SAVEAS:
			return doFileSaveAs();
		case ResourceIDs.ID_FILE_CLOSE:
			return doFileClose();
		case ResourceIDs.ID_FILE_PRINT:
			return doFilePrint();

		case ResourceIDs.ID_EDIT_FIND:
			return doEditFind();
		case ResourceIDs.ID_EDIT_REPLACE:
			return doEditReplace();
		} 
		return fileTarget.otherCommand(name, evt);						
	}
	
	/**
	*	Private function. Goes through all of the known general text commands
	*	(those defined in the ITextOperationTarget 
	*	interface) and calls appropriate methods in that interface
	*	if the command is found. If none of these are found, it calls the
	*	otherCommand() method to see if the command is an application-specific one.
	*
	*	@param	name	Name of command
	*	@param	evt		Event object which generated this command
	*	@returns	true if the command was handled, false if not
	*/
	private boolean checkTextCommands(String name, UIActionEvent evt)
	{
		IUIComponent comp=evt.getActionItem();
		switch( comp.getID() )
		{
		case ResourceIDs.ID_EDIT_UNDO:
			return doEditUndo();

		case ResourceIDs.ID_EDIT_REDO:
			return doEditRedo();

		case ResourceIDs.ID_EDIT_CUT:
			return doEditCut();

		case ResourceIDs.ID_EDIT_COPY:
			return doEditCopy();

		case ResourceIDs.ID_EDIT_PASTE:
			return doEditPaste();

		case ResourceIDs.ID_EDIT_DELETE:
			return doEditDelete();

		case ResourceIDs.ID_EDIT_SELECT_ALL:
			return doEditSelectAll();

		case ResourceIDs.ID_FONT:
			return doFont();

		case ResourceIDs.ID_TEXTCOLOR:
			return doTextColor();

		case ResourceIDs.ID_BGCOLOR:
			return doBackgroundColor();
		}
		return textTarget.otherCommand(name, evt);						
	}
	
	/**
	*	Called when an action event
	*	occurs in one of the talker components. Processes the command through
	*	<a href="#checkTextCommands">checkTextCommands</a> and
	*	<a href="#checkFileCommands">checkFileCommands</a>. 
	*	Part of the IUIActionListener interface. 
	*
	*	@param	evt	UIActionEvent which occurred.
	*/
	public void actionPerformed(UIActionEvent evt)
	{
		String name = evt.getActionCommand();
		
		if (name == null)
		{
			return;
		}
		
		boolean ret = false;
		
		if (fileTarget != null)
		{
			ret = checkFileCommands(name, evt);
		}
		
		if ((textTarget != null) && (ret == false))
		{
			checkTextCommands(name, evt);
		}
		
		textTarget.requestFocus();
	}

	protected boolean doFileNew()
	{
		fileTarget.newFile();
		return true;
	}

	protected boolean doFileOpen()
	{
		fileTarget.openFile();
		return true;
	}

	protected boolean doFileSave()
	{
		fileTarget.saveFile();
		return true;
	}

	protected boolean doFileSaveAs()
	{
		fileTarget.saveFileAs();
		return true;
	}

	protected boolean doFileClose()
	{
		fileTarget.closeFile();
		return true;
	}

	protected boolean doEditFind()
	{
		fileTarget.searchReplace(true);
		return true;
	}

	protected boolean doEditReplace()
	{
		fileTarget.searchReplace(false);
		return true;
	}

	protected boolean doFilePrint()
	{
		fileTarget.printFile();
		return true;
	}

	protected boolean doEditUndo()
	{
		textTarget.undo();
		return true;
	}

	protected boolean doEditRedo()
	{
		textTarget.redo();
		return true;
	}

	protected boolean doEditCut()
	{
		textTarget.cut();
		return true;
	}

	protected boolean doEditCopy()
	{
		textTarget.copy();
		return true;
	}

	protected boolean doEditPaste()
	{
		textTarget.paste();
		return true;
	}

	protected boolean doEditDelete()
	{
		textTarget.delete();
		return true;
	}

	protected boolean doEditSelectAll()
	{
		textTarget.selectAll();
		return true;
	}

	protected boolean doFont()
	{
		textTarget.changeFont();
		return true;
	}

	protected boolean doTextColor()
	{
		textTarget.changeTextColor();		
		return true;
	}

	protected boolean doBackgroundColor()
	{
		textTarget.changeBackColor();
		return true;
	}
}
