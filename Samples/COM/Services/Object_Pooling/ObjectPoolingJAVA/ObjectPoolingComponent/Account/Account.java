/**
 * This class is designed to be packaged with a COM DLL output format.
 * The class has no standard entry points, other than the constructor.
 * Public methods will be exposed as methods on the default COM interface.
 * @com.register ( clsid=C53A6925-551C-448C-97EB-47A97524F13D, typelib=98936258-26B9-41F4-97D5-34DE3EC42397 )
 */
import com.ms.wfc.data.*;

/**
 * @com.register ( clsid=F3BB4B90-8E5C-4F3E-B1DD-8CD6359990F0, typelib=6772DDE7-7A05-47D0-B913-94644899ABCC )
 */
public class Account 
{
	// TODO: Add additional methods and code here

	/**
	 * NOTE: To add auto-registration code, refer to the documentation
	 * on the following method
	 *   public static void onCOMRegister(boolean unRegister) {}
	 */
	
	private Connection	con			=	null;
	
	/**
     * Debit the given amount from the account. 
     *
     * @param       accountNo		Account number from whom the amount is to be debited.
     * @param		amount			Amount to be debited.
     * @return      ---
     **/
	public void debit(String accountNo , long amount)
	{
		if(checkAccount(accountNo)) //Check if account number is valid.
		{
			updateBalance(accountNo , amount * (-1)); // debit the amount from the account.
		}
	}
	
	/**
     * Credit the given amount to the account. 
     *
     * @param       accountNo		Account number to whom the amount is to be credited.
     * @param		amount			Amount to be credited.
     * @return      ---
     **/
	public void credit(String accountNo, long amount)
	{
		if(checkAccount(accountNo)) // Check if account number is valid.
		{
			updateBalance(accountNo , amount); // credit the amount to the account.
		}
	}
	
	/**
     * Transfer the funds between two accounts.
     *
     * @param       accountFrom		Account number from whom the funds are to be transfered
     * @param		accountTo		Account number to whom the funds are to be transfered.
     * @param		amount			Amount to be transfered.
     * @return      ---
     **/
	public void transfer(String accountFrom, String accountTo , long amount)
	{
		if(checkAccount(accountFrom)) // Check if the source account is valid.
		{
			if(checkAccount(accountTo)) // Check if the destination account is valid.
			{
				debit(accountFrom , amount); // debit the amount from the source account.
				credit(accountTo , amount); // credit the amount to the destination account.
			}
		}
	}
	
	/**
     * Check account balance 
     *
     * @param       accountNo		Account number. 
     * @return      long			Account Balance.
     * @see			com.ms.wfc.data.Recordset
     * @see			com.ms.wfc.data.Connection
     **/
	public long checkBalance(String accountNo)
	{
		long			balance		=	0;
		StringBuffer	sql			=	null;
		Recordset		rs			=	null;
		try
		{
			rs		=	new Recordset();
			sql		=	new StringBuffer("");
			sql.append("Select Balance from Bank"); 
			sql.append(" Where account_no = '" + accountNo + " '");
			rs = (InitializeDB()).execute(sql.toString()); // Execute the sql to check balance.
			while(!rs.getEOF())
			{
				balance   = rs.getField("balance").getLong(); // retrive the balance of the account from the recordset.
				rs.moveNext();
			}
		}
		catch(Exception exp)
		{
			com.ms.win32.User32.MessageBox(0,"Exception in check balance", exp.getMessage(),0);
		}
		finally
		{
			if(rs != null) // if recordset is not null, then release the recordset resources.
			{
				rs.close();
			}
			if(con != null)// if connection is not null, then release the connection resources.
			{
				con.close();
				con = null;
			}
		}
		
		
		return balance;
	}
	
	/**
     * Update the account balance in database 
     *
     * @param       accountNo		Account number. 
     * @return      long			Amount to be updated.
     * @see			com.ms.wfc.data.Connection
     **/
	private void updateBalance(String accountNo , long amount)
	{
		long		 currentBalance	=	0;
		StringBuffer sql			=	null;
		int			 result			=	0;
		try
		{
			currentBalance = checkBalance(accountNo);// Check account balance.
			sql		=	new StringBuffer("");
			sql.append("Update Bank set Balance = ");
			sql.append(String.valueOf(currentBalance + amount));
			sql.append(" Where account_no = '" + accountNo + "'");
			result = (InitializeDB()).executeUpdate(sql.toString());// update the account balance.
			
		}
		catch(Exception exp)
		{
			com.ms.win32.User32.MessageBox(0,"Exception in Update Balance", exp.getMessage(),0);
		}
		finally
		{
			if(con != null)// if connection is not null, then release the connection resources.
			{
				con.close();
				con = null;
			}
		}
		
	}
	
	/**
     * Initialize and create the database connection. 
     *
     * @param       ---
     * @return      ---
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
	
	/**
     * Check if account number is valid account.
     *
     * @param       accountNo		Account number. 
     * @return		boolean			True if account number is valid.
     * @see			com.ms.wfc.data.Recordset
     * @see			com.ms.wfc.data.Connection
     **/
	private boolean checkAccount(String accountNo)
	{
		boolean		accountValidFlag	=	false;
		StringBuffer	sql				=	null;
		Recordset		rs				=	null;
		try
		{
			rs		=	new Recordset();
			sql		=	new StringBuffer("");
			sql.append("Select account_no from Bank"); 
			sql.append(" Where account_no = '" + accountNo + "'");
			rs = (InitializeDB()).execute(sql.toString());
			while(!rs.getEOF())
			{
				accountValidFlag = true;// if account number is valid.
				rs.moveNext();
			}
		}
		catch(Exception exp)
		{
			com.ms.win32.User32.MessageBox(0,"Exception in check balance", exp.getMessage(),0);
		}
		finally
		{
			if(rs != null)// if recordset is not null, then release the recordset resources.
			{
				rs.close();
			}
			if(con != null)// if connection is not null, then release the connection resources.
			{
				con.close();
				con = null;
			}
		}
		return accountValidFlag;
	}
}
