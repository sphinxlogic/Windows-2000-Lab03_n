//***************************************************************************
// 
// WMI Sample Script - Class enumeration (JScript)
//
// This script demonstrates the enumeration of sublcasses of a class.
//
//***************************************************************************

var e = new Enumerator (GetObject("winmgmts:").SubclassesOf ("CIM_LogicalElement"));
for (;!e.atEnd();e.moveNext ())
{
	var Subclass = e.item ();
	WScript.Echo ("Subclass name:", Subclass.Path_.Class);
}

