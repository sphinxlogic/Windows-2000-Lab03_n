Attribute VB_Name = "Module1"
Sub Main()
Dim oADsContainer
Dim oADsNewUser
Dim oGuidGen
Dim strGuid
Dim strLdapPath 'The path to the ou=Members container

strLdapPath = "LDAP://andyhar11:5292/o=Microsoft/ou=Members"

'Instantiate the GUID Generator that comes with Site Server
'and store the GUID for use later on.
Set oGuidGen = CreateObject("Membership.GuidGen.1")
strGuid = oGuidGen.GenerateGuid

'Bind to the container in which the Member will be created
Set oADsContainer = GetObject(strLdapPath)

'Create the new user object, note that the Create() method returns
'an interface pointer
Set oADsNewUser = oADsContainer.Create("member", "cn=JohnDoe")
oADsNewUser.Put "givenName", "John"
oADsNewUser.Put "sn", "Doe"
oADsNewUser.Put "userPassword", "password"
oADsNewUser.Put "GUID", CStr(strGuid)
oADsNewUser.SetInfo

'Destroy the objects
Set oGuidGen = Nothing
Set oADsNewUser = Nothing
Set oADsContainer = Nothing

End Sub
