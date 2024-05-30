<%
	'must resume next on error since ADSI will return error if property is empty.
	On Error Resume Next
	
	'Border is used to change table border globaly
	Border = 0
	'Set the machine name here when porting to different machine
	strServerName = "localhost"
	strOrg = "Microsoft"
	Server.ScriptTimeout = 90
	MaxRecord = 200

	'
	'Key for translating LDAP objects to meaningful names
	'
	Email = "rfc822Mailbox"
	FirstName = "givenName"
	LastName = "surName"
	'location
	'comment
	Hidden = "sFlags"			' 0=yes 1=no
	Country = "c"
	Audio = "ilsA32833566"		' no=0 yes=1
	Video = "ilsA32964638"		' no=0 yes=1
	InCall = "ilsA26214430"		' yes=1 no=0
	UserType = "ilsA39321630"	' personal=1 business=2 adult=4
	'ipAddress
	'securityToken
	'objectClass
	'Port
	'protocolMimeType
	'mimeType
	'smodop
	'guid
		
	'Retrieving the array from the Application Object
	aCountry = Application("aCountry")
	aBuckets = Application("aBuckets")
	iRecordCount = Application("iCount")

    Set oMembers = CreateObject("cadscontainer.cadscontainer.1")

	FrmDir = Request("FrmDir")
	If (FrmDir = "TRUE") Then
	
		multimedia_cookie	= Request("multimedia") 		
		incall_cookie		= Request("incall")	
		UserType_cookie		= Request("UserType")
	
		ExpDate = now + 350
		
		Response.Cookies("Search")("multimedia")= multimedia_cookie
		Response.Cookies("Search")("incall") 	= incall_cookie
		Response.Cookies("Search")("UserType") 	= UserType_cookie
		Response.Cookies("Search").Expires 		= ExpDate
			
	Else
		multimedia_cookie	= Request.Cookies("Search")("multimedia")
		incall_cookie		= Request.Cookies("Search")("incall") 
		UserType_cookie		= Request.Cookies("Search")("UserType")
	End If
%>
<%
	' CREATE "strSearch" -- the query that will be executed
	strSearch = "(&(cn=*)(" & Hidden & "=1)"

	If multimedia_cookie <> "" Then
		Select case multimedia_cookie
			Case 0
				' leave it blank.  ALL is selected
			Case 1
				' audio is selected
				strSearch = strSearch & "(" & Audio & "=1)"
			Case 2
				' video is selected
				strSearch = strSearch & "(" & Video & "=1)"
			Case Else
				' if it is anything else, act like it is ALL
		End Select
	End If
	
	If incall_cookie <> "" Then
		strSearch = strSearch & "(" & InCall & "=" & incall_cookie & ")"
	End If
	
	If UserType_cookie <> "" Then
		strSearch = strSearch & "(" & UserType & "=" & UserType_cookie & ")"
	End If

	' close the last paren after adding any other search variables.
	strSearch = strSearch & ")"

	' set the Dn and call the query
	strDn = "LDAP://" & strServerName & "/o=" & strOrg & "/ou=Dynamic"
	'response.write strDN & "<BR>"
	'response.write strSearch & "<BR>"
    oMembers.GetInfo strDN, strSearch
%>

<HTML>
<HEAD>
	<TITLE>NetMeeting Directory</TITLE>
	<SCRIPT LANGUAGE="JAVASCRIPT">
	<!-- comment out javascript for non-supporting browsers
	//------------------------------------------------------------------------------------
	// Clear all inputs when user hits Clear button
	//------------------------------------------------------------------------------------
	function ClearAll()
	{
		document.Directory.elements[1].checked = true;
		document.Directory.elements[5].checked = true;
		document.Directory.elements[8].checked = true;
	}
	// -->                                                                                                                                                                                                                                                                                                                                                                                                             
	</SCRIPT>
</HEAD>

<BODY BGCOLOR="#FFFFFF" VLINK="#999999" LINK="#0000FF" ALINK="#228B22">

<FORM ACTION="directory.asp" METHOD="POST" NAME="Directory">
<INPUT TYPE="Hidden" NAME="FrmDir" VALUE="TRUE">	

<TABLE CELLSPACING="0" WIDTH="100%">
	<TR>
		<TD WIDTH="288">
			<IMG SRC="images/b_netmeeting.gif" ALT="Microsoft NetMeeting" HEIGHT="67" WIDTH="288">
		</TD>
		<TD ALIGN="CENTER">
			<B><FONT FACE="Arial, Helvetica" SIZE=5><%= strServerName %> Directory</FONT></B>
		</TD>
	</TR>
</TABLE>
<P>

<TABLE WIDTH="100%" BORDER="0" CELLSPACING=0 CELLPADDING=0 BORDER="<%= border %>>
	<TR>
		<TD VALIGN="middle">
			<B><FONT FACE="Arial, Helvetica" SIZE=2>
			Specify the NetMeeting users you want to list in the directory, and press the Submit button:
			</FONT></B>
		</TD>
	</TR>
	<TR>
		<TD COLSPAN="4">
			<TABLE CELLPADDING="0" CELLSPACING="10" BORDER="<%= Border %>" width="100%">
				<TR>
					<TD VALIGN="top" ALIGN="center">
						<TABLE CELLPADDING=0 CELLSPACING=0 BORDER="<%= Border %>">
							<TR>
								<TD COLSPAN="2">
									<FONT FACE="Arial, Helvetica" SIZE="2"><B>User Category</B></FONT>
								</TD>
							</TR>
				
							<TR>
								<TD>
									<INPUT TYPE=RADIO NAME="UserType" VALUE="" <% IF(UserType_cookie = "") THEN %> CHECKED <% End If %>>&nbsp;
								</TD>
								<TD>
									<FONT FACE="Arial, Helvetica" SIZE="2">All</FONT>
								</TD>
							</TR>
				
							<TR>
								<TD>
									<INPUT TYPE=RADIO NAME="UserType" VALUE="1" <% IF (UserType_cookie = "1") THEN %> CHECKED<% End If %>>&nbsp;
								</TD>
								<TD>
									<FONT FACE="Arial, Helvetica" SIZE="2">Personal</FONT>
								</TD>
							</TR>
				
							<TR>
								<TD>
									<INPUT TYPE=RADIO NAME="UserType" VALUE="2" <% IF (UserType_cookie = "2") THEN %> CHECKED<% End If %>>&nbsp;
								</TD>
								<TD>
									<FONT FACE="Arial, Helvetica" SIZE="2">Business</FONT>
								</TD>
							</TR>
				
							<TR>
								<TD>
									<INPUT TYPE=RADIO NAME="UserType" VALUE="4" <% IF (UserType_cookie = "4") THEN %> CHECKED<% End If %>>&nbsp;
								</TD>
								<TD>
									<FONT FACE="Arial, Helvetica" SIZE="2">Adult</FONT>
								</TD>
							</TR>
						</TABLE>
					</TD>
					<TD VALIGN="top" ALIGN="center">
						<TABLE CELLPADDING=0 CELLSPACING=0 BORDER="<%= border %>">
							<TR>
								<TD COLSPAN="2">
									<FONT FACE="Arial, Helvetica" SIZE="2"><B>Currently in Call</B></FONT>
								</TD>
							</TR>
							<TR>
								<TD>
									<INPUT TYPE="Radio" NAME="incall" VALUE="" <% IF (incall_cookie = "") THEN %> CHECKED<% End If %>>
								</TD>
								<TD>
									<FONT FACE="Arial, Helvetica" SIZE="2">All</FONT>
								</TD>
							</TR>
							<TR>
								<TD>
									<INPUT TYPE="Radio" NAME="incall" VALUE="1" <% IF (incall_cookie = "1") THEN %> CHECKED<% End If %>>
								</TD>
								<TD>
									<FONT FACE="Arial, Helvetica" SIZE="2"><IMG SRC="images/inacall.gif" ALT="In a call" WIDTH=16 HEIGHT=16 ALIGN="middle"> Yes</FONT>
								</TD>
							</TR>
							<TR>
								<TD>
									<INPUT TYPE="Radio" NAME="incall" VALUE="0" <% IF (incall_cookie = "0") THEN %> CHECKED<% End If %>>
								</TD>
								<TD>
									<FONT FACE="Arial, Helvetica" SIZE="2"><IMG SRC="images/notcall.gif" ALT="Not in a call" WIDTH=16 HEIGHT=16 ALIGN="middle"> No</FONT>
								</TD>
							</TR>	
						</TABLE>
					</TD>
					<TD VALIGN="TOP" ALIGN="CENTER">
						<TABLE CELLPADDING=0 CELLSPACING=0 BORDER="<%= border %>">
							<TR>
								<TD WIDTH="100%" COLSPAN="2">
									<FONT FACE="Arial, Helvetica" SIZE="2">
									<B>Only Show Users</B>
									</FONT>
								</TD>
							</TR>
							<TR>
								<TD>
									<INPUT TYPE="Radio" NAME="multimedia" VALUE="" <% IF (multimedia_cookie = "") THEN %> CHECKED<% End If %>>&nbsp;
								</TD>
								<TD>
									<FONT FACE="Arial, Helvetica" SIZE="2"> All</FONT>
								</TD>
							</TR>
							<TR>
								<TD>
									<INPUT TYPE="Radio" NAME="multimedia" VALUE=1<% IF (multimedia_cookie = "1") THEN %> CHECKED<% End If %>>&nbsp;
								</TD>
								<TD NOWRAP>
									<FONT FACE="Arial, Helvetica" SIZE="2"><IMG SRC="images/audio.gif" ALIGN="middle" ALT="Audio hardware detected" WIDTH=16 HEIGHT=16>With Audio</FONT>
								</TD>
							</TR>
							<TR>
								<TD>
									<INPUT TYPE="Radio" NAME="multimedia" VALUE=2<% IF (multimedia_cookie = "2") THEN %> CHECKED<% End If %>>&nbsp;
								</TD>
								<TD NOWRAP>
									<FONT FACE="Arial, Helvetica" SIZE="2"><IMG SRC="images/video.gif" ALT="Video hardware detected" WIDTH=16 HEIGHT=16 ALIGN="middle">With Video</FONT>
								</TD>
							</TR>
						</TABLE>
					</TD>
				</TR>
				<TR>
					<TD COLSPAN="3">
						<CENTER>
						<INPUT TYPE=SUBMIT VALUE="Submit">&nbsp;
						<INPUT TYPE="button" VALUE="Reset" ONCLICK="ClearAll()">
						</CENTER>
						<HR>
					</TD>
				</TR>
			</TABLE>
		</TD>
	</TR>
</TABLE>
</FORM>
<%  If (FrmDir = "TRUE") Then %>
	<P>
	<FONT SIZE="2" FACE="Arial, Helvetica">
	<% If oMembers.Count <= MaxRecord then %>
		<B><I>Total of <%= oMembers.Count %> users found.</I></B>
	<% Else %>
		<B><I>
			Displaying first <%= MaxRecord %> of total <%= oMembers.Count %> users found.
			Refine your search to reduce number of users found.
		</I></B>
	<% End If %>
	</FONT>
	<P>

<%
    For Each oUser In oMembers

		ils_EmailName = ""
		ils_FirstName = ""
		ils_LastName = ""
		ils_Location = ""
		ils_Comment = ""
		ils_Hidden = ""
		ils_Country = ""
		ils_Audio = ""
		ils_Video = ""
		ils_InCall = ""
		ils_Catagory = ""

		ils_EmailName = oUser.GetEx(email)(0)
		ils_FirstName = oUser.GetEx(FirstName)(0)
		ils_LastName = oUser.GetEx(LastName)(0)
		ils_Location = oUser.GetEx("location")(0)
		ils_Comment = oUser.GetEx("comment")(0)
		ils_Hidden = oUser.GetEx(Hidden)(0)
		ils_Country = oUser.GetEx(Country)(0)
		ils_Audio = oUser.GetEx(Audio)(0)
		ils_Video = oUser.GetEx(Video)(0)
		ils_InCall = oUser.GetEx(InCall)(0)
		ils_Catagory = oUser.GetEx(Catagory)(0)

		If ils_FirstName <> "" Then
			fullname = ils_FirstName & " " & ils_LastName
		Else
			fullname = ils_EmailName
		End If
%>
<TABLE BORDER=<%=border%>>
	<TR>
		<TD ALIGN="RIGHT" VALIGN="top">
			<B>Connect With:</B>
		</TD>
		<TD WIDTH=200 VALIGN="top">
			<A HREF="callto:<%= strServerName %>/<%= ils_EmailName %>">
			<%= fullname %></A>
		</TD>
	</TR>
	<TR>
		<TD ALIGN="right" VALIGN="top">
			<B>Attributes:</B>
		</TD>
		<TD COLSPAN=2 VALIGN="top">
			<% If (ils_Video = "1") Then %>
				<IMG SRC="images/video.gif" ALIGN="middle" ALT="Video hardware detected" WIDTH=16 HEIGHT=16> 
			<% End If %>
		
			<% If (ils_Audio = "1") Then %>
				 <IMG SRC="images/audio.gif" ALIGN="middle" ALT="Audio hardware detected" WIDTH=16 HEIGHT=16> 
			<% End If %>
			
			<% If (ils_InCall = "1") Then %>
				 <IMG SRC="images/inacall.gif" ALIGN="middle" ALT="In a call" WIDTH=16 HEIGHT=16> 
			<% Elseif (ils_InCall = "0") Then %>
				 <IMG SRC="images/notcall.gif" ALIGN="middle" ALT="Not in a call" WIDTH=16 HEIGHT=16> 
			<% End If %>
		</TD>
	</TR>
	<TR>
		<TD ALIGN="right" VALIGN="top">
			<B>Location: </B>
		</TD>
		<TD COLSPAN=2 VALIGN="top">
			<% If ils_Location = "" AND ils_Country = "" Then %>
				&nbsp;
			<% Else %>
				<%
				strSearch = ils_Country
				If iRecordCount <> "" then
					sz1 = LCase( Left( strSearch, 1 ) )
					sz2 = LCase( Right( strSearch, 1 ) )
			
					iHash = ( ( Asc( sz1 ) * 9 ) + ( Asc( sz2 ) * 5 ) ) Mod iRecordCount
					iIndex = aBuckets( iHash )
					
					Do While (iIndex <> "") And (aCountry( 1, iIndex ) <> strSearch)
						iIndex = aCountry( 3, iIndex )
					Loop
				End If
				If iIndex <> "" Then
					LongCountryName = aCountry( 2, iIndex )
				Else
					LongCountryName = strSearch
				End If
				If ils_Location <> "" Then %>
					<FONT FACE="Arial, Helvetica" SIZE=3>
					<XMP><% = ils_Location %>, <%= LongCountryName %></XMP>
				<% Else %>
					<FONT FACE="Arial, Helvetica" SIZE=2>
					<%= LongCountryName %>
				<% End If %>
		 	<% End If %>
	   </TD>
   </TR>
	<TR>
		<TD ALIGN="RIGHT" VALIGN="top">
			<B>Comments: </B>
		</TD>
		<TD COLSPAN=2 VALIGN="top">
			<xmp><%= ils_Comment %></xmp>
		</TD>
	</TR>
	<TR>
		<TD ALIGN="RIGHT" VALIGN="top">
			<B>Send Mail:</B>
		</TD>
		<TD COLSPAN=2 VALIGN="top">
			<% If ils_EmailName <> "" Then %><A HREF="mailto:<%= ils_EmailName %>"><%= ils_EmailName %></A><% End If %>
		</TD>
	</TR>
</TABLE>
<HR SIZE="1" NOSHADE>
<%
		iMyRecordCount = iMyRecordCount + 1
		If iMyRecordCount = MaxRecord then Exit For
	Next
End If
%>
</BODY>
</HTML>
