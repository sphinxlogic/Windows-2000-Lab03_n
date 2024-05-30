// 
// 
//  Copyright (C) 1997 Microsoft Corporation. All Rights Reserved.
// 
//  File: DirectSoundTestFrame.java
// 		 
//  Description: allows DirectSoundTest to run standalone.
// 


import java.awt.*;

class DSoundFrame extends Frame
{
	public DSoundFrame(String str)
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
