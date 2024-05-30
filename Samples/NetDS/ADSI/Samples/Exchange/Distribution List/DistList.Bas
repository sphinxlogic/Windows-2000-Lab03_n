Attribute VB_Name = "Module1"
Sub Main()
'--- IMPORTANT !!!!!!------------------------------------
'----- Note: You must regsvr32 adssecurity.dll before running this sample
'----- adssecurity.dll is in ResourceKit directory.

Dim sec As New ADsSecurity
Dim sd As IADsSecurityDescriptor
Dim dacl As IADsAccessControlList
Dim ace As New AccessControlEntry

Const RIGHT_DS_MODIFY_USER_ATT = &H2
Const RIGHT_MAIL_SEND_AS = &H8
Const RIGHT_MAIL_RECEIVE_AS = &H10





'-------------------------------------------------------
'-----CREATING A DISTRIBUTION LIST  ----------------------
'--------------------------------------------------------

'---- Server, Org and Site information
server = "andyhar04:390"
org = "Microsoft"
Site = "WINDOWS2000"

'--- Distribution List -----
strDisplayname = "Distributed System PM"
strAlias = "dpm"
strSMTPAddr = "dpm@arcadiabay.com"

'--- Build Recipient container's adsPath that looks like this: LDAP://myserver/CN=Recipients, OU=Site, O=Org
ADsPath = "LDAP://" + server
ADsPath = ADsPath + "/cn=Recipients,OU="
ADsPath = ADsPath + Site
ADsPath = ADsPath + ",O="
ADsPath = ADsPath + org


Set objCont = GetObject(ADsPath)
'Create a new DL
Set objNewDL = objCont.Create("groupOfNames", "cn=" & strAlias)
  
'Set the DL props
objNewDL.Put "cn", CStr(strDisplayname)
objNewDL.Put "uid", CStr(strAlias)
objNewDL.Put "mail", CStr(strSMTPAddr)
objNewDL.SetInfo
   
   
   
'---------------------------------------------------------------
'--- ADDING MEMBERS TO A DISTRIBUTION LIST
'-----------------------------------------------------------------
Set dl = GetObject("LDAP://excsrv11/cn=dpm,cn=Recipients,ou=REDMOND,o=Microsoft")
dl.Add "LDAP://excsrv11/cn=jsmith,cn=Recipients,ou=REDMOND,o=Microsoft"
dl.Add "LDAP://excsrv11/cn=andyhar,cn=Recipients,ou=REDMOND,o=Microsoft"

'------------------------------------------------------------------
' -- ENUMERATE MEMBERS IN A DISTRIBUTION LIST
'-----------------------------------------------------------------
Set dl = GetObject("LDAP://excsrv11/cn=dpm,cn=Recipients,ou=REDMOND,o=Microsoft")
For Each member In dl.Members
   Debug.Print member.Name & " (" & member.Class & ")"
Next

'----------------------------------------------------------------------
'--- REMOVING MEMBERS IN A DISTRIBUTION LIST
'-----------------------------------------------------------------------
Set dl = GetObject("LDAP://excsrv11/cn=dpm,cn=Recipients,ou=REDMOND,o=Microsoft")
dl.Remove "LDAP://excsrv11/cn=jsmith,cn=Recipients,ou=REDMOND,o=Microsoft"



'-------------------------------------------------------------------------------------
'--- SET THE OWNER OF THE DISTRIBUTION LIST
'------------------------------------------------------------------------------------
Set dl = GetObject("LDAP://excsrv11/cn=dpm,cn=Recipients,ou=REDMOND,o=Microsoft")
dl.Put "Owner", "cn=andyhar,cn=Recipients,ou=REDMOND,o=Microsoft"
dl.SetInfo

'------------------------------------------------------------------------
'-- SET PERMISSION ON THE OWNER TO MODIFY AND SEND AS/RECEIVE ------------
'--- REQUIRED THE ADSI RESOURCE TOOL KIT INSTALL (IADsSecurity)-----------------------
'-------------------------------------------------------------------------
Set sd = sec.GetSecurityDescriptor("LDAP://excsrv11/cn=dpm,cn=Recipients,ou=REDMOND,o=Microsoft")
Set dacl = sd.DiscretionaryAcl

ace.AccessMask = RIGHT_DS_MODIFY_USER_ATT Or RIGHT_MAIL_SEND_AS Or RIGHT_MAIL_RECEIVE_AS
ace.Trustee = "REDMOND\andyhar"
dacl.AddAce ace
sd.DiscretionaryAcl = dacl
sec.SetSecurityDescriptor sd


End Sub
