Attribute VB_Name = "Module1"
Option Explicit

Sub recFields(r As Record, l As ListBox, t As TextBox)
    Dim f As Field
    Dim s As Stream
    Set s = New Stream
    Dim str As String
    
    For Each f In r.Fields
        l.AddItem f.Name & ": " & f.Value
    Next
    
    t.Text = ""
    
    If r!RESOURCE_CONTENTCLASS = "text/plain" Then
        s.Open r, adModeRead, adOpenStreamFromRecord
        str = s.ReadText(1)
        s.Position = 0
        If Asc(Mid(str, 1, 1)) = 63 Then '//63 = "?"
            s.Charset = "ascii"
            s.Type = adTypeText
        End If
        t.Text = s.ReadText(adReadAll)
    End If
End Sub
