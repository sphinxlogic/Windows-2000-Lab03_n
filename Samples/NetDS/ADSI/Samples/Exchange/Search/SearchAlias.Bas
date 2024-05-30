Attribute VB_Name = "Module1"
Sub Main()


    Set con = CreateObject("ADODB.Connection")
    Set Com = CreateObject("ADODB.Command")
    
    'Open a Connection object
    con.Provider = "ADsDSOObject"
    
    '---------------------------------------------------------------------
    ' If you want to be authenticated other than current logged on user
    ' use connection properties of User ID and Password
    '---------------------------------------------------------------------
    'con.Properties("User ID") = "domain\user"
    'con.Properties("Password") = "password"

    
    
    '------------------------------------
    ' Open the connection
    '-------------------------------------
    con.Open "Active Directory Provider"
    
    ' Create a command object on this connection
    Set Com.ActiveConnection = con
    
    '--------------------------------------------------
    ' set the query string
    '---------------------------------------------------
   
    adDomainPath = "LDAP://exchsrv/o=microsoft"
    searchAlias = "alias"
    Com.CommandText = "select ADsPath, uid, title, givenName, sn, physicalDeliveryOfficeName,telephoneNumber from '" & adDomainPath & "' where uid='" & searchAlias & "'"
    
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
    Set RS = Com.Execute
        
    
    '--------------------------------------
    ' Navigate the record set
    '----------------------------------------
    
    If (RS.EOF = False) Then
      Debug.Print "Alias     = " & RS.Fields("UID").Value
      Debug.Print "Name      = " & RS.Fields("givenName").Value & " " & RS.Fields("sn")
      Debug.Print "Title     = " & RS.Fields("Title").Value
      Debug.Print "Office    = " & RS.Fields("physicalDeliveryOfficeName").Value
      Debug.Print "Telephone = " & RS.Fields("telephoneNumber").Value
    End If

End Sub
