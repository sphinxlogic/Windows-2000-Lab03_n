/*****************************************************************************
 * (C) 1998 Microsoft Corporation.  All rights reserved.                     *
 * This is prerelease software and is provided as is and Microsoft makes no  *
 * warranties,  either express or implied. The entire risk of the use or the *
 * results of the use of this prerelease software remains with the user.     *
 *****************************************************************************/

///////////////////////////////////////////////////////////////////////////////
// This script shows how to change a property of all the application to a fixed
// predetermined value
//

var WebTE = WScript.CreateObject("WebTE.Root");
var admin = WebTE.Arrays.GetContainingArray();
var applications = admin.Applications;

apps = new Enumerator(applications);

try {
    for (; !apps.atEnd(); apps.moveNext() ) {
        var app = apps.item();
        app.OperatorExtension = "1160";
    }
    admin.Save();
    WScript.echo("All applications' operator extensions were changed");
}

catch(e) {
    WScript.echo(e.description);
}

