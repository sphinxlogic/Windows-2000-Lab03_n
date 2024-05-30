//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;

class CastleFrame extends Frame
{
	public CastleFrame(String str)
	{
		super (str);
	}

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
