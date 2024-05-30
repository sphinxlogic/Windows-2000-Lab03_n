//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import AppCommandFeature;

/**
*	Static abstract wrapper class for CommandFeature.
*	AppCommandFeature provides methods to get at the interfaces in CommandFeature,
*	and now this class actually links those interfaces to the actual class. 
*
*	@version	1.0, 8/18/97
*	@see		CommandFeature
*	@see		AppCommandFeature
*/

public class JNoteAppCommandFeature extends AppCommandFeature
{
/**
*	Initializes the interfaces which AppCommandFeature delivers to 
*	classes in this application. We pass the same CommandFeature to 
*	both interfaces since CommandFeature implements	both. 
	*/
	public static void init(CommandFeature commFeature)
	{
		// We call the protected init() function in AppCommandFeature
		// to set the data correctly. AppCommandFeature then returns
		// whichever interface needed.
		AppCommandFeature.init(commFeature, commFeature);
	}
}

