//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.ui.event.*;
import java.awt.*;
import com.ms.ui.resource.*;
import java.util.Hashtable;
import com.ms.fx.FxColor;

/**
*	An extension of UIBand which adds some extra functionality and ease
*	of use features. JNoteMenubar supports loading in menus from resource
*	files, automatically places menu items in a Hashtable for easy access,
*	and supports a Most Recently Used (MRU) Files menu.
*	<p>
*	JNoteMenubar uses the ICommandFeedback interface to enabled and disable menu
*	items (as well as check and uncheck them). The easiest way to get command events
*	from a JNoteMenubar is to use a CommandFeature.
*
*	@see	#ICommandFeedback
*	@see	#CommandFeature
*
*	@version	1.0, 7/9/97
*/

public class JNoteMenubar extends UIBand implements IConstants, ICommandFeedback
{
	/**
	*	Hashtable to store menu items in, for easy access
	*/
	protected Hashtable menuItemTable;
	
	/**
	*	Menu items in most recently used files list	
	*/
	protected UIMenuItem MRUList[];
	
	/**
	*	Maximum number of files in the MRU list.	
	*/
	public static final int MENUBAR_MAX_MRU = 4;
	
	
	/**
	*	Creates a new, empty JNoteMenubar.
	*/
	public JNoteMenubar()
	{
		super();
		init();		
	}
	
	/**
	*	Creates a new JNoteMenubar and fills it with a menu from a resource file.
	*
	*	@param	name	Name of menubar
	*	@param	menuResource	Name of resource file (.res) to load menu from
	*	@param	menuID	integer resource ID of menu to load
	*/
	public JNoteMenubar(String name, String menuResource, int menuID)
	{
		super(name, BREAK);
		loadMenu(this, menuResource, menuID);
		init();
	}

	/**
	*	Creates a new JNoteMenubar and fills it with a menu from a resource file.
	*
	*	@param	name	Name of menubar
	*	@param	menuResource	Win32Resource decoder object to load resources from
	*	@param	menuID	integer resource ID of menu to load
	*/
	public JNoteMenubar(String name, Win32ResourceDecoder menuResource, int menuID)
	{
		super(name, BREAK);
		loadMenu(this, menuResource, menuID);
		init();
	}

	/**
	*	private init method. Initializes all variables and calls loadMenuItems()
	*	to load all menu items into the hashtable.
	*/
	private void init()
	{
		MRUList = null;
		menuItemTable = new Hashtable(23);
		
		loadMenuItems();
	}
	
	
	/**
	*	Goes through a menu, grabs all menu items,
	*	and puts them into the hashtable. Private helper function. 
	*	This function is called recursively on submenus.
	*
	*	@param	menulist	Menu list to traverse. 
	*/
	private void addItemsFromMenuList(UIMenuList menulist, UIMenuLauncher menulistOwner)
	{	
		if (menulist == null)
		{
			return;
		}

		UIComponent comp2 = null;	
		int iNumItems = menulist.getComponentCount();
		
		for (int j=0; j < iNumItems; ++j)
		{
			comp2 = (UIComponent)menulist.getComponent(j);									
			
			if (comp2.getName() != null)
			{
				String name = comp2.getName();
	
				menuItemTable.put(name, comp2);
				
				if (comp2 instanceof UIMenuLauncher)
				{
					UIMenuList ml = ((UIMenuLauncher)comp2).getMenu();
					
					if (ml != null)
					{
						addItemsFromMenuList(ml, (UIMenuLauncher)comp2);
					}
				}
			}
		}
	}
	
	/**
	*	Puts all of the items in the menu into a table. This allows us to
	*	have quick and easy access to menu items.
	*/
	public void loadMenuItems()
	{
		MRUList = new UIMenuItem[MENUBAR_MAX_MRU];
		menuItemTable.clear();
		
		int iNumComp = getComponentCount();
		
		if (iNumComp < 2)
		{
			return;
		}
		
		UIContainer comp = null;
		
		for (int i = 1; i < iNumComp; ++i)
		{
			comp = (UIContainer)getComponent(i);
			
			if ((comp instanceof UIMenuButton))
			{
				UIMenuList menulist = ((UIMenuButton)comp).getMenu();
				
				menuItemTable.put(comp.getName(), menulist);
				
				addItemsFromMenuList(menulist, (UIMenuLauncher)comp);
			}
		}
		
		//loadMRUList();			
	}
	
	/**
	*	Retrieves a menu item from the menu.
	*
	*	@param	name	Name of menu item to retrieve
	*	@returns	Menu item with the given name. Cast this to the proper type.
	*/
	public UIComponent getMenuItem(String name)
	{
		if (name == null)
		{
			return null;
		}
		
		return (UIComponent)menuItemTable.get(name);
	}
	
	/**
	*	Adds a submenu to the given menu item.
	*	
	*	@param	ml	UIMenuList to add to the menu item
	*/
	public boolean addSubmenuToMenu(String command, UIMenuList ml)
	{
		Object item = menuItemTable.get(command);
		
		if ((item != null) && (item instanceof UIMenuLauncher))
		{
			UIMenuLauncher mlaunch = (UIMenuLauncher)item;
		
			// add it to the menu item
			mlaunch.setMenu(ml);

			return true;
		}
		
		return false;
	}


	/**
	*	Adds a word wrap submenu to the given menu ID.
	*
	*	@param	itemID	Menu item ID to add submenu to
	*/
	public boolean addWordWrapSubmenu(String command)
	{
		// create a word wrap submenu
		UIMenuList ml = new UIMenuList();
		
		UIRadioButton noWrap = new UIRadioButton(JNotePad.loadString(ResourceIDs.IDS_NOWORDWRAP));
		UIRadioButton wordWrap = new UIRadioButton(JNotePad.loadString(ResourceIDs.IDS_WORDWRAP));
		UIRadioButton wordWrap2 = new UIRadioButton(JNotePad.loadString(ResourceIDs.IDS_WORDWRAP2));
		noWrap.setID(ResourceIDs.ID_NOWORDWRAP);
		wordWrap.setID(ResourceIDs.ID_WORDWRAP);
		wordWrap2.setID(ResourceIDs.ID_WORDWRAP2);
		
		ml.add(noWrap);
		ml.add(wordWrap);
		ml.add(wordWrap2);

		menuItemTable.put(noWrap.getName(), noWrap);
		menuItemTable.put(wordWrap.getName(), wordWrap);
		menuItemTable.put(wordWrap2.getName(), wordWrap2);

		return addSubmenuToMenu(command, ml);
	}

	/**
	*	Fills a menu with a menu retrieved from a resource file.
	*
	*	@param	menu	Menu to load into
	*	@param	menuResource	Name of resource file to load menu from
	*	@param	menuID	Integer resource ID of menu to load
	*
	*	@returns	true if the menu was loaded, false if not.
	*/
	static public boolean loadMenu(UIBand menu, String menuResource, int menuID)
	{
		Win32ResourceDecoder resdec;
		try
		{
			resdec = new Win32ResourceDecoder(menuResource);
		}
		catch (Exception e)
		{
			// menu init error
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGMENUINIT),
				UIMessageBox.STOP, UIButtonBar.OK);
			box.doModal();									
			
			return false;		
		}

		return loadMenu(menu, resdec, menuID);
	}

	static public boolean loadMenu(UIBand menu, Win32ResourceDecoder menuResource, int menuID)
	{
		try 
		{
			menuResource.populateMenu(menuID, menu);
		}
		catch (Exception e)
		{
			// internal menu error
			UIMessageBox box = new UIMessageBox(null, 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGMENULOAD),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			
			return false;
		}		
		
		return true;
	}

	
	/**
	*	Private method to load the MRU list from the JNoteSettings object
	*/
	private void loadMRUList()
	{
		JNoteSettings settingsObj = JNoteAppSettings.getSettingsObj();
		
		initMRUList();
		
		for (int i=1; i < MENUBAR_MAX_MRU+1; ++i)
		{
			String MRUfile = settingsObj.get("Menubar", "MRU"+i, null);
			if (MRUfile != null)
			{
				addMRUListEntry(MRUfile);
			}
		}								
	}
	
	/**
	*	Private method to initialize the MRU file list.
	*/
	private void initMRUList()
	{
		Object obj = menuItemTable.get("Recent Files");
		UIMenuList menulist = null;
		
		if (obj instanceof UIMenuList)
		{
			menulist = (UIMenuList)obj;
		}
		else if (obj instanceof UIMenuLauncher)
		{
			menulist = ((UIMenuLauncher)obj).getMenu();
		}
		else
		{
			return;
		}			
		
		if (menulist == null)
		{
			return;
		}
		
		if (menulist != null)
		{	
			MRUList[0] = (UIMenuItem)menulist.getComponent(0);
			
			menuItemTable.remove(MRUList[0].getName());
			
			MRUList[0].setName("1 ");
			
			for (int i = 1; i < MENUBAR_MAX_MRU; ++i)
			{
				MRUList[i] = new UIMenuItem((i+1)+" ");
				menulist.add(MRUList[i]);
			}
		}
	}
	
	
	/**
	*	Adds a filename to the Most Recently Used 
	*	(MRU) submenu. The last item in the list is discarded if this addition
	*	causes the list to overflow. Part of the ICommandFeedback feature. 
	*
	*	@param	filename	Name of the file to add to the MRU list.
	*/
	public void addToMRUList(String filename)
	{
		if (filename == null)
		{
			// internal error
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGINTERNALERR),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			
			return;
		}
		
		if (MRUList == null)
		{
			return;
		}
		
		addMRUListEntry(filename);
		
		JNoteSettings settings = JNoteAppSettings.getSettingsObj();
		
		for (int i = 0; i < MENUBAR_MAX_MRU; ++i)
		{
			String MRUfilename = MRUList[i].getName().substring(1);
			settings.put("Menubar", "MRU"+(i+1), MRUfilename);
		}			
	}
	
	
	/**
	*	Private function to actually add an entry to the MRU list. Does not
	*	update any JNoteSettings entries.
	*	
	*	@param	filename	Filename to add
	*/
	protected void addMRUListEntry(String filename)
	{	
		if (MRUList == null)
		{
			return;
		}
		
		if (filename == null)
		{
			return;
		}
		
		for (int i = 0; i < MENUBAR_MAX_MRU; ++i)
		{
			if (MRUList[i].getName().substring(2).equals(filename))
			{
				return;
			}
		}
		
		JNoteSettings settings = JNoteAppSettings.getSettingsObj();
		
		for (int i = MENUBAR_MAX_MRU-1; i > 0; --i)
		{
			String MRUfilename = MRUList[i-1].getName().substring(1);
			MRUList[i].setName((i+1) + MRUfilename);
			settings.put("Menubar", "MRU"+(i+1), MRUfilename);
		}
		
		MRUList[0].setName("1 "+filename);
		settings.put("Menubar", "MRU1", filename);
	}
	
	
	/**
	*	Called when a menu item needs to be enabled
	*	or disabled. Finds the item and changes its state. Part of the ICommandFeedback feature.
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
	*	Queries the enabled state of a menu item. Part of the ICommandFeedback feature.
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
	*	Sets a checkbutton to be checked or unchecked. Part of the ICommandFeedback feature.
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
	*	Called when a control in the system changes color. Since we don't care
	*	about color changes, we do nothing.
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
