//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//


import java.applet.*;
import java.awt.*;
import com.ms.ui.*;
import com.ms.fx.*;
import JNotePadFrame;
import com.ms.ui.resource.*;
import java.io.InputStream;


/** 
* A text editor written in Java. A cross between Wordpad and Notepad
* with extra features, many of them user customizable. 
* <p>
* This is the main class which starts JNotepad and gets everything else
* running. This is a little different than traditional Java applets. This
* is because we want to use the AFC UIApplet class, but browsers don't 
* recognize this because they expect an Applet. Our solution is to use a
* AwtUIApplet wrapper. AwtUIApplet acts like an Applet object, so browsers
* can run it, and it supports AFC. Here we use a private UIApplet class, JNotePadImpl,
* to do all of the work necessary to run the applet, and wrap it inside
* the AwtUIApplet class JNotepad. We create a copy of JNotepadImpl and
* send it to the AwtUIApplet constructor. This gives us a UIApplet which
* will run in a browser. See UIApplet and AwtUIApplet for more detail.
* <p>
* Copyright (C) 1997, Microsoft Corp. 
* <p>
*
* @version 	1.0, 7/9/97
*/

public class JNotePad extends AwtUIApplet
{
	/**
	*	Creates a new JNotepad object.
	*/
	public JNotePad()
	{
		super(new JNotePadImpl());
	}
	
	/**
	*	Program entry point. Creates an instance of the real JNotePad application
	*	object, and runs it the same way as the system runs an applet.
	* 
	* @param args[] Array of command line arguments
	*/
	public static void main(String args[])
	{
		// set sFilename to filename to load into JNotepad		
		
		JNotePadImpl theApp = new JNotePadImpl();
	
		theApp.args=args;

		if (args.length > 0)
		{
			theApp.sFilename = args[0];				
			theApp.isApplet = false;
		}
		
		theApp.init();
		theApp.start();
	}
	
	private static Win32ResourceDecoder resources;
	public static Win32ResourceDecoder getResources()
	{
		if(resources==null)
		{
			try
			{
				WhereAmI here=new WhereAmI();
				Class cl=here.getClass();
				InputStream is = com.ms.fx.FxToolkit.getSystemInterface().getResourceAsStream(cl, "jnotepad.res" );

				resources =new Win32ResourceDecoder( is );
			}
			catch(Exception e)
			{
				// no resource file
				UIMessageBox box = new UIMessageBox(new UIFrame(), 
					JNotePad.loadString(ResourceIDs.IDS_MSGINSTALLERR),
					JNotePad.loadString(ResourceIDs.IDS_MSGNORES),
					box.STOP, UIButtonBar.OK);
				box.doModal();
				return null;
			}
		}
		return resources;
	}

	public static String loadString(int id)
	{
		Win32ResourceDecoder res=getResources();
		try
		{
			return res.getString(id);
		}
		catch (Exception e)
		{
			return null;
		}
	}

	public static UIMenuItem loadMenuItem(int stringID, int cmdID)
	{
		UIMenuItem mi=new UIMenuItem(loadString(stringID));
		mi.setID(cmdID);
		return mi;
	}

	public static UIMenuItem loadMenuItem(int id)
	{
		return loadMenuItem(id,id);
	}
}


/**
*	Class which implements JNotepad. 
*/
class JNotePadImpl extends UIApplet 
{		
	String sFilename;	
	boolean isApplet;
	String args[];

	
	public JNotePadImpl()
	{
		sFilename = null;
		isApplet = false;
	}
	
	public void init()
	{
		// we do nothing in the init() function
	}
	
	public void start()
	{
		// Create Toplevel Window
		JNotePadFrame frame = new JNotePadFrame("JNotePad", sFilename);

		frame.show();		
	}
	
	/** 
	* getAppletInfo() returns information about the applet.
	*/
	public String getAppletInfo()
	{
		return "Name: JNotepad\r\n" +
			"Copyright (C) 1997 Microsoft Corp.\r\n";
	}	
}

interface ResourceIDs
{
	static final int ID_HELP_ABOUT=4020;
	static final int ID_PROPERTIES=4005;
	static final int ID_TIMEDATE=4014;
	static final int ID_EMACS_CUT=-1;
	static final int ID_EMACS_PASTE=-2;

	static final int ID_FILE_NEW=4021;
	static final int ID_FILE_OPEN=4022;
	static final int ID_FILE_SAVE=4023;
	static final int ID_FILE_SAVEAS=4024;
	static final int ID_FILE_CLOSE=4003;
	static final int ID_FILE_PRINT=-3;
	static final int ID_FILE_EXIT=4007;
		
	static final int ID_EDIT_FIND=4017;
	static final int ID_EDIT_REPLACE=4019;
	static final int ID_EDIT_CUT=1001;
	static final int ID_EDIT_COPY=1002;
	static final int ID_EDIT_PASTE=1003;
	static final int ID_EDIT_DELETE=4012;
	static final int ID_EDIT_UNDO=4026;
	static final int ID_EDIT_REDO=4004;
	static final int ID_EDIT_SELECT_ALL=4013;

	static final int ID_WORDWRAPMENU=4006;
	static final int ID_NOWORDWRAP=5000; // dynamically generated
	static final int ID_WORDWRAP=5001;	// dynamically generated
	static final int ID_WORDWRAP2=5002;	// dynamically generated

	static final int ID_FONT=4001;
	static final int ID_TEXTCOLOR=4002;
	static final int ID_BGCOLOR=4011;

	static final int ID_WINDOW_PREVIOUS=4027;
	static final int ID_WINDOW_NEXT=4015;

	//
	// Context menu goo.
	//
	static final int ID_LAUNCH=3000;

	//
	// Strings
	//
	static final int IDS_NEW=101;
	static final int IDS_OPEN=102;
	static final int IDS_SAVE=103;
	static final int IDS_CLOSE=104;

	static final int IDS_UNDO=105;
	static final int IDS_REDO=106;
	static final int IDS_CUT=107;
	static final int IDS_COPY=108;
	static final int IDS_PASTE=109;
	static final int IDS_DELETE=110;
	static final int IDS_SELECT_ALL=121;

	static final int IDS_FONT=111;
	static final int IDS_TEXTCOLOR=112;
	static final int IDS_BGCOLOR=113;

	static final int IDS_LAUNCHSELLINK=114;

	static final int IDS_FIND=115;
	static final int IDS_REPLACE=116;

	static final int IDS_WORDWRAPMENU = 117;
	static final int IDS_NOWORDWRAP = 118;
	static final int IDS_WORDWRAP = 119;
	static final int IDS_WORDWRAP2 = 120;

	// clipboard strings
	static final int IDS_LOCALCLIPBOARD=124;
	static final int IDS_CLIPBOARD=125;
	static final int IDS_INVALIDCLIPBOARDDATA=126;
	static final int IDS_EMPTYCLIPBOARD=127;
	static final int IDS_CLIPBOARDIMG=128;

	// misc strings
	static final int IDS_FILEIMG=129;
	static final int IDS_COLORCHOICEFGTIP=130;
	static final int IDS_COLORCHOICEBGTIP=131;
	static final int IDS_JNOTEPADICON=132;
	static final int IDS_NEWFILETITLE=133;
	static final int IDS_UNTITLEDFILE=239;
	static final int IDS_FINDREPLACE=238;

	// message box text

	static final int IDS_MSGTITLE=122;
	static final int IDS_MSGREADONLY=123;
	static final int IDS_MSGNOSAVE=200;
	static final int IDS_MSGFILENOTFOUND=202;
	static final int IDS_MSGFILEREAD=203;
	static final int IDS_MSGSAVEERR=204;
	static final int IDS_MSGNODIALOG=206;
	static final int IDS_MSGFINDTEXT=207;
	static final int IDS_MSGSEARCHDONE=208;
	static final int IDS_MSGNOMATCH=211;
	static final int IDS_MSGREPLACEDONE=210;
	static final int IDS_MSGMENULOAD=213;
	static final int IDS_MSGMENUINIT=212;
	static final int IDS_MSGINTERNALERR=214;
	static final int IDS_MSGINSTALLERR=215;
	static final int IDS_MSGNORES=216;
	static final int IDS_MSGINIACCELERR=217;
	static final int IDS_MSGINIFONTERR=218;
	static final int IDS_MSGNOFEATURE=219;
	static final int IDS_MSGNOFEATUREINIT=220;
	static final int IDS_MSGINITOOLBARERR=221;
	static final int IDS_MSGINITIMGERR=221;
	static final int IDS_MSGINICOLORERR=222;
	static final int IDS_MSGLAUNCH=223;
	static final int IDS_MSGLAUNCHANNOC=224;
	static final int IDS_MSGLAUNCHERR=225;
	static final int IDS_MSGNOTRUNNABLE=226;
	static final int IDS_MSGFILERUNERR=227;
	static final int IDS_MSGRUNERROR=228;
	static final int IDS_MSGNOSETTINGS=229;
	static final int IDS_MSGSETTINGSERR=230;
	static final int IDS_MSGSETTINGSSAVEERR=231;
	static final int IDS_MSGSAVEFILE=232;
	static final int IDS_MSGSAVECONFIRM=233;	
	static final int IDS_MSGREPLACETEXT=236;
	static final int IDS_MSGLOADFILE=237;
	static final int IDS_MSGOKCANCEL=240;
	static final int IDS_MSGLINKTO=241;

}


class WhereAmI
{
	public WhereAmI()
	{
	}
}
