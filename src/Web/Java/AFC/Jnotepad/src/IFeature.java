//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

/**
 *	Top level class for feature interfaces. Features descend from
 *	this interface but must be instantiated one or more levels down.
 *	<p>
 *	Features are plugin classes which modify the environment somehow. They
 *	operate by attaching event listeners to objects in the JNotepad environment.
 *	By intercepting events from these objects and interacting with them, 
 *	one can extend JNotepad quickly and easily and without touching JNotepad's
 *	source code. One doesn't even need to recompile. 
 *	<p>
 *	There are currently two types of IFeatures:
 *	<ul>
 *	<li><a href="ITextFeature.html">ITextFeature</a> - features that operate on edit controls
 *	<li><a href="IComponentFeature.html">IComponentFeature</a> - features that operate on UIComponents
 *	</ul><p>
 *	Several features in JNotepad are implemented using IFeature:
 *	<ul>
 *	<li><a href="AcceleratorFeature.html">AcceleratorFeature</a>
 *	<li><a href="BraceMatchFeature.html">BraceMatchFeature</a>
 *	<li><a href="DirtyFlagFeature.html">DirtyFlagFeature</a>
 *	<li><a href="JNoteUIStatus.html">AcceleratorFeature</a>
 *	<li><a href="AcceleratorFeature.html">AcceleratorFeature</a>
 *	</ul>
 *	@version	1.0, 7/21/97
 */

public interface IFeature 
{
	/**
	 *	Called when the feature is to be registered on an object. The object it
	 *	is to register itself with is passed in the class-specific init() method.
	 *	This usually involves setting listeners on the object.
	 */
	public void register();

	/**
	 *	Called when the feature needs to unregister itself. 
	 *	This usually involves removing listeners from the object.
	 */
	public void unregister();

	/**
	 *	Called when a feature has been disabled. Resets the state of the feature.
	 */
	public void reset();
	
}

