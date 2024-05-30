/**
 * This class can take a variable number of parameters on the command
 * line. Program execution begins with the main() method. The class
 * constructor is not invoked unless an object of type 'Class1'
 * created in the main() method.
 */
import com.ms.wfc.data.*;
public class InitDatabase
{
	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	private Connection	con	=	null;
	
	public static void main (String[] args)
	{
		// TODO: Add initialization code here
		InitDatabase dbHandler = new InitDatabase();
		dbHandler.handleTableCreation(); // Create bank table 
		dbHandler.insertData(); // insert data into bank table
		com.ms.win32.User32.MessageBox(0,"Done", "Info" ,0);
		
	}
	/**
     * It will first drop the bank table and then create new bank table.
     *
     * @param       ---
     * @return      ---
     **/
	private void handleTableCreation()
	{
		StringBuffer sql	=	new StringBuffer("");
		if(con == null)
		{
			InitializeDB(); // Get the connection to database.
		}
		try
		{
			con.execute("Drop table Bank"); // Drop the old bank table
			createTable(); // create new bank table
		}
		catch(com.ms.wfc.data.AdoException exp)
		{
			createTable(); // In case old bank table is not present.
		}
		
	}
	/**
     * It creates new bank table.
     *
     * @param       ---
     * @return      ---
     **/
	private void createTable()
	{
		try
		{
			con.execute("Create Table Bank (account_no VarChar(10),balance money)");
		}
		catch(Exception exp)
		{
			System.out.println(exp);
		}
	}
	
	/**
     * Insert the intial data into bank table.
     *
     * @param       ---
     * @return      ---
     **/
	private void insertData()
	{
		int index = 0;
		if(con == null)
		{
			InitializeDB();
		}
		for(index = 0; index < 30; index++)
		{
			con.execute(createSql(index + 1));
		}
	}
	
	/**
     * Return sql statement for inserting record into bank table.
     *
     * @param       index		Account number.
     * @return      ---
     **/
	private String createSql(int index)
	{
		StringBuffer sql	=	new StringBuffer("");
		sql.append("insert into Bank values ( ");
		sql.append(String.valueOf(index));
		sql.append(",");
		sql.append(String.valueOf(index * 100) + " )"); 
		return (sql.toString());
	}
	
	/**
     * Initialize and create connection with the database.
     *
     * @param       ---
     * @return      Connection		Database connection.
     * @see			com.ms.wfc.data.Connection
     **/
	private Connection InitializeDB()
	{
		String		conDetail	=	null;
		conDetail	=	"Data Source=" + util.DatabaseSettings.DSN + ";" + "User Id=" + util.DatabaseSettings.User+ ";" + "Password=" + util.DatabaseSettings.pass + ";";
		con			=	new Connection();
		con.open(conDetail);
		return con;
			
	}
}
