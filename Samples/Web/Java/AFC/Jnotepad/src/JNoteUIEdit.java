//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
/** 
*	JNoteUIEdit
*
*	JNotepad extension of UIEdit. Supports ITextOperationTargetExt interface,
*	which allows other classes to control the JNoteUIEdit without knowing
*	anything about it. Adds a right-click context menu and support for HTML links.
*
*	@version	1.0, 7/13/97
*/

import com.ms.ui.*;
import com.ms.ui.event.*;
import com.ms.ui.resource.*;
import java.awt.*;
import java.io.*;
import com.ms.fx.*;
import java.awt.datatransfer.*;


public class JNoteUIEdit extends UIEdit implements ITextOperationTargetExt, IConstants, IUIFocusListener
{
	protected ICommandFeedback commandFeedback;
	protected IComponentFeature compFeature; 
	protected UIContextMenu popupMenu;
	
	protected Clipboard clipBoard;
	protected UIFrame parentFrame;
	
	/**
	* Default constructor. Constructs a JNoteUIEdit.
	*/
	public JNoteUIEdit(UIFrame parentframe)
	{
		super();
		init(parentframe);
	}
	
	/**
	*	Constructs a JNoteUIEdit with the given text.
	*
	*	@param text Text to fill the control with.
	*/
	public JNoteUIEdit(UIFrame parentframe, String text)
	{
		super();
		
		setText(text);
		init(parentframe);
	}
	
	/**
	*	Constructs a JNoteUIEdit with the given text.
	*
	*	@param text	Text to fill the control with.
	*/
	public JNoteUIEdit(UIFrame parentframe, char[] text)
	{
		super();
		
		setText(new String(text));
		init(parentframe);
	}
	
	// private init method. Initializes variables and sets colors and styles.
	private void init(UIFrame parentframe)
	{
		parentFrame = parentframe;
		commandFeedback = null;
		
		setSingleLine(false);
		
		clipBoard = Toolkit.getDefaultToolkit().getSystemClipboard();
		
		loadPopupMenu();		

		// set the initial word wrap. We enable/disable the appropriate menu
		// items in the gotFocus() method.
		setWordWrap(wwWrap);

		// add a focus listener, so we can detect when we gain focus. This class
		// implements IUIFocusListener, so we can set a listener on ourselves. We
		// change the word wrap menu radio buttons to reflect the current word
		// wrapping style.
		addFocusListener(this);
	}
	
	public void setFeedbackObject(ICommandFeedback comfeedback)
	{
		commandFeedback = comfeedback;		
	}
	
	public void setCommandObject(IComponentFeature compfeature)
	{
		compFeature = compfeature;
		
		compFeature.addTalker(popupMenu);		
	}
	
	// private method which loads the right-click popup menu.
	private void loadPopupMenu()
	{
		UIMenuList ml = new UIMenuList();
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_UNDO, ResourceIDs.ID_EDIT_UNDO ));
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_REDO, ResourceIDs.ID_EDIT_REDO ));
		ml.add(new UILine());					
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_CUT,  ResourceIDs.ID_EDIT_CUT ));
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_COPY, ResourceIDs.ID_EDIT_COPY ));
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_PASTE, ResourceIDs.ID_EDIT_PASTE ));
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_DELETE, ResourceIDs.ID_EDIT_DELETE ));
		ml.add(new UILine());
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_FONT, ResourceIDs.ID_FONT ));
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_TEXTCOLOR, ResourceIDs.ID_TEXTCOLOR ));
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_BGCOLOR, ResourceIDs.ID_BGCOLOR ));
		ml.add(new UILine());
		ml.add( JNotePad.loadMenuItem( ResourceIDs.IDS_LAUNCHSELLINK, ResourceIDs.ID_LAUNCH ));
			
		popupMenu = new JNoteContextMenu(this, ml);
	}
	
	
	protected void enableCommand(String command, boolean on)
	{
		if (commandFeedback != null)
		{
			commandFeedback.enableCommand(command, on);
		}
	}
	
	
	protected void setChecked(String command, boolean on)
	{
		if (commandFeedback != null)
		{
			commandFeedback.setChecked(command, on);
		}
	}
	
	
	public boolean handleEvent(Event e)
	{
		// check for right button click
		if ((e.id == Event.MOUSE_UP) && (e.modifiers == Event.META_MASK))
		{
			//Dimension d = TabFileViewer.getSize();
			Point pt = parentFrame.getLocation();
			Point edit = getLocation(parentFrame);
			popupMenu.launchAt(e.x+pt.x+edit.x, e.y+pt.y+edit.y, parentFrame);						
			
			return true;
		}
		else if ((e.id == Event.MOUSE_DOWN) && (e.modifiers == Event.META_MASK))
		{
			// do nothing. We swallow this event and don't give it to the superclass
			// to avoid losing focus for the context menu
			return true;
		}
		else
		{					
			return super.handleEvent(e);
		}
	}
	
	/**
	*	Sets the word wrapping for this control. Makes sure that the	
	*	word wrap radio buttons are properly updated.
	*
	*	@param	iStyle	Word wrap style. See the AFC UIEdit class for more information.
	*	@returns	true
	*/
	protected boolean setWordWrapStyle(int iStyle)
	{
		boolean b1 = false;
		boolean b2 = false;
		boolean b3 = false;

		// decide which radio buttons should be selected and which not
		if (iStyle == wwNone)
		{
			b2=b3=false;
			b1=true;
		}
		else if (iStyle == wwWrap)
		{
			b1=b3=false;
			b2=true;
		}
		else if (iStyle == wwKeepWordIntact)
		{
			b1=b2=false;
			b3=true;
		}

		// set the word wrap menu radio buttons accordingly
		setChecked(JNotePad.loadString(ResourceIDs.IDS_NOWORDWRAP), b1);
		setChecked(JNotePad.loadString(ResourceIDs.IDS_WORDWRAP), b2);
		setChecked(JNotePad.loadString(ResourceIDs.IDS_WORDWRAP2), b3);
			
		setWordWrap(iStyle);

		invalidate();

		return true;
	}

	public boolean otherCommand(String command, UIActionEvent evt)
	{
		boolean ret = false;
		
		IUIComponent comp=evt.getActionItem();
		switch( comp.getID() )
		{ 
		case ResourceIDs.ID_LAUNCH:
			return launchApp();
		case ResourceIDs.ID_NOWORDWRAP:
			return setWordWrapStyle(wwNone);
		case ResourceIDs.ID_WORDWRAP:
			return setWordWrapStyle(wwWrap);
		case ResourceIDs.ID_WORDWRAP2:
			return setWordWrapStyle(wwKeepWordIntact);
		}

		if (evt.getActionItem() instanceof UIStatic)
		{
			UIStatic s = (UIStatic)evt.getActionItem();					
			Object bgcolor = s.getBackground();
			Object fgcolor = s.getForeground();
			
			if (bgcolor instanceof FxColor)
			{
				if (s.getName().startsWith("Custom"))
				{
					changeBackColor();
				}
				else
				{
					setBackground((FxColor)bgcolor);
				}
				commandFeedback.notifyColorChange(this, getBackColor(), 
						commandFeedback.COLORCHANGE_BACKGROUND);
			}
			else if (fgcolor instanceof FxColor)
			{
				if (s.getName().startsWith("Custom"))
				{
					changeTextColor();
				}
				else
				{
					setForeground((FxColor)fgcolor);
				}							
				commandFeedback.notifyColorChange(this, getTextColor(), 
						commandFeedback.COLORCHANGE_FOREGROUND);
			}
			
			ret = true;
		}
		
		return ret;
	}
	
	/**
	*	Tries to run the selected text as a file or HTML link.	
	*
	*	@returns	true
	*/
	protected boolean launchApp()
	{
		String linkText = getSelectedText();
		
		if (linkText.length() == 0)
		{
			int iIndex = getCaretIndex();
			linkText = getWord(iIndex);
			if (linkText == null)
			{
				// file could not be run
				UIMessageBox box = new UIMessageBox(new UIFrame(), 
					JNotePad.loadString(ResourceIDs.IDS_MSGLAUNCHERR),
					JNotePad.loadString(ResourceIDs.IDS_MSGNOTRUNNABLE),
					box.STOP, UIButtonBar.OK);
				box.doModal();
				return true;
			}
		}
		
		// load in the text which links the two strings, depending on whether you're
		// launching an HTML link or a file.
		int linkID = (linkText.startsWith("http://") ? ResourceIDs.IDS_MSGLINKTO : ResourceIDs.IDS_MSGLAUNCH);
		String linkOrFileText = JNotePad.loadString(linkID);
		
		File fileToRun = new File(linkText);
		
		if (fileToRun.exists() || linkID == ResourceIDs.IDS_MSGLINKTO)
		{
			// confirm that user wants to launch this
			UIMessageBox msgbox = new UIMessageBox(parentFrame, 
				JNotePad.loadString(ResourceIDs.IDS_MSGLAUNCH),
				JNotePad.loadString(ResourceIDs.IDS_MSGLAUNCHANNOC)+linkOrFileText+linkText+
				JNotePad.loadString(ResourceIDs.IDS_MSGOKCANCEL), 
				UIMessageBox.INFORMATION, UIButtonBar.OKCANCEL);
			
			UIButton ret = (UIButton)msgbox.doModal();
			
			if (ret.getID() != UIButtonBar.ID_OK)
			{
				return true;
			}
			
			
			ExeRunnerThread exerunner = new ExeRunnerThread(linkText);
			exerunner.start();
		}
		else
		{
			// file could not be run
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGLAUNCHERR),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOTRUNNABLE),
				box.STOP, UIButtonBar.OK);
			box.doModal();
		}
		
		return true;
	}
	
	
	// returns the word at the given character index.
	protected String getWord(int iIndex)
	{
		String editText = getText();
		
		// if we're clicking on valid text
		if ((iIndex >= 0) && (iIndex < editText.length()))
		{
			// try to grab the word. 
			// getWordEdge definition:
			//		getWordEdge(int iPos, boolean pleaseMoveLeft, 
			//				    boolean givePrevious)
			// the ifs test for spaces - if we click right before
			//		or after a space, we have to make sure we
			//		grab the edge of the current word and not the
			//		edge of the next (or prev) word.
			
			int iWordLeftEdge = 0;
			int iWordRightEdge = 0;
			
			if ((iIndex > 0) && (editText.charAt(iIndex-1) == ' '))
			{
				iWordLeftEdge = getWordEdge(iIndex, true, false);
			}
			else
			{
				iWordLeftEdge = getWordEdge(iIndex, true, true);
			}
			
			if ((iIndex < editText.length()-1) && (editText.charAt(iIndex) == ' '))
			{
				iWordRightEdge = getWordEdge(iIndex+1, false, true);
			}
			else
			{
				iWordRightEdge = getWordEdge(iIndex, false, false);
			}
			
			return editText.substring(iWordLeftEdge, iWordRightEdge-1);
		}
		
		return null;
	}
	
	// protected method. Copies given text to clipboard.
	protected void copyToClipboard(String text)
	{
		StringSelection cbdata = new StringSelection(text);
		clipBoard.setContents(cbdata, cbdata);
	}
	
	
	protected String getClipboardContents()
	{
		Transferable cbdata = clipBoard.getContents(this);
		if (cbdata != null)
		{
			try 
			{
				return (String)cbdata.getTransferData(DataFlavor.stringFlavor);							
			}
			catch (Exception e)
			{
				System.out.println("Data not string flavor");
			}						
		}
		
		return null;
	}
	
	//
	// ITextOperation methods
	//
	
	
	/**
	*	IFileOperationTarget method. Called when the user wants to perform a cut
	*	operation. Does the usual thing.
	*/
	public void cut()
	{			
		int iSelStart = getSelectionStart();
		int iSelEnd = getSelectionEnd();
		
		if (iSelStart != iSelEnd)
		{
			String selText = getSelectedText();
			
			copyToClipboard(selText);
			
			remove(iSelStart, iSelEnd - iSelStart);
			
			setSelection(iSelStart, iSelStart);
			
			moveTheCaret(iSelStart);
			
			requestFocus();
		}
	}
	
	/**
	*	IFileOperationTarget method. Called when the user wants to do a copy
	*	operation. Does the usual thing.
	*/
	public void copy()
	{			
		if (getSelectionStart() != getSelectionEnd())
		{
			copyToClipboard(getSelectedText());
		}
	}
	
	/**
	*	IFileOperationTarget method. Called when the user wants to do a paste
	*	operation. Does the usual thing.
	*/
	public void paste()
	{
		String data = getClipboardContents();
		paste(data);						
	}
	
	/**
	*	IFileOperationTarget method. Called when the user wants to change the
	*	font. Pops up a AwtUIFontDialog and does the usual thing.
	*/	
	public void changeFont()
	{
		UIFontDialog dialog = new UIFontDialog(parentFrame);
		dialog.show();
		
		FxFont font = dialog.getFxFont();
		
		if (font != null)
		{
			setFont(font);
		}
	}
	
	/**
	*	IFileOperationTarget method. Called when the user wants to change the
	*	font to a certain font. Does the usual thing.
	*
	*	@param font	Font to change to
	*/
	public void changeFont(FxFont font)
	{
		setFont(font);
	}
	
	/**
	*	IFileOperationTarget method. Called when the user wants to change the
	*	text color. Pops up a AwtUIColorDialog and does the usual thing.
	*/	
	public void changeTextColor()
	{
		UIColorDialog dialog = new UIColorDialog(parentFrame);			
		dialog.show();
		
		FxColor c = dialog.getFxColor();
		if (c != null)
		{
			setForeground(c);
			repaint();
		}				
	}
	
	public void changeBackColor()
	{
		UIColorDialog dialog = new UIColorDialog(parentFrame);
		dialog.show();
		
		FxColor c = dialog.getFxColor();
		if (c != null)
		{
			setBackground(c);
			repaint();
		}				
	}

	public FxColor getTextColor()
	{
		Color c=getForeground();
		if(c!=null)
			return FxColor.getExtendedColor(c);
		return null;
	}
	
	public FxColor getBackColor()
	{
		Color c=getBackground();
		if(c!=null)
			return FxColor.getExtendedColor(c);
		return null;
	}
	
	public void setTextColor(FxColor color)
	{
		setForeground((Color)color);			
	}
	
	public void setBackColor(FxColor color)
	{
		setBackground((Color)color);			
	}
	
	public void selectAll()
	{
		setSelection(0, getText().length());
	}
	
	//
	// ITextOperationTargetExt functions
	//
	
	public void paste(String text)
	{
		int iSelStart = getSelectionStart();
		int iSelEnd = getSelectionEnd();
		
		// if no selection, insert at current caret position
		// if selection, paste over hilited text
		if (iSelStart == iSelEnd)
		{
			iSelStart = iSelEnd = getCaretIndex();
		}
		
		String str = getText();
		str = str.substring(0, iSelStart) + text + str.substring(iSelEnd);
		setText(str);
		moveTheCaret(iSelStart + text.length());
	}
	
	/**
	*	Inserts text at the given character position in the control.
	*	If iPos < 0, insert at caret position.
	*
	*	@param text String to insert
	*	@parem iPos Position to insert at. If < 0, insert at caret.
	*/
	public void insertText(String text, int iPos)
	{
		if (iPos < 0)
		{
			insert(text, getCurrIndex());
		}
		else
		{
			insert(text, iPos);
		}
	}
	
	public void moveCaret(int idx)
	{
		setCurrIndex(idx);
	}

	public void appendText(String text)
	{
		append(text);
	}
	
	public void delete()
	{	
		int iSelStart = getSelectionStart();
		int iSelEnd = getSelectionEnd();
		
		if (iSelStart != iSelEnd)
		{
			remove(iSelStart, iSelEnd - iSelStart);
			
			setSelection(iSelStart, iSelStart);
			
			moveTheCaret(iSelStart);
			
			requestFocus();
		}
	}
	
	public int getCaretIndex()
	{
		return getCurrIndex();
	}
	
	public void moveTheCaret(int idx)
	{
		setCurrIndex(idx);
	}
	
	public void setText(String text)
	{
		setValueText(text);
	}
	
	public String getText()
	{
		return getValueText();
	}

	// part of IUIFocusListener interface.

	/**
	*	Called when this control gets focus, via the IUIFocusListener interface.	
	*	Sets the current word wrap style.
	*
	*	@param	evt	The UIFocusEvent we are handling
	*/
	public void focusGained(UIFocusEvent evt)
	{
		setWordWrapStyle(getWordWrap());
	}
	
	/**
	*	Called when this control loses focus, via the IUIFocusListener interface.	
	*	Does nothing.
	*
	*	@param	evt	The UIFocusEvent we are handling
	*/
	public void focusLost(UIFocusEvent evt)
	{
		// we don't do anything if focus is lost
	}
	
}

/**
*	Thread to start processes. We run external programs using a thread
*	so we can continue to use the app while the program loads.
*	Used by JNoteUIEdit.
*
*	@version	1.0, 8/2/97
*	@see		JNoteUIEdit
*/
class ExeRunnerThread extends Thread
{
/**
*	Name of program to run.
	*/
	String exeFile;
	
	/**
	*	Creates a new ExeRunnerThread.
	*	
	*	@param	exeFile	Name of program to run.
	*/
	public ExeRunnerThread(String exefile)
	{
		super();
		exeFile = exefile;
	}
	
	/**
	*	Called when thread is started. Overrides Thread.start(). Runs
	*	the program using Runtime.exec() and then quits.
	*/
	public void start()
	{						
		try
		{
			Runtime.getRuntime().exec(exeFile);
		}
		catch (IOException e1)
		{
			// error trying to run file
			UIMessageBox mb = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGFILERUNERR),
				JNotePad.loadString(ResourceIDs.IDS_MSGRUNERROR)+exeFile,
				UIMessageBox.INFORMATION, UIButtonBar.OK);
			mb.doModal();
		}
	}
}
