//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
// import java.awt.*;
import com.ms.ui.*;
import com.ms.ui.event.*;
import java.io.File;

/**
*	An abstract base class for FileControls. FileControls encapsulate a file
*	object and supports the IFileOperationTargetExt interface (i.e. DiskFileControl
*	and ClipboardFileControl). Allows one to display and edit a file
*	in a control. Supports interfaces for file load/save and editing. File
*	printing and searching is supported here, as well as file bookkeeping, 
*	and everything else is delegated to descendant classes.
*
*	@version	1.0, 7/15/97
*/

public abstract class FileControl implements IFileOperationTargetExt
{
	
	/**
	*	Edit control attached to this file.	This edit control displays the file's contents.
	*/
	protected ITextOperationTargetExt editControl;
	
	/**
	 * The file, from which you can get the filename and the path.
	 */
	protected File file;
	
	/**
	*	Parent frame - used for displaying dialogs
	*/
	protected UIFrame parentFrame;
	
	
	/**
	*	dirty flag - true if file was modified since it was last opened or saved
	*/
	private boolean bDirty;
	
	/**
	*	read only flag - true if the file cannot be written to
	*/
	private boolean bReadOnly;
	
	/**
	*	The find replace dialog box.	
	*/
	protected JNoteFindReplaceDialog findReplaceDialog;
	
	/**
	*	Creates a new FileControl.
	*
	*	@param	control	Edit control to display the file's contents
	*	@param	parent	Parent frame
	*/
	public FileControl(ITextOperationTargetExt control, UIFrame parent)
	{
		editControl = control;
		parentFrame = parent;
		setFile(null,null);

		findReplaceDialog = new JNoteFindReplaceDialog(parentFrame, 
									JNotePad.loadString(ResourceIDs.IDS_FINDREPLACE),
									false, editControl);

		bReadOnly = false;
		bDirty = false;
	}
	
	/**
	*	Public init function - called to load a file into the control. Sets variables and loads the file.
	*
	*	@param	filepath	Path of file to load.
	*	@param	filename	Name of file to load.
	*/
	public boolean init(String filepath, String filename)
	{
		setFile(filepath, filename);

		// if we're passed a file name, open the file.
		if (getFileName() != null)
			return openFile();

		return true;
	}		
	
	/**
	*	Returns the edit control associated with this file.
	*/
	public ITextOperationTargetExt getEditControl()
	{
		return editControl;
	}
	
	/**
	*	Sets the filename and filepath of the file associated with this control.
	*
	*	@param	path	Path of file to load
	*	@param	name	Name of file to load
	*/
	public void setFile(String path, String name)
	{
		if( (path==null) && (name==null) )
		{
			file=null;
			return;
		}

		if ((path == null) && (name != null))
		{
			int iIndex = name.lastIndexOf('\\');
			if (iIndex > -1)
			{
				path= name.substring(0, iIndex+1);
				name = name.substring(iIndex+1);
			}
			else
			{
				path = ".\\";
			}
		}

		file=new File(path, name);
	}
	
	/**
	*	Returns the path of the file.
	*/
	public String getFilePath()
	{
		if(file!=null)
			return file.getPath();
		return null;
	}
	
	/**
	*	Returns the name of the file.
	*/
	public String getFileName()
	{
		if(file!=null)
			return file.getName();
		return null;
	}

	/**
	*	Returns the location of the file.
	*/
	public String getFileLocation()
	{
		if(file!=null)
			return file.getAbsolutePath();
		return null;
	}

	public void setFile(File f)
	{
		file=f;
	}

	public File getFile()
	{
		return file;
	}
	
	/**
	*	Returns the filename extension. Returns an empty string if there is
	*	no extension and null if there is no filename defined.
	*/
	public String getFileExtension()
	{
		if (getFileName() == null)
			return null;
		
		String sFileName=getFileName();

		int iDotIndex = sFileName.lastIndexOf('.');
		
		if ((iDotIndex < 0) || (iDotIndex == sFileName.length() - 1))
			return "";
		
		return sFileName.substring(iDotIndex+1);
	}
	
	
	/**
	*	Returns the filename that should be displayed on the screen (on a tab,
	*	for example). If the filename is null, returns "(untitled)". Adds
	*	dirty bit indicators and read-only indicators prefixed onto the name.
	*/
	// !! expand this function out a bit
	public String getDisplayFileName()
	{
		if (getFileName() == null)
			return JNotePad.loadString(ResourceIDs.IDS_UNTITLEDFILE);
		
		String sPrefix="";
		
		if (isReadOnly() )
			sPrefix+="[RO] ";
		
		if (isDirty() )
			sPrefix+="* ";
		
		// append a file state prefix to the filename and return it.
		return sPrefix+getFileName();
	}
	
	
	/**
	*	Sets the file's read only state.
	*
	*	@param	ro	true if the file is to be marked read only, false if it is
	*				to be writable.
	*/
	public void setReadOnly(boolean ro)
	{
		bReadOnly = ro;
		editControl.setReadOnly(ro);
	}
	
	/**
	*	Returns the read only state of the file.
	*/
	public boolean isReadOnly()
	{
		return bReadOnly;
	}
	
	/**
	*	Returns the contents of the edit control associated with this file.
	*	This is the contents of the file.
	*/
	public String getText()
	{
		return editControl.getText();
	}
	
	// implements some IFileOperationTarget methods that are
	// common to all files. Override these if you want
	
	/**
	*	Opens up a JNoteFindReplaceDialog on the
	*	text, which handles all searching and replacing in the file. Part of the IFileOperationTarget interface. 
	*
	*	@param	isFind	true if a find dialog is to be opened, false if a replace
	*					dialog is to be opened.
	*/
	public void searchReplace(boolean isFind)
	{								
		int iStyle = (isFind ? UIFindReplaceDialog.FIND : UIFindReplaceDialog.REPLACE);
		findReplaceDialog.startNewSearch();
		findReplaceDialog.display(iStyle);			
	}
	
	
	/**
	*	Closes the file. Returns true if the
	*	file was closed successfully, false if not. This method does nothing.
	*	Part of the IFileOperationTarget interface. 
	*/
	public boolean closeFile()
	{
		return true;
	}
	
	/**
	*	Prints the file. This method does nothing. Part of the IFileOperationTarget interface.
	*/
	public void printFile()
	{
	}
	
	/**
	*	Called when a command is executed which is not
	*	in the CommandFeature class. Use this to handle any application-specific
	*	commands that need to be processed. This method does nothing;
	*	override it to provide custom command functionality. Part of the IFileOperationTarget interface
	*
	*	@returns	false, indicating that the command was not processed here.
	*
	*	@param	command	The name of the command being processed. 
	*	@param	evt	The event which is being processed.
	*/
	public boolean otherCommand(String command, UIActionEvent evt)
	{
		return false;
	}
	
	/**
	*	Called when the file object has been
	*	selected, in a tab view for example. This method does nothing. 
	*/
	public void gotFocus()
	{
		// default is not to care
	}
	
	/**
	*	Called to ask whether this file can be
	*	saved to disk. In this class we return true. Part of the IFileOperationTargetExt interface.
	*/
	public boolean shouldSave()
	{
		return true;
	}
	
	/**
	*	Sets the dirty flag.
	*
	*	@param	b	true if the file is to be made dirty, false if it is to be made clean
	*/
	public void setDirtyFlag(boolean b)
	{
		bDirty = b;
	}
	
	/**
	*	Returns whether the file is dirty or not.
	*/
	public boolean isDirty()
	{
		return bDirty;
	}
	
	/**
	*	Returns the name of the image file we should use to display next to the
	*	filename (in a tab, for example). This is a small picture which represents
	*	the type of file graphically. This class returns an image of a blank file.
	*/
	public String getImageName()
	{
		return "Images\\new.gif";
	}
}
