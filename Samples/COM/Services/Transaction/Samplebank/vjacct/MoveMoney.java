// ==============================================================================
// Filename: MoveMoney.java
//
// Summary:  Visual J++ implememtation of the MoveMoney class for the bank sample
// Classes:  MoveMoney.java
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

import vcacct.*;

/**
 * @com.register ( clsid=C27A1A33-0A80-11D3-A5E7-00C04F79B3EA, typelib=C27A1A30-0A80-11D3-A5E7-00C04F79B3EA )
 */

// F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
//
// Function: Perform
//
// Perform() performs error handling for TruePerform().  If TruePerform() throws an 
// exception, then Perform() will call SetAbort() and pass the exception up 
// to the caller.  Otherwise, Perform() will simply call SetComplete() and return.
//
// Args:     lngPrimeAccount -   "From" Account
//           lngSecondAccount -  "To" Account
//           lngAmount -         Amount of transaction
//           lngTranType -       Transaction Type
//                               (1 = Withdrawal,
//                                2 = Deposit,
//                                3 = Transfer)
//
// Returns:  String -        Account Balance
//
// F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---

/**
 * @com.register ( clsid=177968BC-0E3F-11D3-A5EB-00C04F79B3EA, typelib=C27A1A30-0A80-11D3-A5E7-00C04F79B3EA )
 */
public class MoveMoney implements IMoveMoney {
	
	public String Perform (int lngPrimeAccount, int lngSecondAccount, int lngAmount, int tranType) throws ComFailException {

		String result;
		boolean bSuccess = false;

		// First of all, get the object context
		IObjectContext ctxObject = Context.getObjectContext();

		try {
			// Check for security
			if ((lngAmount > 500 || lngAmount < -500) && !ctxObject.IsCallerInRole ("Managers"))
			//if ((lngAmount > 500 || lngAmount < -500) && (ctxObject.IsCallerInRole ("Managers") != 0 ))
				throw new ComFailException ("Need 'Managers' role for amounts over $500");
			
			// Call the true function
			result = truePerform (lngPrimeAccount, lngSecondAccount, lngAmount, tranType);
			
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
	// Function: Perform
	//
	// TruePerform() is the function that performs the actual work for the Account class.
	// If an error occurs during execution, it will throw a ComFailException for Perform()
	// to handle.
	//
	// Args:     lngPrimeAccount -   "From" Account
	//           lngSecondAccount -  "To" Account
	//           lngAmount -         Amount of transaction
	//           lngTranType -       Transaction Type
	//                               (1 = Withdrawal,
	//                                2 = Deposit,
	//                                3 = Transfer)	
	//
	// Returns:  String -        Account Balance
	//
	// F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---
	
	private String truePerform (int lngPrimeAccount, int lngSecondAccount, int lngAmount, int tranType)
		throws ComFailException {

		String result;
		vcacct.IAccount objAccount = null;
		IGetReceipt objReceipt = null;
		
		try {
			// Create the account object
			objAccount = (vcacct.IAccount) Context.getObjectContext().CreateInstance 
		    		(CAccount.clsid, vcacct.IAccount.iid);

			switch (tranType)
			{
			case 1:		// debit
				result = objAccount.Post (lngPrimeAccount, (- lngAmount));
				break;

			case 2:		// credit
				result = objAccount.Post (lngPrimeAccount, lngAmount);
				break;

			case 3:		// transfer
				result = objAccount.Post (lngPrimeAccount, (- lngAmount));
				result += "    ";
				result += objAccount.Post (lngSecondAccount, lngAmount);
				break;

			default:
				throw new ComFailException ("Invalid transaction type");
			}

			// Get the receipt for the transaction
			objReceipt = (IGetReceipt) Context.getObjectContext().CreateInstance 
					(CGetReceipt.clsid, IGetReceipt.iid);
			int iReceiptNo = objReceipt.GetNextReceipt ();
			result += "; Receipt No:  " + iReceiptNo;

			return result;
		}

		finally {
			// The following code is not strictly necessary. By calling ComLib.release here,
			// the object counts seen in the MTX explorer remain correct. Without these release
			// calls, the objects used here would not get released until after the next time
			// the Java garbage collector runs. No other ill effect would be caused by omitting
			// this code.

			// Note that this code will be executed regardless of whether we leave this
			// method via return or via an exception.
			if (objAccount != null) ComLib.release (objAccount);
			if (objReceipt != null) ComLib.release (objReceipt);
		}
	}
}
