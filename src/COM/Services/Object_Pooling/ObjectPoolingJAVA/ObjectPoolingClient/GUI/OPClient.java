import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;
import com.ms.wfc.html.*;

/**
 * This class can take a variable number of parameters on the command
 * line. Program execution begins with the main() method. The class
 * constructor is not invoked unless an object of type 'OPClient' is
 * created in the main() method.
 */
public class OPClient extends Form
{
	private account.Account_Dispatch acc_obj = null;
	public OPClient()
	{
		// Required for Visual J++ Form Designer support
		initForm();		

		// TODO: Add any constructor code after initForm call
	}

	/**
	 * OPClient overrides dispose so it can clean up the
	 * component list.
	 */
	public void dispose()
	{
		super.dispose();
		acc_obj = null;
		components.dispose();
	}

	/**
     * Process Balance check Button processing
     *
     * @param       ---
     * @return      ---
     **/	
	private void balanceCheck_click(Object source, Event e)
	{
		handleCheckBalance();
	}
	
	/**
     * Process debit account Button processing
     *
     * @param       ---
     * @return      ---
     **/
	private void debitAccount_click(Object source, Event e)
	{
		handleDebitAmount();
	}
	
	/**
     * Process credit account Button processing
     *
     * @param       ---
     * @return      ---
     **/
	private void creditAccount_click(Object source, Event e)
	{
		handleCreditAmount();
	}

	/**
     * Process transfer fund Button processing
     *
     * @param       ---
     * @return      ---
     **/
	private void transferFund_click(Object source, Event e)
	{
		handleTransferFunds();
	}

	/**
     * Debit the given amount from the account. 
     *
     * @param       ---
     * @return      ---
     * @see			com.ms.win32.Ole32.CoGetObject
     **/
	private void handleDebitAmount()
	{
		BalanceTF.setText("");
		try
		{
			if(acc_obj == null) // Check if account object is already created.
			{
				acc_obj = (account.Account_Dispatch)com.ms.win32.Ole32.CoGetObject("new:Account.Account",null,account.Account_Dispatch.iid);
			}
			if(acc_obj != null)
			{
				acc_obj.debit(AccountNumTF.getText(),Integer.parseInt(AmountTF.getText()));
				com.ms.win32.User32.MessageBox(0,"$"+AmountTF.getText() + " is debit from A/c : " + AccountNumTF.getText(),"Info",0);
			}
                                  
		}
		catch(com.ms.com.ComFailException exp)
		{
			System.out.println("Exception in Handle Debit Amount " + exp);
		}
	}
	
	/**
     * Credit the given amount to the account. 
     *
     * @param       ---
     * @return      ---
     * @see			com.ms.win32.Ole32.CoGetObject
     **/
	private void handleCreditAmount()
	{
		BalanceTF.setText("");
		try
		{
			if(acc_obj == null) // Check if account object is already created.
			{
				acc_obj = (account.Account_Dispatch)com.ms.win32.Ole32.CoGetObject("new:Account.Account",null,account.Account_Dispatch.iid);
			}
			if(acc_obj != null)
			{
				acc_obj.credit(AccountNumTF.getText(),Integer.parseInt(AmountTF.getText()));
				com.ms.win32.User32.MessageBox(0,"$" + AmountTF.getText() + " is credited to A/c : " + AccountNumTF.getText(),"Info",0);
			}
                                  
		}
		catch(com.ms.com.ComFailException exp)
		{
			System.out.println("Exception in Handle Credit Amount " + exp);
		}
	}
	
	/**
     * Check the balance of account. 
     *
     * @param       ---
     * @return      ---
     * @see			com.ms.win32.Ole32.CoGetObject
     **/
	private void handleCheckBalance()
	{
		AmountTF.setText("");
		try
		{
			if(acc_obj == null) // Check if account object is already created.
			{
				acc_obj = (account.Account_Dispatch)com.ms.win32.Ole32.CoGetObject("new:Account.Account",null,account.Account_Dispatch.iid);
			}
			if(acc_obj != null)
			{
				BalanceTF.setText(String.valueOf(acc_obj.checkBalance(AccountNumTF.getText())));
			}
                                  
		}
		catch(com.ms.com.ComFailException exp)
		{
			System.out.println("Exception in Handle Check Balance " + exp);
		}
	}
	
	/**
     * Transfer the fund between two accounts.
     *
     * @param       ---
     * @return      ---
     * @see			com.ms.win32.Ole32.CoGetObject
     **/
	private void handleTransferFunds()
	{
		AmountTF.setText("");
		AccountNumTF.setText("");
		BalanceTF.setText("");
		try
		{
			if(acc_obj == null) // Check if account object is already created.
			{
				acc_obj = (account.Account_Dispatch)com.ms.win32.Ole32.CoGetObject("new:Account.Account",null,account.Account_Dispatch.iid);
			}
			if(acc_obj != null)
			{
				acc_obj.transfer(fromAccountNumTF.getText(),toAccountNumTF.getText(),Integer.parseInt(transferAmountTF.getText()));
				com.ms.win32.User32.MessageBox(0,"$" +transferAmountTF.getText() + "  is transfered from A/c : " + fromAccountNumTF.getText() + " to A/c : " + toAccountNumTF.getText(),"Info",0);
			}
                                  
		}
		catch(com.ms.com.ComFailException exp)
		{
			System.out.println("Exception in Handle Check Balance " + exp);
		}
	}
	
	/**
	 * NOTE: The following code is required by the Visual J++ form
	 * designer.  It can be modified using the form editor.  Do not
	 * modify it using the code editor.
	 */
	Container components = new Container();
	GroupBox groupBox1 = new GroupBox();
	Edit AccountNumTF = new Edit();
	Edit AmountTF = new Edit();
	Edit BalanceTF = new Edit();
	Button balanceCheck = new Button();
	Button debitAccount = new Button();
	Button creditAccount = new Button();
	Edit fromAccountNumTF = new Edit();
	Edit toAccountNumTF = new Edit();
	Button transferFund = new Button();
	Edit transferAmountTF = new Edit();
	Label label1 = new Label();
	Label label2 = new Label();
	Label label3 = new Label();
	Label label4 = new Label();
	Label label5 = new Label();
	Label label6 = new Label();

	private void initForm()
	{
		this.setText("Bank Account");
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setClientSize(new Point(638, 262));

		groupBox1.setLocation(new Point(328, 0));
		groupBox1.setSize(new Point(304, 240));
		groupBox1.setTabIndex(0);
		groupBox1.setTabStop(false);
		groupBox1.setText("Transfer Funds");

		AccountNumTF.setLocation(new Point(104, 24));
		AccountNumTF.setSize(new Point(152, 20));
		AccountNumTF.setTabIndex(1);
		AccountNumTF.setText("");

		AmountTF.setLocation(new Point(104, 88));
		AmountTF.setSize(new Point(152, 20));
		AmountTF.setTabIndex(2);
		AmountTF.setText("");

		BalanceTF.setEnabled(false);
		BalanceTF.setLocation(new Point(104, 152));
		BalanceTF.setSize(new Point(152, 20));
		BalanceTF.setTabIndex(3);
		BalanceTF.setText("");

		balanceCheck.setLocation(new Point(8, 208));
		balanceCheck.setSize(new Point(72, 24));
		balanceCheck.setTabIndex(4);
		balanceCheck.setText("Balance");
		balanceCheck.addOnClick(new EventHandler(this.balanceCheck_click));

		debitAccount.setLocation(new Point(112, 208));
		debitAccount.setSize(new Point(72, 24));
		debitAccount.setTabIndex(5);
		debitAccount.setText("Debit");
		debitAccount.addOnClick(new EventHandler(this.debitAccount_click));

		creditAccount.setLocation(new Point(208, 208));
		creditAccount.setSize(new Point(72, 24));
		creditAccount.setTabIndex(6);
		creditAccount.setText("Credit");
		creditAccount.addOnClick(new EventHandler(this.creditAccount_click));

		fromAccountNumTF.setLocation(new Point(128, 32));
		fromAccountNumTF.setSize(new Point(160, 20));
		fromAccountNumTF.setTabIndex(0);
		fromAccountNumTF.setText("");

		toAccountNumTF.setLocation(new Point(128, 88));
		toAccountNumTF.setSize(new Point(160, 20));
		toAccountNumTF.setTabIndex(1);
		toAccountNumTF.setText("");

		transferFund.setLocation(new Point(112, 200));
		transferFund.setSize(new Point(96, 24));
		transferFund.setTabIndex(3);
		transferFund.setText("Transfer");
		transferFund.addOnClick(new EventHandler(this.transferFund_click));

		transferAmountTF.setLocation(new Point(128, 152));
		transferAmountTF.setSize(new Point(160, 20));
		transferAmountTF.setTabIndex(2);
		transferAmountTF.setText("");

		label1.setLocation(new Point(8, 24));
		label1.setSize(new Point(72, 16));
		label1.setTabIndex(7);
		label1.setTabStop(false);
		label1.setText("Account Num");

		label2.setLocation(new Point(8, 96));
		label2.setSize(new Point(72, 16));
		label2.setTabIndex(8);
		label2.setTabStop(false);
		label2.setText("Amount");

		label3.setLocation(new Point(8, 156));
		label3.setSize(new Point(64, 16));
		label3.setTabIndex(9);
		label3.setTabStop(false);
		label3.setText("Balance");

		label4.setLocation(new Point(16, 32));
		label4.setSize(new Point(96, 16));
		label4.setTabIndex(4);
		label4.setTabStop(false);
		label4.setText("Account Num(From)");

		label5.setLocation(new Point(16, 88));
		label5.setSize(new Point(96, 16));
		label5.setTabIndex(5);
		label5.setTabStop(false);
		label5.setText("Account Num(To)");

		label6.setLocation(new Point(16, 152));
		label6.setSize(new Point(104, 16));
		label6.setTabIndex(6);
		label6.setTabStop(false);
		label6.setText("Transfer Amount");

		this.setNewControls(new Control[] {
							label3, 
							label2, 
							label1, 
							creditAccount, 
							debitAccount, 
							balanceCheck, 
							BalanceTF, 
							AmountTF, 
							AccountNumTF, 
							groupBox1});
		groupBox1.setNewControls(new Control[] {
								 label6, 
								 label5, 
								 label4, 
								 transferFund, 
								 transferAmountTF, 
								 toAccountNumTF, 
								 fromAccountNumTF});
	}

	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	public static void main(String args[])
	{
		Application.run(new OPClient());
	}
}
