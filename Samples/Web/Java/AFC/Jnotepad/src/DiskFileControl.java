//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import FileControl;
import java.io.*;
import java.awt.Frame;
import com.ms.ui.*;
import java.util.StringTokenizer;

/**
*	Implementation of abstract class FileControl for disk files. Encapsulates a 
*	file and handles file loading/saving/etc into an edit control.
*
*	@see	 FileControl
*
*	@version	1.0, 7/15/97
*/

public class DiskFileControl extends FileControl
{
	/**
	*	Whether the file separates lines with CRLFs or CRs.	
	*/
	protected boolean bIsCRLF;

	/**
	 * Creates a new DiskFileControl.
	 *
	 *	@param	toTarget	Edit control which this file will display in
	 *	@param	parentFrame	Parent frame window.
	 */
	public DiskFileControl(ITextOperationTargetExt toTarget, UIFrame parentFrame)
	{
		super(toTarget, parentFrame);
		bIsCRLF=true;
	}
	
	/**
	 *	Creates a new file in the edit control. Part of IFileOperationTarget. 
	 */
	public void newFile()
	{
		editControl.setText("");
		setFile(null,null);
	}
	
	// assumes that the new file name has already been set
	// via setFileName()
	/**
	 *	Saves the file to disk under a different
	 *	name. Assumes that the new filename has been set using setFileName(). Part of IFileOperationTarget. 
	 */
	public boolean saveFileAs()
	{			
		return saveFile();
	}
	
	/**
	 *	Saves the file to disk under the current
	 *	name. Simply writes the contents of the edit control to disk. Part of IFileOperationTarget. 
	 */
	public boolean saveFile()
	{
		if (isReadOnly())
		{
			// file cannot be written to
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGREADONLY),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			return false;		
		}
		
		DataOutputStream file = null;			

		// display a wait cursor while we're waiting
		int iOldCursor = showWaitCursor();
		
		try 
		{
			file = new DataOutputStream(new FileOutputStream(getFileLocation()));
		}
		catch (IOException e)
		{
			// file save problem
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE), 
				JNotePad.loadString(ResourceIDs.IDS_MSGNOSAVE),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			
			// restore old cursor
			setCursor(iOldCursor);

			return false;
		}	
		
		boolean ret = true;
		
		// characters which mark end of line. If bIsCRLF is true, then append
		// a carriage return-line feed pair, otherwise just use a carriage return
		String lineTerminator = (bIsCRLF ? "\r\n" : "\r");

		try 
		{
			String line = editControl.getText();
			//file.writeBytes(line);

			//line.replace('\n', '\r');
			int iIndex = line.indexOf('\n');
			int iOldIndex = 0;
			while (iIndex > -1)
			{
				file.writeBytes(line.substring(iOldIndex, iIndex));

				file.writeBytes(lineTerminator);
				
				iOldIndex = iIndex+1;
				iIndex = line.indexOf('\n', iOldIndex);
			}
			//file.writeBytes("\n");			
		}
		catch (IOException e)
		{
			// can't write to disk
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOSAVE),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			
			ret = false;
		}
		
		try
		{
			file.close();
		}
		catch (IOException e1)
		{
		}
		
		// newly saved files are clean (not dirty)
		setDirtyFlag(false);

		// restore the old cursor
		setCursor(iOldCursor);
		
		return ret;
	}
	
	/**
	*	Checks if the file uses CRLF to separate lines or CRs only. 
	*	Returns the next string in the file and sets the bIsCRLF member variable. Note that
	*	this string has a carriage return appended to it.
	*/
	private String checkIfCRLF(DataInputStream file)
	{
		StringBuffer buffer = new StringBuffer(85);
		byte[] b = new byte[1];
		boolean bHitCR = false;
		
		bIsCRLF = false;

		try
		{
			// read file until CR hit. Set a flag and stop reading when that happens.
			int iNumRead = 0;
			b[0] = 0;
			while (iNumRead > -1)
			{		
				iNumRead = file.read(b);
				
				if (b[0] == '\r')
				{
					bHitCR = true;
					iNumRead = -2;
				}
				else
				{
					buffer.append((char)b[0]);
				}				
			} 

			// if we've hit a CR
			if (bHitCR == true)
			{
				// read next char. If this fails, b[0] will be unchanged, which is fine.
				// we only want to do something special if b[0] is \n (i.e. the next char
				// is LF) and if this hits EOF, b[0] will remain what it was. 
				file.read(b);
				
				// append a carriage return 
				buffer.append('\n');
				if (b[0] == '\n')
				{
					// CR followed by a LF. Clearly we're using CRLFs in this file.
					bIsCRLF = true;					
				}
				else
				{
					// not using CRLF in this class. Append the character we read.
					bIsCRLF = false;					
					buffer.append((char)b[0]);
				}				
			}

		} 
		catch (IOException e)
		{
			return null; // !!
		}

		return buffer.toString();
			
	}

	/**
	*	Opens a file from disk and loads it into
	*	the edit control. Assumes filename has already been set by setFileName(). Part of IFileOperationTarget. 
	*/
	public boolean openFile()
	{		
		DataInputStream file = null;
		
		try 
		{
			file = new DataInputStream(new FileInputStream(getFileLocation()));
		}
		catch (IOException e)
		{
			// file not found
			UIMessageBox box = new UIMessageBox(new UIFrame(),
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGFILENOTFOUND)+getFileLocation(),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			
			return false;
		}
		
		// display a wait cursor while we're waiting
		int iOldCursor = showWaitCursor();

		boolean ret = true;				
		
		// check if we should read files with CR or CRLF at end of the lines.
		String line = checkIfCRLF(file);
		editControl.setText("");
		editControl.appendText(line);
		
		try 
		{					
			line = file.readLine();			

			while (line != null)
			{
				editControl.appendText(line+"\n");
				line = file.readLine();
			} 
			
		}
		catch (IOException e)
		{
			// file read error
			UIMessageBox box = new UIMessageBox(new UIFrame(),
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGFILEREAD),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			
			ret = false;
		}
		
		try
		{
			file.close();
		}
		catch (IOException e1)
		{
			// internal saving error
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGSAVEERR),
				box.STOP, UIButtonBar.OK);
			box.doModal();
		}				
		
		// check if file is read only
		File fileObj = getFile();
		if (fileObj.canWrite())
		{
			setReadOnly(false);
		}
		else
		{
			setReadOnly(true);		
		}
		
		// newly loaded files are clean (not dirty)
		setDirtyFlag(false);

		// restore the old cursor
		setCursor(iOldCursor);
		
		return ret;
	}

	/**
	*	Displays a wait cursor.	
	*	@returns	The int ID of the cursor that used to be displayed
	*/
	protected int showWaitCursor()
	{
		// return setCursor(Frame.WAIT_CURSOR);
		return 0;	// we don't show the cursor, becase the this.setCursor does nothing
	}

	/**
	*	Sets the cursor.
	*	@param	iCursor	The ID of the cursor to change to
	*/
	protected int setCursor(int iCursor)
	{
		/*
		int iOldCursor = parentFrame.getFrame().getCursorType();

		parentFrame.getFrame().setCursor(iCursor);

		return iOldCursor;
		*/
		return 0;
	}

	
	// searchReplace is done in parent class and not overridden
	// here
	
	// closeFile is done in parent class, no need to override
	
	// printFile is done in parent class, no need to override
	
}


