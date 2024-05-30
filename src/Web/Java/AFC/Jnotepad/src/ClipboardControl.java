//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import FileControl;
import java.awt.datatransfer.*;
import java.awt.*;
import com.ms.ui.*;

/**
*	Encapsulates the system Clipboard into a FileControl. Allows
*	one to have the Clipboard appear as a tab in the file list. The
*	contents of the clipboard are read in whenever the Clipboard tab is
*	selected.
*
*	@see	FileControl
*	@see	TabFileViewer
*
*	@version	1.0, 7/28/97
*/

public class ClipboardControl extends FileControl
{
	/**
	*	System clipboard object
	*/
	protected Clipboard clipBoard;
	
	/**
	*	Creates a new ClipboardControl. 
	*
	*	@param	control	the edit control which will hold the clipboard contents
	*	@param	parent	the parent UIFrame
	*/
	public ClipboardControl(ITextOperationTargetExt control, UIFrame parent)
	{
		super(control, parent);
		init(null, null);
	}
	
	/**
	*	Public init function. Inherited from FileControl.
	*	Called to create the object and load any data it needs to.
	*
	*	@param	filepath	Not needed for ClipboardControl objects
	*	@param	filename	Not needed for ClipboardControl objects
	*/
	public boolean init(String filepath, String filename)
	{
		setFile(null, null);
		
		// clipboard is read only and never dirty
		setReadOnly(true);
		setDirtyFlag(false);
		
		// load er up
		newFile();
		
		return true;
	}
	
	/**
	*	Returns the name that should be displayed on
	*	a UITabViewer tab. Inherited from FileControl. Clipboards return "[Clipboard]"
	*	if they are running as an application and "[Local clipboard]" when they are
	*	running as applets (since security prevents us from making a system clipboard
	*	as applets).
	*/
	public String getDisplayFileName()
	{				
		if (JNoteAppletObject.isApplet())
		{
			// return local clipboard text
			return JNotePad.loadString(ResourceIDs.IDS_LOCALCLIPBOARD);
		}
		else
		{
			// return clipboard text
			return JNotePad.loadString(ResourceIDs.IDS_CLIPBOARD);
		}
	}
	
	/**
	*	Called when a new file is to be created. For ClipboardControls, this loads
	*	data in from the clipboard and puts it onto the edit control. Inherited from FileControl.
	*/
	public void newFile()
	{	
		String data = JNoteClipboard.get(this);
		
		if (data == null)
		{
			data = JNotePad.loadString(ResourceIDs.IDS_INVALIDCLIPBOARDDATA);
		}
		else if (data.length() == 0)
		{
			data = JNotePad.loadString(ResourceIDs.IDS_EMPTYCLIPBOARD);
		}
		
		// set the text in the edit control
		editControl.setText(data);						
	}
	
	/**
	*	Called when a file is to be loaded. Inherited from FileControl. 
	*	This simply calls newFile() to refresh the clipboard contents.
	*/
	public boolean openFile()
	{
		// reload clipboard
		newFile();
		
		return true;
	}
	
	/**
	*	Called when the file needs to be saved.
	*	This does nothing since we never save the clipboard contents. Inherited from FileControl. 
	*
	*	@see	#shouldSave
	*/
	public boolean saveFile()
	{
		return true;
	}
	
	/**
	*	Called when the file needs to be saved under
	*	a different name. Calls saveFile(). Inherited from FileControl. 
	*
	*	@see	saveFile
	*/
	public boolean saveFileAs()
	{
		return saveFile();
	}
	
	/**
	*	Called when the file control receives focus.
	*	Reloads the clipboard contents by calling newFile(). Inherited from FileControl. 
	*/
	public void gotFocus()
	{
		// reload clipboard data
		newFile();
	}
	
	/**
	*	Returns whether a file control is capable
	*	of being saved to disk. ClipboardControls are not, so this returns false. Inherited from FileControl. 
	*/
	public boolean shouldSave()
	{
		return false;
	}
	
	/**
	*	Called to get the name of the image that is
	*	displayed on the UITab with the file name. We return a clipboard-style image. Inherited from FileControl. 
	*/
	public String getImageName()
	{
		return "Images\\clip.gif";
	}
	
}

