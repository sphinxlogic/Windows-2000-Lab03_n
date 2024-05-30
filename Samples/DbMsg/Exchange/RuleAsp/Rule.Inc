<%
'<!--Rules Sample Application-->
'<!--Rules.inc : Rule routines -->
'<!--RuleClass.inc   : Rule Extraction/Writing routines -->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' Rule.inc contains constants & routines for handling the rule objects.
'
Const mstrRULE_PROVIDER_EDK = "MSExchange.Rules"

Const mstrTEXTIZE_COND_ALL_MESSAGES = "All Messages"
Const mstrTEXTIZE_COND_FROM = "FROM:"
Const mstrTEXTIZE_COND_TO = "TO:"
Const mstrTEXTIZE_COND_TO_FOLDER = "Sent Directly to Folder"
Const mstrTEXTIZE_COND_CC_FOLDER = "(CC) to Folder"
Const mstrTEXTIZE_COND_SUBJECT = "SUBJECT:"
Const mstrTEXTIZE_COND_BODY = "BODY:"
Const mstrTEXTIZE_COND_DELIMITER = ";"

Const mstrTEXTIZE_PROP_INDEX = "RuleIndex"
Const mstrTEXTIZE_PROP_TO_NAME = "RuleToName"
Const mstrTEXTIZE_PROP_TO = "RuleTo"
Const mstrTEXTIZE_PROP_FROM_NAME = "RuleFromName"
Const mstrTEXTIZE_PROP_FROM = "RuleFrom"
Const mstrTEXTIZE_PROP_CCMe = "RuleCCMe"
Const mstrTEXTIZE_PROP_Tome = "RuleTome"
Const mstrTEXTIZE_PROP_SUBJECT = "RuleSubject"
Const mstrTEXTIZE_PROP_BODY = "RuleBody"

Const mstrTEXTIZE_PROP_ACTION_DELETE = "RuleActionDelete"
Const mstrTEXTIZE_PROP_ACTION_RETURN = "RuleActionReturn"
Const mstrTEXTIZE_PROP_ACTION_FORWARD = "RuleActionForward"
Const mstrTEXTIZE_PROP_ACTION_EXIT = "RuleActionExit"

Const RULE_PR_LOGICAL_L_AND = 1
Const RULE_PR_LOGICAL_L_OR = 2
Const RULE_PR_ACTION_DELETE = 3
Const RULE_PR_ACTION_BOUNCE = 8
Const RULE_PR_STATE_ENABLED = 1
Const RULE_PR_STATE_EXIT = 16

Const RULE_FUZZY_FULLSTRING = 0
Const RULE_FUZZY_SUBSTRING = 1
Const RULE_FUZZY_PREFIX = 2
Const RULE_FUZZY_IGNORECASE = &H10000
Const RULE_IGNORENONSPACE = &H20000
Const RULE_LOOSE = &H40000

Const RULE_REL_GE = 1
Const RULE_REL_GT = 2
Const RULE_REL_LE = 3
Const RULE_REL_LT = 4
Const RULE_REL_NE = 5
Const RULE_REL_RE = 6
Const RULE_REL_EQ = 7

Const R_LOGICAL = 1
Const R_BITMASK = 2
Const R_COMMENT = 3
Const R_COMPARE_PROPS = 4
Const R_CONTENT = 5
Const R_EXISTS = 6
Const R_PROPERTY = 7
Const R_SIZE = 8
Const R_SUB = 9

Public Rule_rgstrCondition
Public Rule_rgiRule
'
' Condition Properties
'
Public Rule_Cond_rgaeFrom
Public Rule_Cond_rgaeFromName
Public Rule_Cond_rgaeTo
Public Rule_Cond_rgaeToName
Public Rule_Cond_bSentTo
Public Rule_Cond_bCopiedTo
Public Rule_Cond_strSubject
Public Rule_Cond_strMsgBody
'
' Action Properties
'
Public Rule_Act_bSkipSubsequentRules
Public Rule_Act_bReturn
Public Rule_Act_bDelete
Public Rule_Act_rgaeForward
Public Rule_Act_rgaeForwardName
'
' Initialize
'
    Rule_rgstrCondition = Array()
    Rule_rgiRule = Array()
    Rule_Cond_rgaeFrom = Array()
    Rule_Cond_rgaeFromName = Array()
    Rule_Cond_rgaeTo = Array()
    Rule_Cond_rgaeToName = Array()
    Rule_Act_rgaeForward = Array()
    Rule_Act_rgaeForwardName = Array()

'========================================================

'---------------------------------------
'
'   RULE COL INITIALIZE 
'
'---------------------------------------
Public Sub Rule_Col_Initialize(pstrFolderID)
'
' Creates a Rule collection object for passed folder id.
'
    Dim colRule
    Dim folder
    '
    ' Release current rule if not released
    '
    If Not Session(gstrSESS_RULE) Is Nothing Then
        Set Session(gstrSESS_RULE) = Nothing
    End If
    '
    ' Prepare rule collection for passed folder
    '
    If Session(gstrSESS_COL_RULE) Is Nothing Then
        Set colRule = CreateObject("MSExchange.Rules")

        Set Session(gstrSESS_COL_RULE) = colRule
    Else
        Set colRule = Session(gstrSESS_COL_RULE)
    End If
    '
    ' Set folder property to get the folder's rules
    '
    Set folder = CDO_folderFromID(pstrFolderID)

    colRule.folder = folder

    Set folder = Nothing
    Set colRule = Nothing
End Sub

'----------------------------------- 
'   RULE ADD
'
'   Status: Complete
'-----------------------------------
Public Sub Rule_Add()
'
'  Add a rule to the rules collections 
'  using the Rule Storage Object
   Dim oRule
   Set oRule = nothing
   
   Call Put_Rule(oRule, True)  'Add
   		
End Sub

'-------------------------------------
'
'   RULE MODIFY
'
'-------------------------------------
Public Sub Rule_Modify(piRule)
'
' Modify modifies a rule.
'
	Dim rule
    Dim colRule

    Set colRule = Session(gstrSESS_COL_RULE)

    Set rule = colRule.Item(cLng(piRule))

    'Put condition on Rule but don't add rule just
    'modify existing rule
	Call Put_Rule(rule,False)

    Set rule = Nothing
    Set colRule = Nothing

End Sub

'------------------------------------------
' 
'   RULE DELETE
'
'------------------------------------------
Public Sub Rule_Delete(piRule)
'
' Delete deletes the rule w/ the passed index.
'
    Dim colRule

    Set colRule = Session(gstrSESS_COL_RULE)
	
	'Delete Rule but update Store later
    colRule.Delete CLng(piRule)
	
    Set colRule = Nothing
    
End Sub

'------------------------------------
'				
'   RULE UPDATE
'
'-------------------------------------
Public Sub Rule_Update()
'
' Update commits rule modifications.
'
    Dim colRule

    Set colRule = Session(gstrSESS_COL_RULE)
	
	ColRule.Update
	
    Set colRule = Nothing
    
End Sub


'--------------------------------------------------------
'
'   RULE GET
'
'--------------------------------------------------------
'   Note: If iRule index <> giruleNONE then get rule object
'   and it's properties and store in storage object. 
'   If index = giruleNONE then we don't have an index and
'   just clear the Rule Storage Object.
'--------------------------------------------------------
Public Sub Rule_Get(piRule)
'
	Dim colRule
	Dim rule
	
    Dim sAccum
    Dim erg
    Dim x
    Dim icounter
    Dim iIndex
        
    sAccum = ""
    erg = Array()
	icounter = 0

    '
    ' If modifying an existing rule, copy rule properties
    ' to rule storage object.
    If piRule <> giruleNONE Then
        Set colRule = Session(gstrSESS_COL_RULE)

        Set rule = colRule.Item(CLng(piRule))
		
		'Get Selected Rule Information and populate Rule Storage Object
		Call GetConditions(rule, sAccum)

        Set rule = Nothing
        Set colRule = Nothing
    else
		'Blank out Rule Storage Object for New Rule
		Put_Rule_Subject("")
		Put_Rule_Body("")
		Put_Rule_CCme(False)
		Put_Rule_Tome(False)
		Put_Rule_From(erg)
		Put_Rule_To(erg)
		Put_Rule_Index(-1)
		Put_Rule_Action_Delete(False)
		Put_Rule_Action_Return(False)
		Put_Rule_Action_Exit(False)
    End If

End Sub

'--------------------------------------------------------
'
'   RULE GETPROPERTIES
'
'   Note: Place Properties in the UI
'--------------------------------------------------------
Public Sub Rule_GetProperties()
'
' GetProperties sets property variables from stored rule object.
'
    Dim x
    Dim aEID
	Dim aName
	Dim oAddEntry
	Dim oSession
	
	Set oSession = Session(gstrSESS_CDO_SESSION)

    '
    ' 1. Get Condition Properties from the Rule Storage Object
    ' 2. Redim name array and assign name to it
    '
	Rule_Cond_rgaeTo = Get_Rule_To() 'NOTE: This holds Entry ID
	aEID = Get_Rule_To()
	if ubound(aEID) > -1 then
		Redim Rule_Cond_rgaeToName(ubound(aEID))
		for x = lbound(aEID) to ubound(aEID)
			set oAddEntry = oSession.GetAddressEntry(aEID(x))
			Rule_Cond_rgaeToName(x) = oAddEntry.Name
		next
	else
		Rule_Cond_rgaeToName = array()
	end if

    Rule_Cond_rgaeFrom = Get_Rule_From() 'NOTE: This holds EntryID
	aEID = Get_Rule_From()
	if ubound(aEID) > -1 then
		Redim Rule_Cond_rgaeFromName(ubound(aEID))
		for x = lbound(aEID) to ubound(aEID)
			set oAddEntry = oSession.GetAddressEntry(aEID(x))
			Rule_Cond_rgaeFromName(x) = oAddEntry.Name
		next
	else
		Rule_Cond_rgaeFromName = array()
	end if
	
    Rule_Cond_bSentTo = Get_Rule_Tome()
    Rule_Cond_bCopiedTo = Get_Rule_CCme()
    Rule_Cond_strSubject = Get_Rule_Subject()
    Rule_Cond_strMsgBody = Get_Rule_Body()
    '
    ' Set Actions
    '
    Rule_Act_bSkipSubsequentRules = Get_Rule_Action_Exit()
    Rule_Act_bReturn = Get_Rule_Action_Return()
    Rule_Act_bDelete = Get_Rule_Action_Delete()
    
End Sub

'--------------------------------------
'   
'   SET PROPERTIES
'
'--------------------------------------
Public Sub Rule_SetProperties()
	'
	' Update the rule with new properties or create a new
	' rule. Used the Rule Stored Object properties.
	
    '
    ' Condition Properties
    '
    Put_Rule_From(Rule_Cond_rgaeFrom)
	Put_Rule_To(Rule_Cond_rgaeTo)
    Put_Rule_Tome(Rule_Cond_bSentTo)
    Put_Rule_CCMe(Rule_Cond_bCopiedTo)
    Put_Rule_Subject(Rule_Cond_strSubject)
    Put_Rule_Body(Rule_Cond_strMsgBody)
    
    '
    ' Action Properties
    '
    Put_Rule_Action_Exit(Rule_Act_bSkipSubsequentRules)
    Put_Rule_Action_Return(Rule_Act_bReturn)
    Put_Rule_Action_Delete(Rule_Act_bDelete)
    
End Sub

'-------------------------------------------
'
'   RULE SETNEWINDEX
'
'-------------------------------------------
Public Sub Rule_SetNewIndex(prgiRule, piRule)
'
' SetNewIndex establishes new indices for the rules collection from the passed array of indices.
'
    Dim bTrackRule
    Dim iRule
    Dim bDirty
    Dim rule
    Dim colRule
        
    bDirty = False
    '
    ' Determine whether sequence has changed
    '
    For iRule = LBound(prgiRule) To UBound(prgiRule) - 1
        If Clng(prgiRule(iRule)) > Clng(prgiRule(iRule + 1)) Then
            bDirty = True

            Exit For
        End If
    Next

    If bDirty Then
        bTrackRule = (piRule <> giruleNONE)

        Set colRule = Session(gstrSESS_COL_RULE)
        '
        ' Get current rule
        '
        If bTrackRule Then
             Set rule = colRule.Item(CLng(piRule))
        End If
        ' Get rgiRule.
        '
        Rule_rgiRule = Session(gstrSESS_RG_I_RULE)
        '
        ' Reorder rules using saved indices.
        '
        For iRule = LBound(prgiRule) To UBound(prgiRule)
            colRule.Item(clng(prgiRule(iRule))).NewIndex = clng(Rule_rgiRule(iRule))
        Next

        Call colRule.UpdateIndices
        '
        ' Update piRule for new index
        '
        If bTrackRule Then
            piRule = rule.Index
        End If
         
        Set rule = Nothing
        Set colRule = Nothing
    End If
End Sub

'--------------------------------------
'
'    RULE COND ADD SENT TO ADDRESS
'
'--------------------------------------
Public Sub Rule_Cond_AddSentToAddress(aNewEID)
'
' AddCondSentToAddress adds the passed array of "sent to" EIDs
' 1. Build New String
' 2. Get and Convert old String
' 3. Concatenate

Dim aOldEID
Dim aCatEID
Dim x
Dim y

'Get Existing Array
aOldEID = Get_Rule_To()

If ubound(aNewEID) > -1 then
    ReDim aCatEID(ubound(aNewEID) + ubound(aOldEID) + 1)
	x = 0
	for y = lbound(aOldEID) to ubound(aOldEID)
		aCatEID(x) = aOldEID(y)
		x = x + 1
	next
	for y = lbound(aNewEID) to ubound(aNewEID)
		aCatEID(x) = aNewEID(y)
		x = x + 1
	next
Else
	'No changes were made
End If

Put_Rule_To(aCatEID)

End Sub

'------------------------------------------
'
'    RULE COND ADD FROM ADDRESS
'
'------------------------------------------
Public Sub Rule_Cond_AddFromAddress(aNewEID)
'
' AddCondFromAddressadds the passed array of "from" EIDs
'

Dim aOldEID
Dim aCatEID
Dim x
Dim y

aOldEID = Get_Rule_From()

If ubound(aNewEID) > -1 then
    ReDim aCatEID(ubound(aNewEID) + ubound(aOldEID) + 1)
	x = 0
	for y = lbound(aOldEID) to ubound(aOldEID)
		aCatEID(x) = aOldEID(y)
		x = x + 1
	next
	for y = lbound(aNewEID) to ubound(aNewEID)
		aCatEID(x) = aNewEID(y)
		x = x + 1
	next
Else
	'No changes were made
End If

Put_Rule_From(aCatEID)
    
End Sub



'-----------------------------------------
'
'   RULE RELEASE
'
'-----------------------------------------
Public Sub Rule_Release()

    If Not Session(gstrSESS_RULE) Is Nothing Then
        Set Session(gstrSESS_RULE) = Nothing
    End If

    If Not Session(gstrSESS_COL_RULE) Is Nothing Then
        Set Session(gstrSESS_COL_RULE) = Nothing
    End If

End Sub

'-------------------------------------------
'
'   RULE GETRULELIST
'
'-------------------------------------------
Public Sub Rule_GetRuleList()
'
' GetRuleList prepares rgstrCondition & rgiRule for the current rule.
    Dim colRule
    Dim oRule
    Dim iRuleMax
    Dim iRuleMaxSav
    Dim cRule
    
    Dim sAccum				'String

	Set colRule = Session(gstrSESS_COL_RULE)

    iRuleMaxSav = colRule.Count - 1
    cRule = 0

    If iRuleMaxSav >= 0 Then
        ReDim Rule_rgstrCondition(iRuleMaxSav)
        ReDim Rule_rgiRule(iRuleMaxSav)

        For Each oRule In colRule
            If oRule.Provider = mstrRULE_PROVIDER_EDK Then
            
				'Rule Object Call
				'Get Condition String and Rule Information
				
				sAccum = ""
				Call GetConditions(oRule,sAccum)

                Rule_rgstrCondition(cRule) = sAccum
                Rule_rgiRule(cRule) = oRule.Index

                cRule = cRule + 1
            End If
        Next
        '
        ' Redim rule arrays
        '
        If cRule = 0 Then
            Rule_rgstrCondition = Array()
            Rule_rgiRule = Array()
        Else
            iRuleMax = cRule - 1

            If iRuleMax <> iRuleMaxSav Then
                ReDim Preserve Rule_rgstrCondition(iRuleMax)
                ReDim Preserve Rule_rgiRule(iRuleMax)
            End If
        End If
    Else
        Rule_rgstrCondition = Array()
        Rule_rgiRule = Array()
    End If
    '
    ' Save rgiRule to be used when rules are ordered.
    '
    Session(gstrSESS_RG_I_RULE) = Rule_rgiRule

    Set oRule = Nothing
    Set colRule = Nothing
End Sub

'=================================================
'   RULE STORAGE OBJECT GETS AND PUTS
'=================================================

'------------------------------------------------
Private Function Get_Rule_Index()
	Get_Rule_Index = Session(mstrTEXTIZE_PROP_INDEX)
End Function

Private Sub Put_Rule_Index(iIndex)
	Session(mstrTEXTIZE_PROP_INDEX) = iIndex
End Sub

'------------------------------------------------
Private Function Get_Rule_To()
	Get_Rule_To = Session(mstrTEXTIZE_PROP_TO)
End Function

Private Sub Put_Rule_To(aTo)
	Session(mstrTEXTIZE_PROP_TO) = aTo
End Sub

'------------------------------------------------
Private Function Get_Rule_From()
	Get_Rule_From = Session(mstrTEXTIZE_PROP_FROM)
End Function

Private Sub Put_Rule_From(aFrom)
	Session(mstrTEXTIZE_PROP_FROM) = aFrom
End Sub

'-----------------------------------------------
Private Function Get_Rule_CCme()
	Get_Rule_CCme = Session(mstrTEXTIZE_PROP_CCMe)
end Function

Private Sub Put_Rule_CCme(bCCme)
	Session(mstrTEXTIZE_PROP_CCMe) = bCCme
end sub

'-----------------------------------------------
Private Function Get_Rule_Tome()
	Get_Rule_Tome = Session(mstrTEXTIZE_PROP_Tome)
end Function

Private Sub Put_Rule_Tome(bTome)
	Session(mstrTEXTIZE_PROP_Tome) = bTome
end sub

'-----------------------------------------------
Private Function Get_Rule_Subject()
	Get_Rule_Subject = Session(mstrTEXTIZE_PROP_SUBJECT)
end Function

Private Sub Put_Rule_Subject(sSubject)
	Session(mstrTEXTIZE_PROP_SUBJECT) = sSubject
end sub

'-----------------------------------------------
Private Function Get_Rule_Body()
	Get_Rule_Body = Session(mstrTEXTIZE_PROP_BODY)
end Function

Private Sub Put_Rule_Body(sBody)
	Session(mstrTEXTIZE_PROP_BODY) = sBody
end sub

'-----------------------------------------------
Private Function Get_Rule_Action_Delete()
	Get_Rule_Action_Delete = Session(mstrTEXTIZE_PROP_ACTION_DELETE)
end Function

Private Sub Put_Rule_Action_Delete(bDelete)
	Session(mstrTEXTIZE_PROP_ACTION_DELETE) = bDelete
end sub

'-----------------------------------------------
Private Function Get_Rule_Action_Return()
	Get_Rule_Action_Return = Session(mstrTEXTIZE_PROP_ACTION_RETURN)
end Function

Private Sub Put_Rule_Action_Return(bReturn)
	Session(mstrTEXTIZE_PROP_ACTION_RETURN) = bReturn
end sub

'-----------------------------------------------
Private Function Get_Rule_Action_Exit()
	Get_Rule_Action_Exit = Session(mstrTEXTIZE_PROP_ACTION_EXIT)
end Function

Private Sub Put_Rule_Action_Exit(bExit)
	Session(mstrTEXTIZE_PROP_ACTION_EXIT) = bExit
end sub

'---------------------------------------------------
'
'  GET CONDITIONS
'
'---------------------------------------------------
'
'  Note: Get the condition tree and action collection
'  from passed oRule object. It populates the Rule
'  Storage Object and returns the Display String.
'---------------------------------------------------
Private Sub GetConditions(orule,sAccum)

  Dim bBody				'Boolean
  Dim bSubject			'Boolean
  Dim bDirect			'Boolean
  Dim bCCMe				'Boolean
  
  Dim sBody				'String
  Dim sSubject			'String
  Dim sContent			'String
  
  Dim oTopCon			'Object
  Dim oNextCon			'Object
  Dim oColAction        'Object
  Dim oAction           'Object
  
  Dim x					'Integer
  Dim y					'Integer
      
  Dim aEmpty			'Array
  
  Set oTopCon = orule.Condition
  Set oColAction = orule.Actions
  
  'Clear all Rule Storage Object Action Props to False
  Put_Rule_Action_Delete(False)
  Put_Rule_Action_Return(False)
  Put_Rule_Action_Exit(False)
  
  'Clear out From and To Arrays
  aEmpty = Array()
  Call Put_Rule_From(aEmpty)
  Call Put_Rule_To(aEmpty)
  
  For x = 1 to oColAction.count
	set oAction = oColAction.item(cint(x))
	Select Case oAction.ActionType
		Case RULE_PR_ACTION_DELETE
			Put_Rule_Action_Delete(True)
		Case RULE_PR_ACTION_BOUNCE
			Put_Rule_Action_Return(True)
	End Select
  Next

  If oRule.State AND RULE_PR_STATE_EXIT then
	Put_Rule_Action_Exit(True)
  End If
  
  sAccum = ""
  
  'Find Contents, the body and subject
  Call Get_Content_Or_Prop(oTopCon, bBody, sBody, bSubject, sSubject, sAccum, bDirect, bCCMe)
    
  Select Case oTopCon.Type
    Case R_LOGICAL
		
		If oTopCon.Operator = RULE_PR_LOGICAL_L_AND Then

			'L_AND Conditions - Walk through each one
            '----------------------------------------
			For x = 1 To oTopCon.Count
				
				Set oNextCon = oTopCon.Item(CInt(x))
				Select Case oNextCon.Type
					Case R_LOGICAL
						Call Process_To_From_LOR(oNextCon,sAccum)
					Case R_CONTENT					
						'Ignore this, since it was already retrieved
						'by Get_Content_Or_Prop Call
				    Case R_COMMENT, R_SUB
						'Get to and From information. Once again
						'since there isn't any LOR there's only
						'1 possible of each.
						Call GetFromToCondition(oNextCon,sAccum)
					Case Else   
					   'Not a possible condition of an EDK Rule, ignore entry.
				End Select      
	        next  

        else
			Call Process_To_From_LOR(oTopCon,sAccum)
        end if
  Case R_EXISTS
    sAccum = mstrTEXTIZE_COND_ALL_MESSAGES
  Case R_COMMENT, R_SUB
        'Looking for From/To Information, since there is
        'no lower logic level this must be a single instance
        Call GetFromToCondition(oTopCon, sAccum)
  End Select
  
  Call Put_Rule_Subject(sSubject)
  Call Put_Rule_Body(sBody)  
  Call Put_Rule_Tome(bDirect)
  Call Put_Rule_CCme(bCCMe)
  Call Put_Rule_Index(oRule.index)
 
 Set oTopCon = nothing
 Set oNextCon = nothing
 Set oColAction = nothing
 Set oAction = nothing 
 
End Sub

'------------------------------------
'
'  PROCESS TO FROM LOR
'
'------------------------------------
'  Delegates the search of to and from
'  properties under and LOR logic
'  condition
'------------------------------------
Private Sub Process_To_From_LOR(oLogicCond,sAccum)

	'L_OR Condition - Must be either From or To	
	'Get strings and props
	
	Dim sTemp
	Dim bTo
	
	bTo = True
	
	Call GetFromToCondOred(oLogicCond,sTemp,Not(bTo))
	if len(sTemp) > 0 then
		sAccum = "FROM:" & sTemp & sAccum 				
    end if

    Call GetFromToCondOred(oLogicCond,sTemp,bTo)
	if len(sTemp) > 0 then
		sAccum = "TO:" & sTemp & sAccum 				
    end if
End Sub

Private Sub GetFromToCondOred(pcondLogic, pstrrgNameae, pbTo)
'
' GetFromToCondOred retrieves address entry id's for or'd from/to conditions.
'
    Dim cond
    Dim condComment
    Dim typeCond
    Dim pvComment
    Dim iae
    Dim icond
    Dim strrgIDae
    Dim rgstrIDae
    Dim strIDae

    strrgIDae = vbNullString
    '
    ' Loop through the or'd conditions
    '
    For icond = 1 To pcondLogic.Count
        Set cond = pcondLogic.Item(CInt(icond))
        typeCond = cond.Type

        Select Case typeCond
            Case R_COMMENT, R_SUB

                If typeCond = R_COMMENT Then
                    Set condComment = cond
                Else
                    Set condComment = cond.Condition
                End If
                '
                ' Address entry id for the from/to condition is stored in a property value object 
                ' in the comment condition's collection.
                '
                Set pvComment = condComment.Item(1)
                strIDae = CStr(pvComment.Value)

			    Select Case pvComment.Tag
				    Case Cdo_PR_SENDER_ENTRYID
					    If Not pbTo then
						    strrgIDae = strrgIDae & strIDae & ";"
					    End If
				    Case Cdo_PR_RECEIVED_BY_ENTRYID		
					    If pbTo then
						    strrgIDae = strrgIDae & strIDae & ";"
					    End If
			    End Select
        End Select 
    Next

    If Len(strrgIDae) > 0 then
        '
        ' Remove last semi-colon & create an array
        '
        strrgIDae = Left(strrgIDae,len(strrgIDae)-1)
        rgstrIDae = Split(strrgIDae,";")

        If pbTo then
            Call Put_Rule_To(rgstrIDae)
        Else
            Call Put_Rule_From(rgstrIDae)
        End If
        
        For iae = LBound(rgstrIDae) To UBound(rgstrIDae)
            pstrrgNameae = pstrrgNameae & CDO_strNameFromAddressEntryID(rgstrIDae(iae)) & ";"
        Next
    Else
        pstrrgNameae = vbNullString
    End If

    Set cond = Nothing
    Set condComment = Nothing
    Set pvComment = Nothing
End Sub

Private Sub GetFromToCondition(pcond, pstrCond)
'
' GetFromToCondition retrieves the address entry id associated w/ the passed condition.
'
    Dim pvComment
    Dim strIDae
    Dim strNameae
    Dim condComment

    If pcond.type = R_COMMENT then
        Set condComment = pcond
    Else
        '
        ' pcond is a sub condition.  Comment condition is stored in the sub condition's
        ' condition property.
        '
        Set condComment = pcond.Condition
    End If
    '
    ' Address entry id for the from\to condition is stored in a property value object in
    ' the comment condition's collection.
    '
    Set pvComment = condComment.Item(1)

    strIDae = CStr(pvComment.Value)
    strNameae = CDO_strNameFromAddressEntryID(strIDae)

	Select Case pvComment.Tag
		Case Cdo_PR_SENDER_ENTRYID
			pstrCond = "FROM: " & strNameae & ";" & pstrCond 	    
			Call Put_Rule_From(Array(strIDae))
	  		
		Case Cdo_PR_RECEIVED_BY_ENTRYID		
			pstrCond = "TO: " & strNameae & ";" & pstrCond
			Call Put_Rule_To(Array(strIDae))
	End Select

    Set pvComment = Nothing
    Set condComment = Nothing
End Sub

'-------------------------------------------------------
'
'    GET CONTENT OR PROP
'
'-------------------------------------------------------
Private Sub Get_Content_Or_Prop(oCondUnk,bBody,sBody,bSubject,sSubject,sAccum,bDirect,bCCMe)
  
  Dim oPropVal			'Object
  Dim x					'Integer
  Dim y					'Integer
  Dim oCondition		'Object
  Dim sContent			'String

  If oCondUnk.Type = R_LOGICAL Then
    For x = 1 To oCondUnk.Count
        Set oCondition = oCondUnk.Item(CInt(x))
		Select case oCondition.Type
			Case R_LOGICAL 
				For y = 1 To oCondition.Count
					If oCondition.Item(CInt(y)).Type = R_PROPERTY Then
						Call GetChkProperty(oCondition.Item(CInt(y)), bDirect, bCCMe, sAccum)
					End If
				Next
			Case R_CONTENT
				Call GetPropertyInfo(oCondition, bBody, bSubject, sBody, sSubject, sAccum)
			Case R_PROPERTY
				'Must be a Direct or CC property
				Call GetChkProperty(oCondition, bDirect, bCCMe, sAccum)
        End Select
    Next
  Else
    Select Case oCondUnk.Type
		Case R_CONTENT
			Call GetPropertyInfo(oCondUnk, bBody, bSubject, sBody, sSubject, sAccum)
		Case R_PROPERTY
			'Must be a Direct or CC property
			Call GetChkProperty(oCondUnk, bDirect, bCCMe, sAccum)
    End Select
  End If
  
End Sub

'--------------------------------------------------------
'
'      GET CHK PROPERTY
'
'--------------------------------------------------------
Private Sub GetChkProperty(oCondition,bDirect,bCCMe,sAccum)
  'Look for CC and To Me property tags
  
  Select case oCondition.PropertyTag
	Case Cdo_PR_MESSAGE_CC_TO_ME
		bCCMe = True
		sAccum = sAccum & "Copied (Cc) to;"
	Case Cdo_PR_MESSAGE_TO_ME
		sAccum = sAccum & "Sent directly to;"
		bDirect = True
  end select
  	
End Sub

'------------------------------------------
'
'   GET PROPERTY INFO
'
'------------------------------------------
Private Sub GetPropertyInfo(oPropCon,bBody,bSubject,sBody,sSubject,sAccum)

Dim oPropVal			'Object
Dim sContent			'String

Set oPropVal = oPropCon.Value
sContent = oPropVal.Value
Select Case oPropCon.PropertyType
	Case Cdo_PR_BODY
		bBody = True
		sBody = sContent
		sAccum = sAccum & "BODY:" & Trim(sContent) & ";"
	Case Cdo_PR_SUBJECT
		bSubject = True
		sSubject = sContent
		sAccum = sAccum & "SUBJECT:" & Trim(sContent) & ";"
End Select

End Sub

'---------------------------------------
'
'       PUT RULE
'
'---------------------------------------
Private Sub Put_Rule(oNewRule, bAdd)

	Dim iConditions     'Integer
	Dim iToConditions   'Integer
	  
	Dim x     'Integer
	  
	Dim bSubject	'Boolean
	Dim bBody		'Boolean
	Dim bToMe		'Boolean
	Dim bCCMe		'Boolean
    Dim bExists     'Boolean
	Dim bFrom		'Boolean
	Dim bTo			'Boolean
	Dim bGetFrom	'Boolean

	Dim sBody		'String
	Dim sSubject	'String
  
	Dim aFromEID	'Array
	Dim aFrom		'Array
	Dim aToEID		'Array
	Dim aTo			'Array
	  
	Dim oColRule	'Object
	Dim oAction		'Object
    Dim oCCExists   'Object
	Dim oCCSubject	'Object
	Dim oCCBody		'Object
	Dim oCCProp1	'Object
	Dim oCCProp2	'Object
	Dim oTome		'Object
	Dim oCCme		'Object
	Dim oPCProp	    'Object
	Dim oPCProp2	'Object
	  
	Dim oLogicCond  'Object
	Dim oLogicCond2 'Object
	Dim oLogicCond3 'Object
	  
	Dim oTempCond   'object
	Dim oToCond     'object
	Dim oFromCond   'object
	  
	'Set the rules collection
	Set oColRule = Session(gstrSESS_COL_RULE)
  
	'Create Rule Condition Frame
	If bAdd Then
	  Set oNewRule = CreateObject("MSExchange.Rule")
	End If
	      
	oNewRule.Name = "EDK Rule"
  
	If Get_Rule_Action_Exit() then
	   oNewRule.State = RULE_PR_STATE_ENABLED OR RULE_PR_STATE_EXIT 'Enabled and Exit Rules
	Else
	   oNewRule.State = RULE_PR_STATE_ENABLED  'Enabled
	End If
  
	'Get Rule Storage Object
	sSubject = Get_Rule_Subject()
	sBody = Get_Rule_Body()
	bToMe = Get_Rule_Tome()
	bCCMe = Get_Rule_CCMe()
	aFromEID = Get_Rule_From()
	aToEID = Get_Rule_To()
	  
	'Initialize Variables
	bGetFrom = True
    bExists = False
	bFrom = False
	bTo = False
	bSubject = False
	bBody = False
	iToConditions = 0
    
    If Len(sSubject) = 0 _
        And Len(sBody) = 0 _
        And Not bToMe _
        And Not bCCMe _
        And UBound(aFromEID) < 0 _
        And UBound(aToEID) < 0 Then
        '
        ' This rule selects all messages
        '
        Set oCCExists = CreateObject("MSExchange.ExistsCondition")
        oCCExists.PropertyTag = Cdo_PR_MESSAGE_CLASS
        iConditions = iConditions + 1
        bExists = True
    Else
        'Build From Conditions
	    If BuildCondition(bGetFrom, aFromEID, oTempCond) Then
	        Set oFromCond = oTempCond
	        iConditions = iConditions + 1
	        bFrom = True
	    End If
    
        'Build To Conditions
	    If BuildCondition(Not (bGetFrom), aToEID, oTempCond) Then
	        Set oToCond = oTempCond
	        iConditions = iConditions + 1
		      iToConditions = 1
	        bTo = True
	    End If
    
	    If Len(sSubject) > 0 Then
	      'Add a Context Condition for the subject
	      Set oCCSubject = CreateObject("MSExchange.ContentCondition")
	      oCCSubject.Operator = RULE_FUZZY_IGNORECASE Or RULE_FUZZY_SUBSTRING
	      oCCSubject.PropertyType = Cdo_PR_SUBJECT
	      Set oCCProp1 = CreateObject("MSExchange.PropertyValue")
	        oCCProp1.Tag = Cdo_PR_SUBJECT
	        oCCProp1.Value = CStr(sSubject)
	      oCCSubject.Value = oCCProp1
	      iConditions = iConditions + 1
	      bSubject = True
	    End If
	        
        If Len(sBody) > 0 Then
          'Add a Context Condition for the Body
          Set oCCBody = CreateObject("MSExchange.ContentCondition")
          oCCBody.Operator = RULE_FUZZY_IGNORECASE Or RULE_FUZZY_SUBSTRING
          oCCBody.PropertyType = Cdo_PR_BODY
          Set oCCProp2 = CreateObject("MSExchange.PropertyValue")
            oCCProp2.Tag = Cdo_PR_BODY
            oCCProp2.Value = CStr(sBody)
          oCCBody.Value = oCCProp2
          iConditions = iConditions + 1
          bBody = True
        End If
            
        If bToMe Then
          Set oTome = CreateObject("MSExchange.PropertyCondition")
          oTome.PropertyTag = Cdo_PR_MESSAGE_TO_ME
          Set oPCProp = CreateObject("MSExchange.PropertyValue")
            oPCProp.Tag = Cdo_PR_MESSAGE_TO_ME
            oPCProp.Value = True
          oTome.Operator = RULE_REL_EQ
          oTome.Value = oPCProp
          iConditions = iConditions + 1
          iToConditions = iToConditions + 1
        End If

        If bCCMe Then
          Set oCCme = CreateObject("MSExchange.PropertyCondition")
          oCCme.PropertyTag = Cdo_PR_MESSAGE_CC_TO_ME
          Set oPCProp2 = CreateObject("MSExchange.PropertyValue")
            oPCProp2.Tag = Cdo_PR_MESSAGE_CC_TO_ME
            oPCProp2.Value = True
          oCCme.Operator = RULE_REL_EQ
          oCCme.Value = oPCProp2
          iConditions = iConditions + 1
          iToConditions = iToConditions + 1
        End If
    End If
      
    'BUILD UP THE ACTUAL RULE
    '------------------------
	Select Case iConditions
		Case 0
			'NO RULES
				  
		Case 1
            If bExists Then
			  oNewRule.Condition = oCCExists
            End If
		    If bFrom Then
			  oNewRule.Condition = oFromCond
			End If
			If bTo Then
			  oNewRule.Condition = oToCond
			End If
			If bBody Then
			  oNewRule.Condition = oCCBody
			End If
			If bSubject Then
			  oNewRule.Condition = oCCSubject
			End If
			If bToMe Then
			  oNewRule.Condition = oTome
			End If
			If bCCMe Then
			  oNewRule.Condition = oCCme
			End If
		Case Else			
			'  Add Logical Condition for handle multiple conditions
			Set oLogicCond = CreateObject("MSExchange.LogicalCondition")
			oLogicCond.Operator = RULE_PR_LOGICAL_L_AND
			
			'These are always created under the L_AND					  
			If bBody Then
			  oLogicCond.Add oCCBody
			End If
			If bSubject Then
			  oLogicCond.Add oCCSubject
			End If
			
			Select Case iToConditions
				Case 0
					'Do Nothing
					
				Case 1
					if bTo then
						oLogicCond.Add oToCond
					end if
					If bToMe Then
					    oLogicCond.Add oTome
					End If
					If bCCMe Then
					    oLogicCond.Add oCCme
					End If
				Case else
			        Set oLogicCond2 = CreateObject("MSExchange.LogicalCondition")
				    oLogicCond2.Operator = RULE_PR_LOGICAL_L_OR
					if bTo then
						oLogicCond2.Add oToCond
					end if
					If bToMe Then
					    oLogicCond2.Add oTome
					End If
					If bCCMe Then
					    oLogicCond2.Add oCCme
					End If
					oLogicCond.add oLogicCond2				
			End Select
	        If bFrom Then
		  	   oLogicCond.Add oFromCond
			End If
	
            oNewRule.Condition = oLogicCond
    End Select
    
    Set oAction = CreateObject("MSExchange.Action")

    '*** SCRIPT ACTION HANDLING
    if Get_Rule_Action_Return() Then
	  oAction.ActionType = RULE_PR_ACTION_BOUNCE
      oAction.Arg = CStr("BOUNCE_ACCESS_DENIED")
    else
      'Process as a delete
      oAction.ActionType = RULE_PR_ACTION_DELETE
    end if
    
    'If Modify then delete Old Actions
    If Not bAdd Then
      If oNewRule.Actions.Count > 0 Then
        For x = oNewRule.Actions.Count To 1 Step -1
          oNewRule.Actions.Delete CInt(x)
        Next
      End If
    End If
    
    'Add Action to codllection
    oNewRule.Actions.Add 1, oAction
    
    '*** SCRIPT ADD RULE OPTION
    If bAdd Then
      oColRule.Add oColRule.Count + 1, oNewRule
    End If

End Sub

'--------------------------------------------------------------
'
'      BUILD CONDITION
'
'--------------------------------------------------------------
'   Build Logical Condition and Sub Trees
'--------------------------------------------------------------
Private Function BuildCondition(bFrom, aEID, oCond)

  'bFrom -  Set to True search for FROM property else search
  '         for TO property
  'aEID  -  Entry ID array to return
  'oCond -  Condition to start search from
  
  Dim oPropCond
  Dim oPropVal
  Dim oLogicCond
  Dim x
  Dim strSearchKey
  
  If uBound(aEID) > -1 then
    If UBound(aEID) > 0 Then
	  Set oLogicCond = CreateObject("MSExchange.LogicalCondition")
	  oLogicCond.Operator = RULE_PR_LOGICAL_L_OR
	  For x = 0 To UBound(aEID)
        strSearchKey = CDO_strSearchKeyFromAddressEntryID(aEID(x))

	    Call CreateFromToCondition(oPropCond, bFrom, aEID(x), strSearchKey)
	    oLogicCond.Add oPropCond
	  Next
	  Set oCond = oLogicCond
	Else
        strSearchKey = CDO_strSearchKeyFromAddressEntryID(aEID(0))

		Call CreateFromToCondition(oPropCond, bFrom, aEID(0), strSearchKey)
		Set oCond = oPropCond
	End If
	BuildCondition = True
  Else
	BuildCondition = False
  End If	
  
End Function

Private Sub CreateFromToCondition(pcond, pbFrom, pstrEID, pstrSearchKey)
'
' CreateFromToCondition creates a comment condition to handle recipient/sender restrictions.
' In the case of recipient/sender restrictions, Microsoft Exchange needs the search key associated
' w/ the recipient/sender to execute the rule & the Rule sample UI needs the address entry id
' in order to show the recipient/sender's display name.
'
' The comment condition provides for storing custom information in a rule in addition to
' storing the rule condition.  In this case, the address entry id is stored in the comment 
' condition's properties as a property value object, & the search key is stored as a property
' condition in the comment condition's condition property.
'
' For sender restrictions, the comment condition is returned in pcond.  For recipient restrictions,
' the comment condition is placed in the condition property of a sub condition & the sub condition
' is returned in pcond.
'
    Dim condComment
    Dim condProperty
	Dim pvProperty
    Dim pvComment
    '
    ' Create the comment condition's property value object
    '
	Set pvComment = CreateObject("MSExchange.PropertyValue")

	If pbFrom Then
	  pvComment.Tag = Cdo_PR_SENDER_ENTRYID
	Else
	  pvComment.Tag = Cdo_PR_RECEIVED_BY_ENTRYID
	End If

	pvComment.Value = pstrEID
	'
    ' Create the comment condition's property condition
    '
	Set condProperty = CreateObject("MSExchange.PropertyCondition")

	condProperty.operator = RULE_REL_EQ
	Set pvProperty = CreateObject("MSExchange.PropertyValue")

	If pbFrom Then
	  condProperty.PropertyTag = Cdo_PR_SENDER_SEARCH_KEY
	  pvProperty.Tag = Cdo_PR_SENDER_SEARCH_KEY
	Else
	  condProperty.PropertyTag = Cdo_PR_SEARCH_KEY
	  pvProperty.Tag = Cdo_PR_SEARCH_KEY
	End If

	pvProperty.Value = pstrSearchKey
	condProperty.Value = pvProperty
    '
    ' Create the comment condition
    '
    Set condComment = CreateObject("MSExchange.CommentCondition")

    condComment.Add pvComment
	
    condComment.Condition = condProperty
    '
    ' Set the returned condition
    '
    If pbFrom Then
        Set pcond = condComment
    Else
        Set pcond = CreateObject("MSExchange.SubCondition")

        pcond.Condition = condComment
    End If

	Set pvProperty = Nothing
    Set pvComment = Nothing
    Set condProperty = Nothing
    Set condComment = Nothing
End Sub

%>
