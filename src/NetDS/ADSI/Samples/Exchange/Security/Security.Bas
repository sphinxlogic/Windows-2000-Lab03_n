Attribute VB_Name = "Security"
Public Const RIGHT_DS_ADD_CHILD = &H1
Public Const RIGHT_DS_MODIFY_USER_ATT = &H2
Public Const RIGHT_DS_MODIFY_ADMIN_ATT = &H4
Public Const RIGHT_DS_DELETE = &H10000
Public Const RIGHT_MAIL_SEND_AS = &H8
Public Const RIGHT_MAIL_RECEIVE_AS = &H10
Public Const RIGHT_MAIL_ADMIN_AS = &H20
Public Const RIGHT_DS_REPLICATION = &H40
Public Const RIGHT_DS_MODIFY_SEC_ATT = &H80
Public Const RIGHT_DS_SEARCH = &H100


Sub Main()


'Sample reading and modifying Exchange Security Descriptor Attribute in Exchange 5.5/ADSI 2.5:

Dim propVal As IADsPropertyValue2
Dim sd As IADsSecurityDescriptor
Dim dacl As IADsAccessControlList
Dim ace As IADsAccessControlEntry
Dim o As IADs
Dim srv

srv = "andyhar04"
mailbox = "cn=andyhar"
Site = "ou=Redmond"
Org = "o=Microsoft"


'--- Binding------
ADsPath = "LDAP://" & srv & "/" & mailbox & ",cn=Recipients," & Site & "," & Org
Set o = GetObject(ADsPath)



'-- Get NT Security Descriptor as a raw binary security descriptor
o.GetInfoEx Array("NT-Security-Descriptor;binary"), 0
v = o.Get("NT-Security-Descriptor")

'--- Convert from Raw Security Descriptor to IADsSecurityDescriptor
Set propVal = CreateObject("PropertyValue")
propVal.PutObjectProperty ADSTYPE_OCTET_STRING, v
Set sd = propVal.GetObjectProperty(ADSTYPE_NT_SECURITY_DESCRIPTOR)

'--- Enumerate ACE in DACL
Set dacl = sd.DiscretionaryAcl

For Each ace In dacl

   '--- TRUSTEE----
   perm = ace.Trustee
   
   '----ACE TYPE-----
   If (ace.AceType = ADS_ACETYPE_ACCESS_ALLOWED) Then
      perm = perm & " is allowed to "
   ElseIf (ace.Type = ADS_ACETYPE_ACCESS_DENIED) Then
      perm = perm & " is denied to:"
   End If
   
   '--- ACE MASK ------
   If (ace.AccessMask And RIGHT_MAIL_SEND_AS) Then
      perm = perm & " -send mail"
   End If
   
   If (ace.AccessMask And RIGHT_MAIL_RECEIVE_AS) Then
       perm = perm & " -receive mail as"
   End If
   
   If (ace.AccessMask And RIGHT_DS_MODIFY_USER_ATT) Then
       perm = perm & " -modify user attributes"
   End If
   
   If (ace.AccessMask And RIGHT_DS_MODIFY_ADMIN_ATT) Then
       perm = perm & " -modify admin attributes"
   End If
   
   If (ace.AccessMask & RIGHT_DS_DELETE) Then
     perm = perm & " -delete this object"
   End If
   
   Debug.Print perm
   
Next

'---- You can also add a new ace, and add it to DACL
Set ace = CreateObject("AccessControlEntry")
ace.AceType = ADS_ACETYPE_ACCESS_ALLOWED  ' Allow permission
ace.AccessMask = RIGHT_MAIL_SEND_AS Or RIGHT_DS_MODIFY_USER_ATT Or RIGHT_DS_MODIFY_ADMIN_ATT Or RIGHT_DS_DELETE
ace.Trustee = "NTDEV\Administrator"
dacl.AddAce ace
sd.DiscretionaryAcl = dacl

'--- Now you have to convert back to the Raw Security Descriptor
propVal.PutObjectProperty ADSTYPE_NT_SECURITY_DESCRIPTOR, sd
v = propVal.GetObjectProperty(ADSTYPE_OCTET_STRING)

'-- Commit to the Directory
o.Put "NT-Security-Descriptor;binary", v
o.SetInfo



End Sub
