<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<!--#include file="../../../../constant.inc"-->
<!--#include file="../../../../lib/session.inc"-->
<!--#include file="../../../../lib/render.inc"-->
<!--#include file="../../../../lib/store.inc"-->
<!--#include file="formutil.inc"-->

<!-- #include file="litcrit.inc" -->

<% SendHeader 1, 1 %>
<%
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- Page_n.asp-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->

bstrObj   = Request.QueryString("obj")
CheckSession
On Error Resume Next

nTWfactor = Session("nTWfactor")
nTAfactor = Session("nTAfactor")
nRows = Session("nTARows")

bstrObj = Request.QueryString("obj")
Set objOneMsg = Session(bstrObj)
Set objRenderMsg = GetObjectRenderer
objRenderMsg.DataSource = objOneMsg

fIsImportanceField=false
'With no keyword: Returns true/false 
'With keyword: Returns Enum value or -1 on fail
var bstrEnumList 'make global
fisIE4 = isIE4()

bstrToData = ""
bstrCCData = ""
bstrBCCData = ""
fRecipInitialized = False

If bstrObj <> "" then
  Set objOneMsg = Session(bstrObj)
  msgID = objOneMsg.ID
  Set objRecipsColl = objOneMsg.Recipients
  InitializeRecipients  objRecipsColl 'This subroutine will populate the strings bstrToData, bstrCCData, bstrBCCData

  If urlCaller<>"" Then 'called from root first time in so check attachments flag
    If bstrBCCData<>"" Then 
      fIsBccData=True 
    Else 
      fIsBccData=False
    End If
  End If
End If

'=== BEGIN LITCRIT SPECIFICS
imgMedia = MediaImage(objOneMsg.Fields("Media"))

%>



<HTML>
<body Background="" bgcolor="c0c0c0" onLoad="parent.fBusyTabbing = false;" text=000000 link=000000 vlink=000000 alink=000000 leftmargin=4>
<FORM name="mainForm" ACTION="commands.asp" METHOD="POST" target="command_fr" onSubmit="return(false)">
<input type="hidden" name="fm_buffer">
<!--Custom Fields-->
<table border=0>
	<tr>
		<td width=0 height=0><font size=1>&nbsp</font></td>
		<td width=5><font size=1>&nbsp</font></td>
		<td width=39><font size=1>&nbsp</font></td>
		<td width=13><font size=1>&nbsp</font></td>
		<td width=211><font size=1>&nbsp</font></td>
		<td width=12><font size=1>&nbsp</font></td>
		<td width=31><font size=1>&nbsp</font></td>
		<td width=23><font size=1>&nbsp</font></td>
		<td width=0><font size=1>&nbsp</font></td>
		<td width=143><font size=1>&nbsp</font></td>
		<td width=237><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=8><font size=1>&nbsp</font></td>
		<td colspan=6 rowspan=3 width=311 valign=bottom>
<!-- UniqueID=Image1_148_0_gr Property= PropertyType= PropertyFormat= -->
<img border='0' height='72' width='311' src='Image1_148_0_gr.gif'>
</td>
	</tr>
	<tr>
		<td height=0><font size=1>&nbsp</font></td>
		<td><font size=1>&nbsp</font></td>
		<td width=0></td>
	</tr>
	<tr>
		<td height=46><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td colspan=2 height=15><font size=1>&nbsp</font></td>
		<td rowspan=3 width=39 align=center>
<!-- UniqueID=imgMedia_14c_0_gr Property="{2903020000000000C000000000000046}image" PropertyType=8 PropertyFormat=0 -->
<img border='0' height='39' width='39' src='<%= imgMedia %>'>
</td>
		<td><font size=1>&nbsp</font></td>
		<td width=211>
<!-- UniqueID=txtTitle_147_0_gr Property="{2903020000000000C000000000000046}Item Title" PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"","{2903020000000000C000000000000046}Item Title", False,0,1)%>
<!-- *** Forms Converter:ReadOnly Multiline Field: txtTitle *** -->
<TEXTAREA NAME='txtTitle_147_0_gr' cols='<%=cint((211*.90)*nTAfactor)%>' rows='<%=cint((nRows/280)*21)%>' wrap='virtual' style='height:21;width:<%=cint(211*.90)%>;font-face:Tahoma;font-size:<%=8%>pt;color:000000;background:c0c0c0;text-align:<%=fm__GetTextAlign(1)%>;font-weight:bold;text-decoration:;'ReadOnly onChange='parent.errMsg_ReadOnly();'><% objRenderMsg.write bstr__FieldData,Response %></textarea>
<input type='hidden' name='fUnCh_txtTitle_147_0_gr' value='1'>

</td>
		<td><font size=1>&nbsp</font></td>
		<td colspan=4 width=197>
<!-- UniqueID=txtAuthor_150_0_gr Property="{2903020000000000C000000000000046}LongAuthor" PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"","{2903020000000000C000000000000046}LongAuthor", False,0,1)%>
<!-- *** Forms Converter:ReadOnly Text Field: txtAuthor *** -->
<input type='text' name='txtAuthor_150_0_gr' size='<%=cint((197*.88)*nTWfactor)%>' value="<% objRenderMsg.write bstr__FieldData, Response %>" style='height:21;width:<%=cint(197*.88)%>;font-face:Tahoma;font-size:8pt;color:000000;background:c0c0c0;text-align:<%=fm__GetTextAlign(1)%>;text-decoration:;' ReadOnly onChange='parent.errMsg_ReadOnly();'>
<input type='hidden' name='fUnCh_txtAuthor_150_0_gr' value='1'>

</td>
	</tr>
	<tr>
		<td colspan=2 height=5><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td colspan=2 height=19><font size=1>&nbsp</font></td>
		<td><font size=1>&nbsp</font></td>
		<td colspan=6 width=420>
<!-- UniqueID=txtMedia_149_0_gr Property="{2903020000000000C000000000000046}LongMedia" PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"<untitled>","{2903020000000000C000000000000046}LongMedia", False,0,1)%>
<!-- *** Forms Converter:ReadOnly Text Field: txtMedia *** -->
<input type='text' name='txtMedia_149_0_gr' size='<%=cint((420*.88)*nTWfactor)%>' value="<% objRenderMsg.write bstr__FieldData, Response %>" style='height:21;width:<%=cint(420*.88)%>;font-face:Tahoma;font-size:8pt;color:000000;background:c0c0c0;text-align:<%=fm__GetTextAlign(1)%>;text-decoration:;' ReadOnly onChange='parent.errMsg_ReadOnly();'>
<input type='hidden' name='fUnCh_txtMedia_149_0_gr' value='1'>

</td>
	</tr>
	<tr>
		<td height=23><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=86><font size=1>&nbsp</font></td>
		<td colspan=10 width=714 valign=top>
<%
bVisible = True
bIE4Browser = fisIE4 And (IsMac = 0)
If bIE4Browser <> False then 
	bstrContainerPrefix = "<Fieldset style='overflow:scroll;visibility:visible; background-color:c0c0c0;'>"
	bstrContainerSuffix = "</Fieldset>"
	bstrContainerSize = ""
	bstrCapPrefix = "<Legend>"
	bstrCapSuffix = "</Legend>"
	bstrRowPrefix = ""
	bstrRowSuffix = ""
Else
	bstrContainerPrefix = "<table bgcolor=c0c0c0 border=0>"
	bstrContainerSuffix = "</table>"
	bstrContainerSize = "<tr><td width=717 height=83>"
	bstrCapPrefix = "<tr><td width=717>"
	bstrCapSuffix = "</td></tr>"
	bstrRowSuffix = "</td></tr>"
End If
iFrameWidth = 717
If bIE4Browser <> False Or bVisible Then %>
<%=bstrContainerPrefix%>
<% If iFrameWidth > 8 Then %>
	<%=bstrCapPrefix%>
	<font size='1' face='Tahoma' color='#000000' style='font-size:8pt;'>
	Evaluation
	</font>
	<%=bstrCapSuffix%>
<% End If %>
<%=bstrContainerSize%>
<table border=0>
	<tr>
		<td width=0 height=0><font size=1>&nbsp</font></td>
		<td width=128><font size=1>&nbsp</font></td>
		<td width=13><font size=1>&nbsp</font></td>
		<td width=107><font size=1>&nbsp</font></td>
		<td width=36><font size=1>&nbsp</font></td>
		<td width=79><font size=1>&nbsp</font></td>
		<td width=12><font size=1>&nbsp</font></td>
		<td width=5><font size=1>&nbsp</font></td>
		<td width=91><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=16><font size=1>&nbsp</font></td>
		<td width=128>
<!-- UniqueID=lblTechnical_13c_13b_gr Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Technical Level:&nbsp;
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td rowspan=2 width=107>
<!-- UniqueID=lblTech_140_13b_gr Property="{2903020000000000C000000000000046}Tech Level" PropertyType=8 PropertyFormat=0 -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
<B><% objRenderMsg.Write fm__GetFieldData(8,"<Select Rating>","{2903020000000000C000000000000046}Tech Level",False,0,1), Response %>	&nbsp;</B>
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td colspan=3 width=96>
<!-- UniqueID=lblJob_13d_13b_gr Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Job Relevance:&nbsp;
</font>
</div>
</td>
		<td rowspan=2 width=91>
<!-- UniqueID=lblJob_141_13b_gr Property="{2903020000000000C000000000000046}Job Relevance" PropertyType=8 PropertyFormat=0 -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
<B><% objRenderMsg.Write fm__GetFieldData(8,"<Select Rating>","{2903020000000000C000000000000046}Job Relevance",False,0,1), Response %>	&nbsp;</B>
</font>
</div>
</td>
	</tr>
	<tr>
		<td colspan=3 height=8><font size=1>&nbsp</font></td>
		<td colspan=4><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=24><font size=1>&nbsp</font></td>
		<td rowspan=2 width=128>
<!-- UniqueID=lblClarity_13e_13b_gr Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Clarity of presentation:&nbsp;
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td width=107>
<!-- UniqueID=lblClarity_142_13b_gr Property="{2903020000000000C000000000000046}Clarity Rating" PropertyType=8 PropertyFormat=0 -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
<B><% objRenderMsg.Write fm__GetFieldData(8,"<Select Rating>","{2903020000000000C000000000000046}Clarity Rating",False,0,1), Response %>	&nbsp;</B>
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td width=79>
<!-- UniqueID=lblOverall_13f_13b_gr Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Overall Rating :&nbsp;
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td colspan=2 width=96>
<!-- UniqueID=lblOverall_143_13b_gr Property="{2903020000000000C000000000000046}Overall Rating" PropertyType=8 PropertyFormat=0 -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
<B><% objRenderMsg.Write fm__GetFieldData(8,"<Select Rating>","{2903020000000000C000000000000046}Overall Rating",False,0,1), Response %>	&nbsp;</B>
</font>
</div>
</td>
	</tr>
	<tr>
		<td height=8><font size=1>&nbsp</font></td>
	</tr>
</table>

<%=bstrRowSuffix%>
<%=bstrContainerSuffix%>
<%
End If %></td>
	</tr>
	<tr>
		<td height=183><font size=1>&nbsp</font></td>
		<td colspan=10 width=714 valign=top>
<%
bVisible = True
bIE4Browser = fisIE4 And (IsMac = 0)
If bIE4Browser <> False then 
	bstrContainerPrefix = "<Fieldset style='overflow:scroll;visibility:visible; background-color:c0c0c0;'>"
	bstrContainerSuffix = "</Fieldset>"
	bstrContainerSize = ""
	bstrCapPrefix = "<Legend>"
	bstrCapSuffix = "</Legend>"
	bstrRowPrefix = ""
	bstrRowSuffix = ""
Else
	bstrContainerPrefix = "<table bgcolor=c0c0c0 border=0>"
	bstrContainerSuffix = "</table>"
	bstrContainerSize = "<tr><td width=717 height=183>"
	bstrCapPrefix = "<tr><td width=717>"
	bstrCapSuffix = "</td></tr>"
	bstrRowSuffix = "</td></tr>"
End If
iFrameWidth = 717
If bIE4Browser <> False Or bVisible Then %>
<%=bstrContainerPrefix%>
<% If iFrameWidth > 8 Then %>
	<%=bstrCapPrefix%>
	<font size='1' face='Tahoma' color='#000000' style='font-size:8pt;'>
	Critique
	</font>
	<%=bstrCapSuffix%>
<% End If %>
<%=bstrContainerSize%>
<table border=0>
	<tr>
		<td width=0 height=0><font size=1>&nbsp</font></td>
		<td width=442><font size=1>&nbsp</font></td>
		<td width=246><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=25><font size=1>&nbsp</font></td>
		<td width=442>
<!-- UniqueID=txtCritique_146_144_gr Property=&H0037001f PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"<untitled>",&H0037001f, True,0,1)%>
<!-- *** Forms Converter:ReadOnly Text Field: txtCritique *** -->
<input type='text' name='txtCritique_146_144_gr' size='<%=cint((444*.88)*nTWfactor)%>' value="<% objRenderMsg.write bstr__FieldData, Response %>" style='height:21;width:<%=cint(444*.88)%>;font-face:Tahoma;font-size:8pt;color:000000;background:c0c0c0;text-align:<%=fm__GetTextAlign(1)%>;font-weight:bold;text-decoration:;' ReadOnly onChange='parent.errMsg_ReadOnly();'>
<input type='hidden' name='fUnCh_txtCritique_146_144_gr' value='1'>

</td>
	</tr>
	<tr>
		<td height=121><font size=1>&nbsp</font></td>
		<td colspan=2 width=688>
<!-- UniqueID=txtMessage_145_144_gr Property="{2903020000000000C000000000000046}CritiqueText" PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"","{2903020000000000C000000000000046}CritiqueText", False,0,1)%>
<!-- *** Forms Converter:ReadOnly Multiline Field: txtMessage *** -->
<TEXTAREA NAME='txtMessage_145_144_gr' cols='<%=cint((688*.90)*nTAfactor)%>' rows='<%=cint((nRows/280)*121)%>' wrap='virtual' style='height:121;width:<%=cint(688*.90)%>;font-face:Tahoma;font-size:<%=8%>pt;color:000000;background:c0c0c0;text-align:<%=fm__GetTextAlign(1)%>;text-decoration:;'ReadOnly onChange='parent.errMsg_ReadOnly();'><% objRenderMsg.write bstr__FieldData,Response %></textarea>
<input type='hidden' name='fUnCh_txtMessage_145_144_gr' value='1'>

</td>
	</tr>
</table>

<%=bstrRowSuffix%>
<%=bstrContainerSuffix%>
<%
End If %></td>
	</tr>
</table>

<!--End Custom Fields-->

<!-- **** COMMON FIELDS SUBMITTED ON ALL FORMS **** -->
<input type="hidden" name="tab" value="custom">
<input type="hidden" name="command" value="send">
<input type="hidden" name="objID"   value=<%=bstrObj%>>
<input type="hidden" name="savecopy" value="1">
<input type="hidden" name="importance" value="1">
<input type="hidden" name="replytofolder" value="0">
</FORM>
</BODY>
</HTML>