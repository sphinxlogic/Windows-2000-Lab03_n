// ==============================================================================
// Filename: UpdateReceipt.java
//
// Summary:  Visual J++ implememtation of the UpdateReceipt class for the bank sample
// Classes:  UpdateReceipt.java
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
 * @com.register ( clsid=C27A1A34-0A80-11D3-A5E7-00C04F79B3EA, typelib=C27A1A30-0A80-11D3-A5E7-00C04F79B3EA )
 */
public class UpdateReceipt implements IUpdateReceipt {

	// F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
	//
	// Function: Update
	//
	// Update() performs error handling for TrueUpdate().  If TrueUpdate() throws an 
	// exception, then Update() will call SetAbort() and pass the exception up 
	// to the caller.  Otherwise, Update() will simply call SetComplete() and return.
	//
	// Args:     None
	// Returns:  Long -  next receipt value
	//            -1 if Error
	//
	// F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---

	public int Update () throws ComFailException {

		int result;
		boolean bSuccess = false;

		// First of all, get the object context
		IObjectContext ctxObject = Context.getObjectContext();
		
		try {
			// Call the true function
			result = trueUpdate ();

			bSuccess = true;
			return result;
		}

		// Upon exit, always call SetComplete if happy, or SetAbort if unhappy.
		// We do this because we never save state across method calls.
		finally {
			if (ctxObject !=null)
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
	// Function: trueUpdate
	//
	// trueUpdate() is the function that performs the actual work for the Account class.
	// If an error occurs during execution, it will throw a ComFailException for Update()
	// to handle.
	//
	// Args:     None
	// Returns:  Long -  next receipt value
	//            -1 if Error
	//
	// F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---

	private int trueUpdate () throws ComFailException {
		
		_Connection adoConn = null;
		_Recordset adoRsReceipt = null;
		Field pField = null;
		Fields pFields = null;

		try {
			// Create ADOConnection object and initialize the connection
			adoConn = (_Connection) new Connection();
			String vDSN = "FILEDSN=BankSample";
			adoConn.Open (vDSN, null, null, CommandTypeEnum.adCmdUnspecified);
			
			// Obtain the desired recordset with an SQL query
			Variant	vAdoNull = new Variant();

			String strSQL = "Update Receipt set NextReceipt = NextReceipt + 100";
			adoConn.Execute (strSQL, vAdoNull, - 1);

			strSQL = "Select NextReceipt from Receipt";
			adoRsReceipt = adoConn.Execute (strSQL, vAdoNull, - 1);
			
			// Get the appropriate fields
			pFields = adoRsReceipt.getFields();
			
			// Get the appropriate field
			Variant vField = new Variant();
			Variant lngNextReceipt = new Variant();
			vField.putString ("NextReceipt");
			
			pField = pFields.getItem(vField);
			lngNextReceipt = pField.getValue();
			
			return lngNextReceipt.getInt();
		}

		finally {
			// cleanup that needs to occur whether we leave via a return or an exception.
			if (adoRsReceipt != null) {
				if (adoRsReceipt.getState() == ObjectStateEnum.adStateOpen)
					adoRsReceipt.Close();
				ComLib.release (adoRsReceipt);
			}

			if (adoConn != null) {
				if (adoConn.getState() == ObjectStateEnum.adStateOpen)
					adoConn.Close();
				ComLib.release (adoConn);
			}
		}
	}
}
