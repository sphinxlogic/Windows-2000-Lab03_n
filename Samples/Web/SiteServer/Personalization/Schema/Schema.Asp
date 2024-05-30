<%
	'
	' Settings:
	'
	Dim g_sHostname: g_sHostname = "localhost:1002"
%>

<!--#Include File="schema.vbs"-->
<HTML>

<HEAD>
<TITLE>Schema Sample</TITLE>
</HEAD>

<BODY>
This script uses the schema library to create an attribute, modify the attribute, create a class, modify the class, delete the class, and finally, delete the attribute.  This script will exit immediately if it has any problems.<BR>
<BR>
To configure this script, change the variables in the "Settings" section at the top of the script.  Those settings are currently:<BR>
<B>g_sHostname</B>=<% = g_sHostname %><BR>
<BR>
<BR>
<HR>

<%
	'
	' Create an attribute:
	'		cn=testAttribute
	'		displayName=A Test Attribute
	'		description=This is a test
	'		attributeSyntax=unicodeString
	'		syntaxConstraints=
	'		isSingleValued=false
	'		isSearchable=true
	'
	Response.Write "Creating an attribute named 'testAttribute'<BR>"
	CreateAttribute g_sHostname , "cn=testAttribute", "A Test Attribute", _
	 				"This is a test", "unicodeString", "", True, True
	Response.Write "Attribute created.<BR>"

	'
	' Modify the attribute:
	'		cn=testAttribute
	'		displayName=A Second Test
	'		description=This used to be a test
	'		syntaxConstraints=T:\SampleSite
	Response.Write "Modifying the attribute named 'testAttribute'<BR>"
	ModifyAttribute g_sHostname , "cn=testAttribute", "A Second Test", _
					"This used to be a test", "T:\SampleSite"
	Response.Write "Attribute modified.<BR>"

	'
	' Create a class
	'		cn=testClass
	'		displayName=A Test Class
	'		description=This is a test
	'		mustContain=testAttribute,objectClass,cn
	'		mayContain=
	'		rdnAttrId=cn
	'		possibleSuperiors=organizationalUnit
	'		isContainer=false
	'		containerType=0
	'		isSecurityPrincipal=false
	'
	Response.Write "Creating a class named 'testClass'<BR>"
	CreateClass g_sHostname , "cn=testClass", "A Test Class", _
				"This is a test", Array("cn", "objectClass", "testAttribute"), _
				"", "cn", "organizationalUnit", False, 0, False
	Response.Write "Class created.<BR>"

	'
	' Modify a class
	'		cn=testClass
	'		displayName=A Second Test
	'		description=This used to be a test
	'		mustContain=objectClass,cn
	'		mayContain=testAttribute
	'		rdnAttrId=cn
	'		possibleSuperiors=organizationalUnit
	'		isContainer=false
	'		containerType=0
	'		isSecurityPrincipal=false
	'
	Response.Write "Modifying the class named 'testClass'<BR>"
	ModifyClass g_sHostname, "cn=testClass", "A Second Test", _
				"This used to be a test", Array("cn","objectClass"), _
				"testAttribute", "organizationalUnit", False, 0, False
	Response.Write "Class modified.<BR>"

	'
	' Delete a class
	'
	Dim sSchemaPath: sSchemaPath = GetSchemaPath(g_sHostname )
	Response.Write "Deleting the class named 'testClass'<BR>"
	DeleteObject sSchemaPath & "/cn=testClass"
	Response.Write "Class deleted.<BR>"

	'
	' Delete an attribute:
	'
	Response.Write "Deleting the attribute named 'testAttribute'<BR>"
	DeleteObject sSchemaPath & "/cn=testAttribute"
	Response.Write "Attribute deleted.<BR>"
%>
<BR>
<BR>
<HR>
Test complete.<BR>
<BR>
</BODY>