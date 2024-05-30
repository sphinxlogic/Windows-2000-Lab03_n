Attribute VB_Name = "Module1"
Sub Main()

'Bind to an object with current credential
Set obj = GetObject("WinNT://INDEPENDENCE")


'Bind to an object with alternate credentials
Set DSO = GetObject("WinNT:")
Set usr = DSO.OpenDSObject("WinNT://INDEPENDENCE/JSmith,user", "Administrator", "se**cre*t*", ADS_SECURE_AUTHENTICATION)

   
    

End Sub
