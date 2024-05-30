//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
/**
*	Clipboard for JNotepad. Since Clipboards are security violations when	
*	running as an applet, we implement our own. If we're running standalone,
*	act like a regular clipboard.
*
*	@version	1.0, 8/22/97
*/

import java.awt.datatransfer.*;
import java.awt.*;

import com.ms.ui.*;

public class JNoteClipboard
{
	private static String sClipboardContents;
	private static boolean isApplet;
	
	public JNoteClipboard()
	{
		isApplet = false;
		sClipboardContents = "";
	}
	
	public static void initClipboard()
	{
		isApplet = JNoteAppletObject.isApplet();
	}
	
	public static void put(String text)
	{
		if (isApplet)
		{
			appletPut(text);
		}
		else
		{
			appPut(text);
		}
	}
	
	public static String get(Object pasteTarget)
	{			
		if (isApplet)
		{
			return appletGet();
		}
		else
		{
			return appGet(pasteTarget);
		}
	}
	
	private static void appPut(String text)
	{			
		Clipboard clipBoard = Toolkit.getDefaultToolkit().getSystemClipboard();	
		StringSelection cbdata = new StringSelection(text);
		clipBoard.setContents(cbdata, cbdata);
	}
	
	private static void appletPut(String text)
	{
		sClipboardContents = text;
	}
	
	private static String appGet(Object pasteTarget)
	{			
		Clipboard clipBoard = Toolkit.getDefaultToolkit().getSystemClipboard();	
		Transferable cbdata = clipBoard.getContents(pasteTarget);		
		
		if (cbdata != null)
		{
			try 
			{
				return (String)cbdata.getTransferData(DataFlavor.stringFlavor);							
			}
			catch (Exception e)
			{
				System.out.println("Data not string flavor");
			}						
		}
		
		return "";
	}							
	
	private static String appletGet()
	{	
		return sClipboardContents;
	}
	
	
}