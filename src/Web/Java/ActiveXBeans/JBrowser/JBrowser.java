//////////////////////////////////////////////////////////////////////////
// JBrowser.java
// This is a java application which hosts the WebBrowser control (IE4.0)
// and provides similar UI.
//
// (C) Copyright 1997 by Microsoft Corporation. All rights reserved
//////////////////////////////////////////////////////////////////////////

// AFC
import com.ms.ui.*;
import com.ms.ui.event.*;
import com.ms.fx.*;

// the IE ActiveX control
import com.ms.ie.*;

// for hosting ActiveX Controls
import com.ms.activeX.*;
import com.ms.com.Variant;

// standard Java
import java.awt.*;
import java.awt.event.*;

//
//
// JBrowser
//
//
class JBrowser extends Frame implements IUIActionListener, ActiveXControlListener, WebBrowserEventListener
{
	UIBandBox bandBox = new UIBandBox();													// this contains all the bands.
	UIBand mainMenuBand = new UIBand();														// the main menu band
	UIMenuList fileMenuList = new UIMenuList();												// the list of items in the file menu
	UIMenuButton fileMenu = new UIMenuButton("File", 0, fileMenuList);						// the "File" menu
	UIMenuItem openItem = new UIMenuItem("Open");											// the open item in the file menu
	UIMenuItem exitItem = new UIMenuItem("Exit");											// the exit item in the file menu
	UIMenuList goMenuList = new UIMenuList();												// the list of items in the go menu
	UIMenuButton goMenu = new UIMenuButton("Go", 0, goMenuList);							// the "Go" menu
	UIMenuItem backItem = new UIMenuItem("Back");											// the back item in the go menu
	UIMenuItem forwardItem = new UIMenuItem("Forward");										// the forward item in the go menu
	UIMenuItem homeItem = new UIMenuItem("Home");											// the home item in the go menu
	UIMenuItem searchItem = new UIMenuItem("Search");										// the search item in the go menu
	UIMenuList helpMenuList = new UIMenuList();												// the list of items in the help menu
	UIMenuButton helpMenu = new UIMenuButton("Help", 0, helpMenuList);						// the "Help" menu
	UIMenuItem tutorialItem = new UIMenuItem("Web Tutorial");								// the Web Tutorial item in the help menu
	UIMenuItem aboutItem = new UIMenuItem("About Java Browser");							// the About ... item in the help menu.
	UIBand buttonsBand = new UIBand();														// the band of buttons
	UIPushButton backButton;																// go back to the last page button
	UIPushButton forwardButton;																// fo forward to the next page button
	UIPushButton stopButton;																// stop current transfer
	UIPushButton refreshButton;																// refresh current page button
	UIPushButton homeButton;																// go to the home page
	UIPushButton searchButton;																// go to the search page
	UIBand addressBand = new UIBand("Address ");											// the band of addresses
	EditBox address = new EditBox();														// the edit box for entering the text
	UIBand linksBand = new UIBand("Links");													// the band of links
	UIPushButton bestOfWebButton;															// the "Best of the Web" button
	UIPushButton microsoftJavaButton;														// the microsoft Java page
	UIPushButton microsoftButton;															// the "microsoft" page
	UIDrawText status = new UIDrawText("Status");											// to display the status text
	ProgressBar progress = new ProgressBar(300,20,100,0);									// to display the progress of the download
	StatusBar statusBar = new StatusBar(302,22);											// the status bar which displays progres and the status text
	WebBrowser browser = new WebBrowser();													// the web browser object
	Thread animationThread;																	// The thread which controls the animation of the image
	JAnim animatedImage;																	// the animated image object
	UIPushButton animatedButton;															// The button which has the animated image
	public Font dialogFont;																	// the font to use in dialog boxes

	/**
	 * The main method which creates a JBrowser object.
	 * @param	String[]	The command line parameters
	 */
	public static void main(String[] args)
	{
		new JBrowser();
	}

	/**
	 * Null constructor for JBrowser object. It creates the following
	 * <ol>
	 * <li>Main Menu
	 *	<ul>
	 *	<li>File
	 *		<ul>
	 *		<li>Open</li>
	 *		<li>Exit</li>
	 *		</ul>
	 *	</li>
	 *	<li>Go
	 *		<ul>
	 *		<li>Back</li>
	 *		<li>Forward</li>
	 *		<li>Home Page</li>
	 *		<li>Search The Web</li>
	 *		</ul>
	 *	</li>
	 *	<li>Help
	 *		<ul>
	 *		<li>Web Tutorial</li>
	 *		<li>About JBrowser</li>
	 *		</ul>
	 *	</li>
	 * </li>
	 * <li>An animated button
	 * </li>
	 * <li>Tool Bar with following icons
	 *	<ul>
	 *	<li>Back</li>
	 *	<li>Forward</li>
	 *	<li>Stop</li>
	 *	<li>Refresh</li>
	 *	<li>Home</li>
	 *	<li>Search</li>	
	 *	</ul>
	 * </li>
	 * <li>Creates a bar with the following
	 *	<ul>
	 *	<li>An Address edit box</li>
	 *	<li>A links bar with the following
	 *		<ul>
	 *		<li>Best of the web</li>
	 *		<li>Microsoft Java</li>
	 *		<li>Microsoft</li>
	 *		<li>Yahoo</li>
	 *		</ul>
	 *	</li>
	 *	</ul>
	 * </li>
	 * <li>Creates a status bar which has the following
	 *	<ul>
	 *		<li>A text label which prints the status text</li>
	 *		<li>A progress bar which shows the progress of the current operation</li>
	 *	</ul>
	 * </li>
	 * </ol>
	 * 
	 */

	public JBrowser()
	{
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Add event hooks to the JBrowser
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		addWindowListener(new JBrowserWindow());
		bandBox.addActionListener(this);
		browser.addWebBrowserEventListener(this);
		browser.addActiveXControlListener(this);

		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Add the main menu band
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		
		// give the band box a new layout manager.
		bandBox.setLayout( new UIBarLayout(0,0) );

		// add the file menu 
		fileMenuList.add(openItem);
		fileMenuList.add(exitItem);
		mainMenuBand.add(fileMenu);
				
		// add the go menu
		goMenuList.add(backItem);
		goMenuList.add(forwardItem);
		goMenuList.add(homeItem);
		goMenuList.add(searchItem);
		mainMenuBand.add(goMenu);

		// the forward and the back item will be enabled by browser events
		backItem.setEnabled(false);
		forwardItem.setEnabled(false);

		// add the help menu
		helpMenuList.add(tutorialItem);
		helpMenuList.add(aboutItem);
		mainMenuBand.add(helpMenu);

		mainMenuBand.setEdge(IFxGraphicsConstants.BDR_RAISED);
		
		bandBox.add(mainMenuBand);

		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// create and add an animated image
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		animatedImage = new JAnim( getToolkit().getImage("images/e.gif") , 46, 4 ) ;
		animatedButton = new UIPushButton(animatedImage);
		bandBox.add( animatedButton);

		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Add the buttons band
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		
		// back button
        backButton = createButton("images/previous.gif", "images/previous_g.gif", "Back", UIItem.ABOVE);
		buttonsBand.add(backButton);

		// forward button
        forwardButton = createButton("images/next.gif", "images/next_g.gif", "Forward", UIItem.ABOVE);
		buttonsBand.add(forwardButton);

		// the forward and back buttons will be enabled by browser events
		backButton.setEnabled(false);
		forwardButton.setEnabled(false);

		// stop button
        stopButton = createButton("images/stop.gif", "images/stop_g.gif", "Stop", UIItem.ABOVE);
		buttonsBand.add(stopButton);

		//stop button will be enabled by a download begin event
		stopButton.setEnabled(false);

		// refresh button
        refreshButton = createButton("images/refresh.gif", "images/refresh_g.gif", "Refresh", UIItem.ABOVE);
		buttonsBand.add(refreshButton);
 
		// home button
        homeButton = createButton("images/home.gif", "images/home_g.gif", "Home", UIItem.ABOVE);
		buttonsBand.add(homeButton);

		// search button
        searchButton = createButton("images/search.gif", "images/search_g.gif", "Search", UIItem.ABOVE);
		buttonsBand.add(searchButton);

		buttonsBand.setEdge(IFxGraphicsConstants.BDR_RAISED);
		buttonsBand.setStyle(UIBand.BREAK);

		bandBox.add(buttonsBand);
		
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Add the address band
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		// a panel for hosting the editbox
		UIPanel addressPanel = new UIPanel();
		addressPanel.setBackground(FxColor.white);
		addressPanel.setEdge(IFxGraphicsConstants.BDR_SUNKEN);
		addressPanel.add(address, "center");
		addressBand.add(addressPanel);

		addressBand.setEdge(IFxGraphicsConstants.BDR_RAISED);
		addressBand.setStyle(UIBand.BREAK);
		bandBox.add(addressBand);
		
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Add the links band
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%		
		bestOfWebButton = createButton("images/favorite_small.gif", "images/favorite_small_g.gif", "Best of the Web", UIItem.ONLEFT);
		linksBand.add(bestOfWebButton);

		microsoftButton = createButton("images/favorite_small.gif", "images/favorite_small_g.gif", "Microsoft", UIItem.ONLEFT);
		linksBand.add(microsoftButton);

		microsoftJavaButton = createButton("images/favorite_small.gif", "images/favorite_small_g.gif", "Microsoft Java", UIItem.ONLEFT);
		linksBand.add(microsoftJavaButton);

		linksBand.setEdge(IFxGraphicsConstants.BDR_RAISED);
		linksBand.setStyle(UIBand.DRAGBREAK);

		bandBox.add(linksBand);

		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Add the band box
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		setLayout(new BorderLayout() );
		
		setBackground(FxColor.lightGray);

		bandBox.setEdge(IFxGraphicsConstants.BDR_SUNKEN);
		add("North", new AwtUIHost(bandBox) );


		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Add the ActiveX WebBrowser control
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		add("Center", browser);

		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Add the status bar with status text and the progress bar in it.
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		// this panel will host the status text and the progress bar
		statusBar.setEdge(IFxGraphicsConstants.BDR_RAISED);
		statusBar.setLayout( new UIBorderLayout() );

		// the status text
		statusBar.add(status, "center");

		// the progress bar
		statusBar.add(progress, "east");

		add("South", new AwtUIHost(statusBar) );

		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		// Show the JBrowser
		// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		setBounds(150,100,900,800);
		setTitle("JBrowser");
		setVisible(true);
		dialogFont = new Font("TimesRoman", Font.BOLD, 18) ;
	}


	/**
	 * This class creates a push button with the specified hot and normal images and
	 * a text to be displayed with the image. The button is hot-tracked
	 * 
	 * @param String	The name of the normal image
	 * @param String	The name of the hot image
	 * @param String	The text to be displayed with image
	 * @param int		The location of the image with respect to the text
	 */
	UIPushButton createButton( String normal, String hot, String text, int where)
    {
        Image           gifnormal       = null;         // button in normal state
        Image           gifhot          = null;         // button in hot state
        MediaTracker    tracker;                        // to wait for the images to be loaded
        UIPushButton    button;                         // button to be returned

		// create a media tracker
        tracker = new MediaTracker(this);

		// load the normal image
        if (normal != null)
        {
			// load the normal image
            gifnormal = getToolkit().getImage(normal);

			// track the image neing loaded
            tracker.addImage(gifnormal, 0);
        }

       if (hot != null)
        {
	   		// load the hot-tracked image
			gifhot = getToolkit().getImage(hot);

			// listen on this image being loaded
			tracker.addImage(gifhot, 0);
        }

		// create the button
        button = new UIPushButton(new UIItem(gifnormal, text, UIItem.HOTTRACK, where), 0);
		//button = new UIPushButton( new UIStateItem(gifnormal, gifHot, text, UIStateItem.CENTERED, where), 0);

		// wait for all the images to be loaded
        try 
		{
			tracker.waitForAll();
		} 
		catch (InterruptedException e) 
		{
		}

		return button;
    }

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// Perform the browser actions
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	/**
	 * This shows a dialog box describing the browser in response to the about
	 * item in the help menu
	 */
	public void about()
	{
		UIMessageBox aboutMsg = new UIMessageBox(new UIFrame(),"About JBrowser", "This is a web-browser written in Java which uses the ActiveX control IE4.0",
			UIMessageBox.INFORMATION, UIButtonBar.OK	);

		aboutMsg.setFont(dialogFont);
		aboutMsg.doModal();
	}

	/**
	 * This navigates the browser object to a specified URL
	 *
	 * @param	String	The URL to go to.
	 */
	public void navigate(String url)
	{
		browser.Navigate(url, null, null, null, null);
	}

	/**
	 * This method displays a dialog box which takes a user specified URL
	 * as input and navigates to that URL.
	 */
	public void open()
	{
		new JBrowserOpen(this);
	}
	  
	/**
	 * This closes the browser application
	 */
	public void exit()
	{
		browser.removeWebBrowserEventListener(this);
		browser.removeActiveXControlListener(this);
		System.exit(0);
	}

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// Event handlers for the browser
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// Interface IUIActionListener requires the following method
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	/**
	 * This procedure receives action events which occurred in the browser like keyclicks
	 * on buttons or menuitems. It then calls the appropriate function to handle the event.
	 *
	 * @param	UIActionEvent	The event which occurred
	 */
	public void actionPerformed(UIActionEvent evt)
	{		
		Object target = evt.getActionItem();

		// ignore UIBand events
		if( evt.getSource() instanceof UIBand)
			return;

		if(target == address)
		{
			navigate( address.getValueText() );
		}

		else if(target == aboutItem)
		{
			about();
		}

		else if(target == backItem || target == backButton )
		{
			browser.GoBack();
		}

		else if( target == exitItem )
		{
			exit();
		}

		else if( target == forwardItem || target == forwardButton)
		{
			browser.GoForward();
		}

		else if (target == homeItem || target == homeButton)
		{
			browser.GoHome();
		}

		else if( target == microsoftButton)
		{
			navigate("http://www.microsoft.com");
		}

		else if(target == microsoftJavaButton)
		{
			navigate("http://www.microsoft.com/java");
		}

		else if(target == openItem)
		{
			open();
		}
		
		else if(target == refreshButton)
		{
			browser.Refresh();
		}
		
		else if(target == searchItem || target == searchButton)
		{
			browser.GoSearch();
		}
		
		else if(target == stopButton)
		{
			browser.Stop();
		}

		else if(target == tutorialItem)
		{
			navigate("http://www.microsoft.com/magazine/guides/internet/default.asp?");
		}

		else if(target == bestOfWebButton)
		{
			navigate("http://home.microsoft.com/exploring/exploring.asp");
		}

		else if(target == animatedButton)
		{
			navigate("http://www.microsoft.com/ie/default.asp");
		}
	}


	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// Interface ActiveXControlListener requires the following method
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


	/**
	 * This procedure receives events from the activeX controls after they have been created
	 * The browser control is made to start up from the home page.
	 *
	 * @param	Object	The control which was created
	 */
	public void controlCreated(Object target)
	{
		if(target == browser)
		{
			browser.GoHome();
		}
	}

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// Interface WebBrowserEventListener requires the following methods
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	/**
	 * This method is invoked when the text in the status bar has to be changed
	 *
	 * @param	String	The new text
	 */
	public void StatusTextChange(String text)
	{
		status.setValueText(text);
	}

	/**
	 * This is invoked when the progress bar's position is to be changed
	 *
	 * @param	int	The position
	 * @param	int	The maximum position
	 */
	public void ProgressChange(int pos, int range)
	{
		// UIProgress doesn't like a range of 0 ;-)
		if(range <= 0)
			progress.setRange(100);
		else
			progress.setRange(range);

		// the position is set to -1 when the download has finished
		if(pos < 0)
			progress.setPos(0);
		else
			progress.setPos(pos);
	}

	/**
	 * The title of the page being displayed
	 *
	 * @param	String	The new title
	 */
	public void TitleChange(String text)
	{
		setTitle(text);
	}

	/**
	 * This method is invoked when the Browser object has finished loading a document
	 *
	 * @param	Object	The web-browser frame in which this document was loaded
	 * @param	Variant	The URL of the loaded document
	 */
	public void DocumentComplete(Object pDisp, Variant URL)
	{
		address.setValueText( URL.getString() );
	}

	/**
	 * This method is invoked when the enabled state of a command changes
	 * for example when the forward command or the back command is no longer
	 * enabled
	 *
	 * @param	int		The identifier of the command that changed
	 * @param	boolean	Whether the command is enabled (=>true) or disabled
	 */
	public void CommandStateChange(int Command, boolean Enable)
	{
		switch(Command)
		{
		case CommandStateChangeConstants.CSC_NAVIGATEFORWARD:
			forwardButton.setEnabled(Enable);
			forwardItem.setEnabled(Enable);
			break;

		case CommandStateChangeConstants.CSC_NAVIGATEBACK:
			backButton.setEnabled(Enable);
			backItem.setEnabled(Enable);
			break;
		}
	}

	/**
	 * This method is called when the browser begins downloading
	 */
	public void DownloadBegin()
	{
		// start a new thread for the animated image
		animationThread = new Thread( animatedImage, "Animated Image");
		animationThread.start();

		stopButton.setEnabled(true);
		progress.setVisible(true);
	}

	/**
	 * This method is called when the browser ends downloading
	 */
	public void DownloadComplete()
	{
		// stop the animated image thread.
		animationThread.stop();
		animatedImage.reset();

		stopButton.setEnabled(false);
		progress.setVisible(false);
	}


	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// The following methods of interface WebBrowserEventListener
	// are not implemented
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	public void PropertyChange(String szProperty)
	{
	}

	public void BeforeNavigate2(Object pDisp, Variant URL, Variant Flags, Variant TargetFrameName, Variant PostData, Variant Headers, boolean[] Cancel)
	{
	}

	public void NewWindow2(Object[] ppDisp, boolean[] Cancel)
	{
	}
	
	public void NavigateComplete2(Object pDisp, Variant URL)
	{
	}

	public void OnQuit()
	{
	}
	
	public void OnVisible(boolean Visible)
	{
	}
	
	public void OnToolBar(boolean ToolBar)
	{
	}
	
	public void OnMenuBar(boolean MenuBar)
	{
	}
	
	public void OnStatusBar(boolean StatusBar)
	{
	}
	
	public void OnFullScreen(boolean FullScreen)
	{
	}
	
	public void OnTheaterMode(boolean TheaterMode)
	{
	}

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// Interface WindowListener requires the following inner class
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	/**
	 * This adapter class handles window events like when a user clicks on the 
	 * close window button it closes the browser.
	 */
	class JBrowserWindow extends WindowAdapter
	{
		/**
		 * Handles the event generated when the window is being closed
		 *
		 * @param	WindowEvent	The window event generated
		 */
		public void windowClosing(WindowEvent event)
		{
			exit();
		}


	}
}

/**
 * The progress bar extends the AFC's UIProgress and specifies a size for the same
 */
class ProgressBar extends UIProgress
{
	private int width;					// The width of the progress bar
	private int height;					// The height of the progress bar

	/**
	 * This constructor specifies the width and the height of the progress bar.
	 *
	 * @param	int	width
	 * @param	int	height
	 * @param	int	range -- The maximum range of the progress bar
	 * @param	int	pos   -- The current position of the progress bar
	 */
	public ProgressBar(int width, int height, int range, int pos)
	{
		// tell UIProgress what the range and the pos is
		super(range, pos);

		this.width = width;
		this.height = height;
	}

	/**
	 * The preferred size of this progress bar
	 *
	 * @return	Dimension	The preferred dimension
	 */
	public Dimension getPreferredSize()
	{
		return new Dimension(width, height);
	}

	/**
	 * The minimum size of this progress bar
	 *
	 * @return	Dimension	The minimum size
	 */
	public Dimension getMinimumSize()
	{
		return new Dimension(width, height);
	}
}

/**
 * The status bar is simply a UIPanel with a minimum size. This prevents it
 * from totally disappearing when it has nothing on it.
 */
class StatusBar extends UIPanel
{
	private int width;					// The width of the status bar
	private int height;					// The height of the status bar

	/**
	 * This constructor specifies the width and the height of the status bar.
	 *
	 * @param	int	width
	 * @param	int	height
	 */
	public StatusBar(int width, int height)
	{
		this.width = width;
		this.height = height;
	}

	/**
	 * The preferred size of this progress bar
	 *
	 * @return	Dimension	The preferred dimension
	 */
	public Dimension getPreferredSize()
	{
		return new Dimension(width, height);
	}

	/**
	 * The minimum size of this progress bar
	 *
	 * @return	Dimension	The minimum size
	 */
	public Dimension getMinimumSize()
	{
		return new Dimension(width, height);
	}
}


/**
 * This is an edit-box for entering the address to navigate to in the
 * browser.
 */
class EditBox extends UIEdit
{

	/**
	 * This creates a single line edit box
	 */
	public EditBox()
	{
		setSingleLine(true);
		setBackground(FxColor.white);
	}

	/**
	 * The preferred size of this edit
	 *
	 * @return	Dimension	The preferred dimension
	 */
	
	public Dimension getPreferredSize()
	{
		return new Dimension(700, 16);
	}

	/**
	 * The minimum size of this edit box
	 *
	 * @return	Dimension	The minimum size
	 */
	public Dimension getMinimumSize()
	{
		return new Dimension(700, 16);
	}
}
