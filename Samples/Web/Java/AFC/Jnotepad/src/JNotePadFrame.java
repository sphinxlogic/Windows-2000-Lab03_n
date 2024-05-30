//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
/**
*  JNotePadFrame
*	
*	Main frame class for JNotepad. 
*	This class implements a frame window for JNotepad. Fills the frame 
*	with all the controls needed, and handles closing the app. 
*
*	@version 1.0, 7/9/97
*/

import java.awt.*;
import java.awt.event.*;
import java.io.*;

import com.ms.ui.*;

class JNotePadFrame extends UIFrame implements IConstants
{
	protected JNoteMenubar menuBar;					// JNotepad's menu bar
	protected JNoteToolbar toolBar;					// JNotepad's tool bar
	protected JNoteTabFileViewer tabFileView;		// JNotepad's tab view - where all the files are kept
	protected String loadedFileName = null;			// name of initial file to load
	
	/**
	*	JNotePadFrame constructor.	
	*
	*	@param title Frame window caption
	* 	@param	filename	Name of initial file to load
	*/
	
	public JNotePadFrame(String title, String filename)
	{
		super (title);

		// create new icon for JNotepad
		loadFrameIcon(ResourceIDs.IDS_JNOTEPADICON);

		// create the Settings object, which allows classes to store user
		// configurable option information in. Load in its data file.
		JNoteAppSettings.init("JNotepad.ini");
		JNoteAppSettings.load();

		// Create a CommandFeature. This object handles all of the command
		// processing in the application.
		JNoteCommandFeature commandFeature = new JNoteCommandFeature();
		JNoteAppCommandFeature.init(commandFeature, commandFeature);

		// create menu bar
		menuBar = new JNoteMenubar(null, JNotePad.getResources(), IDR_MENUBAR);
		menuBar.addWordWrapSubmenu(JNotePad.loadString(ResourceIDs.IDS_WORDWRAPMENU));

		// create a toolbar
		toolBar = new JNoteToolbar(JNoteAppletObject.getApplet());
		toolBar.loadButtons(JNotePad.getResources());

		// Create tabbed file viewer
		// This will hold the files and edit controls		
		tabFileView = new JNoteTabFileViewer(this, menuBar, commandFeature, commandFeature);
		
		// initialize the CommandFeature. We pass it the final destination
		// of all commands.
		commandFeature.init(tabFileView, tabFileView);

		// add talkers to the CommandFeature. These objects will be listened to
		// by the CommandFeature for command selection events.
		commandFeature.addTalker(menuBar);
		commandFeature.addTalker(toolBar);
		
		// create a blank file or load in a current file
		if (filename == null)
		{
			tabFileView.newFile();
		}
		else
		{
			tabFileView.addNewFileTab(null, filename);
		}
				
		// activate the CommandFeature.
		commandFeature.register();
		
		// Create a bandbox and put the menu bar and the toolbar inside it.
		// Set this bandbox as the header component in the frame.
		UIBandBox bandBox = new UIBandBox();
		bandBox.add(menuBar);
		bandBox.add(toolBar);
		setMenuBar(bandBox);
		
		// add the tabbed file viewer
		add(tabFileView, "center");
				
		// must show before resizing otherwise insets() doesn't
		// work right
		show();
		hide();
		
		// resize
		resize(getInsets().left + getInsets().right  + 600,
			getInsets().top  + getInsets().bottom + 400);		
		
	}

	/**
	*	Sets the icon for this frame window.
	*
	*	@param	stringID	The ID of the string which contains the name of the image to load.
	*/
	protected void loadFrameIcon(int stringID)
	{
		String imgName = JNotePad.loadString(stringID);

		if (imgName != null)
		{
			// no need for a mediatracker since we won't be displaying it right away
			Image im = Toolkit.getDefaultToolkit().getImage(imgName);

			if (im != null)
			{
				getFrame().setIconImage(im);				
			}
		}		
	}
	
	
	/**
	*	Handles window events. The only one handled is Event.WINDOW_DESTROY,
	*	which signals that the window is to be closed. This is handled by a 
	*	call to closeWindow(). All other events are handled by the superclass.
	* 
	*	@param evt Event that the window is to handle
	*/	  
	public boolean handleEvent(Event evt)
	{
		switch (evt.id)
		{
			// Application shutdown (e.g. user chooses Close from the system menu).
		case Event.WINDOW_DESTROY:
			
			// if the tab file view says its okay to close the app
			// (all files have been saved, and the user hasn't cancelled),
			// then close the window.
			if (tabFileView.closingApp())
			{
				closeWindow();
			}
			
			return true;
			
		default:
			return super.handleEvent(evt);
		}			 
	}
	
	/**
	*	Closes the window after saving the app settings (settingsObj).
	*/
	public void closeWindow()
	{
		JNoteAppSettings.save();	
		
		// !!! dispose();
		setVisible(false);
		System.exit(0);
	}
	
}
