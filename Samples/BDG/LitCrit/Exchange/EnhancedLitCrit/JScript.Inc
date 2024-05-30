<%
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- JScript.inc : Common Javascript Functions -->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
%>

<script language="Javascript">

function fm__setMultivalue(objThisList,objThisHiddenFld,iThisSelection) {
    var sBuffer = "";
    cItems = objThisList.length;
    if (cItems>0) {
        if (iThisSelection==0){ //'checking none unselects the rest
            for(y=0; y < cItems; y++) {
                objThisList.options[y].selected = false
            }
            objThisHiddenFld.value = "";
        }
        else {
            for(y=1; y < cItems; y++) {
                if (objThisList.options[y].selected!=false) 
                  sBuffer+=objThisList.options[y].value+", ";
            }
            objThisHiddenFld.value = sBuffer;
        }
    }
}

function fm__ComboSelectEnum(objThisCombo,szMsgVal) {
    iMsgVal = parseFloat(szMsgVal);
    if (!isNaN(iMsgVal)) {
       objThisCombo.selectedIndex=iMsgVal;
    }
}

function fm__ComboSelectText(objThisCombo,szMsgVal) {
    // Process Text Datatypes
    for(y=0; y < objThisCombo.length; y++){
        if (objThisCombo.options[y].value==szMsgVal) {
           objThisCombo.selectedIndex=y;
           break;
        }
    }
}

function fm__ComboSelectDuration(objThisCombo,szMsgVal) {
    // Process Duration Datatype: 7
    iMsgVal = parseFloat(szMsgVal);
    if (!isNaN(iMsgVal)) {
        for(y=0; y < objThisCombo.length; y++){
            szOptionText = objThisCombo.options[y].value;
            szOptionText = szOptionText.toLowerCase();
            if (szOptionText.indexOf("h") > -1) 
                iThisVal=parseFloat(szOptionText)*60;
            else if (szOptionText.indexOf("d") > -1 )
                iThisVal=parseFloat(szOptionText)*1440;
            else if (szOptionText.indexOf("w") > -1 )
                iThisVal=parseFloat(szOptionText)*(60*24*7);
            else if (szOptionText.indexOf("m") > -1) 
                iThisVal=parseFloat(szOptionText);
            else 
                iThisVal=parseFloat(szOptionText)*60;
            if (iThisVal==iMsgVal) {
               objThisCombo.selectedIndex=y;
               break;
            }
        }
    }
}

function fm__ComboSelectComputerVal(objThisCombo,szMsgVal) {
    // Process Duration Datatype: 7
    iMsgVal = parseFloat(szMsgVal);
    if (!isNaN(iMsgVal)) {
        for(y=0; y < objThisCombo.length; y++){
            szOptionText = objThisCombo.options[y].value;
            szOptionText = szOptionText.toLowerCase();
            if (szOptionText.indexOf("k") > -1) 
                iThisVal=parseFloat(szOptionText)*1024;
            else if (szOptionText.indexOf("m") > -1 )
                iThisVal=parseFloat(szOptionText)*1024*1024;
            else if (szOptionText.indexOf("g") > -1 )
                iThisVal=parseFloat(szOptionText)*1024*1024*1024;
            else if (szOptionText.indexOf("b") > -1 )
                iThisVal=parseFloat(szOptionText);
            else 
                iThisVal=parseFloat(szOptionText);
            if ((iMsgVal-iThisVal<1) && (iMsgVal-iThisVal>-1)) {
               objThisCombo.selectedIndex=y;
               break;
            }
        }
    }
}

function fm__ComboSelectInt(objThisCombo,szMsgVal) {
    // Process Value Datatypes
    iMsgVal = parseInt(szMsgVal);
    if (!isNaN(iMsgVal)) {
        for(y=0; y < objThisCombo.length; y++){
            szOptionText = objThisCombo.options[y].value;
            x = szOptionText.indexOf("(");
            if (x > -1) {
                szOptionText = "-"+szOptionText.substring(1,szOptionText.length-1);
            }
            iThisVal=parseInt(szOptionText);
            if (iThisVal==iMsgVal) {
               objThisCombo.selectedIndex=y;
               break;
            }
        }
    }
}

function fm__ComboSelectValue(objThisCombo,szMsgVal) {
    // Process Value Datatypes
    iMsgVal = parseFloat(szMsgVal);
    if (!isNaN(iMsgVal)) {
        for(y=0; y < objThisCombo.length; y++){
            szOptionText = objThisCombo.options[y].value;
            x = szOptionText.indexOf("(");
            if (x > -1) {
                szOptionText = "-"+szOptionText.substring(1,szOptionText.length-1);
            }
            iThisVal=parseFloat(szOptionText);
            if (iThisVal==iMsgVal) {
               objThisCombo.selectedIndex=y;
               break;
            }
        }
    }
}

function fm__ComboSelectBool(objThisCombo, szMsgVal) {
    // Process Value Datatypes
    szTrueChars  = "1 y Y t T"
    szOnChars    = "On on oN ON";
    szFalseChars = "0 n N f F Of of oF OF";
    szOffChars   = "Of of oF OF";
    if (szMsgVal.charAt(0)=='T') boolVal=true;
    else if (szMsgVal.charAt(0)=='-') boolVal=true; // iis2 uses -1 for True
    else boolVal=false;

    for(y=0; y < objThisCombo.length; y++){
        szOptionText = objThisCombo.options[y].value;
        szSearchChars = szOptionText.charAt(0);
        fSelect=false;
        if (boolVal) { // If the msg data is true and the combo is one of these
            if (szSearchChars != "o" && szSearchChars != "O") {
                if (szTrueChars.indexOf(szSearchChars) > -1) fSelect=true;
            }
            else {
                szSearchChars += szOptionText.charAt(1);
                if (szOnChars.indexOf(szSearchChars) > -1) fSelect=true;
            }
        }
        else {
            if (szSearchChars != "o" && szSearchChars != "O") {
                if (szFalseChars.indexOf(szSearchChars) > -1) fSelect=true;
            }
            else {
                szSearchChars += szOptionText.charAt(1);
                if (szOffChars.indexOf(szSearchChars) > -1) fSelect=true;
            }
        }

        if (fSelect) {
           objThisCombo.selectedIndex=y;
           break;
        }
    }
}

function fm__ComboSelectDateTime(objThisCombo,szMsgVal) {
    if (szMsgVal != "") {
        iMsgDateVal=Date.parse(szMsgVal);
        // Date.parse returns NaN except in ie3 returns 0
        if ( isNaN(iMsgDateVal) || (iMsgDateVal==0) ) {
           y = objThisCombo.length - 1;
           objThisCombo.selectedIndex = y;  
        }
        else {
            bFound=false;
            for(y=0; y < objThisCombo.length; y++){
                szOptionText = objThisCombo.options[y].value;
                iThisDateVal=Date.parse(szOptionText);
            
                if (iThisDateVal==iMsgDateVal) {
                   objThisCombo.selectedIndex = y;
                   bFound = true;
                   break;
                }
            }
            if (bFound==false) {
               y = objThisCombo.length - 1;
               objThisCombo.selectedIndex = y;  
            }
        }
    }    
}

function fm__ComboSelectPercent(objThisCombo,szMsgVal) {
    // Process Percent Datatype: 27
    iMsgVal = parseFloat(szMsgVal);
    if (!isNaN(iMsgVal)) {
        for(y=0; y < objThisCombo.length; y++){
            szOptionText = objThisCombo.options[y].value;
            iThisVal=parseFloat(szOptionText);
            if (Math.abs(iThisVal) >= 1) {
                iThisVal /= 100;
            }
            // floating point math bug in javascript results are +-.0000000000002
            if (Math.abs(iThisVal-iMsgVal) < 0.0000001) {
               objThisCombo.selectedIndex=y;
               break;
            }
         }
    }
}

function fm__ComboSelectCurrency(objThisCombo,szMsgVal) {
    // Process Currency Datatype: 14
    iMsgVal = parseFloat(szMsgVal);
    if (!isNaN(iMsgVal)) {
        for(y=0; y < objThisCombo.length; y++){
            szOptionText = objThisCombo.options[y].value;
            x = szOptionText.indexOf("$");
            if (x > -1) {
                szOptionText = szOptionText.substring(0,x)+szOptionText.substring(x+1)
            }
            x = szOptionText.indexOf("(");
            if (x > -1) {
                szOptionText = "-"+szOptionText.substring(1,szOptionText.length-1);
            }
            iThisVal=parseFloat(szOptionText);
            if (iThisVal==iMsgVal) {
               objThisCombo.selectedIndex=y;
               break;
            }
        }
    }
}

</script>