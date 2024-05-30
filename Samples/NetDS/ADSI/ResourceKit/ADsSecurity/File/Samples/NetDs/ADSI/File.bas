Attribute VB_Name = "Module1"
Sub Main()
Dim sec As New ADsSecurity
Dim sd As IADsSecurityDescriptor
Dim dacl As IADsAccessControlList
Dim ace As IADsAccessControlEntry
Dim newAce As New AccessControlEntry






Set sd = sec.GetSecurityDescriptor("FILE://\\srv01\public")
Set dacl = sd.DiscretionaryAcl

'-- Show the ACEs in the DACL ----
For Each ace In dacl
  Debug.Print ace.Trustee
  Debug.Print ace.AccessMask
  Debug.Print ace.AceType
Next
Debug.Print dacl.AceCount

newAce.Trustee = "ARCADIABAY\jsmith"
newAce.AccessMask = ADS_RIGHT_GENERIC_READ Or ADS_RIGHT_GENERIC_EXECUTE
newAce.AceType = ADS_ACETYPE_ACCESS_ALLOWED

dacl.AddAce newAce
sd.DiscretionaryAcl = dacl
sec.SetSecurityDescriptor sd

End Sub
