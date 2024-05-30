//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

/**
*	IKeyFeature
*	
*	Implements key-based features. Implements the key listener
*	interface so it can register a listener with the text object
*	it is providing features for. It intercepts the keys and modifies
*	the text object accordingly.
*
*	@see	#KeyFeature
*	@see	#IFeature
*
*	@version	1.0,	7/21/97
*/

import com.ms.ui.event.*;

public abstract class KeyFeature implements ITextFeature, IUIKeyListener
{		
	protected ITextOperationTargetExt textTarget;			// text target to listen to
	
	/**
	*	Creates a new KeyFeature()
	*/
	public KeyFeature()
	{
		textTarget = null;
	}
	
	/**
	*	Init function. Called when this feature is attached to a new text target
	*	object.
	*
	*	@param	tTarget	text target to attach this feature to.
	*/
	public void init(ITextOperationTargetExt tTarget)
	{
		textTarget = tTarget;
	}
	
	/**
	*	Called when the feature is attached to a text target. Adds a key listener
	*	to the text target.
	*/
	public void register()
	{
		textTarget.addKeyListener(this);
	}
	
	/**
	*	Called when the feature is detached from the text target. Removes the key
	*	listener.
	*/
	public void unregister()
	{
		textTarget.removeKeyListener(this);
	}
	
	// reset() and all IUIKeyListener functions are to be
	// implemented in a child class.
	
}

