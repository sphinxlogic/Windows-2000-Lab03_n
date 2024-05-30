<%
'####################################################################
'                                                                     
'   Microsoft Site Server v3.00                                   
'                                                                     
'   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'                                                                      
'####################################################################
%>

<%Response.Expires=0%>
<% Response.Buffer = TRUE %>
<!--#include file=LogToFile.txt-->
<!--#include file=CertPageError.txt-->
<!--#include file=DataStore.txt-->
<!--#include file=Utils.txt-->
<HTML>
<HEAD>
<TITLE>Web Server Enrollment Page</TITLE>
<META HTTP-EQUIV="Cache-Control" CONTENT="no cache">
<META HTTP-EQUIV="Pragma" CONTENT="no cache">
<META HTTP-EQUIV="Expires" CONTENT="0">


<% 

    ' This page cannot be called directly.
    If Session("InProcess") <> 1 Then
      ErrorOut("This page cannot be called directly.")
    End if

    ' MAKE SURE WE ARE AUTHENTICATED.
    If Request("REMOTE_USER") = "" Then
       ErrorOut("Step1.asp should be protected by an authentication method.")
    End if


    ' GET OUR CA INTERFACES.
	Dim Certificate, DispositionCode, LastStatus,ConfigString	     
	Dim SubmitFlag, GetCertFlag, Attributes, ControlType

	set ICertRequest = Server.CreateObject("CertificateAuthority.Request")
	set ICertConfig	 = Server.CreateObject("CertificateAuthority.Config") 

	ConfigString = ICertConfig.GetConfig(0)
	PKCS10	     = Request.Form("CertRequest")
	SubmitFlag   = Request.Form("SubmitFlag")
	GetCertFlag  = Request.Form("GetCertFlag")
	Attributes   = Request.Form("CertAttrib")
	ControlType  = Request.Form("ControlType")
   	

	'PROCESS THE PKCS10 REQUEST
	On Error Resume Next
	
	if PKCS10 <> "" then
      DispositionCode = ICertRequest.Submit(SubmitFlag, PKCS10, Attributes, ConfigString)
	  LastStatus = 0
	  LastStatus = ICertRequest.GetLastStatus()

      ' Get the binary certificate for storage in the LDAP store.
      BinaryCert = ICertRequest.GetCertificate(2)

      '  ** BASE64 This code is commented out.  It is an example of acquiring a base64
      '     encoded certificate.  If you are going to add base64 encoded certificates
      '     to your data store, you will have to remove the comment mark and follow the
      '     directions below.
      'Base64Cert = ICertRequest.GetCertificate(1)

      ' Get the certificate in a PKCS7 for the client.
	  Certificate = ICertRequest.GetCertificate(GetCertFlag)

	  Session("CertStore") = Certificate

      '  ** BASE64 This code is commented out.  If you wish to implement it, you must
      '     create a Base64Cert attribute and add it to the valid attributes 
      '     for a user in the Members container.
      ' Store the certificate in the LDAP store as a base 64 encoded string.
      'AddToAttribute "Base64Cert", Base64Cert


      ' ** Store the binary certificate in the data store as a user attribute. **
      ' This requires the CertSource object!  It must be installed
      '  and registered on the server.
      '
      Dim ssCert

      set ssCert = Server.CreateObject("CertSrc.CertSrc.1")
      DNString = "cn=" + Session("UserName") + ",ou=Members,o=" + AuthRootNode
      ssCert.DN = DNString
      ssCert.PortNumber = AuthPortNumber
      ssCert.ServerName = AuthServerName
      ssCert.Certificate = BinaryCert
      ssCert.AddCertToDN

    End If
    		 
%>

   <% if PKCS10 = "" then %>
     <SCRIPT LANGUAGE="VBSCRIPT">
      msg = "The format of your certificate request was invalid:"
	  msg = msg & " The request string was empty."
	  msg = msg & " Please see your system administrator for further"
      msg = msg & " instructions."
      err = MsgBox(msg, 16, "CERTIFICATE SIGNUP")
      window.location = "certerrorpage.asp"
     </SCRIPT>
    <% end if %>        


<% 

     'Format the  PKCS7 for the client.
     FormatedCert = ""
     qc = chr(34)
     CharsLeft = True
     OutP = 1

     while(CharsLeft)
	   BeginLine = OutP
	   OutP = InStr(OutP, Certificate, vbNewLine)

	   if (OutP > 0) then
	     FormatedCert = FormatedCert & "szPKCS7 = szPKCS7 & " & qc & _
	     Mid(Certificate, BeginLine, OutP-BeginLine) & qc 

         if (OutP >= (len(Certificate) - len(vcNewLine))) then 
	        CharsLeft = False
	     end if
	    
	   else
	     CharsLeft = False
	   end if
	   FormatedCert = FormatedCert & vbNewLine
	   OutP = OutP + len(vbNewLine)
     wend

%>

<OBJECT
classid="clsid:43F8F289-7A20-11D0-8F06-00C04FC295E1"
CODEBASE="/CertControl/xenroll.cab#Version=5,102,1680,101"
id=IControl
>
</OBJECT>   

<SCRIPT LANGUAGE="VBSCRIPT">
sub Download() 

Dim result, Message
	
On Error Resume Next
	
szPKCS7 = ""
         <%=FormatedCert%>
  
 	REM IControl.WriteCertToCSP = TRUE
    IControl.AcceptPKCS7(szPKCS7)

    If err.Number = 0 Then

      ' Show them some useful information.
      Message = "Your new certificate has been successfully installed! " & vbcrlf & vbcrlf
      Message = Message & " Press Ok to continue..." & vbcrlf
      result = MsgBox (Message, 64, "Certificate Enrollment Page")

      ' Now go to the page that will create and store the certificate hash for the user.
	  window.location = "Step2.asp"

    Else

      ' Things did not go well. Tell the user about it and link to another page.
      Message = "Unable to install the certificate:" & vbcrlf & vbcrlf 
      Message = Message & "Please verify that your CSP supports any settings you have made " 
      Message = Message & "and that your input is valid." & vbcrlf & vbcrlf 
      Message = Message & "Error: " & Hex(err)
	  result = MsgBox (Message, 48, "<%=ControlType%>")  
      window.location = "certerrorpage.asp"
    End If    

end sub 


</SCRIPT>

<BODY BGCOLOR=#FFFFFF OnLoad="Download">
<HR>

<Center>
	
<%  if DispositionCode = 3 then %>

	  <H1>Certificate Download</H1>
	  <B>
	  <FONT SIZE=5>
	  <BR>Your request has been successfully processed!
	  </FONT>
	  <BR><BR><BR><BR><BR>
<% response.write DNString %>
<BR>
<%  else %>

       <H1>Error!!!</H1>
       <B>
       <FONT SIZE=5>
	  
       Certificate Server is unable to process your request.
       </FONT>
       <BR><BR><BR>
       <FONT SIZE=4>
       <I>
       Last Status Error Code = <%=HEX(LastStatus)%>
       </I>
       </FONT>   
        
      <BR><BR>

      <% if LastStatus = 1722 then %>
        <FONT SIZE=4>
          This error can occur if the Certificate Authority Service<BR>
          has not been started.<BR>
          </FONT>
          <BR><BR>  
	      <FONT SIZE=5>
          Please contact your Certificate Authority for assistance.
          </FONT> 
      <% elseif LastStatus = -2146893811 then %>
        <FONT SIZE=4>
          This error may indicate a problem with the Certificate Authority key.<BR>
          The key was not found and the certificate was not issued.<BR>
          </FONT>
          <BR><BR>
	      <FONT SIZE=5>
          Please contact your Certificate Authority for assistance.
        </FONT>
      <% elseif LastStatus = 87 then %>
        <FONT SIZE=4>
          This error indicates that "Invalid Data" was submitted to Certificate Server.<BR>
          This can occur if A) You are submitting a request that is not formated correctly<BR>
          or B) The the Certificate Authority used a network share or relative path to point<BR>
          to the "Shared Directory" when configuring Certificate Server.                
          </FONT>
          <BR><BR>
	      <FONT SIZE=5>
          Please contact your Certificate Authority for assistance.
        </FONT>
      <% elseif LastStatus = -2147024883 then %>
          <FONT SIZE=4>
          This error may indicate that the encoded length of your request is 7F.<BR>
          Please reapply for this certificate and changing the "length" of the data<BR>
          you entered for Common Name, Department...  
          </FONT>
          <BR><BR><BR>
	      <FONT SIZE=5>
          If this doesn't work, please contact your Certificate Authority.
          </FONT>
      <% else %>
          <FONT SIZE=5>
          <BR><BR>
          Please verify that you are submitting a valid request or contact 
	      <BR>your Certificate Authority for assistance.
          </FONT> 
      <% end if %>
      </B>	
      <BR><BR><BR><BR> 


<%  end if %>

</CENTER>

<!--FOOTER START-->
<HR>
<HR>
<FORM>
<i>&#169; 1998 by Microsoft Corporation. All rights reserved.</i>
</FORM>
<!--FOOTER END-->
	

</BODY>
</HTML>



	
		
	
		

		
