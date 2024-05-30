VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Preferences"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Const modName = "db_CustPreferences.Preferences"
Public Function ReadPreferences(ByVal strCustomerID As String) As ADODB.Recordset
    
    On Error GoTo errHandler
    
    ' Open up the prefereneces table
    Dim rsPref As New ADODB.Recordset
    rsPref.CursorType = adOpenDynamic
    rsPref.CursorLocation = adUseNone
    rsPref.Open "CustomerPreferences", "Provider=Microsoft In-Memory Database Provider;DSN=IsleHop_Online;UID=sa;PWD=;"
    
    ' Select the Customer preferences
    rsPref.Filter = "(CustomerID = '" & strCustomerID & "')"

    'GetObjectContext.SetComplete
    
    Set ReadPreferences = rsPref

    Exit Function
    
errHandler:
    
    'GetObjectContext.SetAbort
    
    Err.Raise Err.Number, SetErrSource(modName, "ReadPreferences"), Err.Description
    
End Function

