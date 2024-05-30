//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
//
//
// IActionFeature
//
// Implements action-based features. Implements the action listener
// interface so it can register a listener with the text object
// it is providing features for. It intercepts actions and modifies
// the text object accordingly.
// 7/21/97 TJS
import com.ms.ui.event.*;

public abstract class MovementFeature implements ITextFeature, IUIKeyListener
{		
	protected ITextOperationTargetExt textTarget;	
	
	public MovementFeature()
	{
	}
	
	public void init(ITextOperationTargetExt tTarget)
	{
		textTarget = tTarget;
	}
	
	public void register()
	{
		textTarget.addKeyListener(this);
		//textTarget.addMouseListener(this);
	}
	
	public void unregister()
	{
		textTarget.removeKeyListener(this);
		//textTarget.removeMouseListener(this);
	}
	
	// reset() and all IUIKeyListener and IUIMouseListener functions are to be
	// implemented in a derived class
}

