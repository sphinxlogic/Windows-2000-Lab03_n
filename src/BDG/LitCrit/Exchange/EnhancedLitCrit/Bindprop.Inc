<%
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- BindProp.inc : Common binding routines-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->

const CDOPROPID = 0
const CDOPROPTYPE = 1
const BMAPIPROP = 2
const PROPERTYFORMAT = 3
const PROPERTYTYPE = 4 'Number or Percent
const REQUIREDFIELD = 5
const ISENUMTYPE = 6
const DEFAULTVAL = 7

'Response Types
const CDO_Reply         = 1
const CDO_ReplyAll      = 2
const CDO_Forward       = 3
const CDO_ReplyToFolder = 4
const CDO_Response      = 5

Sub RegisterField(bstrInputFieldName, bstrCDOPropID, bstrCDOPropType, boolMapiProp, iPropFormat, iType, objDict, boolIsRequired, defaultValue)
    On Error Resume Next
    Dim rgProps(7)
    rgProps(CDOPROPID) = bstrCDOPropID
    rgProps(CDOPROPTYPE) = bstrCDOPropType
    rgProps(BMAPIPROP) =  boolMapiProp
    rgProps(PROPERTYFORMAT) = iPropFormat
    rgProps(PROPERTYTYPE) = iType 
    rgProps(REQUIREDFIELD) = boolIsRequired 
    rgProps(DEFAULTVAL) = defaultValue ' LITCRIT MODIFICATION
    If iType=9 Then
        rgProps(ISENUMTYPE) = True
    Else
        rgProps(ISENUMTYPE) = False
    End If
    bstrInputFieldName = UCASE(bstrInputFieldName)
    'remove item if it already exists (this allows updating)
    IF objDict.Exists(bstrInputFieldName) THEN
        objDict.Remove (bstrInputFieldName)
    END IF
    objDict.Add bstrInputFieldName, rgProps

End Sub

'***************************************************************************
'SetInitialValue - 
'Dependencies - 
'***************************************************************************

Sub SetInitialValue(varFieldID, iPropType, fIsMapiProp, varFieldValue, iPropFormat, iType, objNewMsg)
  
    On Error Resume Next
    fSetValue = False
    If varFieldValue <> "" Then
        
       'a quirk with init % values if they come in with no '%' then need * 100
        IF iPropType=5 AND iType = 27 THEN 
            IF instr(1,varFieldValue,"%",1) > 0 THEN
                varRawData = Replace(varFieldValue, "%", "")
                varRawData = cDbl(varFieldValue)  
            ELSE
                varRawData = cDbl(varFieldValue) * 100
            END IF
            varFieldValue = cStr(varRawData)
        END IF
        varFieldValue = fm__UnformatData(varFieldValue,iPropType,iType,iPropFormat)
        ' Response.Write "Binding: " & varFieldID & "<br>"
        Set objNewField = objNewMsg.Fields(varFieldID)
        If fIsMapiProp then
            If objNewField Is Nothing Then
                Set objNewField = objNewMsg.Fields.Add(varFieldID, varFieldValue)
                fSetValue = True
            Else
                If objNewMsg.ID = "" then 'If ID is blank then we have a new message
                    If objNewField.Value = "" then 
                        objNewField.Value = varFieldValue
                        fSetValue = True
                    End If
                End If
            End If
        Else
            If objNewField Is Nothing Then 
                Set objNewField = objNewMsg.Fields.Add(varFieldID, iPropType, varFieldValue)
                fSetValue = True
            End If
        End If
        
        If fSetValue Then    
            bstrFieldID = cstr(varFieldID)
            If bstrFieldID = "{0820060000000000C000000000000046}0x8506" THEN 'this is 'private' flag (maps to sensivity)
                'there is no Private field, if this is set to true then
                'need to set Sensitivity to 'Private' (2)
                fFieldValue = ConvertToBool(varFieldValue,iPropFormat)
                If fFieldValue=True Then 'set to Private
                    Set objNewField = objNewMsg.Fields.Add(ActMsgPR_SENSITIVITY, ActMsgSensitive_Private)
                    objNewMsg.Fields.Add "{0820060000000000C000000000000046}0x8506", vbBoolean, True
                End If
            ElseIf bstrFieldID = "&H10900003" THEN 'flagged status maps to followup flag field
                varFieldValue = cLng(varFieldValue)
                Set objNewField = objNewMsg.Fields.Add(varFieldID, varFieldValue)
                If varFieldValue <> 0 Then' if Flagged Status is not 'normal'
                    Set objNewField = objNewMsg.Fields.Add("{0820060000000000C000000000000046}0x8530", vbString, "Follow up")
                End If
            ElseIf bstrFieldID = "{0820060000000000C000000000000046}0x8530" Then
                If varFieldValue <> "" Then
                    objNewMsg.Fields.Add &H10900003, 2
                Else
                    objNewMsg.Fields.Add &H10900003, 0
                End IF
                objNewMsg.Fields.Add "{0820060000000000C000000000000046}0x8530", vbString, varFieldValue
            End If
        End If
    set objNewField = Nothing
    End If

End Sub

Function ValidateRequiredFields()
    ON ERROR RESUME NEXT
    Set WindowReg = Session("Registry" & bstrObj)
    bstrRetErrMsg = ""
    err.clear

    Set objRenderMsg = GetObjectRenderer
    objRenderMsg.DataSource = objNewMsg

    rgKeys = WindowReg.Keys
    For x = 0 to WindowReg.Count - 1
        rgProps = WindowReg.Item(rgKeys(x))
        iPropType = rgProps(CDOPROPTYPE)
        boolIsRequired = rgProps(REQUIREDFIELD)
        IF boolIsRequired THEN
            propID = rgProps(CDOPROPID)
            bstrFldData = ""
            if iPropType=vbString+vbArray Then
                bstrFldData = objRenderMsg.RenderProperty(propID)
            else
                bstrFldData = cstr(objNewMsg.Fields(propID))
            end if
            bstrFieldName = rgKeys(x)

'=== LITCRIT SPECIFIC
' The original script checked for blank values, but we need
' to check for default values.  Added another field to array
' that contains the expected default value.  If the default
' value has not been changed, the error message is returned.

            IF bstrFldData = rgProps(DEFAULTVAL) THEN
                IF len(bstrRetErrMsg)=0 THEN 'format string for jscript output
                    bstrRetErrMsg = "DATA ENTRY ERRORS:\n\r" + "Entry Required For: " + bstrFieldName + "\r\n"
                ELSE
                    'append to return error message
                    bstrRetErrMsg = bstrRetErrMsg + "Entry Required For: " + bstrFieldName + "\r\n"
                END IF
            END IF
        END IF
    Next
    
    ValidateRequiredFields = bstrRetErrMsg

End Function

'***************************************************************************
'BindCustomFields - This routine will bind the data in the form object that 
'                   corresponds to the fields stored inside the dictionary object.
'Dependencies - This routine relies on the dictionary objects being intialized by frmRoot.asp
'               and then stored in the application object.
''Returns - jscript formatted string with error message on fail empty string on success
'***************************************************************************

Function BindCustomFields()
  ON ERROR RESUME NEXT
  Set WindowReg = Session("Registry" & bstrObj)
  bstrReturnError=""

  For Each CustField in Request.Form
      bstrFieldName = UCASE(CustField)
      If bstrFieldName <> "" Then
        'If field is registered as bound and it's data has not been unchanged (is changed)
        If WindowReg.Exists(bstrFieldName) then 'registered custom field
            rgProps = WindowReg.Item(bstrFieldName)
            bstrFieldValue = Request.Form(bstrFieldName)

            '1st check If field is empty and it's a required field
            IF bstrFieldValue="" AND rgProps(REQUIREDFIELD)<>False THEN
                if len(bstrReturnError)=0 Then 'format string for jscript output
                    bstrReturnError = "DATA ENTRY ERRORS:\n\r" + "Entry Required For: " + bstrFieldName + "\r\n"
                else
                    'append to return error message
                    bstrReturnError = bstrReturnError + "Entry Required For: " + bstrFieldName + "\r\n"
                end if
            'now if the data has changed (check the dirty field which returns
            'false if the field is dirty or the dirty field does not exist - (optimistic)
            ElseIf Not cBool(Request.Form("fUnCh_"+bstrFieldName)) Or (IsNav And getVersion >= 4) Then 'bind away
                If Not IsNumeric(bstrFieldValue) Then 'make sure not enumerated text
                    iEnum = rgProps(ISENUMTYPE)
                    If iEnum Then
                        If len(bstrFieldValue)>0 Then
                            iEnumKey=CheckEnumeration(rgProps(CDOPROPID),bstrFieldValue)
                        Else
                            iEnumKey=-1
                        End If
                        varFieldValue=iEnumKey
                    Else
                        If len(bstrFieldValue)>0 Then
                            varFieldValue=fm__UnformatData(bstrFieldValue,rgProps(CDOPropType),rgProps(PROPERTYTYPE),rgProps(PROPERTYFORMAT))
                        Else
                          Select Case rgProps(CDOPropType)
                            Case vbArray + vbString
                              ReDim varFieldValue(0)
                              varFieldValue(0) = ""
                            Case vbInteger, vbLong, vbSingle, vbDouble, vbCurrency
                              varFieldValue = 0
                            Case Else
                              varFieldValue=""
                          End Select
                        End If
                    End If
                Else
                    varFieldValue=fm__UnformatData(bstrFieldValue,rgProps(CDOPropType),rgProps(PROPERTYTYPE),rgProps(PROPERTYFORMAT))        
                End If        
        
                If rgProps(BMAPIPROP) Then
                    If rgProps(PROPERTYTYPE) = 20 then 'Recipient fields
                        BindRecipients bstrFieldValue, rgProps(CDOPROPID), objNewMsg.Recipients
                    Else
                        Set objNewField = objNewMsg.Fields.Add(rgProps(CDOPROPID), varFieldValue)
                        If rgProps(CDOPROPID) = ActMsgPR_Sensitivity Then
                            If varFieldValue = ActMsgSensitive_Private Then
                                objNewMsg.Fields.Add "{0820060000000000C000000000000046}0x8506", vbBoolean, True
                            Else
                                objNewMsg.Fields.Add "{0820060000000000C000000000000046}0x8506", vbBoolean, False
                            End If
                        ElseIf rgProps(CDOPROPID)  = &H10900003 Then
                            If varFieldValue <> 0 Then
                                objNewMsg.Fields.Add "{0820060000000000C000000000000046}0x8530", vbString, "Follow up" 
                            Else
                                objNewMsg.Fields.Item("{0820060000000000C000000000000046}0x8530") = ""
                            End If
                        End If
                    End If
                Else
                  If rgProps(CDOPropType) <> vbDate Or (rgProps(CDOPropType) = vbDate And varFieldValue <> "" And LCase(varFieldValue) <> "none") Then
                    'case for WebPage field
                    If rgProps(CDOPROPID) = "{0420060000000000C000000000000046}0x802b" Then
                        ' Force Outlook to use our value
                        If bstrFieldValue = "" Then
                            objNewMsg.Fields(ActMsgPR_BUSINESS_HOME_PAGE)  = ""
                        ElseIf Instr(bstrFieldValue, ":") = 0 Then
                            objNewMsg.Fields(ActMsgPR_BUSINESS_HOME_PAGE)  = "http://" & bstrFieldValue
                        Else
                            objNewMsg.Fields(ActMsgPR_BUSINESS_HOME_PAGE)  = bstrFieldValue
                        End If
                        objNewMsg.Fields.Add AMPidTag_WebPage, 8, objNewMsg.Fields(ActMsgPR_BUSINESS_HOME_PAGE)
                    Else
                        Set objNewField = objNewMsg.Fields.Add(rgProps(CDOPROPID), clng(rgProps(CDOPROPTYPE)), varFieldValue)
                        If rgProps(CDOPROPID) = "{0820060000000000C000000000000046}0x8506" Then
                            If varFieldValue = True Then
                                objNewMsg.Fields.Add ActMsgPR_SENSITIVITY, ActMsgSensitive_Private
                            End If
                        ElseIf rgProps(CDOPROPID) = "{0820060000000000C000000000000046}0x8530" Then
                                         
                            If varFieldValue <> "" Then
                                objNewMsg.Fields.Add &H10900003, 2
                            Else
                                objNewMsg.Fields.Add &H10900003, 0
                            End IF
                        End If
                    End If
                  Else
                    Set objNewField = objNewMsg.Fields(rgProps(CDOPROPID))
                    If Not (objNewField Is Nothing) Then
                      objNewField.Delete
                    End If
                    Set objNewField = objNewMsg.Fields.Add(rgProps(CDOPROPID), 8, "")
                  End If
                End If
            END IF
        End If
        'Now if there are no errors so far need to scroll the dictionary for other required fields
        ' and check the message for emptyness


        
    End If
    set objNewField = Nothing
    Set varFieldValue = Nothing
  Next

  BindCustomFields = bstrReturnError

End Function


%>