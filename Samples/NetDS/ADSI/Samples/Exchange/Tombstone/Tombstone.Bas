Attribute VB_Name = "Module1"
Sub Main()

' To access hidden or deleted items in the directory you must use
' OpenDSObject or AdsOpenObject(for VC++) to explicitly bind to the directory object
' with a valid user account using simple clear text authentication with “cn=admin” appended to the username.
' For example: “cn=jsmith, dc=ARCADIABAY, cn=admin”.
' Also, the Exchange service account must be a member of the local administrators group on the server
' and have explicit Restore Files and Directories privilege

strADsPath = "LDAP://excsvr/cn=JustinH,cn=Recipients,ou=REDMOND,o=ARCADIABAY"
Set dso = GetObject("LDAP:")
Set objDeleted = dso.OpenDSObject(strADsPath, _
                  "cn=Administrator, dc=ARCADIABAY, cn=admin", "PasswordGoesHere", 0)
                  
                  
'"objDeletedObject" now is a reference to a deleted object

Debug.Print objDeleted.Name

End Sub
