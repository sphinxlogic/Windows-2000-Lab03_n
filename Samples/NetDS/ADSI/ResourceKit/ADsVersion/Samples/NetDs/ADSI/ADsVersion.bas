Attribute VB_Name = "Module1"
Sub Main()
  Set vs = CreateObject("ADsVersion")
  '-------------------------------------------------------------------
  'You can also connect remotely to find out the ADSI version number
  'e.g vs.Connect "mycomputer"
  '-------------------------------------------------------------------
  Debug.Print vs.GetVersion
  Debug.Print vs.GetMajorVersion
  Debug.Print vs.GetMinorVersion
  Debug.Print vs.GetLocale
End Sub
