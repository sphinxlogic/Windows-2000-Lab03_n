Attribute VB_Name = "modMain"
Option Explicit


Public Sub Main()
    'Test
End Sub

Public Sub Test()
    Dim obj As New CSqlServerConnect
    
    Debug.Print ""
    Debug.Print "CSqlServerConnect::GetAuthors"
    DumpArray (obj.DaoGetAuthors)
    Debug.Print ""
    Debug.Print "CSqlServerConnect::RdoGetAuthors"
    DumpArray (obj.RdoGetAuthors)
    Debug.Print ""
    Debug.Print "CSqlServerConnect::OleGetAuthors"
    DumpArray (obj.OleGetAuthors)
    
    Stop
    End
End Sub

Sub DumpArray(vArray As Variant)
    Dim i As Integer
    
    Debug.Print "au_fname"; Tab(20); "au_lname"; Tab(40); "state"
    For i = LBound(vArray) To UBound(vArray)
        Debug.Print vArray(i, 1); Tab(20); _
                  ; vArray(i, 2); Tab(40); _
                  ; vArray(i, 3)
    Next i
    
    Debug.Print "(" + CStr(i) + " row(s).)"

End Sub
