//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.util.*;
import java.io.*;
import java.awt.*;

import com.ms.awt.*;
import com.ms.ui.*;
import com.ms.fx.*;
import com.ms.ui.event.*;
import com.ms.fx.FxFont;

//
//
// TabFileViewer
//
//
public class TabFileViewer extends UITabViewer implements IFileOperationTarget, ITextOperationTarget
{
	protected Vector loadedFiles;
	protected int iNumFiles;
	private   IFileOperationTargetExt currentFile;
	protected UIFrame parentFrame;
	private   int iNumNewFiles;
	private   ClipboardControl clipboardControl;
	static    private Image clipboardImage;
	

	public IFileOperationTargetExt getFileTarget()
	{
		return currentFile;
	}

	protected TabFileViewer()
	{
		this(null);
	}
	
	public TabFileViewer(UIFrame parentFrame)
	{
		super();

		loadedFiles = new Vector(5);
		this.parentFrame = parentFrame;
		iNumFiles = 0;
		iNumNewFiles = 0;	
		currentFile = null;

		addClipboardTab();
	}
	
	private void addToVector(IFileOperationTargetExt fc)
	{
		loadedFiles.addElement(fc);
		iNumFiles++;
	}

	protected Image getClipboardImage()
	{
		if(clipboardImage!=null)
			return clipboardImage;

		clipboardImage = Toolkit.getDefaultToolkit().getImage(clipboardControl.getImageName());
		// create an MediaTracker, which will wait until the image is
		// entirely loaded before displaying it
		MediaTracker mt = new MediaTracker(FxToolkit.getHelperFrame());
		mt.addImage(clipboardImage,0);
		try
		{
			mt.waitForAll();
		}
		catch (InterruptedException e)
		{
			// we don't care if we're interrupted...the worst that
			// could happen is that the image loads gradually, which
			// isn't a big deal. This rarely. if ever, happens.
		}

		return clipboardImage;
	}

	public void addClipboardTab()
	{
		// create a new edit control inside a new scroll viewer. This
		// automatically gives us scrolling inside the edit control.

		JNoteUIEdit edit = new JNoteUIEdit(parentFrame);
		UIScrollViewer sv = new UIScrollViewer(edit);
		
		// Create a clipboard control which will encapsulate this edit control 
		// as a file object (of class FileControl).
		clipboardControl = new ClipboardControl((ITextOperationTargetExt)edit, parentFrame);
		
		// add to vector of loaded files
		addToVector(clipboardControl);
		
		currentFile = clipboardControl;

		initNewTab();
		
		// add the UIItem glyph and the ScrollViewer to the tab viewer.
		// The UIItem is displayed on the tab itself, and the ScrollViewer is the
		// content displayed inside the tab body.
		addTab(new JNoteUIItem(getClipboardImage(), clipboardControl.getDisplayFileName()), sv);
	}

	//
	//
	//
	public UIPanel addNewFileTab(String path, String name)
	{	
		// create a new edit control inside a new scroll viewer
		JNoteUIEdit edit = new JNoteUIEdit(parentFrame);
		UIScrollViewer sv = new UIScrollViewer(edit);
		UIPanel p = new UIPanel();
		p.setLayout(new UIBorderLayout());
		p.add(sv, "center");
		
		DiskFileControl dfc = new DiskFileControl((ITextOperationTargetExt)edit, parentFrame);
		if (dfc.init(path, name))
		{
			// add to vector of loaded files
			addToVector(dfc);
			
			Image im = Toolkit.getDefaultToolkit().getImage(dfc.getImageName());							
			JNoteUIItem glyph = null;
			
			// add tab to viewer
			if (name == null)
			{
				++iNumNewFiles;
				
				// create a glyph with "New File" followed by the number of new files in this
				// session
				glyph = new JNoteUIItem(im, JNotePad.loadString(ResourceIDs.IDS_NEWFILETITLE)+iNumNewFiles);
			}
			else
			{
				glyph = new JNoteUIItem(im, dfc.getDisplayFileName());							
			}
			
			removeTab(getChildCount()-1);

			addTab(glyph, p);
			
			addClipboardTab();
			
			// set current file
			currentFile = dfc;

			// init the new tab
			initNewTab();
			
			// set tab selection to this new file
			setSelectedIndex(iNumFiles-2);
			
			edit.requestFocus();
			
			return p;
		}
		
		return null;
	}

	/**
	*	Called when a new tab is created but before it is displayed.
	*/
	protected void initNewTab()
	{
		// does nothing here
	}
	
	protected void refreshTab(UITab tab, IFileOperationTargetExt fc)
	{
		if (fc.getFileName() != null)
		{
			tab.setName(fc.getDisplayFileName());
		}
		tab.invalidateAll();
	}
	
	public void refreshCurrentTab()
	{
		refreshTab((UITab)getSelectedItem(), currentFile);
		currentFile.gotFocus();		
	}
	
	public void removeTab(int iIndex)
	{
		super.removeTab(iIndex);
		loadedFiles.removeElementAt(iIndex);
		--iNumFiles;
	}
	
	public boolean handleEvent(Event e)
	{
		if ((e.arg instanceof UITab) && (e.id == Event.LIST_SELECT))
		{
			currentFile = (IFileOperationTargetExt )(loadedFiles.elementAt(getSelectedIndex()));
			refreshCurrentTab();
		}
		else if ((e.id == Event.KEY_PRESS) && (e.key == '\t'))
		{
			// do nothing. We want the key listener to handle
			// tab switching.
			return(true);
		}
		
		return(super.handleEvent(e));
	}
	
	
	private boolean closeFile(IFileOperationTargetExt fc)
	{
		String filename = fc.getFileName();
		
		if (filename == null)
		{
			filename = JNotePad.loadString(ResourceIDs.IDS_UNTITLEDFILE);
		}
		
		if (currentFile.isDirty())
		{
			// save confirmation
			UIMessageBox msgbox = new UIMessageBox(parentFrame, 
				JNotePad.loadString(ResourceIDs.IDS_MSGSAVEFILE),
				"Do you want to save "+filename+"?",
				UIMessageBox.QUESTION, UIButtonBar.YESNOCANCEL);
			
			int iRet = ((UIButton)msgbox.doModal()).getID();
			
			if (iRet == UIButtonBar.ID_YES)
			{
				fc.saveFile();
			}
			else if (iRet == UIButtonBar.ID_CANCEL)
			{
				return false;
			}
		}
		
		return true;
	}
	
	
	public boolean closingApp()
	{
		Enumeration e = loadedFiles.elements();
		while (e.hasMoreElements())
		{
			IFileOperationTargetExt fc = (IFileOperationTargetExt )e.nextElement();
			if (fc.isDirty())
			{							
				if (!closeFile(fc))
				{
					return false;
				}
			}
		}		
		
		return true;
	}
	
	public IFileOperationTargetExt getCurrentFile()
	{
		return currentFile;
	}
	
	//
	// IFileOperationTarget methods
	//
	
	public void newFile()
	{
		addNewFileTab(null, null);			
	}
	
	public boolean saveFile()
	{
		boolean ret = false;
		
		if (currentFile.getFileName() == null)
		{
			ret = saveFileAs();
			
			String curFileName = currentFile.getFileName();
			if (curFileName != null)
			{							
				getSelectedItem().setName(curFileName);
			}										
		}
		else
		{
			ret = currentFile.saveFile();
		}
		
		return ret;
	}
	
	public boolean saveFileAs()
	{
		if (!currentFile.shouldSave())
		{
			return true;
		}
		
		// open a save dialog
		FileDialog fdialog = new FileDialog(parentFrame.getFrame(), 
									JNotePad.loadString(ResourceIDs.IDS_MSGSAVEFILE), 
									FileDialog.SAVE);
		fdialog.show();
		
		String fileName = fdialog.getFile();
		String filePath = fdialog.getDirectory();
		
		if (fileName == null)
		{
			return true; // ?? correct behavior to return true if no filename?
		}		
		
		currentFile.setFile(filePath, fileName);
		return currentFile.saveFile();
	}
	
	public boolean openFile()
	{
		// open an open file dialog
		FileDialog fdialog = new FileDialog(parentFrame.getFrame(), 
									JNotePad.loadString(ResourceIDs.IDS_MSGLOADFILE), 
									FileDialog.LOAD);
		fdialog.show();
		
		String fileName = fdialog.getFile();
		String filePath = fdialog.getDirectory();
		
		if ((fileName == null) || (addNewFileTab(filePath, fileName) == null))
		{
			return false;
		}
		else
		{			
			return true;
		}
	}
	
	
	public boolean closeFile()
	{			
		if (iNumFiles == 1)
		{
			return false;
		}
		
		if (currentFile.shouldSave() && closeFile(currentFile))
		{
			int iIndex = getSelectedIndex();
			
			removeTab(iIndex);
			
			if (--iIndex < 0) 
			{
				iIndex = 0;
			}
			setSelectedIndex(iIndex);
			
			repaint();
			
			return true;
		}
		
		return false;
	}			
	
	public void searchReplace(boolean isFind)
	{
		currentFile.searchReplace(isFind);
	}
	
	public void printFile()
	{	
		//PrintJob pjob = Toolkit.getDefaultToolkit().getPrintJob(null, "Test", null);
		WPrintJob pjob = null;
		
		try
		{
			Toolkit tools = parentFrame.getToolkit();
			pjob = (WPrintJob)tools.getPrintJob(null, "JNotepad", null);
			//pjob = parentFrame.getToolkit().getPrintJob(parentFrame.getFrame(), "Print", null);
		}
		catch (Exception e)
		{
			System.out.println("Exception thrown in print");
			PrintStream fos = null;
			try
			{
				fos = new PrintStream(new FileOutputStream("jnotepad.log"));
			}
			catch (Exception e1)
			{
				System.out.println("Exception in exception");
			}						
			
			e.printStackTrace(fos);
			
			fos.close();
		}
		
		if (pjob != null)
		{
			Graphics g = pjob.getGraphics();
			if (g != null)
			{
				parentFrame.getFrame().paintAll(g);
				g.dispose();
			}
			
			pjob.end();
		}
		else
		{
			System.out.println("Printjob is null");
		}
		
		//pjob.end();
	}
	
	public boolean otherCommand(String command, UIActionEvent evt)
	{
		boolean ret = false;
		
		IUIComponent comp=evt.getActionItem();
		switch( comp.getID() )
		{ 
		case ResourceIDs.ID_WINDOW_NEXT:
			return doWindowNext();
		case ResourceIDs.ID_WINDOW_PREVIOUS:
			return doWindowPrevious();
		case ResourceIDs.ID_FILE_EXIT:
			return doFileExit();
		}
		
		// !!
		//if (Character.isDigit(command.charAt(0)))
		//{
		//	ret = processNumberCommands(command, evt);										
		//}
		//else					
		{
			ret = currentFile.getEditControl().otherCommand(command, evt);
		}
		
		return ret;
	}
	
	protected boolean doWindowNext()
	{
		// # tabs is one less than # of components in the UITabViewer
		int iIndex = getSelectedIndex();
		int iMaxIndex = getComponentCount() - 1; 

		setSelectedIndex((iIndex+1) % iMaxIndex);
		return true;
	}

	protected boolean doWindowPrevious()
	{
		// # tabs is one less than # of components in the UITabViewer
		int iIndex = getSelectedIndex();
		int iMaxIndex = getComponentCount() - 1; 

		setSelectedIndex((iIndex-1+iMaxIndex) % iMaxIndex);
		return true;
	}

	protected boolean doFileExit()
	{
		// send a window destroy message to the parent. This handles closing up
		// the app, cancelling if necessary, and destroys the parent window.
		Event e = new Event(parentFrame, Event.WINDOW_DESTROY, this);
		parentFrame.postEvent(e);					
		return true;
	}

	private boolean processNumberCommands(String command, UIActionEvent evt)
	{
		if (command.length() < 3)
		{
			return true; // !!! should be false??
		}
		
		boolean ret = false;
		
		if (command.charAt(1) == ' ')				
		{
			// blank line after the # means a MRU selection
			File f = new File(command.substring(2));
			if (f.exists())
			{
				addNewFileTab(null, f.getPath());
				ret = true;
			}
			else
			{
				// file not found
				UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
					JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
					JNotePad.loadString(ResourceIDs.IDS_MSGFILENOTFOUND)+command.substring(2),
					UIMessageBox.STOP, UIButtonBar.OK);
				_box_.doModal();
			}
		}
		else
		{
			// internal error
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGINTERNALERR),
				box.STOP, UIButtonBar.OK);
			box.doModal();
		}		
		
		return ret;
	}
	
	//
	// ITextOperationTarget methods
	// These simply route the command to the current file or the current
	// edit control window.
	//
	
	public boolean undo()
	{
		return currentFile.getEditControl().undo();
	}
	
	public boolean redo()
	{
		return currentFile.getEditControl().redo();
	}
	
	public void cut()
	{
		currentFile.getEditControl().cut();	
	}
	
	public void copy()
	{
		currentFile.getEditControl().copy();
	}
	
	public void paste()
	{
		currentFile.getEditControl().paste();
	}
	
	public void delete()
	{
		currentFile.getEditControl().delete();
	}
	
	public void selectAll()
	{
		currentFile.getEditControl().selectAll();
	}
	
	public void changeTextColor()
	{
		currentFile.getEditControl().changeTextColor();		
	}
	
	public void changeBackColor()
	{
		currentFile.getEditControl().changeBackColor();		
	}
	
	public void changeFont()
	{
		currentFile.getEditControl().changeFont();
	}
	
	public void changeFont(FxFont font)
	{
		currentFile.getEditControl().changeFont(font);
	}
	
	public void setHorizAlign(int h)
	{
		currentFile.getEditControl().setHorizAlign(h);
	}

}


/**
*	JNoteUIItem
*
*	Extends UIItem to add tooltips. This class is used to display file names
*	on a tab in a TabFileViewer. If the name is long, we truncate it
*	and have the tooltip display the real name.
*
*	@see	#TabFileViewer
*
*	@version	1.0, 8/16/97
*/
class JNoteUIItem extends UIItem
{
	private String sLongname;
	private int iMaxNameLength;
	public static final int DEFAULT_NAME_LENGTH = 20;
	
	public JNoteUIItem(Image image, String text)
	{
		super(image, text, UIText.HOTTRACK);			
	}
	
	private void init(String text)
	{
		iMaxNameLength = DEFAULT_NAME_LENGTH;
		
		sLongname = text;
		if (text.length() > iMaxNameLength)
		{
			text = text.substring(0, iMaxNameLength) + "...";
		}			
		super.setName(text);
	}
	
	public void setMaxNameLength(int maxlen)
	{
		iMaxNameLength = maxlen;
		init(sLongname);
	}
	
	public void setName(String name)
	{
		init(name);
	}
	
	public String getHelp()
	{
		return sLongname;
	}
	
}
