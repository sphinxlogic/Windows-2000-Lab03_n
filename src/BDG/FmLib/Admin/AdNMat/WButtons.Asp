<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>

<% 'NOTE: These buttons cannot be part of any form, since they would no longer receive clicks %>
<div ID="WizardStart" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 475px; WIDTH: 100%; Z-INDEX: 5">
	<span class="SortSubButton" style="POSITION: relative; CURSOR: default; TOP: 5px; WIDTH: 120px; COLOR: #C0C0C0" title="Return to Previous Page">&lt; Back</span>
	<span class="SortSubButton" onClick="WizForward()"  style="POSITION: relative; TOP: 5px; WIDTH: 120px" title="Move to Next Page">Next &gt;</span> 
	<br>
</div>
<div ID="WizardMid" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 475px; WIDTH: 100%; Z-INDEX: 5">
	<span class="SortSubButton" onClick="WizBack()"  style="POSITION: relative; TOP: 5px; WIDTH: 120px" title="Return to Previous Page">&lt; Back</span>
	<span class="SortSubButton" onClick="WizForward()"  style="POSITION: relative; TOP: 5px; WIDTH: 120px" title="Move to Next Page">Next &gt;</span> 
	<br>
</div>
<div ID="WizardEnd" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 475px; WIDTH: 100%; Z-INDEX: 5">
	<span class="SortSubButton" onClick="WizBack()"  style="POSITION: relative; TOP: 5px; WIDTH: 120px" title="Return to Previous Page">&lt; Back</span>
	<span class="SortSubButton" onClick="WizFinish()"  style="POSITION: relative; TOP: 5px; WIDTH: 120px" title="Save Changes">Finish</span> 
	<br>
</div>
<div ID="WizardNone" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 475px; WIDTH: 100%; Z-INDEX: 5">
	<span class="SortSubButton" style="POSITION: relative; CURSOR: default; TOP: 5px; WIDTH: 120px; COLOR: #C0C0C0" title="Return to Previous Page">&lt; Back</span>
	<span class="SortSubButton" style="POSITION: relative; CURSOR: default; TOP: 5px; WIDTH: 120px; COLOR: #C0C0C0" title="Move to Next Page">Next &gt;</span> 
	<br>
</div>
<div ID="WizardBackOK" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 475px; WIDTH: 100%; Z-INDEX: 5">
	<span class="SortSubButton" onClick="WizBack()" style="POSITION: relative; TOP: 5px; WIDTH: 120px" title="Return to Previous Page">&lt; Back</span>
	<span class="SortSubButton" style="POSITION: relative; CURSOR: default; TOP: 5px; WIDTH: 120px; COLOR: #C0C0C0" title="Move to Next Page">Next &gt;</span> 
	<br>
</div>

<script LANGUAGE=VBScript>
Dim nCurrentPage

' NOTE: Hosting page must implement ShowPage and SubmitForm

Sub WizStart
   nCurrentPage = 1
   ShowPage 1
End Sub

Sub WizForward()
   nCurrentPage = nCurrentPage + 1
   ShowPage nCurrentPage
End Sub

Sub WizBack()
   nCurrentPage = nCurrentPage - 1
   ShowPage nCurrentPage
End Sub

Sub WizFinish()
   Call SubmitForm
End Sub

Sub ClearWizardDivs()
   WizardStart.style.display = "none"
   WizardMid.style.display = "none"
   WizardEnd.style.display = "none"
   WizardNone.style.display = "none"
   WizardBackOK.style.display = "none"
End Sub
</script>
