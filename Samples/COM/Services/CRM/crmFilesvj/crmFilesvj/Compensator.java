package crmfilesvj;

/*+==========================================================================
File: crmfilesvj.Compensator.java

Summary: 
	This is a sample Compensating Resource Manager (CRM) that creates and 
	deletes files. The CRM Worker provides an interface for creating or 
	deleting files.The CRM Compensator implements ICrmCompensator to receive 
	transaction outcome notifications. The CRM Compensator also implements 
	ICrmFormatLogRecords to support monitoring.

	This CRM can be installed in a server application or in a library
	application. The CRM Worker requires a transaction. The CRM Compensator
	should not have a transaction.

Classes: Compensator

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

import comsvcs.ICrmCompensatorVariants;
import comsvcs.ICrmLogControl;

/** @com.register( 
 *		clsid=E39660F2-ED34-11D2-BA28-00A0CC3901C7, 
 *		typelib=DBE637F8-F3B5-11D2-BA35-00A0CC3901C7, 
 *		version="1.0", 
 *		description="crmfilesvj.Compensator Class"
 * )*/

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: Compensator

	This is the CRM Compensator. It is created once a transaction is completed

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 


public class Compensator implements IUnknown,com.ms.com.NoAutoScripting,comsvcs.ICrmCompensatorVariants
	{
	/**	Fields */
	
	private ICrmLogControl m_crmLogControl;

	private int		m_commandType;
	private String	m_permFileName;
	private String	m_tempFileName;

	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Compensator()

Summary: Constructor (facilitates debugging)

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
	
	Compensator()
		{
		}
	
/***********************
 ICrmCompensator Methods
 ***********************/
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: SetLogControlVariants

Summary: Delivers an ICrmLogControl interface to the CRM Compensator.
	
Args: comsvcs.ICrmLogControl crmLogControl

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public void SetLogControlVariants( comsvcs.ICrmLogControl crmLogControl )
		{
		Debug.print( "cmrfilesvj.Compensator.SetLogControlVariants\n" );
	    m_crmLogControl = crmLogControl;
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: BeginPrepareVariants

Summary: Notifies the CRM Compensator of the prepare phase of the transaction completion and that records are about to be delivered.
	
Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public void BeginPrepareVariants()
		{
		Debug.print( "cmrfilesvj.Compensator.BeginPrepareVariants\n" );
		// Do nothing
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: PrepareRecordVariants

Summary: Delivers a log record to the CRM Compensator during the prepare phase.
	
Args: Variant crmLogRecord

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public boolean PrepareRecordVariants( Variant crmLogRecord )
		{
		Debug.print( "cmrfilesvj.Compensator.PrepareRecordVariants\n" );
		return false; // Do nothing
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: EndPrepareVariants

Summary: Notifies the CRM Compensator that it has had all the log records available during the prepare phase.
	
Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public boolean EndPrepareVariants()
		{
		Debug.print( "cmrfilesvj.Compensator.EndPrepareVariants\n" );
		return true; // Always vote yes
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: BeginCommitVariants

Summary: Notifies the CRM Compensator of the commit phase (phase 2) of the transaction completion, and that records are about to be delivered.

Args: boolean bRecovery 

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public void BeginCommitVariants( boolean bRecovery )
		{
		Debug.print( "cmrfilesvj.Compensator.BeginCommitVariants\n" );
		// Do nothing
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CommitRecordVariants

Summary: Delivers a log record to the CRM Compensator during the commit phase.
	
Args: Variant crmLogRecord

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public boolean CommitRecordVariants( Variant crmLogRecord ) // throws ComFailException
		{
		Debug.print( "cmrfilesvj.Compensator.CommitRecordVariants\n" );
		boolean bForget = false;

		try {
			ProcessLogRecord( crmLogRecord );

			if ( m_commandType == CommandType.ct_DeleteFile )
				File.delete( m_tempFileName );

			// This forget isn't forced - could force on next record if required
			bForget = true;
			}
		finally
			{
			return bForget;
			}
		}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: EndCommitVariants

Summary: Notifies the CRM Compensator that it has delivered all the log records available during the commit phase.
	
Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


	public void EndCommitVariants()
		{
		Debug.print( "cmrfilesvj.Compensator.EndCommitVariants\n" );
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: BeginAbortVariants

Summary: Notifies the CRM Compensator of the abort phase of the transaction completion, and that records are about to be delivered.
	
Args: boolean fRecovery

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public void BeginAbortVariants( boolean fRecovery )
		{
		Debug.print( "cmrfilesvj.Compensator.BeginAbortVariants\n" );
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: AbortRecordVariants

Summary: Delivers a log record to the CRM Compensator during the abort phase.
	
Args:  Variant crmLogRecord

Returns: boolean

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	public boolean AbortRecordVariants( Variant crmLogRecord )
		{
		Debug.print( "cmrfilesvj.Compensator.AbortRecordVariants\n" );
		boolean bForget = false;
		
		try {
			ProcessLogRecord( crmLogRecord );

			switch ( m_commandType )
				{
				case CommandType.ct_CreateFile:
					{
					// Delete the file we created

					if ( File.exists( m_permFileName ) )
						File.delete( m_permFileName );

					break;
					}

				case CommandType.ct_DeleteFile:
					{
					// Restore the deleted file

					boolean bPermFileExists = File.exists( m_permFileName );
					boolean bTempFileExists = File.exists( m_tempFileName );

					if ( ! bPermFileExists )
						{
						if ( ! bTempFileExists )
							throw new ComFailException(); // Something is hosed!

						// Rename (i.e., move) the temp file back to permanent storage

						File.rename( m_tempFileName, m_permFileName );
						}
					}
				}
			}
		finally
			{
			return bForget;
			}
		}
	
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: EndAbortVariants

Summary: Notifies the CRM Compensator that it has received all the log records available during the abort phase.
	
Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


	public void EndAbortVariants()
		{
		Debug.print( "cmrfilesvj.Compensator.EndAbortVariants\n" );
		}

/***************
 private Methods
 ***************/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: ProcessLogRecord

Summary: Given a log record set some member variables. 

Args: Variant varLogRecord 
	
Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

	
	private void ProcessLogRecord( Variant varLogRecord )
		{
		Debug.print( "cmrfilesvj.Compensator.ProcessLogRecord\n" );

		SafeArray saLogRecord = varLogRecord.toSafeArray();
		int n = saLogRecord.getLBound();
		
		switch ( m_commandType = saLogRecord.getInt( n + 0 ) )
			{
			case CommandType.ct_CreateFile:
				{
				m_permFileName = saLogRecord.getString( n + 1 );
				m_tempFileName = null;
				break;
				}
			case CommandType.ct_DeleteFile:
				{
				m_permFileName = saLogRecord.getString( n + 1 );
				m_tempFileName = saLogRecord.getString( n + 2 );
				break;
				}
			}
		}
	}
