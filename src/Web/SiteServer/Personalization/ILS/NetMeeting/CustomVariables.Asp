<%
	'Global variables for all pages
	
	'Set the machine name here when porting to different machine
	strServerName = "your server goes here"
	'Organization in LDAP string.  This is what O= is set to
	strOrg = "Microsoft"
	'Fully Qualified Domain Name.  Used in 'callto:' so you can run on seprate server from LDAP
	strFQDN = ""
	'Max length of time scripts will run.  Make sure this is long enough to show MaxRecords
	Server.ScriptTimeout = 90
	'Maximum number of records to show in one search.
	MaxRecord = 200
	
	'*** DO NOT CHANGE ANYTHING BELOW THIS LINE ***
	
	' If strFQDN is left blank, it will use local server name in 'callto:'
	If strFQDN = "" then strFQDN = Request.ServerVariables("HTTP_HOST")
%>