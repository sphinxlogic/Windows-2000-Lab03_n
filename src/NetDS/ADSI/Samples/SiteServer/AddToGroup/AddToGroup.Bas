Attribute VB_Name = "AddToGroup"
Sub Main()

'-- adopted from Site Server Knowledge Base
Dim adsMemberOf
Dim adsGroup
Dim strLdapSrv
Dim strMemberPath, strUserCn, strUserDn, _
strGroupDn, strAdmin, strAdminPwd

strLdapSrv = "LDAP://localhost:5292"
strMemberPath = ",ou=Members,o=Microsoft"
strUserCn = "cn=JohnDoe"
strUserDn = strUserCn + strMemberPath
strGroupDn = strLdapSrv + "/o=Microsoft/ou=Groups/cn=Public"
strAdmin = "cn=Administrator,ou=Members,o=Microsoft"
strAdminPwd = "password"


'Bind to the specific group using Administrator credentials
Set adsGroup = GetObject("LDAP:")
Set adsGroup = adsGroup.OpenDSObject(strGroupDn, strAdmin, _
strAdminPwd, CLng(0))


'Create the new 'memberOf' object that will be stored in the group
Set adsMemberOf = adsGroup.Create("memberof", strUserCn)

'Add the path to the user and store it in the 'memberObject' property
adsMemberOf.Put "memberobject", CStr(strUserDn)

'Flush the property cache and update the directory
adsMemberOf.SetInfo

'Destroy the objects Set adsMemberOf = Nothing
Set adsGroup = Nothing

End Sub
