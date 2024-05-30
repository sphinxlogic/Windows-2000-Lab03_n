//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.event.*;
import java.awt.*;
import com.ms.fx.*;

/**
*	Extends ITextOperationTarget to add some methods that are specific to
*	objects which act like edit controls. Use this if you have a class which handles
*	the generic text operations in ITextOperationTarget but also acts more
*	like an edit control. Using this interface allows one to use edit controls
*	without relying on a specific class -- one can plug in another class which uses
*	this same interface, and things should work without a problem.
*
*	@see	ITextOperationTarget
*
*	@version	1.0, 7/15/97
*/

public interface ITextOperationTargetExt extends ITextOperationTarget
{
	/**
	*	Sets the text in the object.
	*
	*	@param text	String containing the new text.
	*/
	public void setText(String text);
	
	/**
	*	Returns the text in the object.
	*
	*	@returns String	text contained in the object.
	*/
	public String getText();
	
	/**
	*	Inserts text at the given character offset from the beginning of 
	*	the object's text.
	*
	*	@param	text	Text to insert
	*	@param	iPos	Zero-based character offset (from the beginning of the
	*						object's text) to insert the text at.
	*/
	public void insertText(String text, int iPos);
	
	/**
	*	Appends text to the end of the object's text.
	*
	*	@param	text	String to append
	*/
	public void appendText(String text);
	
	/**
	*	Retrieves the font used in the object.
	*
	*	@returns	Font object used in the object's text field.
	*/
	public Font getFont();
	
	/**
	*	Sets the background color.
	*	
	*	@param	color	Color to set the background to.
	*/
	public void setTextColor(FxColor color);
	
	/**
	*	Sets the foreground color.
	*	
	*	@param	color	Color to set the foreground to.
	*/
	public void setBackColor(FxColor color);	
	
	/**
	*	Retrieves the foreground color.
	*	
	*	@returns	Color of the foreground.
	*/
	public FxColor getTextColor();	
	
	/**
	*	Retrieves the background color.
	*	
	*	@returns	Color of the background.
	*/
	public FxColor getBackColor();
	
	/**
	*	Pastes text from the clipboard at the current position in the object's
	*	text field.
	*
	*	@param	text	String to paste into the object
	*/
	public void paste(String text);
	
	
	/**
	*	Retrieves the character indexed position of the caret.
	*
	*	@returns	zero-based index into the object's text.
	*/
	public int getCaretIndex();
	
	/**
	 *	Moves the caret.
	 *
	 *	@param	idx	Zero-based character index to move the caret to.
	 */
	public void moveTheCaret(int idx);
	
	/**
	*	Retrieves the beginning index of selected text.	
	*
	*	@returns	the zero-based index where selection begins. If there is no
	*					selected text, this value is equal to the that returned
	*					by getSelectionEnd()
	*/
	public int getSelectionStart();
	
	/**
	*	Retrieves the ending index of selected text.	
	*
	*	@returns	the zero-based index where selection ends. If there is no
	*					selected text, this value is equal to the that returned
	*					by getSelectionStart()
	*/	
	public int getSelectionEnd();
	
	/**
	*	Sets the selected text to the given range.
	*
	*	@param	selStart	the zero-based index which marks the beginning of the text to be selected
	*	@param	selEnd		the zero-based index which marks the end of the text to be selected
	*/
	public void setSelection(int selStart, int selEnd);
	
	/**
	*	Retrieves the window coordinates of the character at the given position.
	*
	*	@param	iPos	The zero-based index of the character
	*	@returns	The control-relative coordinates of the character.
	*/
	public Point getCharLocation(int iPos);
	
	/**
	*	Retrieves the character index closest to the given point.
	*
	*	@param	scrnPos	Point at which to find the character position
	*	@returns	The index of the character at the given point.
	*/
	public int getCharFromScreen(Point scrnPos);
	
	/**
	*	Checks if the previous action can be undone.
	*	
	*	@returns	true if the previous action can be undone, false if not
	*/
	public boolean isUndoable();
	
	/**
	*	Checks if the previous undo can be redone.
	*	
	*	@returns	true if the previous undo can be redone, false if not
	*/
	public boolean isRedoable();
	
	/**
	*	Adds a Key listener object (one which implements IUIKeyListener)
	*	to the ITextOperationTargetExt object.
	*
	*	@param	l	The object which will listen to key events from this object.
	*/
	public void addKeyListener(IUIKeyListener l);
	
	/**
	*	Removes the Key listener object from the ITextOperationTargetExt object.
	*
	*	@param	l	The object to remove a key listener from.
	*/
	public void removeKeyListener(IUIKeyListener l);
	
	/**
	*	Adds a Mouse listener object (one which implements IUIMouseListener)
	*	to the ITextOperationTargetExt object.
	*
	*	@param	l	The object which will listen to Mouse events from this object.
	*/	
	public void addMouseListener(IUIMouseListener l);
	
	/**
	*	Removes the Mouse listener object from the ITextOperationTargetExt object.
	*
	*	@param	l	The object to remove a Mouse listener from.
	*/
	public void removeMouseListener(IUIMouseListener l);
	
	/**
	*	Adds a MouseMotion listener object (one which implements IUIMouseMotionListener)
	*	to the ITextOperationTargetExt object.
	*
	*	@param	l	The object which will listen to MouseMotion events from this object.
	*/	
	public void addMouseMotionListener(IUIMouseMotionListener l);
	
	/**
	*	Removes the MouseMotion listener object from the ITextOperationTargetExt object.
	*
	*	@param	l	The object to remove a MouseMotion listener from.
	*/
	public void removeMouseMotionListener(IUIMouseMotionListener l);
	
	/**
	*	Adds a Action listener object (one which implements IUIActionListener)
	*	to the ITextOperationTargetExt object.
	*
	*	@param	l	The object which will listen to Action events from this object.
	*/
	public void addActionListener(IUIActionListener l);
	
	/**
	*	Removes the Action listener object from the ITextOperationTargetExt object.
	*
	*	@param	l	The object to remove an Action listener from.
	*/
	public void removeActionListener(IUIActionListener l);
	
	/**
	*	Adds a Text listener object (one which implements IUITextListener)
	*	to the ITextOperationTargetExt object.
	*
	*	@param	l	The object which will listen to Text events from this object.
	*/	
	public void addTextListener(IUITextListener l);
	
	/**
	*	Removes the Text listener object from the ITextOperationTargetExt object.
	*
	*	@param	l	The object to remove a Text listener from.
	*/	
	public void removeTextListener(IUITextListener l);
	
	
	/**
	*	Sends an Event message to the object.
	*
	*	@param	evt	The Event object to send
	*	@returns	if false, event is posted to object's parent.
	*/
	public boolean postEvent(Event evt);
	
	/**
	*	Sets the object to be read only
	*
	*	@param	ro	true if the file is to be set to read only, false if it is to be writable
	*/
	public void setReadOnly(boolean ro);
	
	/**
	*	Checks if the object is read only	
	*	
	*	@returns	true if the object is read only, false if not
	*/
	public boolean isReadOnly();
	
	/**
	*	Sets the ICommandFeedback object for this object. ICommandFeedback objects
	*	are used to disable user commands.
	*
	*	@see	ICommandFeedback
	*	@param	ICommandFeedback object to attach to this object
	*/
	public void setFeedbackObject(ICommandFeedback compFeedback);
	
	/**
	*	Sets the IComponentFeature object for this object. IComponentFeature objects
	*	are used to handle user commands.
	*
	*	@see	IComponentFeature
	*	@param	IComponentFeature object to attach to this object
	*/
	public void setCommandObject(IComponentFeature compfeature);
	
	
	/**
	*	Redraws the object.
	*/
	public void repaint();	
}

