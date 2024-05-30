// 
//----------------------------------------------------------------------------
//
// This is a sample file that shows how to connect to a ODBC data source.
// Please make sure you have a valid data source URL in your url variable.
// Copyright (C) 1997 Microsoft Corporation All rights reserved 
//
//----------------------------------------------------------------------------


import java.sql.*;

class SimpleSelect {


public static void main (String args[]) {
	String url   = "JDBC:ODBC:my_dsn";
	String query = "SELECT * FROM authors"; 

	try {

		// Load the jdbc-odbc bridge driver

		Class.forName ("com.ms.jdbc.odbc.JdbcOdbcDriver");

		DriverManager.setLogStream(System.out);

		// Attempt to connect to a driver.  

		Connection con = DriverManager.getConnection (
			url, "my_user", "my_pwd");

		// If we were unable to connect, an exception
		// would have been thrown.  So, if we get here,
		// we are successfully connected to the URL

		// Check for, and display and warnings generated
		// by the connect.

		checkForWarning (con.getWarnings ());

		// Get the DatabaseMetaData object and display
		// some information about the connection

		DatabaseMetaData dma = con.getMetaData ();

		System.out.println("\nConnected to " + dma.getURL());
		System.out.println("Driver       " + 
			dma.getDriverName());
		System.out.println("Version      " +
			dma.getDriverVersion());
		System.out.println("");

		// Create a Statement object so we can submit
		// SQL statements to the driver

		Statement stmt = con.createStatement ();

		// Submit a query, creating a ResultSet object

		ResultSet rs = stmt.executeQuery (query);

		// Display all columns and rows from the result set

		dispResultSet (rs);

		// Close the result set

		rs.close();

		// Close the statement

		stmt.close();

		// Close the connection

		con.close();
	}

	catch (SQLException ex) {

		// A SQLException was generated.  Catch it and
		// display the error information.  Note that there
		// could be multiple error objects chained
		// together

	System.out.println ("\n*** SQLException caught ***\n");

	while (ex != null) {
		System.out.println ("SQLState: " +
				ex.getSQLState ());
		System.out.println ("Message:  " + ex.getMessage ());
		System.out.println ("Vendor:   " +
				ex.getErrorCode ());
		ex = ex.getNextException ();
		System.out.println ("");
		}
	}
	catch (java.lang.Exception ex) {

		// Got some other type of exception.  Dump it.

		ex.printStackTrace ();
	}
}

//-------------------------------------------------------------------
// checkForWarning
// Checks for and displays warnings.  Returns true if a warning
// existed
//-------------------------------------------------------------------

private static boolean checkForWarning (SQLWarning warn) 	
										throws SQLException  {
	boolean rc = false;

	// If a SQLWarning object was given, display the
	// warning messages.  Note that there could be
	// multiple warnings chained together

	if (warn != null) {
		System.out.println ("\n *** Warning ***\n");
		rc = true;
		while (warn != null) {
			System.out.println ("SQLState: " +
				warn.getSQLState ());
			System.out.println ("Message:  " +
				warn.getMessage ());
			System.out.println ("Vendor:   " +
				warn.getErrorCode ());
			System.out.println ("");
			warn = warn.getNextWarning ();
		}
	}
	return rc;
}

//-------------------------------------------------------------------
// dispResultSet
// Displays all columns and rows in the given result set
//-------------------------------------------------------------------

private static void dispResultSet (ResultSet rs)
	throws SQLException
{
	int i;

	// Get the ResultSetMetaData.  This will be used for
	// the column headings

	ResultSetMetaData rsmd = rs.getMetaData ();

	// Get the number of columns in the result set

	int numCols = rsmd.getColumnCount ();

	// Display column headings

	for (i=1; i<=numCols; i++) {
		if (i > 1) System.out.print(",");
		System.out.print(rsmd.getColumnLabel(i));
	}
	System.out.println("");
	
	// Display data, fetching until end of the result set

	boolean more = rs.next ();
	while (more) {

		// Loop through each column, getting the
		// column data and displaying

		for (i=1; i<=numCols; i++) {
			if (i > 1) System.out.print(",");
			System.out.print(rs.getString(i));
		}
		System.out.println("");

		// Fetch the next result set row

		more = rs.next ();
	}
}

}

