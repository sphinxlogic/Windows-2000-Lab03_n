<% @ LANGUAGE=VBSCRIPT CODEPAGE = 1252 %>
<!--#include file="../../../../constant.inc"-->
<!--#include file="../../../../lib/session.inc"-->
<% SendHeader 1, 1 %>
<!--#include file="../../../../lib/render.inc"-->
<!--#include file="../../../../lib/store.inc"-->
<!--#include file="formutil.inc"-->

<!-- #include file="litcrit.inc"-->

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

'=== LITCRIT SPECIFIC CODE
imgMedia = MediaImage(objOneMsg.Fields(sGUID & "Media"))
%>

<HTML>
<body Background="" bgcolor="c0c0c0" onLoad="parent.fBusyTabbing = false;" text=000000 link=000000 vlink=000000 alink=000000 leftmargin=4>
<FORM name="mainForm" ACTION="commands.asp" METHOD="POST" target="command_fr" onSubmit="return(false)">
<input type="hidden" name="fm_buffer">
<!--Custom Fields-->
<table border=0>
	<tr>
		<td width=0 height=0><font size=1>&nbsp</font></td>
		<td width=8><font size=1>&nbsp</font></td>
		<td width=40><font size=1>&nbsp</font></td>
		<td width=8><font size=1>&nbsp</font></td>
		<td width=288><font size=1>&nbsp</font></td>
		<td width=24><font size=1>&nbsp</font></td>
		<td width=0><font size=1>&nbsp</font></td>
		<td width=173><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td colspan=4 height=0><font size=1>&nbsp</font></td>
		<td rowspan=3 width=288 align=center>
<!-- UniqueID=Image1_139_0_3 Property= PropertyType= PropertyFormat= -->
<img border='0' height='72' width='311' src='Image1_139_0_3.gif'>
</td>
		<td><font size=1>&nbsp</font></td>
		<td width=0>
<!-- UniqueID=ImageList1_13e_0_3 Property= PropertyType= PropertyFormat= -->
<!-- Uncomment object tag and add hand code as necessary to implement
     custom control
<OBJECT id="ImageList1" width=50 height=50
CLASSID="CLSID:{2C247F23-8591-11D1-B16A-00C0F0283628}">
</OBJECT>
End comment for custom control -->

</td>
	</tr>
	<tr>
		<td colspan=4 height=8><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td colspan=2 height=32><font size=1>&nbsp</font></td>
		<td width=40 valign=bottom>
<!-- UniqueID=imgMedia_4_0_3 Property="{2903020000000000C000000000000046}image" PropertyType=8 PropertyFormat=0 -->
<img border='0' height='32' width='40' src='<%= imgMedia %>'>
</td>
		<td><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=112><font size=1>&nbsp</font></td>
		<td colspan=7 width=541 valign=top>
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
	bstrContainerSize = "<tr><td width=541 height=112>"
	bstrCapPrefix = "<tr><td width=541>"
	bstrCapSuffix = "</td></tr>"
	bstrRowSuffix = "</td></tr>"
End If
iFrameWidth = 541
If bIE4Browser <> False Or bVisible Then %>
<%=bstrContainerPrefix%>
<% If iFrameWidth > 8 Then %>
	<%=bstrCapPrefix%>
	<font size='1' face='Tahoma' color='#000000' style='font-size:8pt;'>
	Description
	</font>
	<%=bstrCapSuffix%>
<% End If %>
<%=bstrContainerSize%>
<table border=0>
	<tr>
		<td width=0 height=0><font size=1>&nbsp</font></td>
		<td width=61><font size=1>&nbsp</font></td>
		<td width=7><font size=1>&nbsp</font></td>
		<td width=119><font size=1>&nbsp</font></td>
		<td width=335><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=17><font size=1>&nbsp</font></td>
		<td width=61>
<!-- UniqueID=Label54_13c_12b_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Media:&nbsp;
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td width=119>
<!-- UniqueID=txtMedia_13d_12b_3 Property="{2903020000000000C000000000000046}Media" PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"Book","{2903020000000000C000000000000046}Media", False,0,1)%>
<!-- *** Forms Converter:ReadOnly Text Field: txtMedia *** -->
<input type='text' name='txtMedia_13d_12b_3' size='<%=cint((119*.88)*nTWfactor)%>' value="<% objRenderMsg.write bstr__FieldData, Response %>" style='height:21;width:<%=cint(119*.88)%>;font-face:Tahoma;font-size:8pt;color:000000;background:c0c0c0;text-align:<%=fm__GetTextAlign(1)%>;text-decoration:;' ReadOnly onChange='parent.errMsg_ReadOnly();'>
<input type='hidden' name='fUnCh_txtMedia_13d_12b_3' value='1'>

</td>
	</tr>
	<tr>
		<td height=11><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=19><font size=1>&nbsp</font></td>
		<td width=61>
<!-- UniqueID=Label52_13a_12b_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
<B>		Item Title:&nbsp;</B>
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td colspan=2 width=454>
<!-- UniqueID=txtTitle_12c_12b_3 Property="{2903020000000000C000000000000046}Item Title" PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"","{2903020000000000C000000000000046}Item Title", False,0,1)%>
<!-- *** Forms Converter:ReadOnly Text Field: txtTitle *** -->
<input type='text' name='txtTitle_12c_12b_3' size='<%=cint((456*.88)*nTWfactor)%>' value="<% objRenderMsg.write bstr__FieldData, Response %>" style='height:21;width:<%=cint(456*.88)%>;font-face:Tahoma;font-size:8pt;color:000000;background:c0c0c0;text-align:<%=fm__GetTextAlign(1)%>;text-decoration:;' ReadOnly onChange='parent.errMsg_ReadOnly();'>
<input type='hidden' name='fUnCh_txtTitle_12c_12b_3' value='1'>

</td>
	</tr>
	<tr>
		<td height=10><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=14><font size=1>&nbsp</font></td>
		<td width=61>
<!-- UniqueID=Label53_13b_12b_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Authors:&nbsp;
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td colspan=2 rowspan=2 width=454>
<!-- UniqueID=txtAuthor_12f_12b_3 Property="{2903020000000000C000000000000046}AuthName" PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"","{2903020000000000C000000000000046}AuthName", False,0,1)%>
<!-- *** Forms Converter:ReadOnly Text Field: txtAuthor *** -->
<input type='text' name='txtAuthor_12f_12b_3' size='<%=cint((456*.88)*nTWfactor)%>' value="<% objRenderMsg.write bstr__FieldData, Response %>" style='height:21;width:<%=cint(456*.88)%>;font-face:Tahoma;font-size:8pt;color:000000;background:c0c0c0;text-align:<%=fm__GetTextAlign(1)%>;text-decoration:;' ReadOnly onChange='parent.errMsg_ReadOnly();'>
<input type='hidden' name='fUnCh_txtAuthor_12f_12b_3' value='1'>

</td>
	</tr>
	<tr>
		<td colspan=3 height=7><font size=1>&nbsp</font></td>
	</tr>
</table>

<%=bstrRowSuffix%>
<%=bstrContainerSuffix%>
<%
End If %></td>
	</tr>
	<tr>
		<td height=8><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=87><font size=1>&nbsp</font></td>
		<td colspan=7 width=541 valign=top>
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
	bstrContainerSize = "<tr><td width=541 height=87>"
	bstrCapPrefix = "<tr><td width=541>"
	bstrCapSuffix = "</td></tr>"
	bstrRowSuffix = "</td></tr>"
End If
iFrameWidth = 541
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
		<td width=119><font size=1>&nbsp</font></td>
		<td width=120><font size=1>&nbsp</font></td>
		<td width=17><font size=1>&nbsp</font></td>
		<td width=95><font size=1>&nbsp</font></td>
		<td width=120><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td colspan=2 height=5><font size=1>&nbsp</font></td>
		<td rowspan=3 width=120>
<!-- UniqueID=cmbTechnical_124_5_3 Property="{2903020000000000C000000000000046}Tech Level" PropertyType=8 PropertyFormat=0 -->
 
<!-- *** Forms Converter: Outlook Combo Field Name: cmbTechnical *** -->
<%bstr__Value = GetComboboxData("{2903020000000000C000000000000046}Tech Level",False,False)%>
<select name="cmbTechnical_124_5_3" width='120' onChange='this.form.fUnCh_cmbTechnical_124_5_3.value=0;' style='width:120;font-face:Tahoma;font-size:8;color:000000;background:ffffff;'>
<% If bstr__Value = "" Then %>
    <option value="">
<% End If %>
    <% bstr__Values = ",&lt;Select rating&gt;,Expert,Advanced,Intermediate,Beginner," %>

    <option value="&lt;Select rating&gt;">&lt;Select rating&gt;
                <option value="Expert">Expert
                <option value="Advanced">Advanced
                <option value="Intermediate">Intermediate
                <option value="Beginner">Beginner
<%if len(bstr__Value) > 0 Then
    If InStr(1, bstr__Values, "," & bstr__Value & ",", 1) <= 0 Then %>
    <option value="<%objRenderMsg.Write bstr__Value,Response%>"><%objRenderMsg.Write bstr__Value,Response%>
    <%end if
end if %>
</select>
<script language='javascript'>
    parent.fm__ComboSelectText(document.mainForm.cmbTechnical_124_5_3,"<%=bstr__Value%>");
</script>
<input type='hidden' name='fUnCh_cmbTechnical_124_5_3' value='1'>
</td>
		<td colspan=2><font size=1>&nbsp</font></td>
		<td rowspan=3 width=120>
<!-- UniqueID=cmbJob_129_5_3 Property="{2903020000000000C000000000000046}Job Relevance" PropertyType=8 PropertyFormat=0 -->
 
<!-- *** Forms Converter: Outlook Combo Field Name: cmbJob *** -->
<%bstr__Value = GetComboboxData("{2903020000000000C000000000000046}Job Relevance",False,False)%>
<select name="cmbJob_129_5_3" width='120' onChange='this.form.fUnCh_cmbJob_129_5_3.value=0;' style='width:120;font-face:Tahoma;font-size:8;color:000000;background:ffffff;'>
<% If bstr__Value = "" Then %>
    <option value="">
<% End If %>
    <% bstr__Values = ",&lt;Select Rating&gt;,Highly relevant,Mostly relevant,Somewhat relevant,Not relevant," %>

    <option value="&lt;Select Rating&gt;">&lt;Select Rating&gt;
                <option value="Highly relevant">Highly relevant
                <option value="Mostly relevant">Mostly relevant
                <option value="Somewhat relevant">Somewhat relevant
                <option value="Not relevant">Not relevant
<%if len(bstr__Value) > 0 Then
    If InStr(1, bstr__Values, "," & bstr__Value & ",", 1) <= 0 Then %>
    <option value="<%objRenderMsg.Write bstr__Value,Response%>"><%objRenderMsg.Write bstr__Value,Response%>
    <%end if
end if %>
</select>
<script language='javascript'>
    parent.fm__ComboSelectText(document.mainForm.cmbJob_129_5_3,"<%=bstr__Value%>");
</script>
<input type='hidden' name='fUnCh_cmbJob_129_5_3' value='1'>
</td>
	</tr>
	<tr>
		<td height=13><font size=1>&nbsp</font></td>
		<td width=119>
<!-- UniqueID=lblTechnical_126_5_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Technical Level:&nbsp;
</font>
</div>
</td>
		<td><font size=1>&nbsp</font></td>
		<td width=95>
<!-- UniqueID=lblJob_12a_5_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Job Relevance:&nbsp;
</font>
</div>
</td>
	</tr>
	<tr>
		<td colspan=2 height=6><font size=1>&nbsp</font></td>
		<td colspan=2><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=14><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=20><font size=1>&nbsp</font></td>
		<td width=119>
<!-- UniqueID=lblClarity_127_5_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Clarity of presentation:&nbsp;
</font>
</div>
</td>
		<td width=120>
<!-- UniqueID=cmbClarity_123_5_3 Property="{2903020000000000C000000000000046}Clarity Rating" PropertyType=8 PropertyFormat=0 -->
 
<!-- *** Forms Converter: Outlook Combo Field Name: cmbClarity *** -->
<%bstr__Value = GetComboboxData("{2903020000000000C000000000000046}Clarity Rating",False,False)%>
<select name="cmbClarity_123_5_3" width='120' onChange='this.form.fUnCh_cmbClarity_123_5_3.value=0;' style='width:120;font-face:Tahoma;font-size:8;color:000000;background:ffffff;'>
<% If bstr__Value = "" Then %>
    <option value="">
<% End If %>
    <% bstr__Values = ",&lt;Select rating&gt;,Very clear,Mostly clear,Somewhat clear,Not clear," %>

    <option value="&lt;Select rating&gt;">&lt;Select rating&gt;
                <option value="Very clear">Very clear
                <option value="Mostly clear">Mostly clear
                <option value="Somewhat clear">Somewhat clear
                <option value="Not clear">Not clear
<%if len(bstr__Value) > 0 Then
    If InStr(1, bstr__Values, "," & bstr__Value & ",", 1) <= 0 Then %>
    <option value="<%objRenderMsg.Write bstr__Value,Response%>"><%objRenderMsg.Write bstr__Value,Response%>
    <%end if
end if %>
</select>
<script language='javascript'>
    parent.fm__ComboSelectText(document.mainForm.cmbClarity_123_5_3,"<%=bstr__Value%>");
</script>
<input type='hidden' name='fUnCh_cmbClarity_123_5_3' value='1'>
</td>
		<td><font size=1>&nbsp</font></td>
		<td width=95>
<!-- UniqueID=lblOverall_128_5_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
<B>		Overall Rating:&nbsp;</B>
</font>
</div>
</td>
		<td width=120>
<!-- UniqueID=cmbOverall_125_5_3 Property="{2903020000000000C000000000000046}Overall Rating" PropertyType=8 PropertyFormat=0 -->
 
<!-- *** Forms Converter: Outlook Combo Field Name: cmbOverall *** -->
<%bstr__Value = GetComboboxData("{2903020000000000C000000000000046}Overall Rating",False,False)%>
<select name="Overall Rating" width='120' onChange='this.form.fUnCh_cmbOverall_125_5_3.value=0;' style='width:120;font-face:Tahoma;font-size:8;color:000000;background:ffffff;'>
<% If bstr__Value = "" Then %>
    <option value="">
<% End If %>
    <% bstr__Values = ",&lt;Select Rating&gt;,****,***,**,*," %>

    <option value="&lt;Select Rating&gt;">&lt;Select Rating&gt;
                <option value="****">****
                <option value="***">***
                <option value="**">**
                <option value="*">*
<%if len(bstr__Value) > 0 Then
    If InStr(1, bstr__Values, "," & bstr__Value & ",", 1) <= 0 Then %>
    <option value="<%objRenderMsg.Write bstr__Value,Response%>"><%objRenderMsg.Write bstr__Value,Response%>
    <%end if
end if %>
</select>
<script language='javascript'>
    parent.fm__ComboSelectText(document.mainForm.elements("Overall Rating"),"<%=bstr__Value%>");
</script>
<input type='hidden' name='fUnCh_cmbOverall_125_5_3' value='1'>
</td>
	</tr>
</table>

<%=bstrRowSuffix%>
<%=bstrContainerSuffix%>
<%
End If %></td>
	</tr>
	<tr>
		<td height=9><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=184><font size=1>&nbsp</font></td>
		<td colspan=7 width=541 valign=top>
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
	bstrContainerSize = "<tr><td width=541 height=184>"
	bstrCapPrefix = "<tr><td width=541>"
	bstrCapSuffix = "</td></tr>"
	bstrRowSuffix = "</td></tr>"
End If
iFrameWidth = 541
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
		<td width=73><font size=1>&nbsp</font></td>
		<td width=45><font size=1>&nbsp</font></td>
		<td width=395><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=19><font size=1>&nbsp</font></td>
		<td colspan=2 width=118>
<!-- UniqueID=Label50_137_134_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Title:&nbsp;
</font>
</div>
</td>
	</tr>
	<tr>
		<td height=21><font size=1>&nbsp</font></td>
		<td colspan=3 width=513>
<!-- UniqueID=TextBox2_136_134_3 Property=&H0037001f PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"<untitled>",&H0037001f, True,0,1)%>
<!-- *** Forms Converter:Text Field: TextBox2 *** -->
<input type='text' name='TextBox2_136_134_3' size='<%=cint((513*.88)*nTWfactor)%>' value="<% objRenderMsg.write bstr__FieldData, Response %>" style='height:21;width:<%=cint(513*.88)%>;font-face:Tahoma;font-size:8pt;color:000000;background:ffffff;text-align:<%=fm__GetTextAlign(1)%>;text-decoration:;' <%if isIE4() Then%> onFocus='this.form.fm_buffer.value=this.value' onBlur='if (this.form.fm_buffer.value!=this.value) {this.form.fUnCh_TextBox2_136_134_3.value=0;}'<%else%> onChange='this.form.fUnCh_TextBox2_136_134_3.value=0;'<%end if%>>
<input type='hidden' name='fUnCh_TextBox2_136_134_3' value='1'>

</td>
	</tr>
	<tr>
		<td height=8><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=16><font size=1>&nbsp</font></td>
		<td width=73>
<!-- UniqueID=Label51_138_134_3 Property= PropertyType= PropertyFormat= -->
<div style='background-color:c0c0c0;'>
<font size='2' face='Tahoma' color='#000000' style='font-face:Tahoma;font-size:8pt;color:000000;'>
Text:&nbsp;
</font>
</div>
</td>
	</tr>
	<tr>
		<td height=9><font size=1>&nbsp</font></td>
	</tr>
	<tr>
		<td height=72><font size=1>&nbsp</font></td>
		<td colspan=3 width=513>
<!-- UniqueID=txtMessage_135_134_3 Property="{2903020000000000C000000000000046}CritiqueText" PropertyType=8 PropertyFormat=0 -->
<%bstr__FieldData=fm__GetFieldData(8,"","{2903020000000000C000000000000046}CritiqueText", False,0,1)%>
<!-- *** Forms Converter:Multiline Field: txtMessage *** -->
<TEXTAREA NAME='txtMessage_135_134_3' cols='<%=cint((513*.90)*nTAfactor)%>' rows='<%=cint((nRows/280)*72)%>' wrap='virtual' style='height:72;width:<%=cint(513*.90)%>;font-face:Tahoma;font-size:<%=8%>pt;color:000000;background:ffffff;text-align:<%=fm__GetTextAlign(1)%>;text-decoration:;'<%if isIE4() then%> onBlur=<%else%>onChange=<%end if%>'if (this.form.fUnCh_txtMessage_135_134_3 != null) this.form.fUnCh_txtMessage_135_134_3.value=0'><% objRenderMsg.write bstr__FieldData,Response %></textarea>
<input type='hidden' name='fUnCh_txtMessage_135_134_3' value='1'>

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