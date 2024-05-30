Attribute VB_Name = "Module1"
Sub Main()

Dim ADOConn As ADODB.Connection
Dim ADOCommand As New Command
Dim RS As ADODB.Recordset
    
Set ADOConn = CreateObject("ADODB.Connection")
ADOConn.Provider = "ADSDSOObject"
ADOConn.Open "Active Directory Provider"
      
Set ADOCommand.ActiveConnection = ADOConn
ADOCommand.CommandText = "<LDAP://localhost/o=ARCADIABAY>;(USN-Changed>1030);rdn;subtree"
Set RS = ADOCommand.Execute
While Not RS.EOF
    Debug.Print (RS.Fields(0))
     RS.MoveNext
Wend
RS.Close

End Sub
