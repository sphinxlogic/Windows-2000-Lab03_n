//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.event.*;

/**
 *	Some classes don't support action listeners. This interface provides
 *	methods that will allow limited support of action listeners. This is
 *	made for interaction with CommandFeature by objects which don't support
 *	action listeners. See JNoteContextMenu for an example of how to use
 *	this interface.
 *
 *	@see	JNoteContextMenu
 *	@see	CommandFeature
 *
 *	@version	1.0, 8/14/97
 */

public interface IActionTalker 
{
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

}

