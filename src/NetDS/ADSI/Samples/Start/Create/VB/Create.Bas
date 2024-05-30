Attribute VB_Name = "Module1"
Sub Main()
Set cont = GetObject("WinNT://INDEPENDENCE")

'---- Creating a user
Set usr = cont.Create("user", "JohnD")
usr.FullName = "John Doe"
usr.SetInfo

End Sub
