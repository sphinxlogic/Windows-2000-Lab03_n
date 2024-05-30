Attribute VB_Name = "Module1"
Sub Main()

'Bind to the parent container
Set cont = GetObject("WinNT://INDEPENDENCE")

'---- Getting a child object from the container
Set usr = cont.GetObject("user", "JJohnson")


End Sub
