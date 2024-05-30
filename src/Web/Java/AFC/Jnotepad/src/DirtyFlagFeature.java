//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.event.*;
import com.ms.ui.*;

/**
*	Class to detect keystrokes on clean files and mark them as dirty.
*	It's best to attach these to clean files only, cause it's useless otherwise...
*	When a keystroke is detected inside an edit control, the file attached to
*	that edit control is marked as dirty.
*	This feature plugin module uses the ITextFeature and IUIKeyListener interfaces.
*
*	@see	ITextFeature
*	@see	IFeature
*	@see	JNoteKeyFeature
*
*	@version	1.0, 8/9/97
*/

public class DirtyFlagFeature extends JNoteKeyFeature
{
/**
*	The object we notify when the dirty flag changes	
	*/
	FeatureTabFileViewer tabTarget;
	
	/**
	*	Determines whether the dirty flag listener has unloaded itself yet or not
	*/
	boolean bStillLoaded;
	
	/**
	*	Creates a new DirtyFlagFeature which notifies the specified object when
	*	a clean file is made dirty.
	*
	*	@param	tabtarget Object to notify
	*/
	public DirtyFlagFeature(FeatureTabFileViewer tabtarget)
	{
		super();
		tabTarget = tabtarget;
		bStillLoaded = false;
	}
	
	/**
	*	Called when this feature is attached to
	*	an edit control. Part of the ITextFeature interface. 
	*
	*	@param	ttarget	The edit control to be attached to
	*/
	public void init(ITextOperationTargetExt ttarget)
	{
		textTarget = ttarget;
		bStillLoaded = false;
	}
	
	/**
	*	Called when this feature needs to attach
	*	itself to the edit control. This is done using listeners. Part of the IFeature interface. 
	*/
	public void register()
	{
		super.register();			
		bStillLoaded = true;
	}
	
	/**
	*	Called when the feature is detached from
	*	the edit control. Removes listeners from the edit control. Part of the IFeature interface. 
	*/
	public void unregister()
	{
		super.unregister();
		bStillLoaded = false;
	}
	
	/**
	*	Called when a key is typed. 
	*	When a key comes in, sets the dirty flag on the current file in the
	*	TabFileViewer object passed in the init() method and then unregisters
	*	itself. Once a file is dirty, there's no need to keep marking it dirty
	*	on every keystroke. Part of the IUIKeyListener interface. 
	*	
	*	@param	ke	Key event which is being processed.
	*/
	public synchronized void keyTyped(UIKeyEvent ke)
	{
		IFileOperationTargetExt fileTarget = tabTarget.getCurrentFile();
		fileTarget.setDirtyFlag(true);
		
		tabTarget.refreshCurrentTab();
		
		unregister();
	}
	
	/**
	*	Called when the feature plugin needs to
	*	be reset. This method does nothing in this class. Part of the IFeature interface. 
	*/
	public void reset()
	{
		if (bStillLoaded)
		{
			unregister();
		}
	}
	
}

