<?XML version="1.0"?>
<!-- 
Note: To run this sample channel, post the files in this directory on an HTTP server.
Make sure you replace the path name below (www.mysite.com/Channel) with the one where the 
files exist on your server. The link specified in the screensaver file (scrnsave.htm) 
should also be changed.
-->
<CHANNEL HREF="http://www.mysite.com/Channel/homepage.htm"
	 BASE="http://www.mysite.com/Channel/">
	<TITLE>Sample "Color" Channel</TITLE>
	<ABSTRACT>The sample color channel contains a red, green, and blue page for viewing.</ABSTRACT>
	<LOGO HREF="logo_big.gif" STYLE="IMAGE-WIDE"/>
	<LOGO HREF="logo_med.gif" STYLE="IMAGE"/>
	<SCHEDULE STARTDATE="1997-09-23">
		<INTERVALTIME DAY="1" />
		<EARLIESTTIME HOUR="2" />
		<LATESTTIME HOUR="6" />
	</SCHEDULE>
   	<ITEM HREF="page1.htm">
		<LOGO HREF="red.gif" STYLE="ICON"/>
		<TITLE>The Red Page</TITLE>
		<ABSTRACT>This is the abstract description for the red page.</ABSTRACT>
	</ITEM>
	<ITEM HREF="page2.htm">
		<LOGO HREF="green.gif" STYLE="ICON"/>
 		<TITLE>The Green Page</TITLE>
		<ABSTRACT>This is the abstract description for the green page.</ABSTRACT>
   	</ITEM>
	<ITEM HREF="page3.htm">
		<LOGO HREF="blue.gif" STYLE="ICON"/>
		<TITLE>The Blue Page</TITLE>
		<ABSTRACT>This is the abstract description for the blue page.</ABSTRACT>
	</ITEM>
	<ITEM HREF="scrnsave.htm">
		<USAGE VALUE="ScreenSaver"></USAGE>
	</ITEM>

</CHANNEL>
