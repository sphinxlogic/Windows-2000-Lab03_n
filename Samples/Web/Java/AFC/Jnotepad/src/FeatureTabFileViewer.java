//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.util.Vector;
import java.util.Enumeration;
import java.io.*;
import java.awt.*;

import com.ms.ui.*;
import com.ms.ui.event.*;
import java.awt.event.*;
import java.util.Date;

/**
*	FeatureTabFileViewer is an extension of TabFileViewer which supports
*	features. Features are classes which adhere to the IFeature interface.
*	IFeature provides a framework for adding features and functionality to
*	a program without touching the original program at all. It also allows
*	one to mix and match features easily and flexibly. Many of FeatureTabFileViewer's
*	functionality is implemented as features. 
*	<p>
*	FeatureTabFileViewer provides support for:
*	<ul>
*	<li>dirty file marking
*	<li>accelerator keys
*	<li>status bar
*	<li>autosave
*	<li>right-button context menu
*	</ul>
*	
*	@see	IFeature
*	@see	TabFileViewerer
*	@version	1.0, 7/10/97
*/

public class FeatureTabFileViewer extends TabFileViewer implements IConstants
{
	/**
	*	Thread which automatically saves all open files periodically
	*/
	private AutosaveThread autosaveThread;		
	
	/**
	*	Thread which handles and runs feature plugins
	*/
	private FeatureThread featureThread;
	
	/**
	*	Feature which handles enabling and disabling of menu items
	*/
	protected ICommandFeedback feedbackObj;

	/**
	*	Feature which handles command processing
	*	
	*/
	protected IComponentFeature	compFeature;

	/**
	*	Right button context menu
	*/
	protected JNoteContextMenu tabContextMenu;
	
	/**
	*	Creates a new FeatureTabViewer.	
	*	
	*	@param	parFrame	Parent frame window
	*	@param	feedback	ICommandFeedback interface used for command processing
	*/
	public FeatureTabFileViewer(UIFrame parFrame, ICommandFeedback feedback, IComponentFeature compFeature)
	{
		this(parFrame, null, feedback, compFeature);
	}
	
	/**
	*	Creates a new FeatureTabViewer.	
	*	
	*	@param	parFrame	Parent frame window
	*	@param	menubar		Menu used as the target of accelerator commands
	*	@param	feedback	ICommandFeedback interface used for command processing
	*/
	public FeatureTabFileViewer(UIFrame parFrame, UIBand menubar, ICommandFeedback feedback, IComponentFeature compobj)
	{			
		super(parFrame);

		feedbackObj = feedback;
		compFeature = compobj;
		tabContextMenu = null;
		
		autosaveThread = new AutosaveThread(this, 15000);
		//autosaveThread.start();			
		
		featureThread = new FeatureThread(this);
		featureThread.start();
		
		enableAccelerators(menubar);

		EnablerFeature enablerFeature = new EnablerFeature(feedbackObj);
		registerListener(enablerFeature);
		
		loadListeners();			
		enablerFeature.checkCommandStatus();
		createTabContextMenu();
	}
	
	/**
	*	Adds a feature to the current file. It is not activated until
	*	the features are loaded via loadListeners(). This calls the registerListeners()
	*	method in the feature thread.
	*
	*	@see	#loadListeners
	*	@see	FeatureThread#registerListener
	*	
	*	@param	fl	The feature to add
	*/
	protected void registerListener(IFeature fl)
	{
		featureThread.registerListener(fl);
	}
	
	/**
	*	Loads and enables the current set of features on the current file.	
	*	Calls loadListeners in the feature thread.
	*
	*	@see	FeatureThread#loadListeners
	*/
	protected void loadListeners()
	{
		if(getFileTarget()!=null)
			featureThread.loadListeners(getFileTarget());
	}
	
	/**
	*	Unloads all listeners enabled on the current file. Calls removeListeners
	*	in the feature thread.
	*
	*	@see	FeatureThread#removeListeners	
	*/
	protected void removeListeners()
	{
		featureThread.removeListeners();
	}
	
	/**
	*	Enables a DirtyFlagFeature on the current file if the file is dirty.
	*	Calls attachDirtyFlagListener in the feature thread.
	*
	*	@see	FeatureThread#attachDirtyFlagListener
	*/
	protected void attachDirtyFlagListener()
	{
		featureThread.attachDirtyFlagListener(getFileTarget());
	}
	
	/**
	*	Adds a status bar to a panel and attaches it to the current file's
	*	edit control. Usually used by obtaining the panel the edit control
	*	resides on and passing that panel to this function so that the
	*	status bar is placed below it. The status bar is implemented as
	*	an IFeature feature plugin.
	*	
	*	@parem	panel	UIPanel to place the status bar on. The status bar is placed
	*					in the south end of this panel.
	*/
	private void addStatusBar(UIPanel panel)
	{
		JNoteUIStatus statusbar = new JNoteUIStatus("");
		panel.add(statusbar, "south");
		
		statusbar.init(getFileTarget().getEditControl());
		statusbar.register();			
	}
	
	/**
	*	Adds accelerator support to the system. Creates an AcceleratorFeature object
	*	and loads it with accelerators from the JNoteSettingsObject. The feature is
	*	the registered as a feature.
	*
	*	@param	menubar	The UIComponent to send command events to.
	*/
	private void enableAccelerators(UIComponent menubar)
	{
		if (menubar == null)
			return;
		
		AcceleratorFeature accel = new AcceleratorFeature(menubar, feedbackObj);
		
		JNoteAppSettings.getSettingsObj().loadAccelerators(accel);
		
		registerListener(accel);		
	}
	
	/**
	*	Enables or disables a command. Runs the enableCommand method in the
	*	local ICommandFeedback object. Part of the ICommandFeedback interface. 
	*/
	protected void enableCommand(String command, boolean on)
	{
		if (feedbackObj != null)
		{
			feedbackObj.enableCommand(command, on);
		}
	}
	
	/**
	*	Adds a new file tab to the viewer. Calls the parent addNewFileTab method,
	*	sets component and command objects on the current edit controls, and adds
	*	a status bar.
	*	
	*	@param	path	Path of file which will be loaded into the new tab
	*	@param	name	Name of file which will be loaded into the new tab
	*/	
	public UIPanel addNewFileTab(String path, String name)
	{
		UIPanel panel = null;
		
		if ((panel = super.addNewFileTab(path, name)) != null)
		{											
			addStatusBar(panel);
			
			return panel;
		}
		else
		{
			return null;
		}
	}

	/*
	public void addClipboardTab()
	{
		System.out.println(feedbackObj);

		super.addClipboardTab();

		ITextOperationTargetExt editControl = getFileTarget().getEditControl();

		editControl.setFeedbackObject(feedbackObj);
		editControl.setCommandObject(compFeature);
	}
	*/

	protected void initNewTab()
	{
		super.initNewTab();

		ITextOperationTargetExt editControl = getFileTarget().getEditControl();

		editControl.setFeedbackObject(JNoteAppCommandFeature.getCommandFeedback());
		editControl.setCommandObject(JNoteAppCommandFeature.getCompFeature());
	}
	
	/**
	*	Creates a context menu to be displayed when the user right clicks on
	*	a tab. Also adds the menu to the list of items that compFeature
	*	is listening to for command events.
	*/
	private void createTabContextMenu()
	{

		UIMenuList ml = new UIMenuList();
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_NEW, ResourceIDs.ID_FILE_NEW ));
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_OPEN, ResourceIDs.ID_FILE_OPEN ));
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_SAVE, ResourceIDs.ID_FILE_SAVE ));
		ml.add(new UILine());					
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_CLOSE, ResourceIDs.ID_FILE_CLOSE ));

		tabContextMenu = new JNoteContextMenu(ml);
		
		compFeature.addTalker(tabContextMenu);
	}
	
	/**
	*	Displays the tab context menu at the specifed screen coordinates.
	*
	*	@param	x	x coordinate of the point to display the menu, relative to the upper left corner of the screen
	*	@param	y	y coordinate of the point to display the menu, relative to the upper left corner of the screen
	*/
	protected void showTabContextMenu(int x, int y)
	{			
		Point pt = parentFrame.getLocation();
		Point edit = getLocation(parentFrame);		

		tabContextMenu.launchAt(x+pt.x+edit.x, y+pt.y+edit.y, parentFrame);		
	}
	
	/**
	*	Saves all modified open files. Does not save untitled files. Called
	*	by the feature thread.
	*
	*	@see	FeatureThread#run
	*/
	public void saveAll()
	{			
		// grabs the tabs in the viewer. 
		UITabList tablist = (UITabList)getComponent(0);	
		UITab tab = null;
		int i = 0;
		
		Enumeration e = loadedFiles.elements();
		
		// go through all the files
		while (e.hasMoreElements())
		{
			IFileOperationTargetExt  fc = (IFileOperationTargetExt )e.nextElement();
			
			// if the file is dirty and has a name we can save under, save it
			if (fc.isDirty() && (fc.getFileName() != null))
			{
				fc.saveFile();
				
				// refresh the tab so the dirty flag gets removed
				tab = (UITab)tablist.getComponent(i);
				refreshTab(tab, fc);
			}
			
			++i;
		}
		
	}
	
	/**
	*	Handles incoming events. Removes and reloads the listeners when the
	*	current tab changes, and displays the context menu when the right button
	*	is pressed. All other events are sent to the paren.
	*
	*	@param	e	Event to handle.	
	*/
	public boolean handleEvent(Event e)
	{			
		boolean ret = false;
		
		if ((e.arg instanceof UITab) && (e.id == Event.LIST_SELECT))
		{
			removeListeners();
			
			ret = super.handleEvent(e);
			
			loadListeners();
		}
		else if ((e.id == Event.MOUSE_UP) && (e.modifiers == Event.META_MASK))
		{
			showTabContextMenu(e.x, e.y);			
		}
		else
		{
			return super.handleEvent(e);
		}
		
		return ret;
	}
	
	
	// overriding TabFileViewer's file i/o commands to update the dirty flag listener
	
	/**
	*	Overrides saveFile() to add dirty flag support. Runs the parent's
	*	saveFile method; if the dirty bit changes after the save (from dirty
	*	to clean), attach a dirty flag listener and refresh the tab.
	*	
	*	@see	TabFileViewer#saveFile
	*/
	public boolean saveFile()
	{
		boolean bIsDirty = getFileTarget().isDirty();
		
		boolean ret = super.saveFile();
		
		// if dirty bit changed (from dirty to clean), attach a listener
		// The dirty bit can only go from dirty to clean after a save, but
		// may stay dirty if the save was cancelled. It can never go from clean to dirty
		// after a save
		if (bIsDirty != getFileTarget().isDirty())
		{
			attachDirtyFlagListener();
			refreshCurrentTab();
		}
		
		return ret;
	}
	
	/**
	*	Overrides saveFileAs() to add dirty flag support. Runs the parent's
	*	saveFileAs method; if the dirty bit changes after the save (from dirty
	*	to clean), attach a dirty flag listener and refresh the tab.
	*	
	*	@see	TabFileViewer#saveFileAs
	*/
	public boolean saveFileAs()
	{
		boolean bIsDirty = getFileTarget().isDirty();
		
		boolean ret = super.saveFileAs();			
		
		// if dirty bit changed (from dirty to clean), attach a listener
		if (bIsDirty != getFileTarget().isDirty())
		{
			attachDirtyFlagListener();
			refreshCurrentTab();
		}
		
		return ret;
	}
	
	/**
	*	Overrides openFile() to add dirty flag and MRU support. Runs the parent's
	*	openFile method and add a dirty flag listener (cause the file is now clean).
	*	Adds the file to the MRU file list.
	*	
	*	@see	TabFileViewer#saveFile
	*/	
	public boolean openFile()
	{			
		if (super.openFile())
		{
			attachDirtyFlagListener();						
			
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	*	Called when a new tab is selected. Refreshes the tab and enables/disables the 
	*	close option as appropriate.
	*/
	public void refreshCurrentTab()
	{
		super.refreshCurrentTab();

		// we can't close the clipboard, so disable the close option when the clipboard
		// is selected
		if (getFileTarget() instanceof ClipboardControl)
		{
			feedbackObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_CLOSE), false);
		}
		else
		{
			feedbackObj.enableCommand(JNotePad.loadString(ResourceIDs.IDS_CLOSE), true);
		}
	}
	
}


/**
*	This thread implements timed save; after so many minutes, all the open
*	files are saved. 
*	<p>
*	This runs the saveAll() method in FeatureTabViewer to save the files.
*	<p>
*	@version	1.0, 7/28/97
*/

class AutosaveThread extends Thread
{
	/**
	*	The tab viewer which has files to save
	*/
	FeatureTabFileViewer featureView;
	
	/**
	*	Time to delay, in milliseconds
	*/
	int autosaveTime = 0;
	
	/**
	*	Creates a new AutosaveThread.	
	*	
	*	@param	view	The object which has open files we need to save.
	*	@param	sleeptime	The time (in milliseconds) before a save
	*/
	public AutosaveThread(FeatureTabFileViewer view, int sleeptime)
	{
		featureView = view;
		autosaveTime = sleeptime;
	}
	
	/**
	*	Sets the time between automatic saves. The new time takes effect
	*	after the next save.
	*
	*	@param	delay	Time between saves, in seconds.
	*/
	public void setDelay(int delay)
	{
		autosaveTime = delay*1000;
	}
	
	/**
	*	Runs the thread. Overrides Thread.run(). Loops infinitely; at each time through
	*	the loop, it sleeps for the correct interval and then calls the
	*	saveAll() method on the featureView object.
	*
	*	@see	FeatureTabFileViewer#saveAll
	*/
	public void run()
	{
		while (true)
		{
			try
			{
				sleep(autosaveTime);
			}
			catch (InterruptedException e)
			{
				// if we're interrupted, it's okay, we'll
				// just save now.
			}
			
			// save all open files
			featureView.saveAll();						
		}					
	}
	
}


/**
*	FeatureThread class
*	
*	A private class which runs feature plugins (which adhere to the IFeature
*	interface) in a separate thread. This is done to make the main program
*	a bit faster and more responsive. We don't guaranteed to be synchronized
*	with the main program, but since feature plugins are implemented through
*	listeners (which are by their very nature asynchronous), this isn't a
*	problem.
*
*	This class simply accepts new listeners, adds them to a local Vector,
*	and then registers and unregisters them when asked.
*
*	@version	1.0, 8/17/97
*
*	@see	IFeature
*	@see	FeatureTabFileViewer
*/

class FeatureThread extends Thread
{
	/**
	*	The list of feature listeners in the system
	*/
	private Vector featureListeners;
	
	/**
	*	The dirty flag feature.
	*/
	private DirtyFlagFeature dirtyFlagFeature;
	
	/**
	*	Creates a new FeatureThread.
	*
	*	@param	tabTarget	The object to notify when the dirty flag changes.
	*/
	public FeatureThread(FeatureTabFileViewer tabTarget)
	{
		init(tabTarget);
	}
	
	/**
	*	Private init function. Initializes variables and inits the DirtyFlagFeature.
	*
	*	@param	tabTarget	The object to notify when the dirty flag changes.
	*/
	private void init(FeatureTabFileViewer tabTarget)
	{
		featureListeners = new Vector(10);
		dirtyFlagFeature = new DirtyFlagFeature(tabTarget);			
	}
	
	/**
	*	Adds the feature to the system. This simply adds the feature to the	
	*	featureListeners Vector.
	*
	*	@param	fl	Feature to add
	*/
	public void registerListener(IFeature fl)
	{
		featureListeners.addElement(fl);
	}
	
	/**
	*	Loads the features onto the current file. This is done by iterative
	*	through all of the features and running init() and register() on
	*	each one. The dirty flag listener is attached at the end.
	*	
	*	@param	fileObj	The file control to attach features to.
	*/
	public void loadListeners(IFileOperationTargetExt fileObj)
	{		
		if (featureListeners == null)
		{
			return;
		}
		
		ITextOperationTargetExt editControl = fileObj.getEditControl();
		
		Enumeration enum = featureListeners.elements();
		while (enum.hasMoreElements())
		{
			ITextFeature fl = (ITextFeature)enum.nextElement();
			
			fl.init(editControl);
			fl.register();									
		}
		
		attachDirtyFlagListener(fileObj);
	}
	
	
	/**
	*	Unattaches features from a file. Goes through all of the features and
	*	calls reset() and unregister() on each one. 
	*/
	public void removeListeners()
	{
		if (featureListeners == null)
		{
			return;
		}
		
		Enumeration enum = featureListeners.elements();
		while (enum.hasMoreElements())
		{
			IFeature fl = (IFeature)enum.nextElement();
			
			fl.reset();
			fl.unregister();					
		}
		
		// if the dirty flag feature is still loaded, this will remove it
		dirtyFlagFeature.reset();
	}
	
	/**
	*	Adds a dirty flag listener to the given file. This feature plugin notifies
	*	the tab viewer when a file has been modified. 
	*
	*	@param	fileObj	The file control to listen to for changes
	*/
	public void attachDirtyFlagListener(IFileOperationTargetExt  fileObj)
	{			
		if (!fileObj.isDirty() && !fileObj.isReadOnly())
		{
			// attaches the feature to the file control
			dirtyFlagFeature.init(fileObj.getEditControl());
			dirtyFlagFeature.register();
		}			
	}
	
	/**
	*	The thread run method. Since we just wait for our methods to be
	*	called, this method does nothing.
	*/
	public void run()
	{
		// we don't need to do anything. We just wait for people
		// to call our public methods. Then our code runs in this
		// thread, not in the caller's thread.			
	}
	
}



