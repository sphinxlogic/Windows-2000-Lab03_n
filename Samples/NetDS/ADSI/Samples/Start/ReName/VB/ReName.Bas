Attribute VB_Name = "Module1"
Sub Main()

'Bind to the parent's destination
Set cont = GetObject("LDAP://OU=DSys,DC=windows2000,DC=nttest,DC=microsoft,DC=com")

'---- Moving a user from one organization to another
Set usr = cont.MoveHere("LDAP://CN=Mike Smith,OU=MCS,DC=windows2000,DC=nttest,DC=microsoft,DC=com", vbNullString)


End Sub
