//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import com.ms.ui.event.UIKeyEvent;

/**
*	A feature plugin which matches parentheses. When the user types the closing paren,
*	the cursor moves to the matching open paren. The next keystroke puts the caret back in 
*	the expected place. Useful for coding.
*
*	@see	IFeature
*	@see	JNoteKeyFeature
*
*	@version	1.0, 8/13/97
*/

public class BraceMatchFeature extends JNoteKeyFeature
{
	/**
	*	Constant which indicates normal state - no open parenthese
	*/
	static protected int STATE_NORMAL = 0;
	
	/**
	*	Constant which indicates open state - an open parenthese
	*/
	static protected int STATE_OPEN   = 1;
	
	/**
	*	Constant which indicates closed state - a closing parenthese has been typed
	*/
	static protected int STATE_CLOSED = 2;		// closed paren has been typed.
	
												/**
												*	Current state of parenthese matching
	*/
	int iState = STATE_NORMAL;
	
	/**
	*	Character index of open parenthese
	*/
	int iLastBrace = -1;
	
	/**
	*	Character index of closed parenthese
	*/
	int iEndPos = -1;
	
	
	/**
	*	Creates a new BraceMatchFeature()
	*/
	public BraceMatchFeature()
	{
		super();
	}
	
	/**
	*	Called when a key is pressed but before it
	*	is released. Part of IUIKeyListener.  If the state is STATE_CLOSED, remove the section 
	*	around the open parenthese.
	*
	*	@param	ke	UIKeyEvent which is being processed
	*/
	public synchronized void keyPressed(UIKeyEvent ke)
	{
		if (iState == STATE_CLOSED)
		{
			textTarget.setSelection(0,0);
			textTarget.moveTheCaret(iEndPos);
			iState = STATE_NORMAL;
		}
	}
	
	/**
	*	Part of IUIKeyListener. Called when a key is typed (pressed and released).
	*	Checks if the user just typed a close paren or an open paren and sets 
	*	the state accordingly.
	*
	*	@param	ke	UIKeyEvent which is being processed
	*/
	public synchronized void keyTyped(UIKeyEvent ke)
	{
		if (iState == STATE_CLOSED)
		{
			return;
		}
		
		if (ke.getKeyChar() == '(') 
		{
			iLastBrace = textTarget.getCaretIndex()-1;
			iState = STATE_OPEN;
		}		
		
		if ((ke.getKeyChar() == ')') && (iState == STATE_OPEN))
		{
			iEndPos = textTarget.getCaretIndex();
			//textTarget.moveCaret(iLastBrace);
			textTarget.setSelection(iLastBrace, iLastBrace+1);
			iState = STATE_CLOSED;				
		}
		
	}		
	
	
	/**
	*	Resets the feature. Called when the feature is removed from an edit control.
	*	Resets the state to STATE_NORMAL.
	*/
	public void reset()
	{
		iState = STATE_NORMAL;
		iEndPos = -1;
	}
}

