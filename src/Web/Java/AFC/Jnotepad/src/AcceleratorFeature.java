//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import JNoteKeyFeature;
import com.ms.ui.event.*;
import java.awt.event.*;
import java.awt.*;
import com.ms.ui.*;
import java.util.Hashtable;

/**
*	IFeature plugin. Intercepts accelerator keys (also known as shortcut keys)
*	from the text area and converts them into menu item events. 
*
*	@see	IFeature
*	@see	IKeyFeature
*	@see	JNoteKeyFeature
*
*	@version	1.0, 7/23/97
*/

public class AcceleratorFeature extends JNoteKeyFeature
{
	/**
	*	Hashtable to hold keys-event pairs for control-key combinations	
	*/
	protected Hashtable controlKeysTable;
	
	/**
	*	Hashtable to hold keys-event pairs for shift-control-key combinations	
	*/
	protected Hashtable shiftCtrlKeysTable;
	
	/**
	*	Component to send events to	
	*/
	protected UIComponent eventTarget;
	
	
	/**
	*	Object which handles feedback (components telling menu bars/toolbars what to gray out)
	*/
	protected ICommandFeedback feedbackObj;
	
	/**
	*	Creates a new AcceleratorFeature which sends events to the given target
	*
	*	@param	eventtarget	UIComponent to send command selection events to
	*/
	public AcceleratorFeature(UIComponent eventtarget)
	{
		localInit(eventtarget, null);
	}	
	/**
	*	Creates a new AcceleratorFeature which sends events to the given target
	*
	*	@param	eventtarget	UIComponent to send command selection events to
	*	@param	feedbackobj	Object which handles command feedback - enabling and disabling menu items
	*/
	public AcceleratorFeature(UIComponent eventtarget, ICommandFeedback feedbackobj)
	{
		localInit(eventtarget, feedbackobj);
	}	
	
	/**
	*	Private init function. Handles initialization of variables. 
	*/
	private void localInit(UIComponent eventtarget, ICommandFeedback feedbackobj)
	{
		controlKeysTable = new Hashtable(11);
		shiftCtrlKeysTable = new Hashtable(11);
		eventTarget = eventtarget;
		feedbackObj = feedbackobj;
	}
	
	/**
	*	Adds an accelerator key.
	*
	*	@param	accelKey	key to add to accelerator list.
	*	@param	action		Name of command to activate when accelerator key is pressed.
	*	@param	hasShift	false if the command requires control to be held with the accelerator key,
	*							true if the command requires control and shift to be held down.
	*/
	public void addAccelerator(char accelKey, String action, boolean hasShift)
	{		
		// convert to uppercase and place in Character object
		Character e1 = new Character(Character.toUpperCase(accelKey));
		// create a new action event which will simulate clicking on the
		//		menu item/toolbar button.
		Event e2 = new Event(eventTarget, 0, Event.ACTION_EVENT, 0, 0,
			0, 0, new UIMenuItem(action));
		
		// put key-event pair in the right hashtable
		if (!hasShift)
		{
			controlKeysTable.put(e1, e2);
		}
		else
		{
			shiftCtrlKeysTable.put(e1, e2);
		}
	}
	
	/**
	*	Removes an accelerator key.
	*
	*	@param	accelKey	Key to remove
	*	@param	hasShift	true if removing from control-shift-key accelerator list,
	*							false if from the control-key acclerator list.
	*/
	public void removeAccelerator(char accelKey, boolean hasShift)
	{
		controlKeysTable.remove(new Character(accelKey));
	}
	
	/**
	*	Called when a key is pressed. Part of IUIKeyListener. Finds out if an
	*	accelerator key has been pressed; if so, find the Event associated with
	*	it and send it to the event target.
	*
	*	@param	ke	KeyEvent which is being handled
	*/
	public synchronized void keyPressed(UIKeyEvent ke)
	{
		int iModifiers = ke.getModifiers();
		
		if ((iModifiers & UIInputEvent.CTRL_MASK) > 0)
		{
			// it's a control-key combo
			Character e1 = new Character((char)ke.getKeyCode());
			Event e = null;
			
			// pull Event out of right table
			if ((iModifiers & UIInputEvent.SHIFT_MASK) == 0)
			{
				e = (Event)controlKeysTable.get(e1);
			}
			else
			{
				e = (Event)shiftCtrlKeysTable.get(e1);
			}
			
			// Send a item selected message to the
			// attached event target
			if (e != null)
			{
				// if there's a feedback object, ask it if the item is
				// disabled.
				if (feedbackObj != null) 
				{
					if (!feedbackObj.isEnabled(((UIComponent)e.arg).getName()))
					{
						// not enabled, so don't do anything
						return;
					}
				}
				
				try
				{
					int i = Integer.parseInt(((UIComponent)e.arg).getName());
					((IUIComponent)e.arg).setID(i);
				}
				catch ( Exception ex )
				{
				}

				// send the event to the right place
				eventTarget.postEvent(e);
			}
		}
		
	}
	
	/**
	*	Resets the feature; done when it is removed from
	*	an edit control. Does nothing since there is no state to reset.
	*	Part of IFeature. 
	*/
	public void reset()
	{
		// no need to do anything. Accelerator keys don't
		// change between files.
	}
	
}

