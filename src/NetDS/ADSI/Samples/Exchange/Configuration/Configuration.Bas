Attribute VB_Name = "Module1"
Sub Main()

'This example displays and sets the value of the maximum message size on
'an Exchange Server's Message Transfer Agent to 5mb.

Dim objMTA As IADs
Set objMTA = GetObject("LDAP://exchsrv/cn=Microsoft MTA,cn=exchsrv,cn=Servers,cn=Configuration,ou=REDMOND,o=ARCADIABAY")
    
'Getting
objMTA.GetInfoEx Array("Deliv-Cont-Length"), 0
Debug.Print objMTA.Get("Deliv-Cont-Length")
      
'Modifying
objMTA.Put "Deliv-Cont-Length", 5000
objMTA.SetInfo
Set bjMTA = Nothing


End Sub
