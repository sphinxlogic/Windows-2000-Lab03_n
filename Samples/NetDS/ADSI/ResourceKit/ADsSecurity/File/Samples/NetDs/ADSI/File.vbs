Const ADS_RIGHT_GENERIC_READ = &H80000000
Const ADS_RIGHT_GENERIC_EXECUTE = &H20000000
Const ADS_ACETYPE_ACCESS_ALLOWED = 0

Set sec = CreateObject("ADsSecurity")

Set sd = sec.GetSecurityDescriptor("FILE://c:\public\specs")
Set dacl = sd.DiscretionaryAcl

'-- Show the ACEs in the DACL ----
For Each ace In dacl
  wscript.echo ace.Trustee
  wscript.echo ace.AccessMask
  wscript.echo ace.AceType
Next

Set ace = CreateObject("AccessControlEntry")
ace.Trustee = "ARCADIABAY\jsmith"
ace.AccessMask = ADS_RIGHT_GENERIC_READ Or ADS_RIGHT_GENERIC_EXECUTE
ace.AceType = ADS_ACETYPE_ACCESS_ALLOWED

dacl.AddAce ace
sd.DiscretionaryAcl = dacl
sec.SetSecurityDescriptor sd

