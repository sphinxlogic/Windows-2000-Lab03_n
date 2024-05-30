
    Set oArgs = wscript.Arguments

    if ( oArgs.Count <> 1 ) then
      wscript.echo "Usage exchsrch alias"
      wscript.echo "e.g cscript exchsrch.vbs andyhar"
      wscript.quit(0)
    end if 


    Const ADS_SCOPE_SUBTREE=2

    searchAlias = oArgs(0)
    exchServer  = "red-msg-01"
    Set con = CreateObject("ADODB.Connection")
    Set Com = CreateObject("ADODB.Command")
    
    'Open a Connection object
    con.Provider = "ADsDSOObject"
    
    '---------------------------------------------------------------------
    ' If you want to be authenticated other than current logged on user
    ' use connection properties of User ID and Password
    '---------------------------------------------------------------------
    'con.Properties("User ID") = "domain\username"
    'con.Properties("Password") = "password"
    'con.Properties("Encrypt Password") = True

    
    
    '------------------------------------
    ' Open the connection
    '-------------------------------------
    con.Open "Active Directory Provider"
    
    ' Create a command object on this connection
    Set Com.ActiveConnection = con
    
    '--------------------------------------------------
    ' set the query string
    '---------------------------------------------------
   
    adsPath = "LDAP://" & exchServer & "/o=microsoft"
   
    Com.CommandText = "select ADsPath, uid, title, givenName, sn, physicalDeliveryOfficeName,telephoneNumber from '" & adsPath & "' where uid='" & searchAlias & "'"
    
    '-----------------------------------------
    'Set the preferences for Search
    '--------------------------------------
    Com.Properties("Page Size") = 100
    Com.Properties("Timeout") = 30 'seconds
    Com.Properties("searchscope") = ADS_SCOPE_SUBTREE 'Define in ADS_SCOPEENUM
    Com.Properties("Cache Results") = False ' do not cache the result, it results in less memory requirements
    
    '--------------------------------------------
    'Execute the query
    '--------------------------------------------
    Set rs = Com.Execute
        
    
    '--------------------------------------
    ' Navigate the record set
    '----------------------------------------
    

    if ( rs.EOF = False ) then
      wscript.echo "Alias     = " & rs.Fields("UID").Value
      wscript.echo "Name      = " & rs.Fields("givenName").Value & " " & rs.Fields("sn")
      wscript.echo "Title     = " & rs.Fields("Title").Value
      wscript.echo "Office    = " & rs.Fields("physicalDeliveryOfficeName").Value
      wscript.echo "Telephone = " & rs.Fields("telephoneNumber").Value

  
      Set mailRc = GetObject(rs.Fields("ADsPath").Value )
      wscript.echo "Manager = " & mailRC.Get("Extension-Attribute-1")
      
    end if 

    