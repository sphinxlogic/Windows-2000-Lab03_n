 

   
   Set oArgs = wscript.Arguments
   wscript.echo oArgs(0)
   If (oArgs.Count < 1) Then
        WScript.Echo "usage: search name"
        '"where name can be alias, first/last name, group name"
        WScript.Quit(1)
   end if 

  if ( oArgs.Count = 2 ) then
    ADsDomain = oArgs(1)
  else
    ADsDomain = "ntdev.microsoft.com"
  end if 
 
  

  
  userName = oArgs(0)


  Set con = CreateObject("ADODB.Connection")
  Set com =   CreateObject("ADODB.Command")
  domainPath = "LDAP://" & ADsDomain
    
  'Open the ADSI Connection.
  con.Provider = "ADsDSOObject"

  'Credentials  
   con.Properties("User ID") = "NTDEV\ntdev"
   con.Properties("Password") = "ntdevntdev"

   con.Open "Active Directory Provider"
   Set Com.ActiveConnection = con



   
   Com.CommandText = "<" & domainPath & ">;(&(anr=" & userName & ")(|(objectCategory=organizationalPerson)(objectCategory=group)));ADsPath,name,telephoneNumber,title,physicalDeliveryOfficeName,department,objectCategory;subtree"

   Com.Properties("Page Size") = 64
   Com.Properties("Timeout") = 30 'seconds
   
      




   '--- TIME BEGIN
   wscript.echo "Searching..."
   t = Timer
   Set rs = Com.Execute
   elapse = Mid(CStr(Timer - t),1,5)
   '--- TIME END
   On Error Resume Next
   counter = 0


 
While Not rs.EOF

     'Increment the counter 
     counter = counter + 1 
     'Alternate background color for enhancing the appearance 
      wscript.echo rs.Fields("name")
     rs.MoveNext
Wend

   wscript.echo "Query was executed in: " & elapse & " second(s)"
