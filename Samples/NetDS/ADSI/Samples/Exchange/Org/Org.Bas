Attribute VB_Name = "Module1"
Sub Main()

srvName = "andyhar09:390"

Set objRoot = GetObject("LDAP://" & srvName)
Debug.Print objRoot.Get("o")


'--- OR ------
Set objRoot = GetObject("LDAP://" & srvName & "/RootDSE")
Debug.Print objRoot.Get("defaultNamingContext")

End Sub
