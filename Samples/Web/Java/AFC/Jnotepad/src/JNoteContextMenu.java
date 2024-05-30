//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.ui.event.*;
import java.util.*;
import java.awt.*;
import com.ms.fx.*;

/**
*	Right click Context menu for JNotepad. Sames as UIContextMenu, except
*	it adds support for loading from resources. 
*	This class works with CommandFeature to send user commands to the right place.
*	Since UIContextMenu (the class from which this class descends) has no support
*	for action listeners, we implement the IActionTalker interface, which provides us
*	with equivalent functionality.
*
*	@version	1.0, 8/4/97
*
*	@see		CommandFeature
*	@see		IActionTalker
*/

public class JNoteContextMenu extends UIContextMenu implements IActionTalker, ICommandFeedback
{
/**
*	Hashtable that stores objects that are listening to our commands	
	*/
	private Hashtable actionListenerTable;
	
	/**
	*	Hashtable that stores the menu items that we hold.
	*/
	protected Hashtable menuItemTable;
	
	
	/**
	*	Creates a new JNoteContextMenu.
	*
	*	@param	menulist	UIMenuList which contains the items in the context menu
	*/
	public JNoteContextMenu(UIMenuList menulist)
	{
		super(menulist);
		init(menulist);
	}
	
	/**
	*	Creates a new JNoteContextMenu.
	*
	*	@param	menulist	UIMenuList which contains the items in the context menu
	*	@param	comp		The component to be displayed in the control
	*/
	public JNoteContextMenu(IUIComponent comp, UIMenuList menulist)
	{
		super(comp, menulist);
		init(menulist);
	}
	
	/**
	*	Private init function. Initializes the actionListenerTable hashtable.
	*/
	private void init(UIMenuList menulist)
	{
		actionListenerTable = new Hashtable(5);
		menuItemTable = new Hashtable(5);
		addMenuListToTable(menulist);
	}
	
	/**
	*	Adds the elements in the UIMenuList to a private hashtable. This allows
	*	us to retrieve the elements quickly later and grab them by name. Used
	*	mainly for enabling and disabling menu items.
	*	
	*	@param	comp	Component to add to the menu
	*/
	private void addMenuListToTable(UIMenuList ml)
	{
		// iterate through all the items in the UIMenuList and add them
		// to the menuItemTable hash table.
		int iNumItems = ml.getComponentCount();
		for (int i=0; i < iNumItems; ++i)
		{
			IUIComponent comp = ml.getComponent(i);
			
			// we want to add just menu items, not UILine separators
			if (comp instanceof UIMenuItem)
			{
				menuItemTable.put(comp.getName(), comp);
			}
		}
	}
	
	/**
	*	Adds a Action listener object (one which implements IUIActionListener)
	*	to the ITextOperationTargetExt object.
	*
	*	@param	l	The object which will listen to Action events from this object.
	*/
	public void addActionListener(IUIActionListener l)
	{
		// add listener to table. We only care about the listener object, 
		// so we give it a dummy value to put into the table.
		actionListenerTable.put(l, new Object());
	}
	
	/**
	*	Removes the Action listener object from the ITextOperationTargetExt object.
	*
	*	@param	l	The object to remove an Action listener from.
	*/
	public void removeActionListener(IUIActionListener l)
	{
		// remove listener from table. Quick and easy with a hashtable.
		if (l != null)
		{
			actionListenerTable.remove(l);
		}
	}
	
	/**
	*	Handles events that happen in the context menu -- selection of commands
	*	by the user. Tells all of the listeners in the actionListenerTable that
	*	an event has occurred.
	*	
	*	@param	evt	Action Event that occurred.
	*	@param	what	Object it occurred to (i.e. the UIMenuItem that was selected)
	*	@returns	true if the event was handled, false if not
	*/
	public boolean action(Event evt, Object what)
	{
		
		if (!(what instanceof IUIComponent))
		{
			return false;
		}
		
		// grab all the items in the table, go through them, and call the
		// received an action event method in the listener object.
		// We adhere to the listener method names and interface for maximum
		// compatibility.

		Enumeration e = actionListenerTable.keys();
		while (e.hasMoreElements())
		{
			IUIActionListener l = (IUIActionListener)e.nextElement();
			
			// we call the actionPerformed method directly, rather than implictly
			// via a listener.
			l.actionPerformed(new UIActionEvent(this, UIActionEvent.ACTION_PERFORMED,
				(IUIComponent)what, ((UIComponent)what).getName()));
		}
		
		return true;
	}
	
	/**
	*	Called when a menu item needs to be enabled	or disabled. Finds the 
	*	item and changes its state. Part of the ICommandFeedback interface. 
	*
	*	@param	command	Name of menu item to enable or disable
	*	@param	on	true if menu item is to be enabled, false if not
	*/
	public void enableCommand(String command, boolean on)
	{
		Object m = menuItemTable.get(command);
		
		if (m != null)
		{
			((UIComponent)m).setEnabled(on);
		}
	}
	
	
	/**
	*	Queries the enabled state of a menu item. Part of the ICommandFeedback interface.
	*
	*	@param	command	Name of menu item to check
	*	@returns	true if menu item is enabled, false if it is not
	*/
	public boolean isEnabled(String command)
	{
		Object m = menuItemTable.get(command);
		
		if (m != null)
		{
			return ((UIComponent)m).isEnabled();
		}
		else
		{
			return true;
		}
	}
	
	/**
	*	Sets a checkbutton to be checked or unchecked. Part of the ICommandFeedback interface.
	*	
	*	@param	command	Name of menu item to check or uncheck
	*	@param	on	true if button is to be checked, false if it is to be unchecked
	*/
	public void setChecked(String command, boolean on)
	{
		Object m = menuItemTable.get(command);
		
		if ((m != null) && (m instanceof UICheckButton))
		{
			((UICheckButton)m).setChecked(on);
		}
	}
	
	/**
	*	Adds a filename to the Most Recently Used (MRU) submenu. Since this
	*	class doesn't maintain an MRU list, this does nothing.
	*
	*	@param	filename	Name of the file to add to the MRU list.
	*/
	public void addToMRUList(String filename)
	{
		// do nothing since we don't keep an MRU list
	}
	
	/**
	*	Called when a control in the system changes color. We don't care about
	*	color changes, so we do nothing.
	*
	*	@param	comp	Component who had a color change
	*	@param	color	Color that the component was changed to
	*	@param	whichPart	Which part of the component had a color change. This can
	*						be either FOREGROUND or BACKGROUND.
	*/		
	public void	notifyColorChange(Object comp, FxColor color, int whichPart)
	{
		// do nothing
	}
	
}


