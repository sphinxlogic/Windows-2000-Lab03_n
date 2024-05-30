Attribute VB_Name = "Module1"
Sub Main()
'--------------------------------------------------------
' Security object for SD manipulation
' (REQUIRED ADSI TOOL KIT - REGSVR32 ADSSECURITY.DLL )
'---------------------------------------------------------
Dim sid As New ADsSID  'You can also use -- Set sid = CreateObject("ADsSID") for late binding
Dim sec As New ADsSecurity 'You can also use -- Set sec = CreateObject("ADsSecurity") for late binding


'-------------------------------------
'- The rest uses ADSI Interfaces
'-------------------------------------
Dim sd As IADsSecurityDescriptor
Dim dacl As IADsAccessControlList
Dim ace As New AccessControlEntry



'----------------------------------------------------------------------------
'--- If you don't include the ADSI 2.5 Security Type Library as you reference
'--- you must manually declare the following constants
'-----------------------------------------------------------------------------
Const ADS_SID_HEXSTRING = 1
Const ADS_SID_WINNT_PATH = 5
Const ADS_RIGHT_EXCH_MODIFY_USER_ATT = &H2
Const ADS_RIGHT_EXCH_MAIL_SEND_AS = &H8
Const ADS_RIGHT_EXCH_MAIL_RECEIVE_AS = &H10


'-------------------------------------------------------
'-----CREATING A MAILBOX  ----------------------
'--------------------------------------------------------

'---- Server, Org and Site information
server = "andyhar11"
Org = "MICROSOFT"
Site = "INDEPENDENCE"
domain = "INDEPENDENCE"
userName = "andyhar"
password = "passwordHere"

'--- MailBox Parameters -----
strDisplayName = "Andy Harjanto"
strFirstName = "Andy"
strLastName = "Harjanto"
strAlias = userName
strMTA = "cn=Microsoft MTA,cn=" & server & ",cn=Servers,cn=Configuration,ou=" & Site & ",o=" & Org
strMDB = "cn=Microsoft Private MDB,cn=" & server & ",cn=Servers,cn=Configuration,ou=" & Site & ",o=" & Org
strSMTPAddr = "andyhar@microsoft.com"


'------ Creating an NT user to be associated with the mail box
Set dom = GetObject("WinNT://" & domain)
Set usr = dom.Create("user", userName)
usr.SetInfo
usr.SetPassword password


'--- Build Recipient container's adsPath that looks like this: LDAP://myserver/CN=Recipients, OU=Site, O=Org
ADsPath = "LDAP://" + server
ADsPath = ADsPath + "/cn=Recipients,OU="
ADsPath = ADsPath + Site
ADsPath = ADsPath + ",O="
ADsPath = ADsPath + Org



Set objCont = GetObject(ADsPath)

'Create a new MailBox
Set mailBox = objCont.Create("organizationalPerson", "cn=" & strAlias)
mailBox.Put "mailPreferenceOption", 0
mailBox.Put "givenName", strFirstName
mailBox.Put "sn", strLastName
mailBox.Put "cn", strDisplayName
mailBox.Put "uid", strAlias
mailBox.Put "Home-MTA", strMTA
mailBox.Put "Home-MDB", strMDB
mailBox.Put "mail", strSMTPAddr
mailBox.Put "MAPI-Recipient", True
mailBox.Put "rfc822Mailbox", strSMTPAddr

'--------------------------------------------------------
'  ASSOCIATING TO NT PRIMARY ACCOUNT
' (REQUIRED ADSI TOOL KIT - REGSVR32 ADSSECURITY.DLL )
'---------------------------------------------------------
sid.SetAs ADS_SID_WINNT_PATH, "WinNT://" & domain & "/" & strAlias & ",user"
sidHex = sid.GetAs(ADS_SID_HEXSTRING)
mailBox.Put "Assoc-NT-Account", sidHex

' Commit the property cache to the directory service
mailBox.SetInfo



'-------------------------------------------------
'--- SET THE MAIL BOX SECURITY ------------------
'-- To allow the user to modify user attribute, send mail and receive mail
'-------------------------------------------------
Set sd = sec.GetSecurityDescriptor(mailBox.ADsPath)
Set dacl = sd.DiscretionaryAcl
ace.Trustee = domain & "\" & strAlias
ace.AccessMask = ADS_RIGHT_EXCH_MODIFY_USER_ATT Or ADS_RIGHT_EXCH_MAIL_SEND_AS Or ADS_RIGHT_EXCH_MAIL_RECEIVE_AS
ace.AceType = ADS_ACETYPE_ACCESS_ALLOWED
dacl.AddAce ace
sd.DiscretionaryAcl = dacl
sec.SetSecurityDescriptor sd

  


End Sub
