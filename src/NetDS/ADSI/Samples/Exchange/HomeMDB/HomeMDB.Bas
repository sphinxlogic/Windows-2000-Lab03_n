Attribute VB_Name = "Module1"
Sub Main()


srvName = "exchsrv"
Set objMailbox = GetObject("LDAP://" & srvName & "/cn=jsmit,cn=Recipients,ou=REDMOND,o=ArcadiaBay")
    
objMailbox.GetInfoEx Array("Home-MDB"), 0
dnPath = objMailbox.Get("Home-MDB")
Debug.Print dnPath

'Build the ADsPath for Home MDB
adsPath = "LDAP://" & srvName & "/" & dnPath
Set homeMDB = GetObject(adsPath)

'Home MDB object resides on the computer object
'So we need to go up one level before we get the computer object
Set srvMDB = GetObject(homeMDB.Parent())
Debug.Print "Home MDB ServerName is: " & srvMDB.Get("rdn")


End Sub
