<?XML version="1.0"?>

<CHANNEL HREF="http://<your server>/osd/GenericSample/circ3_home.htm">
	<TITLE>Circle Control Channel</TITLE>

	<USAGE VALUE="SoftwareUpdate"/>
	<SOFTPKG HREF="/osd/GenericSample/circ3_setup.htm"
		NAME="{9DBAFCCF-592F-101B-85CE-00608CEC297B}"
		VERSION="1,0,0,2"
		STYLE="MSICD"
		PRECACHE="yes"
		>
		
		<USAGE VALUE="email"/>

		<TITLE>Circle Control</TITLE>
		<ABSTRACT> This is v2 of Circle</ABSTRACT>
		<IMPLEMENTATION>
			<PROCESSOR VALUE="x86" />
			<CODEBASE HREF="/osd/GenericSample/circ3.cab"/>
		</IMPLEMENTATION>

	</SOFTPKG>

</CHANNEL>

