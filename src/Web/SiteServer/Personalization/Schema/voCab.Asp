<HTML>

<BODY>
<%
	'
	' Configure this to point to your hierarchy:
	'
	Dim sTagPath
	sTagPath = "LDAP://localhost:1002/o=microsoft/ou=admin/ou=other/ou=TagTerms/modelName=default"
%>

This script prints out the site vocabulary pointed to by the sTagPath variable inside this file.<BR>
<BR>
<B>sTagPath<B>=<% = sTagPath %><BR>
<BR>
<HR>
<BR>

<%
	'
	' Print out all of the terms:
	'
	Dim oTerm
	Dim oTerms: Set oTerms = CreateObject("CADSContainer.CADSContainer.1")
	Dim cBasePathLen: cBasePathLen = Len(sTagPath)

	oTerms.GetInfo sTagPath,"%objectClass=tagTerm"
	For Each oTerm in oTerms
		sTermPath = Replace(Mid(oTerm.ADsPath, cBasePathLen + 1), "/cn=", "\")
		Response.Write sTermPath & "<BR>"
	Next
%>

</BODY>
</HTML>