//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

/**
 *	Extends IFileOperationTarget to add some methods that are specific to
 *	objects which act like files. Classes which encapsulate files or file-like
 *	objects should adhere to this interface. This allows others to use an
 *	entirely different implementation of this interface with your code and have
 *	everything work.
 *	<p>
 *	JNotepad uses this interface in:
 *	<ul>
 *	<li><a href="FileControl.html">FileControl</a>
 *	<li><a href="DiskFileControl.html">DiskFileControl</a>
 *	<li><a href="ClipboardControl.html">ClipboardControl</a>
 *	</ul>
 *
 *	@see	IFileOperationTarget
 *
 *	@version	1.0, 7/15/97
 */

import java.io.File;

public interface IFileOperationTargetExt extends IFileOperationTarget
{
	/**
	 *	Returns the edit control associated with this file control.
	 */
	public ITextOperationTargetExt getEditControl();
	
	/**
	 *	Sets the filename and filepath of the file associated with this control.
	 *
	 *	@param	path	Path of file to load
	 *	@param	name	Name of file to load
	 */
	public void setFile(String path, String name);
		
	/**
	 *	Returns the path of the file.
	 */
	public String getFilePath();
		
	/**
	 *	Returns the name of the file.
	 */
	public String getFileName();

	/**
	 *	Returns the file object
	 */
	public File getFile();

	/**
	 *	Returns the file object
	 */
	public void setFile(File f);

	/**
	 *	Returns the path and the name together
	 */
	public String getFileLocation();

	/**
	 *	Returns the filename that should be displayed on the screen (on a tab,
	 *	for example). If the filename is null, returns "(untitled)". Adds
	 *	dirty bit indicators and read-only indicators prefixed onto the name.
	 */
	public String getDisplayFileName();	
	
	/**
	 *	Returns the extension of the file, without the period.
	 *	
	 *	@returns	The extension of the file. If there is no extension, an empty
	 *				string is returned. The period is not included. If there is no
	 *				filename defined, returns null.
	 */
	public String getFileExtension();

	/**
	 *	Sets the file's read only state.
	 *
	 *	@param	ro	true if the file is to be marked read only, false if it is
	 *				to be writable.
	 */
	public void setReadOnly(boolean ro);
		
	/**
	 *	Returns the read only state of the file.
	 */
	public boolean isReadOnly();
		
	/**
	 *	Returns the contents of the edit control associated with this file.
	 *	This is the contents of the file.
	 */
	public String getText();
			
	/**
	 *	Returns the name of the image file we should use to display next to the
	 *	filename (in a tab, for example). This is a small picture which represents
	 *	the type of file graphically. This class returns an image of a blank file.
	 */
	public String getImageName();

	/**
	 *	Called when the object has received focus. Usually done when it is
	 *	kept in a tab and the tabviewer has brought the tab into focus.
	 */
	public void gotFocus();	

	/**
	 *	Returns whether this file is capable of being saved. Returning false from 
	 *	this method prevents applications from trying to save it to disk or asking users
	 *	if they want to save it to disk.
	 *
	 *	@returns Returns true if it can be saved, false if it cannot. 
	 */
	public boolean shouldSave();

	/**
	 *	Returns the dirty state of the object. 
	 *
	 *	@returns	true if the object has been modified, false if it has not.
	 */
	public boolean isDirty();

	/**
	 *	Sets the dirty flag of the object. 
	 *
	 *	@param	b	true if the object is to be set dirty, false if it is not
	 */
	public void setDirtyFlag(boolean b);

}
