<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>

<!-- SEARCH MENU DIV -->
<div STYLE="HEIGHT: 95%; LEFT:5px; POSITION: absolute; TOP: 30px; WIDTH: 170px">

<span STYLE="HEIGHT: 24px; LEFT: 2px; POSITION: absolute; TOP: 120px; WIDTH: 120px">
<input name="txtWord" style="HEIGHT: 20px; WIDTH: 109px"></span>
<span class="UpButton"  title="Start Search" onClick="DoSearch()"
      OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()"
      style="TOP:118px;LEFT=125px">Search</span>
<span style="FONT-FAMILY: Verdana, Arial; FONT-SIZE: 8 pt; HEIGHT: 42px; LEFT: 4px; POSITION: absolute; TOP: 148px; WIDTH: 193px">
	<input onClick="takeFocus()" TYPE="Radio" NAME="Type" ID="cbTitle"   VALUE="Title" CHECKED><label FOR="cbTitle" TITLE="Search By Title">Title</label>&nbsp;
	<input onClick="takeFocus()" TYPE="Radio" NAME="Type" ID="cbAuthor"  VALUE="Author"><label FOR="cbAuthor" TITLE="Search By Author">Author</label>&nbsp;
	<input onClick="takeFocus()" TYPE="Radio" NAME="Type" ID="cbSubject" VALUE="Subject"><label FOR="cbSubject" TITLE="Search By Subject">Subject</label><br>
	Combine keywords using <strong>AND</strong>, <strong>OR</strong>, or <strong>NEAR</strong>. 
</span>

<!-- INCLUDE COLLECTION DIV -->
<span CLASS="Item" STYLE="LEFT: 5px; TOP: 210px">Include...<br>

<input onClick="takeFocus()" NAME="cbAV"   ID="cbAV"   TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbAV)" src="../images/iconav.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbAV"   TITLE="Include Audio and Video">Audio/Visual</LABEL>
<br>

<input onClick="takeFocus()" NAME="cbBook" ID="cbBook" TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbBook)" src="../images/iconbook.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbBook" TITLE="Include Books (Hard/Softcover)">Books</LABEL>
<br>

<input onClick="takeFocus()" NAME="cbPrd"  ID="cbPrd"  TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbPrd)" src="../images/iconprd.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbPrd"  TITLE="Include Magazines and Journals">Periodicals</LABEL>
<br>

<input onClick="takeFocus()" NAME="cbRef"  ID="cbRef"  TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbRef)" src="../images/iconref.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbRef"  TITLE="Include Non-Circulating Materials">Reference</LABEL>
<br>

<input onClick="takeFocus()" NAME="cbSoft" ID="cbSoft" TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbSoft)" src="../images/iconsoft.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbSoft" TITLE="Include Computer Programs">Software</LABEL>
<br>

</span>

<div CLASS="BUTTON" ID="selectAll"  onClick="selection(True)" STYLE="DISPLAY: none; TOP: 335px" TITLE="Select All" >Select All</div>
<div CLASS="deselButton" ID="selectNone" onClick="selection(False)" STYLE="TOP: 335px" TITLE="Deselect All">Deselect All</div>

</div>

<script language=VBScript>
Sub push()
   window.event.srcElement.className = "DownButton"
End Sub

Sub unPush()
   window.event.srcElement.className = "UpButton"
End Sub

'--- Trap ENTER key and invoke SUBMIT function
Sub document_onkeypress()
	If Window.Event.keyCode = 13 Then
	   DoSearch()
	End If
End Sub

Sub DoSearch()
   Dim  strSearch,optSearch,passString,newSearch
   strSearch = Trim(txtWord.value)
   If strSearch <> "" Then
      If setCheckboxValues Then
         nLastSearch = cSearch
         optSearch = ChooseTypeOfSearch()
         newSearch = "Yes"
         passString = "search.asp?currentword=" & escape(strSearch) & _
                      "&optSearch=" & optSearch & "&newSearch=" & newSearch & _
                      "&cbAV=" & cbAVVal & "&cbBook=" & cbBookVal & "&cbPrd=" & _
                      cbPrdVal & "&cbRef=" & cbRefVal & "&cbSoft=" & cbSoftVal
         document.all.ifControl.src = passString
      Else
         MsgBox "You must include at least one item type to search."
      End If
   Else
      MsgBox "You must enter a search string"
      txtWord.Focus
   End If
End Sub
</script>

<script LANGUAGE=VBScript>
Dim cbAVVal,cbBookVal,cbPrdVal,cbRefVal,cbSoftVal

'--- Called as buttons are pressed, and returns focus to textbox
Sub TakeFocus()
   Call checkSelection
   txtWord.Focus
End Sub

'--- Changes the button style if all selections are made
Sub checkSelection()
   If (cbAV.checked = FALSE OR _
	      cbBook.checked = FALSE OR _
	      cbPrd.checked = FALSE OR _
	      cbRef.checked = FALSE OR _
	      cbSoft.checked = FALSE) Then
	   selectNone.style.display = "none"
	   selectAll.style.display = ""
   Else
	   selectAll.style.display = "none"
	   selectNone.style.display = ""
   End If
End Sub

'--- Changes the status of a single checkbox
Sub flipSelection(oSel)
   oSel.checked = Not oSel.checked
   Call TakeFocus
End Sub

'--- Selects everything as a group to on or off
Sub Selection(bSel)
	cbAV.checked = bSel
	cbBook.checked = bSel
	cbPrd.checked = bSel
	cbRef.checked = bSel
	cbSoft.checked = bSel

   ' Change the button style by switching the display style
   If bSel Then	
	   selectAll.style.display = "none"
	   selectNone.style.display = ""
   Else
	   selectNone.style.display = "none"
	   selectAll.style.display = ""
   End If
   
	txtWord.Focus
End Sub
</script>

<script LANGUAGE=VBScript>
'--- IIf (Inline If) function is not available in VBS, so we reproduce it here
Private Function IIf(ByVal bcase,ByVal btrue,ByVal bFalse)
   If (bCase) Then
      IIf = bTrue
   Else 
      IIf = bFalse
   End If
End Function

'--- Functions used to store and retrieve checkbox state to and from the URL
Function setCheckBoxValues()
   cbAVVal = IIf(cbAV.checked,1,0)
   cbBookVal = IIf(cbBook.checked,1,0)
   cbPrdVal = IIf(cbPrd.checked,1,0)
   cbRefVal = IIf(cbRef.checked,1,0)
   cbSoftVal = IIf(cbsoft.checked,1,0)
   
   ' make sure at least one include value is checked
   If (cbAVVal + cbBookVal + cbPrdVal + cbRefVal + cbSoftVal = 0) Then
      setCheckBoxValues = False
   Else
      setCheckBoxValues = True
   End If
End Function

Sub SetCheckBoxes(ByVal vAV, ByVal vBook, ByVal vPrd, ByVal vRef, ByVal vSoft)
   cbAV.checked = IIf(vAV,True,False)
   cbBook.checked = IIf(vBook,True,False)
   cbPrd.checked = IIf(vPrd,True,False)
   cbRef.checked = IIf(vRef,True,False)
   cbSoft.checked = IIf(vSoft,True,False)
End Sub
</script>

<script LANGUAGE=VBScript>
'--- Choose option from checked radio button 
Function ChooseTypeOfSearch()
   Dim optSearch
   If (cbTitle.checked = True) Then
     optSearch = 1
   ElseIf (cbAuthor.checked = True) Then
     optSearch = 2
   Else
     optSearch = 3
   End If
   ' set return value
   ChooseTypeOfSearch = optSearch
End Function
</script>
