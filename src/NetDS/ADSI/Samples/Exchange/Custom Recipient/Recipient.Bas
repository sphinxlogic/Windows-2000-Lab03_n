Attribute VB_Name = "Module1"
Sub Main()

'-------------------------------------------------------
'-----CREATING A CUSTOM RECIPIENT ----------------------
'--------------------------------------------------------


'---- Server, Org and Site information
server = "exchsrv55"
org = "Microsoft"
site = "Redmond"

'--- Custom Recipient-----
strDisplayname = "John Smith"
strAlias = "jsmith"
strTelephone = "867-5309"

'--- Build adsPath that looks like this: LDAP://myserver/CN=Recipients, OU=Site, O=Org
adsPath = "LDAP://" + server
adsPath = adsPath + "/cn=Recipients,OU="
adsPath = adsPath + site
adsPath = adsPath + ",O="
adsPath = adsPath + org


Set objCont = GetObject(adsPath)
Set objNewCR = objCont.Create("Remote-Address", CStr("cn=" & strAlias))
objNewCR.Put "cn", CStr(strDisplayname)
objNewCR.Put "uid", CStr(strAlias)
objNewCR.Put "telephoneNumber", CStr(strTelephone)
objNewCR.Put "Target-Address", "SMTP:jsmith@microsoft.com"
objNewCR.SetInfo

End Sub
