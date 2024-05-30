package crmfilesvj;

/*+==========================================================================
File: crmfilesvj.Worker.java

Summary: 
	This is a sample Compensating Resource Manager (CRM) that creates and 
	deletes files. The CRM Worker provides an interface for creating or 
	deleting files.The CRM Compensator implements ICrmCompensator to receive 
	transaction outcome notifications. The CRM Compensator also implements 
	ICrmFormatLogRecords to support monitoring.

	This CRM can be installed in a server application or in a library
	application. The CRM Worker requires a transaction. The CRM Compensator
	should not have a transaction.

Classes: Worker

----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/


//
// Auto-generated using JActiveX.EXE 5.00.3167.1
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /b+ /xh  /w /xi /X:rkc /l "C:\DOCUME~1\Davidno\LOCALS~1\Temp\jvc1D3.tmp" /nologo /d "P:\COMPlus\SDK\samples\com\Services\CRM" "\\DAVIDNO-1\Visual Studio Projects\COMPlus\SDK\samples\com\Services\CRM\CrmFilesVJ\CrmFilesVJ.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

import com.ms.com.*;
import com.ms.wfc.io.File;
import com.ms.wfc.util.Debug;

import comsvcs.CRMClerk;
import comsvcs.ICrmLogControl;
import comsvcs.IObjectControl;
import comsvcs.tagCRMREGFLAGS;
import comsvcs.XACTE;


/** @com.register(
 *		clsid=6596BAAA-ED34-11D2-BA28-00A0CC3901C7, 
 *		typelib=DBE637F8-F3B5-11D2-BA35-00A0CC3901C7, 
 *		version="1.0", 
 *		description="crmfilesvj.Worker Class"
 * )*/

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: Worker

	This is the CRM Worker. All work done on the resource during the transaction
	is done through this object

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 


public class Worker implements IUnknown,com.ms.com.NoAutoScripting,crmfilesvj.ICrmFilesWorkerDefault,comsvcs.IObjectControl
	{
	/** Fields */

	private ICrmLogControl m_crmLogControl;
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Worker()

Summary: Constructor (facilitates debugging)

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	Worker()
		{
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CreateFile

Summary: Logs the fact we created a file, then creates a file. 

Args: String bstrFileName

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	
	public void CreateFile(String bstrFileName) 
		{
		Debug.print( "cmrfilesvj.Worker.CreateFile( " + bstrFileName.toString() + " )\n" );
		GetCrmLogControl();

		if ( File.exists( bstrFileName ) )
			m_crmLogControl.ForceTransactionToAbort();

		// WRITE AHEAD - Log that we are about to create the file

		SafeArray saLogRecord = new SafeArray( Variant.VariantVariant, 2 );
		
		saLogRecord.setInt( 0, CommandType.ct_CreateFile );
		saLogRecord.setString( 1, bstrFileName );

		Debug.print( "1.\n" );
		m_crmLogControl.WriteLogRecordVariants( new Variant( saLogRecord, false ) );

		// Ensure the durability of the log record in the log
		
		Debug.print( "2.\n" );
		m_crmLogControl.ForceLog();

		// Create the file

		Debug.print( "3.\n" );
		File.create( bstrFileName );
		
		Debug.print( "4.\n" );
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: DeleteFile

Summary: Logs the fact we will delete a file, then renames the file. 

Args: String bstrFileName

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	public void DeleteFile( String bstrFileName ) 
		{
		Debug.print( "cmrfilesvj.Worker.DeleteFile( " + bstrFileName.toString() + " )\n" );
		GetCrmLogControl();

		if ( ! File.exists( bstrFileName ) )
			return; // not an error if the file doesn't exist
		
		// WRITE AHEAD - Log that we are about to delete (rename) a file

		// We're vulnerable, but we'll accept the risk that someone could delete
		// this file before we rename it

		// Leverage the fact that the file we're renaming is unique
		
		String tempFileName = bstrFileName + ".crmtemp";
			
		SafeArray saLogRecord = new SafeArray( Variant.VariantVariant, 3 );
		
		saLogRecord.setInt( 0, CommandType.ct_DeleteFile );
		saLogRecord.setString( 1, bstrFileName );
		saLogRecord.setString( 2, tempFileName );

		Debug.print( "1.\n" );
		m_crmLogControl.WriteLogRecordVariants(new Variant(saLogRecord,false));

		// Ensure the durability of the log record in the log
		
		Debug.print( "2.\n" );
		m_crmLogControl.ForceLog();

		// Rename the file

		Debug.print( "3.\n" );
		File.rename( bstrFileName, tempFileName );
		}
	
/***************
  comsvcs.IObjectControl Methods 
****************/
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Activate

Summary: Allows an object to perform context-specific initialization whenever
		 it's activated. This method is called by COM+ before any other methods 
		 are called on the object.
Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	
	public void Activate() throws ComFailException
		{
		Debug.print( "cmrfilesvj.Worker.Activate()\n" );
		
		if ( m_crmLogControl != null )
			throw new ComFailException();
		}
	
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Deactivate

Summary: Allows an object to perform whatever cleanup is necessary before 
		 it's recycled or destroyed. This method is called by COM+ whenever an 
		 object is deactivated.
	
Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	public void Deactivate()
		{
		Debug.print( "cmrfilesvj.Worker.Deactivate()\n" );

		m_crmLogControl = null; // Let the Java garbase collector release this 
								// object on its own time
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CanBePooled

Summary: Allows an object to notify COM+ of whether it can be pooled for
		 reuse.
	
Returns: int

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public int CanBePooled()
		{
		Debug.print( "cmrfilesvj.Worker.Deactivate()\n" );
		return 1; // Indicates that this object can be pooled
		}
	
/***************
 private Methods 
 ***************/
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: GetCrmLogControl

Summary: Register the CRM Compensator with the CRM infrastructure.
	
Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


	private void GetCrmLogControl() throws ComFailException
		{
		Debug.print( "cmrfilesvj.Worker.GetCrmLogControl()\n" );
		
		if ( m_crmLogControl != null )
			return;

		// Try to register our CRM Compensator (try 5X if recovery is in progress)

		m_crmLogControl = ( ICrmLogControl ) new CRMClerk();
		String progID = "crmfilesvj.Compensator"; //"CrmDebugCompensator.CrmDebugCompensator.1";
		
		for ( int i = 0; i < 5; i++ )
			{
			try
				{
				m_crmLogControl.RegisterCompensator( progID,
					"Compensator for the Java implementation of the COM+ CRM Sample",
					tagCRMREGFLAGS.CRMREGFLAG_ALLPHASES );
				Debug.print( "CrmFilesVJ.Compensator registration completed\n" );
				return;
				}
			catch ( ComFailException exception )
				{
				if ( XACTE.XACT_E_RECOVERYINPROGRESS != exception.getHResult() )
					{
					Debug.print( "CrmFilesVJ.Compensator registration of " +
								 progID + " failed: " + 
								 exception.getMessage() );
					throw exception;
					}
				}

			try {
				Thread.sleep( 1000L );
				}
			catch ( InterruptedException exception )
				{
				throw new ComFailException( "Interrupted while trying to register CrmFilesVJ.Compensator" );
				}
			}

		throw new ComFailException( "Timed out waiting to register CrmFilesVJ.Compensator" );
		}
	}
