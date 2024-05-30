Attribute VB_Name = "Module1"
Option Explicit

Global doc As Object ' Global XML Object

Sub Load_XML_File(FileName As String)

On Error Resume Next

'Clean up before loading new file
        
XSL_Pattern.lstNodes.Clear
XSL_Pattern.lstAttributes.Clear
XSL_Pattern.txtAttributeValue.Text = ""
XSL_Pattern.txtPattern.Text = ""
XSL_Pattern.txtPatternResults.Text = ""
XSL_Pattern.txtValue.Text = ""
XSL_Pattern.cmdDrill.Enabled = False
XSL_Pattern.cmdDrillup.Enabled = False
        
Set doc = CreateObject("Microsoft.XMLDOM")

doc.Load (FileName) ' Load XML File

If FileName <> "" Then

    If doc.parseError.reason <> "" Then ' Display errors is any
      MsgBox "Parser Error: " & doc.parseError.reason & Chr$(13) & "Line: " & doc.parseError.Line _
      & Chr$(13) & "Line Pos: " & doc.parseError.linepos _
      & Chr$(13) & "URL: " & doc.parseError.URL _
      & Chr$(13) & "File Pos: " & doc.parseError.filepos
      
      XSL_Pattern.WebBrowser1.Navigate ("about:blank")
      
    Else
        Call Find_Nodes(0)
        XSL_Pattern.WebBrowser1.Navigate (FileName)
            
    End If

End If

On Error GoTo 0

End Sub

Sub Find_Nodes(Direction As Integer)

  On Error GoTo Find_Node_Errors
  
  Dim intX As Double
  Dim Temp_Pattern As String
  Dim Reverse_Temp_Pattern As String
  Dim Tree_Position As Object
  
  intX = 0
 
  If Direction = 0 Then ' Root
  
    XSL_Pattern.lstNodes.Clear
    
    XSL_Pattern.lblNodes.Caption = "Available Nodes:"
    
    For intX = 0 To (doc.documentElement.childNodes.length - 1)
    
      If InStr(doc.documentElement.childNodes.Item(intX).nodeName, "#") = 0 Then ' Don't include comments, etc...
      
        XSL_Pattern.lstNodes.AddItem (doc.documentElement.childNodes.Item(intX).nodeName)
          
      End If
      
    Next
    
    XSL_Pattern.cmdDrillup.Enabled = False ' disable since you are at the top of the document
    XSL_Pattern.cmdDrill.Enabled = False ' disable until user clicks in lstNodes
    
  ElseIf Direction = 1 Then ' Down
  
    ' Build XSL pattern to keep track of location in XML Document - used for drilling up and down
    
    If XSL_Pattern.lblNodes.Caption = "Available Nodes:" Then
    
      Temp_Pattern = "*[" & XSL_Pattern.lstNodes.ListIndex & "]"
    
    Else
    
      Temp_Pattern = Mid(XSL_Pattern.lblNodes.Caption, 17, Len(XSL_Pattern.lblNodes.Caption)) & "/*" & "[" & XSL_Pattern.lstNodes.ListIndex & "]"
      
    End If
        
    Set Tree_Position = doc.documentElement.selectNodes(Temp_Pattern)
    
    Set Tree_Position = Tree_Position.nextNode()
    
    If (Tree_Position.childNodes.Item(0).nodeName <> "#text" Or Tree_Position.childNodes.length > 1) Then
    
        XSL_Pattern.lblNodes.Caption = "Available Nodes: " & Temp_Pattern
        
        XSL_Pattern.lstNodes.Clear
        
        For intX = 0 To (Tree_Position.childNodes.length - 1)
        
          If InStr(Tree_Position.childNodes.Item(intX).nodeName, "#") = 0 Then ' Don't include comments, etc...
          
            XSL_Pattern.lstNodes.AddItem (Tree_Position.childNodes.Item(intX).nodeName)
          
          End If
          
        Next
            
    Else
    
       MsgBox "No children below current selected node."
       
    End If
    
    XSL_Pattern.cmdDrillup.Enabled = True
    
  ElseIf Direction = 2 Then ' Up
  
    ' Build XSL pattern to keep track of location in XML Document - used for drilling up and down
    
    If XSL_Pattern.lblNodes.Caption = "Available Nodes:" Then
    
      MsgBox "Can't drill up - you are at the top of the document"
      
      Set Tree_Position = Nothing
      
      Exit Sub
    
    Else
    
      Temp_Pattern = Mid(XSL_Pattern.lblNodes.Caption, 18, Len(XSL_Pattern.lblNodes.Caption))
      
        If InStr(Temp_Pattern, "/") > 0 Then
      
            For intX = 1 To Len(Temp_Pattern)
            
              Reverse_Temp_Pattern = Reverse_Temp_Pattern + Right(Temp_Pattern, 1)
              
              Temp_Pattern = Left(Temp_Pattern, Len(Temp_Pattern) - 1)
              
            Next
            
            intX = InStr(Reverse_Temp_Pattern, "/")
            
            Temp_Pattern = Mid(XSL_Pattern.lblNodes.Caption, 17, Len(XSL_Pattern.lblNodes.Caption))
            
            Temp_Pattern = Left(Temp_Pattern, (Len(Temp_Pattern) - intX))
            
        Else
    
            Call Find_Nodes(0) ' Display the root nodes again
             
            Set Tree_Position = Nothing
             
            Exit Sub
            
        End If
        
    End If
        
    Set Tree_Position = doc.documentElement.selectNodes(Temp_Pattern)
    
    Set Tree_Position = Tree_Position.nextNode()
                 
    If (Tree_Position.childNodes.Item(0).nodeName <> "#text") Then
    
        XSL_Pattern.lblNodes.Caption = "Available Nodes: " & Temp_Pattern
        
        XSL_Pattern.lstNodes.Clear
        
        For intX = 0 To (Tree_Position.childNodes.length - 1)
        
          If InStr(Tree_Position.childNodes.Item(intX).nodeName, "#") = 0 Then ' Don't include comments, etc...
          
            XSL_Pattern.lstNodes.AddItem (Tree_Position.childNodes.Item(intX).nodeName)
          
          End If
          
        Next
          
    Else
    
       MsgBox "No children below current selected node."
       
    End If
    
  End If
    
  XSL_Pattern.txtValue.Text = "" ' clear value text box
  
  On Error GoTo 0
   
  Set Tree_Position = Nothing
  
  Exit Sub
  
Find_Node_Errors:
  
    MsgBox "Unexpected Error: " & Error
          
    Set Tree_Position = Nothing
    
End Sub
