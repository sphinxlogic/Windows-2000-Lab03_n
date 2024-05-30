//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import com.ms.ui.event.*;

/**
*	Feature plug in which handles the enabling and disabling of basic menu
*	items. It does this by listening to a text control and setting the
*	state of the commands accordingly. Descends from KeyFeature, which implements
*	listening on keystrokes. We also add support for mouse listening in this
*	class via the IUIMouseListener interface.
*
*	@see	ITextFeature
*	@see	KeyListener
*
*	@version	1.0, 7/16/97
*/

public class EnablerFeature extends KeyFeature implements IUIMouseListener
{
	/**
	*	Command feedback object. We send all requests for command enabling/disabling to this object.	
	*/
	protected ICommandFeedback commandObj;
	
	/**
	*	Creates a new EnablerFeature.
	*
	*	@param	commandobj	Command feedback object
	*/
	public EnablerFeature(ICommandFeedback commandobj)
	{
		textTarget = null;
		commandObj = commandobj;
	}
	
	/**
	*	Called to register the feature with a control. Sets up listeners	
	*	so any incoming mouse events or key events can be detected. 
	*	Part of the IFeature interface.
	*/
	public void register()
	{
		super.register();	// this adds keyboard listeners
		textTarget.addMouseListener(this);			
	}
	
	/**
	*	Called to unregister the feature. Removes all listeners on the edit control.
	*	Part of the IFeature interface.
	*/
	public void unregister()
	{
		super.unregister();
		textTarget.removeMouseListener(this);			
	}
	
	/**
	*	Called to reset the state of this feature. Since we don't hold any state,
	*	this method does nothing. Part of the IFeature interface.
	*/
	public void reset()
	{
	}
	
	/**
	*	Checks the state of the edit control we're attached to and determines
	*	which commands should be enabled and which should be disabled.
	*/
	public void checkCommandStatus()
	{
		boolean bCutCopyDelete = false;
		boolean bSelectFindReplace = false;
		boolean bPaste = true;
		boolean bUndo = false;
		boolean bRedo = false;
	
		if(textTarget==null)
			return;

		// if no text is selected, disable cut, copy, and delete. Otherwise,
		// enable them
		if (textTarget.getSelectionStart() == textTarget.getSelectionEnd()) 
		{
			bCutCopyDelete = false;
		}
		else
		{
			bCutCopyDelete = true;
		}
		
		if (textTarget.isReadOnly())
		{
			bPaste = false;
			bCutCopyDelete = false;
			bUndo = bRedo = false;
		}
		
		// !! check if we can make this algorithm nicer
		// check if we can undo or redo
		if (textTarget.isUndoable())
		{
			bUndo = true;
		}
		else
		{
			bUndo = false;
		}
		
		if (textTarget.isRedoable())
		{
			bRedo = true;
		}
		else
		{
			bRedo = false;
		}
		
		// if there's no text in the control, disable find/replace and
		// select all. Otherwise enable them.
		if (textTarget.getText().length() == 0)
		{
			bSelectFindReplace = false;
		}
		else
		{
			bSelectFindReplace = true;
		}
		
		// enable and disable the controls
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_CUT), bCutCopyDelete);
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_COPY), bCutCopyDelete);
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_PASTE), bPaste);
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_DELETE), bCutCopyDelete);
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_SELECT_ALL), bSelectFindReplace);
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_FIND), bSelectFindReplace);
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_REPLACE), bSelectFindReplace);
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_UNDO), bUndo);
		commandObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_REDO), bRedo);	
		
	}
	
	/**
	*	Called when a key is pressed but before it
	*	is released. Does nothing; we do all processing in keyReleased(). Part of IUIKeyListener. 
	*
	*	@param	ke	Key event being processed.
	*/
	public synchronized void keyPressed(UIKeyEvent ke)
	{
	}
	
	/**
	*	Called when a key is released. Calls checkCommandStatus() for command
	*	processing. Part of IUIKeyListener. 
	*
	*	@see	#checkCommandStatus
	*	@param	ke	Key event being processed.
	*/	
	public synchronized void keyReleased(UIKeyEvent ke)
	{
		checkCommandStatus();
	}
	
	/**
	*	Called when a key is typed (after it is released). Does nothing; we do all
	*	processing in keyReleased(). Part of IUIKeyListener. 
	*
	*	@param	ke	Key event being processed.
	*/	
	public synchronized void keyTyped(UIKeyEvent ke)
	{			
	}
	
	/**
	*	Called when the mouse button is clicked (pressed and released). Does nothing; we do all
	*	processing in mouseReleased(). Public IUIMouseListener method. 
	*
	*	@param evt Mouse event that occurred
	*/	
	public void mouseClicked(UIMouseEvent evt)
	{
	}
	
	/**
	*	Called when the mouse button is pressed. Does nothing; we do all
	*	processing in mouseReleased(). Public IUIMouseListener method. 
	*
	*	@param evt Mouse event that occurred	 
	*/
	public void mousePressed(UIMouseEvent evt)
	{
	}
	
	/**
	*	Called when the mouse button is released. Calls checkCommandStatus()
	*	for command processing. Public IUIMouseListener method. 
	*
	*	@param evt Mouse event that occurred	 
	*	@see	#checkCommandStatus
	*/	
	public void mouseReleased(UIMouseEvent evt)
	{
		checkCommandStatus();
	}
	
	/**
	*	Called when the mouse enters the control. Does nothing; we don't
	*	care about this event. Public IUIMouseListener method. 
	*
	*	@param evt Mouse event that occurred	 
	*/	
	public void mouseEntered(UIMouseEvent evt)
	{
		// don't care about this
	}
	
	/**
	*	Called when the mouse leaves the control. Does nothing; we don't
	*	care about this event. Public IUIMouseListener method. 
	*
	*	@param evt Mouse event that occurred	 
	*/	
	public void mouseExited(UIMouseEvent evt)
	{
		// don't care about this
	}
	
	
}