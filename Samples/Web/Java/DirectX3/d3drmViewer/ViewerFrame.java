//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import java.awt.*;

class ViewerFrame extends Frame
{
	//////////////////////////////////////////////////////////////////////////
	public ViewerFrame(String str)
	{
		super (str);
	}

	//////////////////////////////////////////////////////////////////////////
	public boolean handleEvent(Event evt)
	{
		switch (evt.id)
		{
			case Event.WINDOW_DESTROY:
				dispose();
				System.exit(0);
				return true;

			default:
				return super.handleEvent(evt);
		}			 
	}
}
