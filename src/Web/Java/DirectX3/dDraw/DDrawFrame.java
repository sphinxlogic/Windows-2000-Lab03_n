//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;

class DDrawFrame extends Frame
{
	public DDrawFrame(String str)
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

			case Event.KEY_ACTION:
				if(evt.key == Event.F12)
				{
					dispose();
					System.exit(0);
					return true;
				}				
			default:
				return super.handleEvent(evt);
		}			 
	}
}
