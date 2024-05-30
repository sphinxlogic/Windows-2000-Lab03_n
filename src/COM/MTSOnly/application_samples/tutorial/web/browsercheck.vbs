<%	
	'This file is provided as part of the Microsoft Visual Studio 6.0 Samples

	'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
	'WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
	'INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
	'OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
	'PURPOSE.

	'Copyright (C) 1997, 1998 Microsoft Corporation, All rights reserved

	'**************************************************
	'	Include Purpose: Checks for Internet Explorer 4
	'**************************************************
	Dim strUserAgent

	strUserAgent = Request("HTTP_USER_AGENT")
	 if inStr(1, UCase(Request("HTTP_USER_AGENT")),"MSIE 4.",1) = 0 Then
		Response.Redirect("getMSIE4.htm")
	End If 
%> 			 

			 