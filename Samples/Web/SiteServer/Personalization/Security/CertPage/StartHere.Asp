<%
'####################################################################
'                                                                     
'   Microsoft Site Server v3.00                                   
'                                                                     
'   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
'
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'####################################################################
%>

<%Response.Expires=0%>
<% Response.Buffer = TRUE %>
<!--#include file=LogToFile.txt-->
<!--#include file=CertPageError.txt-->
<HTML>
<HEAD>
<TITLE>Certificate Server Enrollment Form</TITLE>
<META HTTP-EQUIV="Cache-Control" CONTENT="no cache">
<META HTTP-EQUIV="Pragma" CONTENT="no cache">
<META HTTP-EQUIV="Expires" CONTENT="0">

<%

    ' LogginOn controls event logging for this page.
    InitLogging("D:\CERTPAGE\SSCertPage.Log")

    ' Verify that we are authenticated. 
    If Request("REMOTE_USER") = "" Then
       ErrorOut("This page must be protected by an authentication method.")
    End if

    ' Initialize the signup application state variable.  It allows other
    '  pages in the application to be called.
    Session("InProcess") = 1 

    ' Save the user name for other pages.
    Session("UserName") = Request("REMOTE_USER")

    ' Create the user DN for the PKCS10 that will be created by the client.
    '  This example does not include anything for O or OU.
    Set Session("AUO") = Server.CreateObject("Membership.UserObjects")
    if Err <> 0 Then
	    Response.Write "Server.CreateObject failed for Membership.UserObjects"
	    Response.End
    End if
    UserDN =          "C="     & Session("AUO").c  & ";" 
    UserDN = UserDN & "S="     & Session("AUO").st & ";" 
    UserDN = UserDN & "L="     & Session("AUO").l  & ";"
    UserDN = UserDN & "O="     & ";"
    UserDN = UserDN & "OU="    & ";"
    UserDN = UserDN & "CN="    & Session("AUO").givenName & " " & Session("AUO").sn & ";"
    UserDN = UserDN & "Email=" & Session("AUO").mail & ";"

    ControlType = "XENROLL" 

    ' This logs the request CN for the new cert to a file if the logging option is on.
    '  ** LogToFile: This code is commented out.  If you wish to log the request
    '                DNs to a file, uncomment the following line.  
    'LogToFile(UserDN)

%>
  
  <OBJECT
    classid="clsid:43F8F289-7A20-11D0-8F06-00C04FC295E1"
    CODEBASE="/CertControl/xenroll.cab#Version=5,102,1680,101"       
    id=IControl
    >
  </OBJECT>
  

  <SCRIPT LANGUAGE="JAVASCRIPT">
   function geterror(message, url, value) 
   {

     if (message == "Out of memory") 
     {
       msg = "Xenroll is unable to generate a PKCS10:\n\n Please verify ";
       msg = msg + "that your CSP supports any settings you have made \n";
       msg = msg + "and that your input is valid."; 
       alert(msg);
       return true;
     }
     else 
     { 
       return false;
     }
   }
  </SCRIPT>

  <SCRIPT LANGUAGE="JAVASCRIPT">
    function SubmitRequest() 
    {

      szPKCS10 = "";

      DN = "<%=UserDN%>"; 

        onerror=geterror; 

        IControl.KeySpec = 1;
        document.ReqData.CertUsage.value = "1.3.6.1.5.5.7.3.2";

        szPKCS10 = IControl.CreatePKCS10(DN, document.ReqData.CertUsage.value);
        document.ReqData.CertRequest.value = szPKCS10;


         if (szPKCS10.length > 10)
           document.ReqData.submit();
         else {
           Msg = "The data you have entered appears to be invalid.";
           alert(Msg);
           window.location = "certerrorpage.asp"
         }
    }   
  </SCRIPT> 


</HEAD>

 <BODY BGCOLOR=#FFFFFF>
 <HR>

 <CENTER> 
 
 <FONT SIZE=6><B>Certificate Enrollment Form</B></FONT>
 
  <FORM NAME="ReqForm" ENCTYPE=x-www-form-encoded METHOD=POST>

   <TABLE BORDER=8>
   <TR>
   <TH ALIGN=LEFT><B> CERTIFICATE ENROLLMENT IS COMMENCING </B></TH>	
   <TR>
   </TABLE>
   </FORM>
   </FONT>

   <FORM NAME="ReqData" ACTION="Step1.asp" ENCTYPE=x-www-form-encoded METHOD=POST>
     <INPUT TYPE="HIDDEN" NAME="CertRequest">
     <INPUT TYPE="HIDDEN" NAME="CertAttrib" VALUE="">
     <INPUT TYPE="HIDDEN" NAME="SubmitFlag" VALUE=257>
     <INPUT TYPE="HIDDEN" NAME="GetCertFlag" VALUE=257>
     <INPUT TYPE="HIDDEN" NAME="ControlType" VALUE=<%=ControlType%>>
     <INPUT TYPE="HIDDEN" NAME="PassThru">       
     <INPUT TYPE="HIDDEN" NAME="CertUsage">
     <INPUT TYPE="HIDDEN" NAME="WriteCertToCSP">
     <INPUT TYPE="HIDDEN" NAME="SaveCert">
     <INPUT TYPE="Submit" NAME="Request" value=" Continue " onClick="SubmitRequest()">
   </FORM>

 </CENTER>
 


  <!--FOOTER START-->
  <HR>
  <HR>
  <i>&#169; 1997 by Microsoft Corporation. All rights reserved.</i>
  <!--FOOTER END-->
 
</BODY>
</HTML>


