//
// (C) Microsoft Corp. 1997
//
//

// For UI
import java.applet.*;
import java.awt.*;
import com.ms.ui.*;
import com.ms.fx.*;

// For events.
import java.awt.Event;

// For resources
import com.ms.ui.resource.*;
import java.io.InputStream;
import java.util.Date;

//
// For the file
//
import java.io.File;

public class GuiApp extends UIApplet implements Runnable
{
	//
	// For more UI - these are used.
	//
	private GuiAppFrame m_frame;
	private	Thread		m_GuiApp = null;

	public static void main(String args[])
	{
		GuiApp App=new GuiApp();
		App.init();
		App.start();
	}

	public GuiApp()
	{
	}

	public String getAppletInfo()
	{
		return "Name: GuiApp\r\n" +
		       "Created with Microsoft Visual J++ Version 1.0";
	}

	public void init()
	{
		m_frame=new GuiAppFrame("SomeTitle",this);
		doProperties();
		System.exit(1);
	}

	public void destroy()
	{
	}

	public void start()
	{
		if (m_GuiApp == null)
		{
			m_GuiApp = new Thread(this);
			m_GuiApp.start();
		}
	}
	
	public void stop()
	{
		if (m_GuiApp != null)
		{
			m_GuiApp.stop();
			m_GuiApp = null;
		}
	}

	//
	// My app doesn't do anything.
	//
	public void run()
	{
		try
		{
			while (true)
			{
				Thread.sleep(300);
			}
		}
		catch (InterruptedException e)
		{
			stop();
		}
	}

	private ExamplePropertyDialog sheet;

	private void doProperties()
	{
		// Explicitly set the font so that all systems
		// will realize what font is used in the
		// upcoming property sheet
	    Win32ResourceDecoder res = ExamplePropertyDialog.getResources();
        ResourcePropertyPage template = new ResourcePropertyPage(res,
            ExamplePropertyDialog.IDD_BUTTONS);
        template.addContent();

        Font oldFont = m_frame.getFont();
		m_frame.setFont(template.getFont());
		sheet=new ExamplePropertyDialog(m_frame,"Resource Tester",true,res);
        m_frame.setFont(oldFont);

		sheet.display();
	}
}

//
// This is a property Dialog - holds property pages.
//
class ExamplePropertyDialog extends UIPropertyDialog
{
	public static int IDD_BUTTONS	=102;
	public static int IDD_STATICS	=103;
	public static int IDD_GROUPS	=104;
	public static int IDD_BOXES		=105;
	public static int IDD_EDIT		=106;
	public static int IDD_PROGRESS	=107;
	public static int IDD_MULTILINE	=108;
	public static int IDD_COMBOS	=109;
	public static int IDD_USERCLASS	=110;

	//
	// The resources needed
	//
	private static Win32ResourceDecoder resources;

	//
	//
	//
	public static  int IDS_FILETYPE=18;
	public static  int IDS_BUTTONS=19;
	public static  int IDS_EDIT=20;
	public static  int IDS_MULTILINE=21;
	public static  int IDS_COMBOS=22;
	public static  int IDS_BOXES=23;
	public static  int IDS_GROUPS=24;
	public static  int IDS_STATICS=25;
	public static  int IDS_USER=26;
	public static  int IDS_PROGRESS=27;

    private Dimension m_size;

	int getCharWidth(IUIContainer parent)
	{
		Font f = parent.getFont();
		if(f == null)
			f = new FxFont("Dialog", Font.PLAIN, 8);

		FontMetrics m = parent.getFontMetrics(f);
		String s     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int    width = m.stringWidth(s) / s.length();

		if (width <= 0)
			width = 1;
		return width;
	}

	int getCharHeight(IUIContainer parent)
	{
		FontMetrics m = parent.getFontMetrics(parent.getFont());
		int height = m.getHeight();
		return height;
	}

	void mapDimension(Dimension dim, int charWidth, int charHeight)
	{
		dim.width  = (dim.width  * 4 + charWidth  - 1) / charWidth;
		dim.height = (dim.height * 8 + charHeight - 1) / charHeight;
	}

	ExamplePropertyDialog(UIFrame frame, String title, boolean modal,
        	Win32ResourceDecoder res)
	{
		super(frame,title,modal);

        m_size = new Dimension(100, 100);

		// addPage( getString(IDS_FILETYPE),	new FileGeneral(res, "c:\\win\\win.ini") );
		addPage( getString(IDS_BUTTONS),	new ResourcePropertyPage( res, IDD_BUTTONS));
		addPage( getString(IDS_EDIT),		new ResourcePropertyPage( res, IDD_EDIT));
		addPage( getString(IDS_MULTILINE),	new ResourcePropertyPage( res, IDD_MULTILINE));
		addPage( getString(IDS_COMBOS),		new ComboTestPage( res, IDD_COMBOS));
		addPage( getString(IDS_BOXES),		new ResourcePropertyPage( res, IDD_BOXES));
		// addPage( getString(IDS_GROUPS),		new ResourcePropertyPage( res, IDD_GROUPS));
		addPage( getString(IDS_STATICS),	new ResourcePropertyPage( res, IDD_STATICS));
		// addPage( getString(IDS_USER),		new ResourcePropertyPage( res, IDD_USERCLASS));
		// addPage( getString(IDS_PROGRESS),	new ResourcePropertyPage( res, IDD_PROGRESS));

        mapDimension(m_size, getCharWidth(frame), getCharHeight(frame));
	}

	public void addPage(String name, IUIComponent comp)
    {
        super.addPage(name, comp);

        if (comp instanceof UIPropertyPage)
        {
            ((UIPropertyPage)comp).addContent();
        }

        Dimension size = comp.getPreferredSize();
        m_size.width  = Math.max(m_size.width , size.width );
        m_size.height = Math.max(m_size.height, size.height);
    }

	//
	// Returns a valid resource stream
	//
	public static Win32ResourceDecoder getResources()
	{
		if(resources==null)
		{
			Class cl=ExamplePropertyDialog.class;
			InputStream is=cl.getResourceAsStream("strtable.res");
			try
			{
				resources=new Win32ResourceDecoder( is );
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
		}
		return resources;
	}

	//
	// Adds a page - rather lame really
	//
	private void addDialog(int id)
	{
		UIPanel p=new UIPanel();
		populate(p, id);
		addPage( p );
	}

	//
	// Given a Panel (UIPropertyPage) and an ID, it will populates it for you.
	//
	public void populate(UIPanel uip, int id)
	{
		Win32ResourceDecoder res=getResources();
		try
		{
			res.populateDialog(uip, id);
		}
		catch (Exception e)
		{
			System.out.println("Problem "+e);
		}
	}

	//
	// This property dialog has a Custom Size
	//
	public Dimension getPageDimension()
	{
		return new Dimension(m_size);
	}

	public boolean doCancelAction(Event e, Object o)
	{
		System.out.println("Do Cancel");
		dispose();
		return false;
	}

	private String getString(int id)
	{
		Win32ResourceDecoder res=getResources();
		String st="";
		
		try{
			st=res.getString(id); 
		}
		catch (Exception e)
		{
		}
		return st;
	}
}

//
// A PropertyPage that understands it comes from a resource file
//
class ResourcePropertyPage extends UIPropertyPage
{
	//
	//
	//
	private Win32ResourceDecoder res;
	private int id;
    private boolean contentAdded = false;

	ResourcePropertyPage( Win32ResourceDecoder res, int id)
	{
		this.res = res;
		this.id  = id;
	}

	public boolean addContent()
	{
        if (contentAdded)
        {
            return(true);
        }

		try
		{
			res.populateDialog(this, id);
		}
		catch ( Exception e)
		{
		}

        contentAdded = true;
		return true;
	}

	public void setText(int id, String text)
	{
		IUIComponent comp=getComponentFromID(id);
		if(comp!=null)
		{
			if(comp instanceof UIScrollViewer)
				comp = ((UIScrollViewer)comp).getContent();

			if(comp instanceof IUIContainer)
			{
				IUIContainer uic=(IUIContainer)comp;
				int i=0;
				try
				{
					while(i>=0)
					{
						comp = uic.getChild(i);
						if(comp instanceof UIDrawText)
						{
							((UIDrawText)comp).setValueText(text);
							return;
						}
						i++;
					}
				}
				catch(Exception e)
				{
				}
			}
			if(comp instanceof UIEdit)
				((UIEdit)comp).setValueText(text);
		}
	}
}

//
// General file properties tab.
//
class FileGeneral extends ResourcePropertyPage
{
	public static int IDD_FILEINFO	=101;
	static final int ID_NAME=101;
	static final int ID_PATH=102;
	static final int ID_LOCATION=103;
	static final int ID_SIZE=104;
	static final int ID_MODIFIED=108;
	static final int ID_READABLE=1000;
	static final int ID_WRITEABLE=1001;

	File file;	// the file we are looking at.
	FileGeneral(Win32ResourceDecoder res, String fileName)
	{
		super(res, IDD_FILEINFO );
		this.file=new File(fileName);
	}

	FileGeneral(Win32ResourceDecoder res, File Name)
	{
		super(res, IDD_FILEINFO );
		this.file=Name;
	}

	//
	// We actually populate the content for this dialog
	//
	public boolean addContent()
	{
		if(super.addContent() == false)
			return false;

		try
		{
			setText( ID_NAME, file.getName() );
			setText( ID_PATH,file.getPath() );
			setText( ID_LOCATION,file.getParent() );
			setText( ID_SIZE,""+file.length());
			Date  date=new Date( file.lastModified() );
			setText( ID_MODIFIED,date.toString());
			getComponentFromID( ID_READABLE).setChecked( file.canRead() );
			getComponentFromID( ID_WRITEABLE).setChecked( file.canWrite() );
		}
		catch (Exception e)
		{
			System.out.println("Problem with controls "+e);
		}
		return true;
	}
}


//
//
//
class ComboTestPage extends ResourcePropertyPage
{
	static final int ID_DROPDOWN=1000;
	static final int ID_SIMPLE=1002;
	static final int ID_DROPLIST=1003;


	static final int ID_LISTSINGLE=1001;
	static final int ID_LISTMULTIPLE=1004;
	static final int ID_LISTEXTENDED=1005;
	static final int ID_LISTTABBED=1006;
	static final int ID_LISTNOSEL=1008;

	File file;	// the file we are looking at.
	ComboTestPage(Win32ResourceDecoder res, int id)
	{
		super(res, id );
	}

	//
	// We actually populate the content for this dialog
	//
	public boolean addContent()
	{
		if(super.addContent() == false)
			return false;

		try
		{
			fillCombo(ID_DROPDOWN);
			fillCombo(ID_SIMPLE);
			fillCombo(ID_DROPLIST);

			fillList(ID_LISTSINGLE);
			fillList(ID_LISTMULTIPLE);
			fillList(ID_LISTEXTENDED);
			fillList(ID_LISTTABBED,true);
			fillList(ID_LISTNOSEL);
		}
		catch (Exception e)
		{
			System.out.println("Problem with controls "+e);
		}
		return true;
	}

	private void fillCombo(int id)
	{
		fillCombo(id, false);
	}

	private void fillList(int id)
	{
		fillList(id, false);
	}

	private void fillCombo(int id, boolean tabs)
	{
		try
		{
			UIChoice uic=(UIChoice)getComponentFromID(id);
			for(int i=0;i<10;i++)
			{
				if(tabs)
					uic.addString("Item\t"+i+"\t Tabbed");
				else
					uic.addString("Item "+i);
			}
		}
		catch ( Exception e)
		{
			System.out.println(e);
		}
	}

	private void fillList(int id, boolean tabs)
	{
		try
		{
			UIScrollViewer uisc=(UIScrollViewer)getComponentFromID(id);
			UIList uic=(UIList)uisc.getContent();
			for(int i=0;i<10;i++)
			{
				if(tabs)
					uic.add("Item\t"+i+"\t Tabbed");
				else
					uic.add("Item "+i);
			}
		}
		catch ( Exception e)
		{
			System.out.println(e);
		}
	}

}

//==============================================================================
// STANDALONE APPLICATION SUPPORT
// 	This frame class acts as a top-level window in which the applet appears
// when it's run as a standalone application.
//==============================================================================
class GuiAppFrame extends UIFrame
{
	IUIComponent parent;
	public boolean action(Event e, Object o)
	{
		return parent.action(e,o);
	}

	public GuiAppFrame(String str, IUIComponent c)
	{
		super (str);
		parent=c;
	}

	public boolean handleEvent(Event evt)
	{
		switch (evt.id)
		{
			case Event.WINDOW_DESTROY:
				hide();
				System.exit(0);
				return true;

			default:
				return super.handleEvent(evt);
		}			 
	}
}
