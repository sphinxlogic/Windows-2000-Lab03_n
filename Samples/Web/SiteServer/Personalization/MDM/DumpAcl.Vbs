'
' 	Microsoft (R) P&M Dump ACL script.
' 	Copyright (C) Microsoft Corporation 1997.
'
'	File: dumpacl.vbs
'
'	Contents:	Dumps an ACL given a DN.
'
'	History:	9/27/97	robertc	Created
'
'	LEGEND:
'
'	----------------------------------------------------------------------------
'	MASK
'	----------------------------------------------------------------------------
'
'	The mask field contains one or more of the following values OR'ed together:
'	
'	0x00000001	Create-Child	
'	0x00000002  Delete-Child
'	0x00000004	Search (List Contents)
'	0x00000010	Read
'	0x00000020	Write
'	0x00010000	Delete-Self
'	0x00040000	View/Set Security (Write DAC)
'
'	Assuming that the ACL was set using the Membership Directory Manager (MDM) 
'	alone, the following are the only possible combinations:
'
'	0x00000001	Create-Child	
'	0x00000002  Delete-Child
'	0x00000003  Create/Delete-Child
'	0x00000004	Search (List Contents)
'	0x00000010	Read
'	0x00000020	Write
'	0x00000030	Read/Write
'	0x00010000	Delete-Self
'	0x00040000	View/Set Security (Write DAC)
'	0x0005003F	Full (0x00000008 also gets set but is not used anywhere.)
'	
'	----------------------------------------------------------------------------
'	TYPE
'	----------------------------------------------------------------------------
'	
'	0 or 5	Allow
'	1 or 6	Deny
'
'	----------------------------------------------------------------------------
'	ACEFLAGS
'	----------------------------------------------------------------------------
'	
'	The AceFlags field contains three pieces of information OR'ed together:
'
'	Info 1 (one of the following):
'	0x03	Full inheritance
'	0x07	One-level inheritance
'
'	Info 2:
'	0x08	Apply permission to child objects only.
'
'	Info 3:
'	0x10	Ace is inherited.
'
'	Sample values:
'
'	0x00	No inheritance.  Ace is explicit (i.e. not inherited).
'	0x13	Full inheritance.  Ace is inherited.
'	0x0F	One-level inheritance.  Ace is explicit.  Apply permission to child objects only.
'
'	----------------------------------------------------------------------------
'	FLAGS
'	----------------------------------------------------------------------------
'
'	0	Granularity is set to "All".
'	1	Granularity is set on a particular object class or attribute.
'
'	----------------------------------------------------------------------------
'	GUID
'	----------------------------------------------------------------------------
'	
'	This is non-blank only if FLAGS is 1.  It is the GUID of the attributeSchema or
'	classSchema to which the permission applies.  For instance, if you grant a user
'	read permission to the age of another user, then FLAGS will be set to 1 and GUID
'	will be set to the GUID of the "age" attributeSchema.
'	
'	----------------------------------------------------------------------------
'	INOBJTYPE
'	----------------------------------------------------------------------------
'
'	Inherited Object Type.  This is not used and is therefore always blank.
'


' Localizable strings
	const L_MAIN_HEADER	= "P&M Dump ACL Script"
	const L_MAIN_COPYRIGHT = "(c) 1997 Microsoft Corporation"

	const L_HELP_SYNTAX		= "Syntax: DumpAcl.vbs AdsPath [BindDN] [Password]"
	const L_HELP_SYNTAX_2   = "   AdsPath - Full ADS Path for the object to get "
	const L_HELP_SYNTAX_3	= "             (LDAP://localhost:389/o=OrgName) "



' ***************************************************************
' FUNCTIONS.
' ***************************************************************


' ///////////////////////////////////////////////////////////////////////////
'	Function:	EchoErr
' 
' ///////////////////////////////////////////////////////////////////////////
Function EchoErr(Err)
	
	wScript.Echo "<--- 0x" & Hex(Err.Number)
	wScript.Echo "<--- " & Err.Description

end function


' ///////////////////////////////////////////////////////////////////////////
'	Function:	DumpSecurityDescriptor
'		Prints to the screen the SecurityDescriptor.
' 
' ///////////////////////////////////////////////////////////////////////////
Function DumpSecurityDescriptor(byref SecDes)

	If (DebugOutput) Then

		on error goto 0

		Dim Ace
		wScript.Echo "* ---------------------------------- *"
		wScript.Echo "* Debug Output of SecurityDescriptor *"
		wScript.Echo "* ---------------------------------- *"
		set dacl = SecDes.DiscretionaryAcl
		For Each Ace In Dacl
			wScript.Echo "Trustee: " & Ace.Trustee
			wScript.Echo "  Mask :     " & Hex(Ace.AccessMask)
			wScript.Echo "  Type:      " & Hex(Ace.AceType)
			wScript.Echo "  AceFlags:  " & Hex(Ace.AceFlags)
			wScript.Echo "  Flags:     " & Hex(Ace.Flags)
			wScript.Echo "  GUID:      " & Ace.ObjectType
			wScript.Echo "  InObjType: " & Ace.InheritedObjectType
			wScript.Echo "  ------------------"
		Next

		on error resume next
	end if
End Function


' ///////////////////////////////////////////////////////////////////////////
'	Function:	Usage
' 
' ///////////////////////////////////////////////////////////////////////////
Function Usage()

	wscript.Echo 
	wscript.Echo L_HELP_SYNTAX
	wscript.Echo L_HELP_SYNTAX_2
	wscript.Echo L_HELP_SYNTAX_3
	wscript.Echo
	wscript.Quit(-1)

end Function


' ***************************************************************
' MAIN
' ***************************************************************
'
'	on error resume next

	Dim SecDes
	Dim	Ace
	Dim BaseDN
	Dim BindDN
	Dim PassWord

	wscript.Echo L_MAIN_HEADER
	wscript.Echo L_MAIN_COPYRIGHT

	Set objArgs = WScript.Arguments

	if ((objArgs.count > 3) OR (objArgs.count < 1)) then
		Call Usage
		wscript.Quit(-1)
	end if

	' Get the command line arguments.
	BaseDN = objArgs(0)
	If Len(BaseDN) = 0 Then
		Call usage
		wscript.Quit(-1)
	end if
	if (objArgs.count = 3) then
		BindDN	 = objArgs(1)
		PassWord = objArgs(2)
	else
		BindDN	 = ""
		PassWord = ""
	end if

	' /////////////////////////////////////////
	' Get and dump the security descriptor.
	on error resume next

	DebugOutput = True

	wScript.Echo "Opening: " & BaseDN
	set OpenObject = GetObject("LDAP:")
	Set RootObj = OpenObject.OpenDSObject(BaseDN, BindDN, PassWord, 0)
	If (Err.Number <> 0) Then
	    wScript.Echo "Could not open object " & BaseDN
		EchoErr(Err)
		wscript.Quit(-1)
	End If

	wScript.Echo "Getting the SecurityDescriptor"
	Set SecDes = RootObj.Get("ntSecurityDescriptor")
	If (Err.Number <> 0) Then
		wScript.Echo "*** No SecurityDescriptor Value Found ***"
	else
		DumpSecurityDescriptor(SecDes)
	End If







