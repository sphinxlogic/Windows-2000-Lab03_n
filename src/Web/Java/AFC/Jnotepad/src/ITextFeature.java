//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

/**
 *	The ITextFeature interface is used with features which attach themselves
 *	to and modify ITextOperationTargetExt objects (primarily edit controls). 
 *	This interface extends IFeature and only adds an initialization method
 *	which takes a ITextOperationTargetExt object. 
 *
 *	@see	IFeature
 *	@see	ITextOperationTargetExt 
 *
 *	@version	1.0, 7/21/97
 */

public interface ITextFeature extends IFeature
{
	/**
	 *	Initialization method for the feature. Initializes the feature with
	 *	the object it is going to monitor and modify. This is called every
	 *	time the feature is attached to an object, which can be several
	 *	times during an app's run.
	 *
	 *	@param	tObject	The object which the feature will attach itself to.
	 */
	public void init(ITextOperationTargetExt tObject);
}

