// ==============================================================================
// Filename: Account.java
//
// Summary:  Visual J++ implememtation of the account class for the bank sample
// Classes:  Account.java
//
// This file is part of the Microsoft COM+ Samples
//
// Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved
//
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation.  See these other
// materials for detailed information reagrding Microsoft code samples.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//

import com.ms.mtx.*;
import com.ms.com.*;

import msado15.*;
import vcacct.*;


/**
 * @com.register ( clsid=C27A1A31-0A80-11D3-A5E7-00C04F79B3EA, typelib=C27A1A30-0A80-11D3-A5E7-00C04F79B3EA )
 */
public class Account implements vcacct.IAccount {
	
	// F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
	//
	// Function: Post
	//
	// Post() performs error handling for TruePost().  If Truepost() throws an exception,
	// then Post() will call SetAbort() and pass the exception up to the caller.  Otherwise,
	// Post() will simply call SetComplete() and return.
	//
	// Args:     lngAccountNo -    Account to be posted
	//           lngAmount -     Amount to be posted
	// Returns:  String -        Account Balance
	//
	// F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---

	public String Post (int lngAccountNo, int lngAmount) throws ComFailException {

		String result;
		boolean bSuccess = false;


		// First of all, get the object context
		IObjectContext ctxObject = MTx.GetObjectContext();

	
		try {
	
			// Check for security
			if ((lngAmount > 500 || lngAmount < -500) && !ctxObject.IsCallerInRole ("Managers"))
			//if ((lngAmount > 500 || lngAmount < -500) && (ctxObject.IsCallerInRole ("Managers")!= 0))
				throw new ComFailException ("Need 'Managers' role for amounts over $500");
			// Call the true function

			result = truePost (lngAccountNo, lngAmount);

			bSuccess = true;
			return result;
		}

		// Upon exit, always call SetComplete if happy, or SetAbort if unhappy.
		// We do this because we never save state across method calls.
		finally {

			if (ctxObject!=null)
			{
				if (bSuccess)
					ctxObject.SetComplete();
				else
					ctxObject.SetAbort();
			}
		}
	}

	// F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
	//
	// Function: TruePost
	//
	// TruePost() is the function that performs the actual work for the Account class.
	// If an error occurs during execution, it will throw a ComFailException for Post() to
	// handle.
	//
	// Args:     lngAccountNo -    Account to be posted
	//           lngAmount -     Amount to be posted
	// Returns:  String -        Account Balance
	//
	// F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---

	private String truePost (int lngAccountNo, int lngAmount) throws ComFailException {

		_Recordset adoRsBalance  = null;
		_Connection adoConn = null;
		Field pField = null;
		Fields pFields = null;
		String result;
		
		try {
			// Create ADOConnection object and initialize the connection

			adoConn = (_Connection) new Connection();
			String vDSN = "FILEDSN=BankSample";
			adoConn.Open (vDSN, null, null, CommandTypeEnum.adCmdUnspecified);

			// Obtain the desired recordset with an SQL query
			Variant	vRowCount = new Variant();

			String strSQL = "UPDATE Account SET Balance = Balance + " + lngAmount + 
				" WHERE AccountNo = " + lngAccountNo;
			adoConn.Execute (strSQL, vRowCount, ExecuteOptionEnum.adExecuteNoRecords);

			// See whether the record is present.
			if (vRowCount.getInt() == 0)
				throw new ComFailException ("Error. Account " + lngAccountNo + " not on file.");

			strSQL = "SELECT Balance FROM Account WHERE AccountNo = " + lngAccountNo;
			adoRsBalance = adoConn.Execute (strSQL, new Variant(), - 1);
			
			// Get the appropriate fields
			pFields = adoRsBalance.getFields();
			
			// Get the appropriate field
			Variant vField = new Variant();
			Variant vBalance = new Variant();
			vField.putString ("Balance");
			
			pField = pFields.getItem (vField);
			vBalance = pField.getValue ();
			int lngBalance = vBalance.getInt();
			
			// Check if account is overdrawn, then prepare return string
			if ((lngBalance) < 0)
				throw new ComFailException("Error. Account " + lngAccountNo + " would be overdrawn by "
						+ (-lngBalance) + ". Balance is still " + (lngBalance - lngAmount) + ".");

			if (lngAmount > 0)
				result = "Credit to";
			else
				result = "Debit from";
			result += " account " + lngAccountNo + ", balance is $" + lngBalance + ".  (VJ++)";

			return result;
		}

		finally {
			// cleanup that needs to occur whether we leave via a return or an exception.
			if (adoRsBalance != null) {
				if (adoRsBalance.getState() == ObjectStateEnum.adStateOpen)
					adoRsBalance.Close();
				ComLib.release (adoRsBalance);
			}

			if (adoConn != null) {
				if (adoConn.getState() == ObjectStateEnum.adStateOpen)
					adoConn.Close();
				ComLib.release (adoConn);
			}
		}
	}
}
