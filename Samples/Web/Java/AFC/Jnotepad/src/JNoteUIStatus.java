//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
/**
*	JNoteUIStatus
*
*	A status bar for JNotepad. Implemented as a feature, which makes it really
*	easy to do. Implements both the key listener and the mouse listener interfaces,
*	which allow it to intercept both mouse clicks and key clicks. When we get a 
*	click that changes the position of the caret, well, we update ourselves!
*
*	@version	1.0, 8/6/97
*	@see		com.ms.ui.IUIMouseListener
*	@see		com.ms.ui.IUIKeyListener
*	@see		ITextFeature
*/

import com.ms.ui.*;
import com.ms.ui.event.*;
import java.awt.*;

class JNoteUIStatus extends UIStatus implements ITextFeature, IUIMouseListener, IUIKeyListener
{
	protected ITextOperationTargetExt tTarget;					// text target to listen to
	protected UIText textBox;									// text field to display status information
	protected UIText statusBox;									// text field to display caret position in
	
	/**
	*	Creates a new JNoteUIStatus object.
	*/
	public JNoteUIStatus()
	{
		super("", UIStatic.LEFT);
		localInit(" ");
	}
	
	/**
	*	Creats a new JNoteUIStatus object initalized with a string.
	*
	*	@param text	Text to be displayed in status bar.
	*/
	public JNoteUIStatus(String text)
	{
		super(text, UIStatic.LEFT);			
		localInit(text);
	}
	
	/**
	*	Private init method. Creates text fields for the caret position and
	*	for general text.
	*
	*	@param	text	Text to put into the status bar
	*/
	private void localInit(String text)
	{
		//int iCaretPos = tTarget.getCaretIndex();
		
		textBox = new UIText(text);			
		statusBox = new UIText("Line: 1 Position: 1", UIText.RIGHT);
		
		add(textBox, "east");
		add(statusBox, "west");
	}
	
	// IFeature and ITextFeature methods
	
	/**
	*	Public IFeature initialization method. Called every time this feature
	*	is attached to a new object. Sets the target object properly.
	*
	*	@param tObject Object to obtain position status from.
	*/
	public void init(ITextOperationTargetExt tObject)
	{
		tTarget = tObject;
	}
	
	/**
	*	Public IFeature registration method. Called to attaches listeners to the 
	*  target object so we can peek at events that happen to it and modify it 
	*	accordingly.
	*/
	public void register()
	{
		tTarget.addKeyListener(this);
		tTarget.addMouseListener(this);
	}
	
	/**
	*	Public IFeature unregistration method. Called to detaches listeners from 
	*  the target object.
	*/	
	public void unregister()
	{
		tTarget.removeKeyListener(this);
		tTarget.removeMouseListener(this);
	}
	
	/**
	*	Resets the feature. Called to clear any state we may have saved. Since
	*	no state is kept, we do nothing.
	*/
	public void reset()
	{
		// we keep no state, so nothing to reset			
	}
	
	// private methods
	
	/**
	*	Sets the status bar text field.	
	*
	*	@param	iLine	Current line number value.
	*	@param	iPos	Current position in the line.
	*/
	protected void printStatusLine(int iLine, int iPos)
	{
		statusBox.setName("Line: "+iLine+" Position: "+iPos);
	}
	
	/**
	*	Updates the status in the status bar. Displays the current location
	*	of the caret in the text target.
	*/
	protected void updateStatus()
	{
		int iCaretPos = tTarget.getCaretIndex();
		
		// grab the dimensions of the current font.
		FontMetrics fontMetrics = getToolkit().getFontMetrics(tTarget.getFont());	
		
		// grab the location (in pixels) of the caret.
		Point p = tTarget.getCharLocation(iCaretPos);
		
		// calculate current line by dividing current y position by the
		// height of the font. Add one to make it one based.
		int iLine = p.y / fontMetrics.getHeight() + 1;
		
		// grab index of the first character in current line by zeroing out
		// the x coordinate of our positoin and grab the index at that point.
		p.x = 0;
		int iCharPos = tTarget.getCharFromScreen(p);
		
		// print the status bar.
		printStatusLine(iLine, (iCaretPos-iCharPos+1));
		
		statusBox.repaint();
	}	
	
	// Key listener methods
	
	/**
	*	Public IUIKeyListener method. We do nothing here, all procesessing is
	*	in <a href="#keyTyped">keyReleased()</a>
	*
	*	@param ke Key event that occurred	 
	*/
	public synchronized void keyPressed(UIKeyEvent ke)
	{
		// do it all in keyReleased
	}
	
	/**
	*	Public IUIKeyListener method. Update the status of the status bar
	*	(i.e. current caret position) whenever a key is released.
	*
	*	@param ke Key event that occurred
	*/
	public synchronized void keyReleased(UIKeyEvent ke)
	{
		updateStatus();
	}
	
	/**
	*	Public IUIKeyListener method. We do nothing here, all procesessing is
	*	in <a href="#keyTyped">keyTyped()</a>
	*
	*	@param ke Key event that occurred	 
	*/
	public synchronized void keyTyped(UIKeyEvent ke)
	{
		// do it all in keyPressed
	}
	
	
	// Mouse listener methods
	
	/**
	*	Public IUIMouseListener method. Update the status of the status bar
	*	(i.e. current caret position) whenever the mouse is clicked.
	*
	*	@param evt Mouse event that occurred
	*/	
	public void mouseClicked(UIMouseEvent evt)
	{
		updateStatus();
	}
	
	/**
	*	Public IUIMouseListener method. We do nothing here, all procesessing is
	*	in <a href="#keyTyped">mouseClicked()</a>
	*
	*	@param evt Mouse event that occurred	 
	*/
	public void mousePressed(UIMouseEvent evt)
	{
		// we'll do it all in mouseClicked
	}
	
	/**
	*	Public IUIMouseListener method. We do nothing here, all procesessing is
	*	in <a href="#keyTyped">mouseClicked()</a>
	*
	*	@param evt Mouse event that occurred	 
	*/	
	public void mouseReleased(UIMouseEvent evt)
	{
		// we'll do it all in mouseClicked
	}
	
	/**
	*	Public IUIMouseListener method. We do nothing here, all procesessing is
	*	in <a href="#keyTyped">mouseClicked()</a>
	*
	*	@param evt Mouse event that occurred	 
	*/	
	public void mouseEntered(UIMouseEvent evt)
	{
		// don't care about this
	}
	
	/**
	*	Public IUIMouseListener method. We do nothing here, all procesessing is
	*	in <a href="#keyTyped">mouseClicked()</a>
	*
	*	@param evt Mouse event that occurred	 
	*/	
	public void mouseExited(UIMouseEvent evt)
	{
		// don't care about this
	}
	
	
}

