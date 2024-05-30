<HTML>
<%

Dim objPref, rs

'set objPref = Server.CreateObject("db_CustPreferences.Preferences")
'set rs = objPref.ReadPreferences("traceyt@microsoft.com")

URLFrameUL="http://www.microsoft.com/com"
URLFrameUR="http://www.disney.com"
URLFrameLL="http://www.msnbc.com"
URLFrameLR="http://espn.sportszone.com/"

'URLFrameUL=rs("URLFrameUL").Value

%>
<FRAMESET ROWS="15%,*">
   <FRAME SRC="Welcome.htm" SCROLLING=NO >
   <FRAMESET COLS="50%,*" ROWS="50%, *">
      <FRAME SRC="<%=URLFrameUL%>">
      <FRAME SRC="<%=URLFrameUR%>">
      <FRAME SRC="<%=URLFrameLL%>">
      <FRAME SRC="<%=URLFrameLR%>">
    </FRAMESET>
</FRAMESET>
</HTML>

