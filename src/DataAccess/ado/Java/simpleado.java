/******************************************************************************
 * simpleado.java	Applet
 * 
 * Copyright 1996-1999 Microsoft Corporation
 *
 ******************************************************************************
*/
import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import com.ms.com.Variant;
import simpleadoframe;
// The WFC class includes the ADO objects used.
import com.ms.wfc.data.*;

/******************************************************************************
 *
 * simpleado Class
 * 
 * This is the primary class of the three used in this application.
 * It defines and drives the work to be done.
 *
 ******************************************************************************
*/
public class simpleado extends Applet
		implements ActionListener
{
	// Toolbar member objects.
	Panel  m_toolbar;
	Button m_first;
	Button m_prev;
	Button m_next;
	Button m_last;

	// Data Entry Form
	SimpleForm m_form;
	Recordset  m_recordset;
	
	// Define constants to specify Application run mode.
	static final int TYPEUndef = 0;
	static final int TYPEApplet = 1;
	static final int TYPEStandAlone = 2;
	
	// PARAMETER SUPPORT:
	//		Parameters allow an HTML author to pass information to the applet;
	// the HTML author specifies them using the <PARAM> tag within the <APPLET>
	// tag.  The following variables are used to store the values of the
	// parameters.
    //--------------------------------------------------------------------------

    // Members for applet parameters
    // <type>       <MemberVarName>   = <Default Value>
    //--------------------------------------------------------------------------
	private String m_ConnectionString = "dsn=OLE_DB_NWind_Jet;uid=Admin;pwd=;";
	private String m_CommandText      = "select EmployeeID, LastName, FirstName, HomePhone, Address, City, Region, PostalCode, Country from Employees";
	
    // Parameter names.  To change a name of a parameter, you need only make
	// a single change.  Simply modify the value of the parameter string below.
    //--------------------------------------------------------------------------
	private final String PARAM_Connection = "Connection";
	private final String PARAM_Command    = "Command";
	
	/******************************************************************
	*
	*  simpleado Class Constructor
	* 
	*******************************************************************
	*/
	public simpleado()
	{
		// Create the toolbar and add it to the applet
		m_toolbar = new Panel();
		add("North", m_toolbar);		
	}

	/******************************************************************
	* simpleado.Main() Method
	* 
	* Main is the first method called if run as a standalone
	* application.  (Whereas Start is the first method called if run as
	* an Applet in a container, such as an HTML page in a Web browser.)
	*
	*******************************************************************
	*/
	public static void main(String args[])
	{
		// Create Window to contain the simpleado applet
		simpleadoframe frame = new simpleadoframe("simpleado");

		// Start the applet running within the frame window.
		simpleado applet_simpleado = new simpleado();
		frame.add("Center", applet_simpleado);	
		frame.setSize(600,500);
		
		// Get the parameter values from the command line. 
		applet_simpleado.GetParameters(args);
		
		// Activate the buttons and data for the user to browse.
		applet_simpleado.initButton();
		applet_simpleado.initData();
		
		frame.setVisible(true);
	}
	
	/******************************************************************
	* simpleado.init() Method
	* 
	* Init is called by the AWT when an applet is loaded or reloaded
	* (to browser)
	*
	*******************************************************************
	*/
	public void init()
	{
		resize(600, 500);
	}

	/******************************************************************
	* simpleado.start() Method
	* 
	* Start is the first method called (after Init) when run as an
	* applet, such as from an HTML page in a browser.
	*
	*******************************************************************
	*/
	public void start()
	{			
		GetParameters(null);
		initButton();
		initData();
	}
	
	/******************************************************************
	*
	* simpleado.initButton() Method
	* 
	* Initialize button support.
	*  
	*******************************************************************
	*/
	public void initButton()
	{
		// Create first Button
		m_first = new Button("First");
		// Enable button clicks to take action
		m_first.addActionListener(this);
		// Add it to the toolbar
		m_toolbar.add(m_first);
		
		// Do the same with the remaining buttons.
		m_prev = new Button("Prev");
		m_prev.addActionListener(this);
		m_toolbar.add(m_prev);
		
		m_next = new Button("Next");
		m_next.addActionListener(this);
		m_toolbar.add(m_next);
		
		m_last = new Button("Last");
		m_last.addActionListener(this);
		m_toolbar.add(m_last);
	}

	/******************************************************************
	*
	* simpleado.initData() Method
	* 
	* Initialize Recordset values on the applet.
	* 
	*******************************************************************
	*/		
	public void initData()
	{
		// Initialize Recordset values
		// ---------------------------
		try
		{
			// Create the recordset object
			m_recordset = new Recordset();
			m_recordset.open(m_CommandText, 
							 m_ConnectionString, 
							 AdoEnums.CursorType.STATIC,
							 AdoEnums.LockType.READONLY, 
							 AdoEnums.CommandType.TEXT);
		
			// Create the data display form, passing it the recordset
			m_form = new SimpleForm(m_recordset);

			// Add it to the applet
			add("Center", m_form);

			// Get the first record in the recordset
			m_recordset.moveFirst();

			// Display that record
			m_form.showData();
		}
		catch( AdoException ae )
		{
			// Print error if from ADO.		
			System.out.println("Exception: " + ae.getMessage());
			
			// Print errors collected by ADO from the Provider.
			// As passing a Recordset, check for null pointer first.
			if (m_recordset != null)
			{
				PrintProviderError(m_recordset.getActiveConnection());
			}
		}

	}

	/******************************************************************
	*
	* simpleado.finalize() Method
	* 
	* The finalize() method is called when the windows application
	* is closed. Use Finalize for clean up work when writing an
	* application.
	* 
	*******************************************************************
	*/
	public void finalize()
	{
		stop();
	}
	
	/******************************************************************
	*
	* simpleado.stop() Method
	* 
	* The stop() method is called when the page containing the applet is
	* no longer on the screen. Use Stop when writing an applet.
	* 
	*******************************************************************
	*/
	public void stop()
	{
		// Close the recordset
		m_recordset.close();
		m_recordset = null;
		
		// Remove the buttons
		m_toolbar.remove(m_first);
		m_first.removeActionListener(this);
		remove(m_first);
		m_first = null;
		
		m_toolbar.remove(m_prev);
		m_prev.removeActionListener(this);
		remove(m_prev);
		m_prev = null;
		
		m_toolbar.remove(m_next);
		m_next.removeActionListener(this);
		remove(m_next);
		m_next = null;
		
		m_toolbar.remove(m_last);
		m_last.removeActionListener(this);
		remove(m_last);
		m_last = null;

		// Remove the form
		remove(m_form);
		m_form = null;
	}

	/******************************************************************
	*
	* simpleado.destroy() Method
	* 
	* Place additional applet clean up code here.  destroy() is called when
	* when the applet is terminating and being unloaded.
	* 
	*******************************************************************
	*/
	public void destroy()
	{
	}

	/******************************************************************
	*
	* simpleado.paint() Method
	* 
	*******************************************************************
	*/
	public void paint(Graphics g)
	{
	}

	/******************************************************************
	* simpleado.getAppletInfo() Method
	* 
	* The getAppletInfo() method returns a string describing the applet's
	* author, copyright date, or miscellaneous information.
	*
	*******************************************************************
	*/
	public String getAppletInfo()
	{
		return "Name: SimpleAdo\r\n" +
		       "Author: Microsoft Data Access Group\r\n" +
		       "Built with Microsoft Visual J++ Version 6.0";
	}
	
	/******************************************************************
	*
	* simpleado.getParameterInfo() Method
	* 
	* The getParameterInfo() method returns an array of strings describing
	* the parameters understood by this applet. Not called directly in
	* this sample.
	*
    * simpleado Parameter Information:
    *  { "Name", "Type", "Description" },
	* 
	*******************************************************************
	*/
	public String[][] getParameterInfo()
	{
		String[][] info =
		{
			{ PARAM_Connection, "String", "Connection String" },
			{ PARAM_Command, "String", "Command Text" },
		};
		return info;		
	}

	/******************************************************************
	* simpleado.GetParameter() Method
	* 
	* This method is called by GetParameters() and returns the value 
	* of the specified parameter.
	* 
	* @param String strName - Name identifier for the argument whose value
	*					is in the second parameter.
	* @param String args - A string containing the command line arguments.
	* @return String - The one command line value that matches the 
	*					parameter Name provided as strName.
	* 
	* @see - Mirrors the getParameter() method which comes with Applet.
	*			This version allows this functionality to be used from
	*			both the Applet and Standalone modes.
	* 
	*******************************************************************
	*/
	String GetParameter(String strName, String args[])
	{
		if (args == null)
		{
			// Then, running as applet within an HTML page, 
			// so, call the built in getParameter() method.
			return getParameter(strName);
		}
	
		// Else, running as standalone application.
		// Parameter values are obtained from the command line.
		//
		// The user specifies them as follows:
		//	JView simpleado param1=<val> param2=<"val with spaces"> ...
		//-----------------------------------------------------------------------
		int    i;
		String strArg	= strName + "=";
		String strValue = null;

		for (i = 0; i < args.length; i++)
		{
			if ( strArg.equalsIgnoreCase(args[i].substring(0, strArg.length()  )) )
			{
				// Found matching parameter on command line, so extract its value.
				// If in double quotes, remove the quotes.
				//---------------------------------------------------------------
				strValue = args[i].substring( strArg.length() );
				if (strValue.startsWith("\""))
				{
					strValue = strValue.substring(1);
					if (strValue.endsWith("\""))
						strValue = strValue.substring(0, strValue.length() - 1);
				}
			}
		}
		return strValue;
	}
	
	/******************************************************************
	* simpleado.GetParameters() Method
	* 
	* The GetParameters() method retrieves the values of each of the 
	* applet's parameters and stores them in variables.
	* 
	* Called both from HTML applet and standalone:
	* When the applet is run as a standalone application, this method is
	* called by the main() method, which passes it the command-line arguments.
	* When the applet is run within an HTML page, this method is called by the
	* init() method with args == null.
	* 
	* @param String - Takes the string list of arguments passed into
	*				  the application and parses them into applet 
	*				  defined parameter variables.
	* 
	*******************************************************************
	*/
	void GetParameters(String args[])
	{
		// Query values of all Parameters
		//--------------------------------------------------------------
		String param = "";

		// Connection: Parse and fill in new parameter, if specified
		param = GetParameter(PARAM_Connection, args);
		if (param != null)
			m_ConnectionString = param;

		// Recordset:  Parse and fill in new parameter, if specified
		param = GetParameter(PARAM_Command, args);
		if (param != null)
			m_CommandText = param;
	}
	
	/******************************************************************
	* simpleado.ActionListener.actionPerformed() Method
	* 
	* Implements standard method for the ActionListener interface
	* on the simpleado class.
	* 
	* Defines the actions to take when a Button is clicked.
	*
	*******************************************************************
	*/
	public void actionPerformed(ActionEvent evt)
	{		
		// Handle click on the First button
		if (evt.getSource() == m_first)
		{
			// Move to the requested record
			m_recordset.moveFirst();
			// Show that record
			m_form.showData();
		}
		
		// Handle click on the Prev button
		if (evt.getSource() == m_prev)
		{
			m_recordset.movePrevious();
			// Move to the requested record,
			// except if already there, to prevent falling off end.
			if ( m_recordset.getBOF() )
				m_recordset.moveFirst();
					
			// Show that record
			m_form.showData();
		}
		
		// Handle click on the Next button
		if (evt.getSource() == m_next)
		{
			// Move to the requested record
			m_recordset.moveNext();
			// except if already there, to prevent falling off end.
			if ( m_recordset.getEOF() )
				m_recordset.moveLast();

			// Show that record
			m_form.showData();
		}
		
		// Handle click on the Last button
		if (evt.getSource() == m_last)
		{
			// Move to the requested record
			m_recordset.moveLast();

			// Show that record
			m_form.showData();
		}
	}
	
	/******************************************************************
	* 
	* PrintProviderError Function
	* 
	* Called when an ADO connection attempt fails in a Try/Catch.
	* Displays the error message for debugging.
	* 
	* @param  Connection - Show the ADO errors collected from the 
	*					ADO Connection object.
	* 
	*******************************************************************
	*/
	static void PrintProviderError( Connection Cnn1 )
	{
		// Print errors from the ADO Errors collection via
		// the Connection object. These would be of a type
		// like connection failures.
		com.ms.wfc.data.Error	ErrItem = null;
		long					nCount	= 0;
		int						i		= 0;
		
		nCount = Cnn1.getErrors().getCount();
		
		// If there are any errors in the collection, print them.
		if( nCount > 0);  
		{
			// Collection ranges from 0 to nCount - 1
			for (i = 0; i< nCount; i++)
			{
				ErrItem = Cnn1.getErrors().getItem(i);
				System.out.println("\t Error number: " + ErrItem.getNumber()
						+ "\t" + ErrItem.getDescription() );
			}
		}
		
	}
}

/******************************************************************************
 *
 * SimpleForm Class
 * 
 * Called by simpleado class to set up and display the data to screen.
 *
 ******************************************************************************
*/

// SimpleForm is the data entry form for the sample
class SimpleForm extends Panel
{
	// Member recordset for access to the data
	Recordset m_FormRecordset;
	
	// Member TextField object array to display data in the form
	TextField m_rgFormFields[];
	
	/******************************************************************
	* SimpleForm Constructor
	* 
	* Builds an internal structure onto the Panel which can later be
	* used to display the data.
	* 
	* @param Recordset - Takes an ADO recordset from which it builds
	*					a model.
	*
	********************************************************************
	*/
	SimpleForm(Recordset rs)
	{
		// Populate member recordset with data already retrieved.
		m_FormRecordset = rs;
		
		// Create a field array to match the number of columns in recordset.
		m_rgFormFields = new TextField[m_FormRecordset.getFields().getCount()];

		// Create panels for the labels and fields.
		// The Label identifies the column, the field displays the value.
		Panel PanelLabels = new Panel();
		Panel PanelFields = new Panel();

		// Set those panels as a grid, each one column wide
		PanelLabels.setLayout(new GridLayout(0, 1));
		PanelFields.setLayout(new GridLayout(0, 1));

		// Set the form as labels to the left, fields to the right
		setLayout(new FlowLayout());
		add(PanelLabels);
		add(PanelFields);

		int			intCount;
		int			intIndex;
		Field		CurField;

		intCount = m_FormRecordset.getFields().getCount();
		for (intIndex = 0;
			 intIndex < intCount;
			 intIndex ++)
		{
			CurField = m_FormRecordset.getFields().getItem(intIndex);
			//	Create the label and add it into the form
			PanelLabels.add(new Label(CurField.getName()));

			//	Create the field and add it into the form
			m_rgFormFields[intIndex] = new TextField(40);
			PanelFields.add(m_rgFormFields[intIndex]);
		}
	}
		
	/******************************************************************
	* SimpleForm.showData Method
	* 
	* Displays the current row's data in the form.
	*
	*******************************************************************
	*/
	void showData()
	{
		// Get the fields in the recordset
		Fields fields = m_FormRecordset.getFields();
		int		intCount = fields.getCount();
		int		intIndex;
		Variant	value;
		String	strValue;

		for (intIndex = 0;
			 intIndex < intCount;
			 intIndex ++)
		{
			// Get its value
			value = fields.getItem(intIndex).getValue();

			if (value.getvt() == Variant.VariantNull)
				strValue = "";
			else
				strValue = value.toString();

			// Set the field in the form
			m_rgFormFields[intIndex].setText(strValue);
		}
	}
}
