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
	Location = "location"
	Comment = "comment"
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

	FrmSrch = Request("FrmSrch")
	If (FrmSrch = "TRUE") Then
		fname_cookie		= Request("fname") 		
		country_cookie		= Request("country")	
		location_cookie		= Request("location")	
		comment_cookie		= Request("comment") 		
		lname_cookie		= Request("lname") 
		email_cookie		= Request("email")
	Else
		email_cookie		= ""
		fname_cookie		= ""
		lname_cookie		= ""
		country_cookie		= ""
		location_cookie		= ""
		comment_cookie		= ""
	End If
%>
		
<HTML>
<HEAD>
	<TITLE>ILS Search Page</TITLE>
	<SCRIPT LANGUAGE="JavaScript">
	<!-- comment out javascript for non-supporting browsers
	//------------------------------------------------------------------------------------
	// Clear all inputs when user hits Clear button
	//------------------------------------------------------------------------------------
	function ClearAll()
	{
		document.Search.fname.value 			= "";
		document.Search.lname.value 			= "";
		document.Search.email.value 			= "";
		document.Search.location.value 			= "";
		document.Search.country.SelectedIndex 	= 0;
		document.Search.comment.value 			= "";
	}
	// -->
	</SCRIPT>
</HEAD>
<BODY BGCOLOR="#FFFFFF" VLINK="#999999" LINK="#0000FF" ALINK="#228b22"><A NAME="#top">
<FONT FACE="Arial, Helvetica">
<TABLE CELLSPACING="2" WIDTH="100%">
	<TR>
		<TD WIDTH="288"><IMG SRC="images/b_netmeeting.gif" ALT="Microsoft NetMeeting" HEIGHT=67 WIDTH=288></TD>
		<TD ALIGN="CENTER"><B><FONT FACE="Arial, Helvetica" SIZE=5><%= strServerName %> Search</FONT></B></TD>
	</TR>
</TABLE>

<FONT FACE="Arial, Helvetica" SIZE="2">
<FORM ACTION="search.asp" METHOD="post" NAME="Search">
<INPUT TYPE="hidden" NAME="FrmSrch" VALUE="TRUE">
<TABLE CELLSPACING="2" CELLPADDING="2" BORDER="<% = border %>">
	<TR>
		<TD VALIGN="middle">
		<FONT FACE="Arial, Helvetica" SIZE="2"><B>
		To find a particular NetMeeting user, enter the search criteria below, and press the Submit button:
		</B></FONT>
		</TD>
	</TR>
	
	<TR>
		<TD>
		<TABLE WIDTH="100%" CELLSPACING="2" CELLPADDING="2" ALIGN="CENTER" BORDER="<% = border %>">
			<TR>
				<TD ALIGN="RIGHT" VALIGN="middle"><FONT FACE="Arial, Helvetica" SIZE="2"><NOBR>First Name:</NOBR></FONT></TD>
				<TD VALIGN="middle"><INPUT TYPE=TEXT SIZE=20 VALUE="<%= fname_cookie %>" name="fname"></TD>
				<TD ALIGN="RIGHT" VALIGN="middle"><FONT FACE="Arial, Helvetica" SIZE="2">City/State:</FONT></TD>
				<TD VALIGN="middle"><INPUT TYPE=TEXT SIZE=38 VALUE="<%= location_cookie %>" name="location"></TD>
			</TR>
		
			<TR>
				<TD ALIGN="RIGHT" VALIGN="middle"><FONT FACE="Arial, Helvetica" SIZE="2"><NOBR>Last Name:</NOBR></FONT></TD>
				<TD VALIGN="MIDDLE"><INPUT TYPE=TEXT SIZE=20 VALUE="<%= lname_cookie %>" name="lname"></TD>
				<TD ALIGN="RIGHT" VALIGN="middle"><FONT FACE="Arial, Helvetica" SIZE="2">Country:</FONT></TD>
				<TD VALIGN="middle">
					<NOBR>
					<SELECT NAME="country">
						<OPTION VALUE="" <% IF (COUNTRY_cookie = "") THEN %>selected<% end if %>>&lt; All &gt;
						<% for i = 0 to iRecordCount step 1 %>
							<OPTION VALUE="<%= aCountry( 1, i ) %>"<%if Country_cookie = acountry( 1, i ) then %> selected<% end if %>><%= aCountry( 2, i ) %>
						<% next %>
					</SELECT>
					</NOBR>
				</TD>
			</TR>
		
			<TR>
				<TD ALIGN="RIGHT" VALIGN="middle"><FONT FACE="Arial, Helvetica" SIZE="2">Email:</FONT></TD>
				<TD VALIGN="middle"><INPUT TYPE=TEXT SIZE=20 VALUE="<%= email_cookie %>" name="email"></TD>
				<TD ALIGN="RIGHT" VALIGN="middle"><FONT FACE="Arial, Helvetica" SIZE="2">Comments:</FONT></TD>
				<TD VALIGN="middle"><INPUT TYPE=TEXT SIZE=38 VALUE="<%= comment_cookie %>" name="comment"></TD>
			</TR>
		
			<TR>
				<TD COLSPAN="4" ALIGN="CENTER">
				<BR>
				<INPUT TYPE=SUBMIT VALUE="Submit">&nbsp;<INPUT TYPE="button" VALUE="Reset" ONCLICK="ClearAll()">
				</TD>
			</TR>
		</TABLE>
		</TD>
	</TR>
</TABLE>
</FORM>
<HR ALIGN="CENTER" SIZE="1" WIDTH="100%" NOSHADE>
<%
	If (FrmSrch = "TRUE") Then 
		' CREATE "strSearch" -- the query that will be executed
		strSearch = "(&(cn=*)(" & Hidden & "=1)"
	
		If fname_cookie <> "" Then
			strSearch = strSearch & "(" & FirstName & "=" & fname_cookie & "*)"
		End If
	
		If lname_cookie <> "" Then 
			strSearch = strSearch & "(" & LastName & "=" & lname_cookie & "*)"
		End If
	
		If email_cookie <> "" Then
			strSearch = strSearch & "(" & Email & "=" & email_cookie & ")"
		End If
	
		If country_cookie <> "" Then
			strSearch = strSearch & "(" & Country & "=" & country_cookie & ")"
		End If
	
		If location_cookie <> "" Then
			strSearch = strSearch & "(" & Location & "=" & location_cookie & "*)"
		End If
			
		If comment_cookie <> "" Then
			strSearch = strSearch & "(" & Comment & "=" & comment_cookie & "*)"
		End If
	
		' close the last paren after adding any other search variables.
		strSearch = strSearch & ")"
	
		' set the Dn and call the query
		strDn = "LDAP://" & strServerName & "/o=" & strOrg & "/ou=Dynamic"
		'response.write strDN & "<BR>"
		'response.write strSearch & "<BR>"
	    oMembers.GetInfo strDN, strSearch

		If (FrmSrch = "TRUE") and (findresult = 0) Then %>
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
<TABLE BORDER= <%= border %>>
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
End If
%>
</BODY>
</HTML>
