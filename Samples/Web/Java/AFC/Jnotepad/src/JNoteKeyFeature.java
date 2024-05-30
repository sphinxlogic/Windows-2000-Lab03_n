//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import KeyFeature;
import com.ms.ui.event.*;

/**
*	Class to wrap KeyFeature's key listener events a little
*	and give key features a little easier access to key events.
*	<p>
*	Gives default implementations for the less important keyPressed()
*	and keyReleased() methods. This is an abstract class; subclass it and
*	add functionality before using.
*
*	@see	KeyFeature
*	@see	ITextFeature
*
*	@version	1.0, 7/21/97
*/

public abstract class JNoteKeyFeature extends KeyFeature
{
/**
*	Called when a key is pressed but before it
*	is released. Does nothing in this class. Part of the IUIKeyListener interface. 
*
*	@param	ke	Key event being processed.
	*/
	public synchronized void keyPressed(UIKeyEvent ke)
	{
	}
	
	/**
	*	Called when a key is released. Does nothing in this class.
	*	Part of the IUIKeyListener interface.
	*
	*	@param	ke	Key event being processed.
	*/	
	public synchronized void keyReleased(UIKeyEvent ke)
	{
	}
	
	/**
	*	Called when a key is typed (after it is released).
	*	Does nothing in this class. Part of the IUIKeyListener interface.
	*
	*	@param	ke	Key event being processed.
	*/	
	public synchronized void keyTyped(UIKeyEvent ke)
	{
	}
}

