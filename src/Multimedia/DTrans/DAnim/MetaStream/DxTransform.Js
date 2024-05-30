//The following JavaScript is Copyright ©1998 MetaCreations Corporation
//Any reproduction of the following code is prohibited without permission.

if(navigator.appName == "Netscape") {
	document.writeln("<embed type='application/metastream' ID='Sneaker' name='Sneaker' width=401 height=357 src='http://www.metastream.com/dev/demo/walkthru/models/mcre.mts' BackgroundImage='clouds.jpg' AutoResolution=1 BorderStyle=1 BackgroundColor='0' border=0>");
} else {
//We want to show off Chrome in IE, but we let Netscape users see it anyway.

	//Start off by creating our object and scene
	document.writeln("<OBJECT id='DAControl' classid='CLSID:69AD90EF-1C20-11d1-8801-00C04FC29D46' width=401 height=357>");
	document.writeln("</OBJECT>");
}