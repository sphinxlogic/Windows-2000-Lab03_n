'-- Replace this variables accordingly ----
siteName = "INDEPENDENCE"
exchSrv = "andyhar11"

' By getting rootDSE's defaultNamingContext we don't have to hard code Exchange Organization
Set rootDSE = GetObject("LDAP://" & exchSrv & "/RootDSE")

'Build ADsPath for the container
contPath = "LDAP://" & exchSrv & "/" & "CN=Recipients," & "OU=" & siteName & "," & rootDSE.Get("defaultNamingContext")
Set cont = GetObject(contPath)

'Print all persons in the recipient container
wscript.echo "Person List----"
cont.Filter = Array("organizationalPerson")
For Each person In cont
   wscript.echo person.Name
Next
wscript.echo

'Print all custom-recipient in the recipient container
wscript.echo "Custom Recipient List----"
cont.Filter = Array("Remote-Address")
For Each cr In cont
   wscript.echo cr.Name
Next


wscript.echo
wscript.echo "Distribution List----"
'Print all distribution lists in the recipient container
cont.Filter = Array("groupOfNames")
For Each dl In cont
   wscript.echo dl.Name
Next
