<%
'<!--Microsoft Outlook HTML Form Converter-->
'<!--IPM.Post.EnhancedLitCrit -- FormUtil.inc : Common VBScript Routines-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->

'Dependencies - bstrToData, bstrCCData, and bstBCCData  have to be defined as globals.
Sub InitializeRecipients(objRecips)
  If fRecipInitialized = False Then
    Count = objRecips.Count
      
    For i = 1 To Count
      Set objOneRecip = objRecips.Item(i)
      strRecipient = objOneRecip.Name
      strAddress = objOneRecip.Address
      If IsEXAddress(strAddress) Then
        GetSMTPAddress objOneRecip.AddressEntry, strAddress
        If Len(strAddress) > 0 Then
          strRecipient = strRecipient & " [" & strAddress & "]"
        End If
      ElseIf strAddress <> "" then
        strRecipient = strRecipient & " [" & strAddress & "]"
      End If
      If not strRecipient = "" then 
        If objOneRecip.Type = 1 Then
          If bstrToData = "" Then
            bstrToData = strRecipient
          Else
            bstrToData = bstrToData & " ; " & strRecipient
          End If
        ElseIf objOneRecip.Type = 2 Then
          If bstrCCData = "" Then
            bstrCCData = strRecipient
          Else
            bstrCCData = bstrCCData & " ; " & strRecipient
          End If
        Else
          If bstrBCCData = "" Then
            bstrBCCData = strRecipient
          Else
            bstrBCCData = bstrBCCData & " ; " & strRecipient
          End If
        End If
      End If
    Next    
        fRecipInitialized = True
    End If
End Sub


'varEnumKeyElement as the keyword Returns the index or -1
'varEnumKeyElement as the index Returns the keyword or ""
Function CheckEnumeration(fldID,varEnumKeyElement)
    L_keysIMPORTANCE_TEXT     = "0Low;1Normal;2High"
    L_keysSENSITIVITY_TEXT    = "0Normal;1Personal;2Private;3Confidential"
    L_keysFLAGSTATUS_TEXT     = "0Normal;1Completed;2Flagged"
    L_keysGENDER_TEXT         = "0Unspecified;1Female;2Male"
    L_keysREMOTESTATUS_TEXT   = "0Normal;1Remote;2Retrieved;3Retrieved copy;4Delete"
    L_keysTRACKINGSTATUS_TEXT = "0None;1Delivered;2Not delivered;6Read;3Not read;4Recall failed;5Recall successful;7Replied"

    bstrEnumList = ""

    fIsImportanceField=false 'need to call frmTitle.asp.setImportance(iVal) Importance processing
    if varType(fldID)=8 Then 'string for Outlook std field
        if fldID="{0820060000000000C000000000000046}0x8511" then 'Remote Status
            bstrEnumList = L_keysREMOTESTATUS_TEXT
        elseif fldID="{0820060000000000C000000000000046}0x8809" then 'Tracking Status
            bstrEnumList = L_keysTRACKINGSTATUS_TEXT
        end if
        
    else 'number for MAPI std field
        if fldID = ActMsgPR_IMPORTANCE then
            bstrEnumList=L_keysIMPORTANCE_TEXT
            fIsImportanceField=true
        elseif fldID = ActMsgPR_SENSITIVITY then
            bstrEnumList= L_keysSENSITIVITY_TEXT
        elseif fldID = ActMsgPR_FLAG_STATUS then
            bstrEnumList= L_keysFLAGSTATUS_TEXT
        elseif fldID = &H3a4d0002 then 'Gender
            bstrEnumList= L_keysGENDER_TEXT
        end if
    end if

    if len(bstrEnumList)=0 then
        CheckEnumeration=-1
    else 'check if keyword is in string and return enum value
        if varType(varEnumKeyElement)=8 then
            ix=inStr(1,bstrEnumList,varEnumKeyElement,1) 'case insensitive
            if ix>0 then
                'note: this wont work for enums > 9 (two digits)
                CheckEnumeration=cLng(Mid(bstrEnumList,ix-1,1))
            else
                CheckEnumeration=-1
            end if
        else 'given the index pass back the keyword
            If varEnumKeyElement = -1 Then 'asking for the default item
                If fldID = ActMsgPR_IMPORTANCE Then 'only Importance default not 0
                    CheckEnumeration = GetKeyword(bstrEnumList,1)
                Else 
                    CheckEnumeration = GetKeyword(bstrEnumList,0)
                End If
            Else
                CheckEnumeration = GetKeyword(bstrEnumList,varEnumKeyElement)
            End If
        end if
    end if
End Function


Function GetKeyword(bstrEnumList,idx)
    bstrKeyWord=""

    iX=instr(1,bstrEnumList,cstr(idx))
    if iX then
        iX=iX+1
        iY=instr(iX,bstrEnumList,";")
        if iY then
            bstrKeyWord=mid(bstrEnumList,iX,iY-iX)
        else
            bstrKeyWord=mid(bstrEnumList,iX)
        end if
    end if
    GetKeyword=bstrKeyWord

End Function

Function isIE4()
    isIE4 = False
    If isMSIE() then
        If getversion() >= 4 then
            isIE4 = True
        End If
    End If
End Function


Function fm__FormatDateTime(dtValue,iType)
    ON ERROR RESUME NEXT

    iYear = Year(dtValue)
    IF iYear=1899 THEN
            dtValue = cStr(Month(Now()))+"/"+cStr(Day(Now()))+"/"+cStr(Year(Now())) +" "+ _
                      cstr(Hour(dtValue))+":"+cstr(Minute(dtValue))+":"+cstr(Second(dtValue))
    END IF

    iYear = Year(dtValue)
    iDay = Day(dtValue)
    iMonth = Month(dtValue)
    bstrFullYear = cstr(iYear)
    bstrShortYear = right(bstrFullYear,2)
    iWeek = Weekday(dtValue)
    bstrFullWeekdayName = WeekdayName(iWeek,false)
    bstrShortWeekdayName = WeekdayName(iWeek,true)
    bstrFullMonthName = MonthName(iMonth,false)
    bstrShortMonthName = MonthName(iMonth,true)

    bstrReturnDate = FormatDateTime(dtValue) 
    if iType=0 Then      'Wednesday, December 17, 1997 5:40 PM
        bstrReturnDate = FormatDateTime(dtValue,1) +  " " + FormatDateTime(dtValue,3)

    elseif iType=1 Then  '12/17/97 5:40 PM
        bstrReturnDate = FormatDateTime(dtValue,0)

    elseif iType=2 Then  'Wed 12/17/97 5:40 PM
        bstrReturnDate = bstrShortWeekdayName + " " + FormatDateTime(dtValue,0)

    elseif iType=3 Then  'Wed 12/17 5:40 PM
        bstrReturnDate = bstrShortWeekdayName+" "+cstr(iMonth)+"/"+cstr(iday)+" "+FormatDateTime(dtValue,3)

    elseif iType=4 Then  'Wednesday, December 17, 1997
        bstrReturnDate = FormatDateTime(dtValue,1)

    elseif iType=5 Then  'December 17, 1997
        bstrReturnDate = Mid(FormatDateTime(dtValue,1),instr(FormatDateTime(dtValue,1)," ")+1)

    elseif iType=6 Then  '17 December, 1997
        bstrReturnDate = cstr(iDay)+" "+bstrFullMonthName+", "+cstr(iYear)

    elseif iType=7 Then  '17-Dec-97
        bstrReturnDate = cstr(iDay)+"-"+bstrShortMonthName+"-"+right(cstr(iYear),2)

    elseif iType=8 Then  '12/17/97
        bstrReturnDate = replace(FormatDateTime(dtValue,2),cstr(iYear),right(cstr(iYear),2))

    elseif iType=9 Then  'Wed 12/17
        bstrReturnDate = bstrShortWeekdayName+" "+ cstr(iMonth)+"/"+cstr(iday)

    elseif iType=10 Then 'December 97
        bstrReturnDate = bstrFullMonthName+" "+right(cstr(iYear),2)

    elseif iType=11 Then '12/97
        bstrReturnDate = cstr(iMonth)+"/"+right(cstr(iYear),2)

    elseif iType=12 Then 'Wed 12/17/97
        bstrReturnDate = bstrShortWeekdayName + " " + FormatDateTime(dtValue,2)

    elseif iType=13 Then 'Wed 12/17/1997
        bstrReturnDate = bstrShortWeekdayName + " " + replace(FormatDateTime(dtValue,2),right(cstr(iYear),2),cstr(iYear))

    elseif iType=14 Then '5:40 PM
        bstrReturnDate = FormatDateTime(dtValue,3)

    elseif iType=15 Then '5:40
        bstrReturnDate = FormatDateTime(dtValue,4)

    end if
   fm__FormatDateTime = bstrReturnDate

End Function

Function fm__FormatDuration(lValue,iFormat)
    'lValue comes in as Minutes
    If lValue = 0 Then 
        bstrUnits = "hours"
    Else
        fHrs = lValue Mod 60
        fDays = lValue Mod 1440
        fWeeks = lValue Mod (60*24*7)

        if fWeeks=0 Then 
            bstrUnits = "weeks"
            lValue=lValue\(60*24*7)
        elseif fDays=0 Then 
            bstrUnits = "days"
            lValue=lValue\1440
        elseif fHrs=0 Then 
            bstrUnits = "hours"
            lValue=lValue\60
        else 
            bstrUnits = "minutes"
        end if
    End If

    Select Case iFormat
    Case 0 '12 u
        bstrRet = cstr(lValue)+" "+left(bstrUnits,1)
    Case 1 '12 units
        bstrRet = cstr(lValue)+" "+bstrUnits
    Case 2  '12 d/w (workdays) 'not supported
        bstrRet = cstr(lValue)+" "+left(bstrUnits,1)
    Case 3  '12 days/weeks (workdays) not supported
        bstrRet = cstr(lValue)+" "+bstrUnits
    Case Else
        bstrRet = cstr(lValue)+" "+left(bstrUnits,1)
    End Select


    fm__FormatDuration=bstrRet

End Function

Function fm__FormatComputer(bstrValue, iFormat)
  'lValue comes in as Bytes
  If bstrValue = "" Then
    lValue = 0
  Else
    lValue = cDbl(bstrValue)
  End If

  If lValue <> 0 Then
    If iFormat >= 2 Then
      If lValue >= (1024*1024*1024) Then
        'GB
        lValue = lValue / (1024*1024*1024)
        bstrUnits = "GB"
      ElseIf lValue >= (1024*1024) Then
        'MB
        lValue = lValue / (1024*1024)
        bstrUnits = "MB"
      ElseIf lValue >= 1024 Then
        'KB
        lValue = lValue / 1024
        bstrUnits = "KB"
      Else
        'Bytes
        bstrUnits = "B"
      End If
      sValue = cStr(lValue)
      iPos2 = Instr(sValue, ".")
      If iPos2 > 0 Then
        If Len(sValue) > iPos2 + 1 Then
          If Mid(sValue, iPos2 + 2, 1) >= 5 Then
            sValue = Left(sValue, iPos2) & cStr(cInt(Mid(sValue, iPos2 + 1, 1)) + 1)
          End If
        End If
        sValue = Left(sValue, iPos2 + 1)
      End If
    End If

    Select Case iFormat
      Case 0 '1,234
        bstrRet = cstr(lValue)
      Case 1 'Kilobytes Only
        bstrRet = cStr(lValue / 1024) & " K"
      Case 2  'B, K, M, G
        bstrRet = sValue & " " & Left(bstrUnits,1)
      Case Else  'B, KB, MB, GB
        bstrRet = sValue & " " & bstrUnits
    End Select
  Else
    bstrRet = ""
  End If

  fm__FormatComputer=bstrRet

End Function

Function fm__FormatData(iPropFormat, iPropType, iType, varValue)
    ON ERROR RESUME NEXT
  
    bstrPropType = cstr(iPropType)
    Select Case bstrPropType
         Case "3" 'Duration
            if varValue="" Then varValue=0
            If iType=7 Then
                varFieldData=fm__FormatDuration(varValue,iPropFormat)
            Else
                varFieldData = varValue
            End If
         Case "6" 'Currency
            if varValue="" Then varValue=0
            if iPropFormat=0 Then 'two decimals
                varFieldData=FormatCurrency(varValue,2)
            else    'no decimals
                varFieldData=FormatCurrency(varValue,0)
            end if
        Case "7"  'Date/Time 
            if len(varValue) Then 'there is a date/time value
              If varValue = "12/31/4500 4:00:00 PM" Then
                varFieldData = "none"
              Else
                varFieldData = fm__FormatDateTime(varValue, iPropFormat)
              End If
            else
                varFieldData = "none"
            end if
            
        Case "5"  'Number or Percent 
            if varValue="" Then varValue=0
            If iType <> 27 Then'Not a percent type
                varFieldData = fm__FormatNumber(varValue, iPropFormat)
            Else 
                varFieldData = fm__FormatPercent(varValue, iPropFormat)
            End If
        Case "11" 'Boolean
            if varValue="" Then varValue=False
            varFieldData = fm__FormatBoolean(varValue, iPropFormat) 
        Case Else
            varFieldData = varValue
    End Select
    fm__FormatData = varFieldData
End Function

Function fm__FormatNumber(lValue, iFormat)
    ON ERROR RESUME NEXT
    bstrFormat = cstr(iFormat)
    Select Case bstrFormat
    Case "0" 'All Digits
        bstrNum = cstr(lValue)
        iDigits = len(mid(bstrNum,instr(1,bstrNum,".")+1))
        bstrNum = FormatNumber(lValue, iDigits, False, False, True)
    Case "1" 'Truncated 1,2345
        bstrNum = FormatNumber(lValue, 0, False, False, True)
    Case "2" '1 Decimal 1,1234.6
        bstrNum = FormatNumber(lValue, 1, False, False, True)
    Case "3" '2 Decimal 
        bstrNum = FormatNumber(lValue, 2, False, False, True)
    Case "8" 'raw
        bstrNum = cstr(lValue)
    Case Else
        bstrNum = cstr(lValue)
        iDigits = len(mid(bstrNum,instr(1,bstrNum,".")+1))
        bstrNum = FormatNumber(lValue, iDigits, False, False, True)
        
    End Select

    'prepend a zero like outlook does
    If bstrNum="" Or bstrNum="-" Then 
        bstrNum="0"
    ElseIf left(bstrNum,2)="-." Then 
        bstrNum = "-0" + mid(bstrNum,2)
    ElseIf left(bstrNum,1)="." Then 
        bstrNum = "0" + bstrNum
    End If
    fm__FormatNumber = bstrNum


End Function

Function  fm__FormatPercent(lValue, iFormat)
    ON ERROR RESUME NEXT
    Select Case iFormat
    Case 0 'Rounded
        'hack for a vbScript bug in FormatPercent()
        bstrNum = FormatPercent(lValue, 0, False, False, True)
        If bstrNum="%" Then
            bstrNum = "0%"
        ElseIf bstrNum="-%" Then
            bstrNum = "-0%"
        End If
    Case 1 '1 decimal
        bstrNum = FormatPercent(lValue, 1, False, False, True)
    Case 2 '2 Decimal 
        bstrNum = FormatPercent(lValue, 2, False, False, True)
    Case 3 'All Digits
        bstrNum = cstr(lValue * 100) & "%"
    Case Else
        bstrNum = cstr(lValue * 100) & "%"
    End Select

    'prepend a zero like outlook does
    If bstrNum="" Then 
        bstrNum="0"
    ElseIf left(bstrNum,1)="." Then 
        bstrNum = "0" + bstrNum
    ElseIf left(bstrNum,2)="-." Then 
        bstrNum = "-0" + mid(bstrNum,2)
    End If
    
    fm__FormatPercent=bstrNum
End Function


Function fm__FormatBoolean(boolVal, iFormat)
    ON ERROR RESUME NEXT
    L_YES_Text = "Yes"
    L_NO_Text = "No"
    L_ON_Text = "On"
    L_OFF_Text = "Off"
    L_TRUE_Text = "True"
    L_FALSE_Text = "False"

    if iFormat = 0 Then         'Yes/No
        bstrPositive = L_YES_Text
        bstrNegative = L_NO_Text
    elseif iFormat = 1 Then     'On/Off
        bstrPositive = L_ON_Text
        bstrNegative = L_OFF_Text
    elseif iFormat = 2 Then     'True/False
        bstrPositive = L_TRUE_Text
        bstrNegative = L_FALSE_Text
    elseif iFormat = 3 Then      'Icon (Yes/No)
        bstrPositive = L_YES_Text
        bstrNegative = L_NO_Text
    end if
    If boolVal = True then
        fm__FormatBoolean = bstrPositive
    Else
        fm__FormatBoolean = bstrNegative
    End If

End Function

Function ConvertToBool(varValue, ipropFormat)
If varValue  <> "" then
    bstrValue = lcase(cstr(varValue))
    L_YES_Text = "yes"
    L_NO_Text = "no"
    L_ON_Text = "on"
    L_OFF_Text = "off"
    L_TRUE_Text = "true"
    L_FALSE_Text = "false"

    Select Case bstrValue 
        Case "1", "-1", L_YES_Text, L_TRUE_Text, L_ON_Text
	        ConvertToBool = True
        Case "0", L_NO_Text, L_FALSE_Text, L_OFF_Text 
            ConvertToBool = False
        Case Else
            ConvertToBool = False
    End Select
Else
    ConvertToBool = False
End If
End Function


'***************************************************************************
'StringToArray - Takes a comma or semicolon delimeted string  and returns and array.
'***************************************************************************

Public Function StringToArray(KeywordStr)
    bstrList = KeywordStr
    iLength = Len(KeywordStr)
    ' Convert comas to semicolons
    bstrList = Replace(bstrList, ",", ";")

    ' Copy tokens to Keywords array
    StartPos = 1
    NumWords = 0
    Do
        EndPos = InStr(StartPos, bstrList, ";", 1)
        If EndPos = 0 Then
            If StartPos <= iLength Then
                bstrItem = Trim(Mid(bstrList, StartPos, iLength))
                ReDim Preserve Keywords(Numwords)
                Keywords(Numwords) = bstrItem
                Exit Do
            Else
                If NumWords = 0 Then
                  ReDim Keywords(0)
                  Keywords(0) = ""
                End If
                Exit Do
            End If
        End If
        bstrItem = Trim(Mid(bstrList, StartPos, EndPos - StartPos))
        If bstrItem <> "" Then
            ReDim Preserve Keywords(Numwords)
            Keywords(Numwords) = bstrItem
            Numwords = Numwords + 1
        End If
        StartPos = EndPos + 1
    Loop
    StringToArray = Keywords 
End Function


'********************************
' BindRecipients - This subroutine will merge new recipients into the recipients collection
' bstrRecipData - Semicolon delimited string of recipients
' hProp - Hex value of recipient field
' objRecipients - Recipients collection
'*********************************
Sub BindRecipients(bstrRecipData, hProp, ByRef objRecipients)
    On Error Resume Next
    If hProp = &H0e04001f then
        iType = 1
    ElseIf hProp = &H0e03001f then
        iType = 2
    Else
        iType = 3
    End If
        
    lCount = 0
    lCount = objRecipients.Count
    If bstrRecipData = "" then
        For m = lCount to 1 step -1
            Set objRecip =  objRecipients.Item(m)
            If objRecip.Type = iType then
                objRecip.Delete
            End If
        Next
        Exit Sub
    End If

    If lCount <> 0 then
        rgRecipients = RecipStringToArray(bstrRecipData)
        iLbound = Lbound(rgRecipients)
        iUbound = Ubound(rgRecipients)    
        
        Do
            If i > objRecipients.Count then
                Exit Do
            End If
            Set objRecip = objRecipients.Item(i)
            If objRecip.Type <> iType then
                i = i + 1
            Else
               'Find the entry in the string - Comparison is display name and smtp address.
                fMatch = False
                For j= iLBound to iUbound
                    If instr(lcase(rgRecipients(j)),lcase(objRecip.Name)) <> 0 then
                        If instr(rgRecipients(j), "SMTP:") <> 0 then
                            Set objAddressEntry = objRecip.AddressEntry
                            GetSMTPAddress objAddressEntry, strAddress
                            If strAddress <> "" then
                                If instr(lcase(rgRecipients(j)), lcase(strAddress)) then
                                    fMatch = True
                                    rgRecipients(j) = ""
                                    Exit For
                                Else
                                    fMatch = False
                                End If
                            End If
                        End If
                    End If
                Next
                'If the recipient is not in the string then
                If fMatch = False then
                    'Do not increment i because the recipient table will shift up after deletion
                    objRecip.Delete
                Else 
                    i = i + 1
                End If
                Set objRecip = Nothing
            End If

        Loop While i <= lcount
        bstrRecipData = ""
        For x=iLBound to iUbound
            If rgRecipients(x) <> "" then
                bstrRecipData = bstrRecipData + rgRecipients(x) + ";"
            End If
        Next
        
    End If
    bstrRecipData = EscapeAddresses(bstrRecipData)
    objRecipients.AddMultiple bstrRecipData, iType
End Sub

'******************************
'RecipStringToArray - Parses semicolon delimited string and returns an array
'bstrRecipString - Semicolon delimited string
'******************************
Function RecipStringToArray(bstrRecipString)
    bstrList = bstrRecipString
    iLength = Len(bstrRecipString)
       
    StartPos = 1
    NumWords = 0
   Do
        EndPos = InStr(StartPos, bstrList, ";", 1)
        If EndPos = 0 Then
            If StartPos <= iLength Then
                bstrItem = Trim(Mid(bstrList, StartPos, iLength))
                ReDim Preserve rgRecipients(Numwords)
                rgRecipients(Numwords) = bstrItem
                Exit Do
            Else
                Exit Do
            End If
        End If
        bstrItem = Trim(Mid(bstrList, StartPos, EndPos - StartPos))
        If bstrItem <> "" Then
            ReDim Preserve rgRecipients(Numwords)
            rgRecipients(Numwords) = bstrItem
            Numwords = Numwords + 1
        End If
        StartPos = EndPos + 1
    Loop
    RecipStringToArray = rgRecipients
End Function

'used to set text-align: enum prop in styles
Function fm__GetTextAlign(iTextAlign)
    IF iTextAlign = 3 THEN 
        fm__GetTextAlign="right"
    ELSEIF iTextAlign = 2 Then 
        fm__GetTextAlign="center"
    ELSE 
        fm__GetTextAlign="left"
    END IF
End Function

Function fm__GetFieldData(iPropertyType,varFieldData, bstrFieldID,fIsMapiProperty,iPropertyFormat,iType)
	ON ERROR RESUME NEXT
    i__PropType = iPropertyType
    bstr__FieldData = ""
    
    IF iType=9 THEN 'is enumerated data
        'retrieve the EnumIndex number
        iKey = objOneMsg.Fields(bstrFieldID)
        If iKey = "" Then  
            If len(varFieldData) > 0 Then
                bstr__FieldData = varFieldData
            Else
                '0 is not always the default enum index! (importance = 1)
                bstr__FieldData = CheckEnumeration(bstrFieldID,-1)
            End If
        Else
            bstr__FieldData = CheckEnumeration(bstrFieldID,iKey)
        End If
    ELSEIF i__PropType = vbString  THEN 'it's a string (use renderer to Encode it)
        bstr__FieldData = objOneMsg.Fields.Item(bstrFieldID)
    ELSEIF i__PropType = vbArray + vbString Then
        rgItems = objOneMsg.Fields.Item(bstrFieldID)
        Err.Clear
        i = lbound(rgITems)
        bstr__FieldData = rgitems(i)
        If Err.Number <> 0 Then
          bstr__FieldData = varFieldData
        Else
          For i = i + 1  to ubound(rgitems)
            bstr__FieldData = bstr__FieldData & "; "  & rgItems(i)
          Next
        End If
    ELSE 'numeric data 
        bstr__FieldData = objOneMsg.Fields(bstrFieldID)
        bstr__FieldData = fm__FormatData(iPropertyFormat, iPropertyType , iType, bstr__FieldData)
    END IF

    'process atypical fields
    if vartype(bstrFieldID) <> vbString Then
        if bstrFieldID=&H0e070003 then 'is 'read' field uses last bit of number
           if bstr__FieldData mod 2 then 'last bit set (odd)
              bstr__FieldData = "Yes"
           else 
              bstr__FieldData = "No"
           end if
        end if
    End if


    fm__GetFieldData = bstr__FieldData

End Function

Function fm__UnformatData(varFormattedData,iPropType,iType,iPropFormat)
	ON ERROR RESUME NEXT
    IF varFormattedData="" THEN
        IF iPropType <> vbString AND iPropType <> vbString + vbArray THEN
            'convert empty string to number 0
            varFormattedData = "0"
        END IF
    END IF

    IF iPropType = vbString THEN 
        varRawData = cStr(varFormattedData)

    ELSEIF iPropType = vbString + vbArray THEN
        varRawData = StringToArray(varFormattedData)

    ELSEIF iPropType = vbCurrency THEN
        varRawData = cCur(varFormattedData)

    ELSEIF iPropType = vbDate THEN
      err.clear
      IF VarType(varFormattedData)=vbString THEN
          If LCase(varFormattedData)="none" Then
              varFormattedData = ""
          ELSE
              DO WHILE inStr(1,varFormattedData,"#",1) > 0 
                  varFormattedData = Replace(varFormattedData,"#","",1,-1,1)                
              LOOP
          END IF
      END IF
      If varFormattedData = "" Then
        varRawData = ""
      Else
        varFormattedData = ConvertShortDate(varFormattedData, iPropFormat)
        varRawData = ShortYearToLongYear(varFormattedData)
        IF varRawData = "" THEN 'conversion failed, if dayname then remove and retry
            fFinished=False
            For X=1 To 7
                SELECT CASE X
                CASE 1
                    bstrLongDayName = L_Saturday_Text
                CASE 2
                    bstrLongDayName = L_Sunday_Text
                CASE 3
                    bstrLongDayName = L_Monday_Text
                CASE 4
                    bstrLongDayName = L_Tuesday_Text
                CASE 5
                    bstrLongDayName = L_Wednesday_Text
                CASE 6
                    bstrLongDayName = L_Thursday_Text
                CASE 7
                    bstrLongDayName = L_Friday_Text
                END SELECT
                bstrShortDayName = Left(bstrLongDayName,3)

                IF inStr(1,varFormattedData, bstrLongDayName,1)>0 THEN 'search long dayname first
                    IF inStr(1,varFormattedData, bstrLongDayName+",",1)>0 THEN 'capture the comma
                        bstrNewlyFormattedData = Trim(Replace(varFormattedData,bstrLongDayName+",","",1,-1,1))
                    ELSE
                        bstrNewlyFormattedData = Trim(Replace(varFormattedData,bstrLongDayName,"",1,-1,1))
                    END IF
                    fFinished = True
                ELSEIF inStr(1,varFormattedData,bstrShortDayName,1)  THEN 'short dayname
                    IF inStr(1,varFormattedData, bstrShortDayName+",",1)>0 THEN 'capture the comma
                        bstrNewlyFormattedData = Trim(Replace(varFormattedData,bstrShortDayName+",","",1,-1,1))
                    ELSE
                        bstrNewlyFormattedData = Trim(Replace(varFormattedData,bstrShortDayName,"",1,-1,1))
                    END IF
                    fFinished = True
                END IF
                IF fFinished THEN Exit For
            Next
    
            If Len(bstrNewlyFormattedData)>0 Then
                bstrNewlyFormattedData = ConvertShortDate(bstrNewlyFormattedData, iPropFormat)
                varRawData = ShortYearToLongYear(bstrNewlyFormattedData)
            Else
                varRawData = ""
            End If
        END IF
      End If

    ELSEIF iPropType = vbInteger THEN
        varRawData = cInt(varFormattedData)

    ELSEIF iPropType = vbLong THEN
        IF iType=7 THEN 'duration
            IF IsNumeric(varFormattedData) THEN 'no units given outlook assumes this as hours
                varRawData = cLng(cDbl(varFormattedData)*60) 'cDbl to convert decimals
            ELSEIF inStr(1,varFormattedData,"m",1) > 0 THEN
                varRawData = cLng(Trim(Left(varFormattedData,inStr(1,varFormattedData,"m",1)-1)))
            ELSEIF inStr(1,varFormattedData,"h",1) > 0 THEN
                varRawData = cLng(cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"h",1)-1)))*60)
            ELSEIF inStr(1,varFormattedData,"d",1) > 0 THEN
                varRawData = cLng(cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"d",1)-1)))*1440)
            ELSEIF inStr(1,varFormattedData,"w",1) > 0 THEN
                varRawData = cLng(cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"w",1)-1)))*(60*24*7))
            END IF
        ELSEIF iType = 3 THEN 'computer field
            IF IsNumeric(varFormattedData) THEN 'no units given assume minutes
                varRawData = cLng(varFormattedData)
            ELSEIF inStr(1,varFormattedData,"k",1) > 0 THEN
                varRawData = cLng(cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"k",1)-1)))*1024)
            ELSEIF inStr(1,varFormattedData,"m",1) > 0 THEN
                varRawData = cLng(cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"m",1)-1)))*1024*1024)
            ELSEIF inStr(1,varFormattedData,"g",1) > 0 THEN
                varRawData = cLng(cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"g",1)-1)))*1024*1024*1024)
            ELSEIF inStr(1,varFormattedData,"b",1) > 0 THEN
                varRawData = cLng(Trim(Left(varFormattedData,inStr(1,varFormattedData,"b",1)-1)))
            END IF
        ELSE
            varRawData = cLng(varFormattedData)
        END IF

    ELSEIF iPropType = vbSingle THEN
        varRawData=cSng(varFormattedData)
     
    ELSEIF iPropType = vbDouble THEN
        IF iType = 27 THEN 'percents
            IF inStr(1,varFormattedData,"%",1) > 0 THEN
                varRawData = Replace(varFormattedData, "%", "")
                varRawData = cDbl(varRawData)/100
            ELSE
                varRawData = cDbl(varFormattedData)
                'the following make this behave like outlook
                ' 10 = 10% but .1 = 10% as well
                IF Abs(varRawData) >= 1 THEN 
                    varRawData = varRawData / 100
                END IF
            END IF
        ELSEIF iType = 12 THEN 'computer field
            IF IsNumeric(varFormattedData) THEN 'no units given assume minutes
                varRawData = cDbl(varFormattedData)
            ELSEIF inStr(1,varFormattedData,"k",1) > 0 THEN
                varRawData = cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"k",1)-1)))*1024
            ELSEIF inStr(1,varFormattedData,"m",1) > 0 THEN
                varRawData = cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"m",1)-1)))*1024*1024
            ELSEIF inStr(1,varFormattedData,"g",1) > 0 THEN
                varRawData = cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"g",1)-1)))*1024*1024*1024
            ELSEIF inStr(1,varFormattedData,"b",1) > 0 THEN
                varRawData = cDbl(Trim(Left(varFormattedData,inStr(1,varFormattedData,"b",1)-1)))
            END IF
            

        ELSE 'everything else
            varRawData=cDbl(varFormattedData)
        END IF
 
    ELSEIF iPropType = vbBoolean THEN
        varRawData = ConvertToBool(varFormattedData, iPropFormat)
    
    ELSE 
        varRawData = varFormattedData

    END IF
    
    fm__UnformatData = varRawData

End Function

Function ConvertShortDate(varFormattedData, iPropFormat)
  If iPropFormat = 11 Then 'Short Date mm/yy
    If Len(varFormattedData) < 6 Then
      varFormattedData = Replace(varFormattedData, "-", "/")
      iCtr = 0
      For iPos = 1 to Len(varFormattedData)
        If mid(varFormattedData, iPos, 1) = "/" Then iCtr = iCtr + 1
      Next
      If iCtr = 1 Then 'Treat date as mm/yy
        iPos = InStr(varFormattedData, "/")
        varFormattedData = Left(varFormattedData, iPos) & "01/" & Right(varFormattedData, Len(varFormattedData) - iPos)
      End If
    End If
  End If
  ConvertShortDate = varFormattedData
End Function

Function ShortYearToLongYear(varFormattedData)
  On Error Resume Next
  dFinalDate = CDate(varFormattedData)
  If Err.Number = 0 Then
    sYear = CStr(Year(dFinalDate))
    If Left(sYear, 2) = "19" And CInt(Right(sYear, 2)) < 69 Then
      If InStr(1, CStr(varFormattedData), sYear, vbTextCompare) <= 0 Then
        varFormattedData = Month(dFinalDate) & "/" & Day(dFinalDate) & "/20" & Right(sYear, 2)
      End If
    End If
    ShortYearToLongYear = cDate(varFormattedData)
  Else
    ShortYearToLongYear = ""
  End If
End Function

Dim fm__fIsEnumerated
Function GetListboxData(bstrMsgID,fIsMapiProperty,fIsMultiselect,fIsEnum)
	ON ERROR RESUME NEXT
    'set the global
	fm__fIsEnumerated=fIsEnum
    IF fIsMultiSelect THEN 'Get the delimited field selections (cdo returns an array so this allows use of instr instead of looping the array)
		GetListboxData = objRenderMsg.RenderProperty(bstrMsgID) 
	ELSE
		GetListboxData = objOneMsg.Fields(bstrMsgID) 
    END IF
End Function

Function GetComboboxData(bstrMsgID,fIsMapiProperty,fIsEnum)
    ON ERROR RESUME NEXT
    varValue = objOneMsg.Fields(bstrMsgID)
    fm__fIsEnumerated=fIsEnum

    'for enum bstr__Value will be a variant, in this case the enum value.
    IF fIsEnum THEN 
        bstrValue = varValue
    ELSE
        If vartype(varValue) >= vbArray then 'scroll thru and build
            i = lbound(varValue)
            bstrValue = varValue(i)
            For i = i + 1  to ubound(varValue)
                bstrValue = bstrValue & "; "  & varValue(i)
            Next
        Else
            bstrValue = varValue
        End If
        
    END IF

    GetComboboxData = bstrValue

End Function

Dim fm__fIsSelected
Function GetOptionData(bstrFieldID,varThisValue,fIsMapiProperty,fIsEnumerated,iPropertyFormat,iPropertyType,iType)
    On Error Resume Next
    opt__Value = objOneMsg.Fields.Item(bstrFieldID) 
    If fIsEnumerated Then
        lEnumVal = cLng(varThisValue)
        If Err.Number <> 0 Then
          Err.Clear
          lEnumVal = CheckEnumeration(bstrFieldID,varThisValue)
        End If
        If opt__Value = lEnumVal Then
          fm__fIsSelected = True
        Else
          fm__fIsSelected = False
        End If
        opt__Value = lEnumVal
    Else
        varThisValue = fm__UnformatData(varThisValue,iPropertyType,iType,iPropertyFormat)
        fm__fIsSelected = False
        IF VarType(opt__Value) = VarType(varThisValue) Then
          If VarType(opt__Value) >= vbArray + vbString Then
            'Keywords
            If uBound(opt__Value) = uBound(varThisValue) Then
              bEqual = True
              For iCtr = 0 to uBound(opt__Value)
                If opt__Value(iCtr) <> varThisValue(iCtr) Then
                  bEqual = False
                  Exit For
                End If
              Next
              if bEqual Then
                fm__fIsSelected = True
              End If
            End If
          Else
            If opt__Value = varThisValue Then
              fm__fIsSelected = True
            End If
          End If
        End If

        opt__Value = fm__FormatData(iPropertyFormat,iPropertyType,iType,opt__Value)
    END IF

    GetOptionData = opt__Value

End Function

Function GetFromFieldData(objMsg)
    Dim bstrFromData
    Rep=objMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_SEARCH_KEY)
    Sender=objMsg.Fields.Item(ActMsgPR_SENDER_SEARCH_KEY)

    'Localizable strings for send on behalf of case
    '(PreFromText)Sender(MidFromText)Representing(PostFromText)
    L_PreFrom_Text=""
    L_PostFrom_Text=""

    If Rep<>Sender Then 

	    bstrFromData =L_PreFrom_Text
	    bstrFromData = bstrFromData + objMsg.Fields.Item(ActMsgPR_SENDER_NAME) + " " + L_OnBehalfOf_Text 
	    
    End If
    
    AddrType = objMsg.Fields(ActMsgPR_SENT_REPRESENTING_ADDRTYPE)
    Address  = objMsg.Fields(ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS)
    bstrFromData = bstrFromData + objMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_NAME)
    If AddrType <> "" And AddrType <> "EX" And Address <> "" Then
        bstrFromData = bstrFromData + "[" + objMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_ADDRTYPE) + ":" + objMsg.Fields.Item(ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS) + "]"
    End If 
     bstrFromData = bstrFromData + L_PostFrom_Text
    GetFromFieldData = bstrFromData
End Function

Function GetSendCommand(bstrType)
On Error Resume Next
    bstrTemp = mid(bstrMsgType,1,8)
    If instr(1,bstrTemp,"note",1) > 0 then
        bstrCommand = "send"
    Elseif instr(1,bstrTemp,"post",1) > 0 then
        bstrCommand = "post"
    Else
        bstrCommand = "send"
    End If            
    GetSendCommand = bstrCommand
End Function

'Global string set to folder name when CreateReplyToFolder is called
gbstrFolderName = ""

Function CreateReplyToFolder (objSrcMsg)
    On Error Resume Next
    bstrFolderID = objSrcMsg.FolderID
    Set oFolder = OpenFolder(bstrFolderID)
    If oFolder Is Nothing Or oFolder.ID="" Then
        ReportError1 L_errFailOpenFolder_ErrorMessage
    End If
    gbstrFolderName = oFolder.Name
    nAccess = oFolder.Fields.Item(ActMsgPR_ACCESS)
    bCanPost = nAccess And MAPI_ACCESS_CREATE_CONTENTS
    If bCanPost Then
       Set objNewMsg = objSrcMsg.CopyTo(oFolder.ID) 
      
       If Err.Number <> 0 Then
          ReportError1 L_errFailCreateMessage_ErrorMessage     
       End If           
       objNewMsg.Recipients.Delete
       objNewMsg.Sent = False
       objNewMsg.Submitted = False
       objNewMsg.ConversationIndex = ""
       objNewMsg.DeliveryReceipt = False
       objNewMsg.ReadReceipt = False
       objNewMsg.Fields(ActMsgPR_SENDER_EMAIL_ADDRESS).Delete
       objNewMsg.Fields(ActMsgPR_SENDER_ADDRTYPE).Delete
       objNewMsg.Fields(ActMsgPR_SENDER_NAME).Delete
       objNewMsg.Fields(ActMsgPR_SENDER_ENTRYID).Delete
       objNewMsg.Fields(ActMsgPR_SENDER_SEARCH_KEY).Delete
       objNewMsg.Fields(ActMsgPR_RCVD_REPRESENTING_ADDRTYPE).Delete
       objNewMsg.Fields(ActMsgPR_RCVD_REPRESENTING_EMAIL_ADDRESS).Delete
       objNewMsg.Fields(ActMsgPR_RCVD_REPRESENTING_NAME).Delete
       objNewMsg.Fields(ActMsgPR_RCVD_REPRESENTING_ENTRYID).Delete
       objNewMsg.Fields(ActMsgPR_RCVD_REPRESENTING_SEARCH_KEY).Delete
       objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_NAME).Delete
       objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_EMAIL_ADDRESS).Delete
       objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_ADDRTYPE).Delete
       objNewMsg.Fields(ActMsgPR_SENT_REPRESENTING_ENTRYID).Delete
       objNewMsg.Fields.Item(ActMsgPR_DISPLAY_CC).Delete
       objNewMsg.Fields.Item(ActMsgPR_DISPLAY_TO).Delete
       objNewMsg.Fields.Item(ActMsgPR_DISPLAY_BCC).Delete               
       objNewMsg.Fields(&H6F020102).Delete
       err.clear
    Else
       ReportError1 L_errCreateItemPermision_ErrorMessage
    End If            
    Set CreateReplyToFolder = objNewMsg
End Function



Function CreateObjID()
    On Error Resume Next    
    Randomize
    CreateObjID = cstr(int(100000 * Rnd()))

End Function

Function CreateApptItem()
    On Error Resume Next
    Set objNewMsg = objOMSession.GetDefaultFolder(0).Messages.Add
    objNewMsg.Type = "IPM.Appointment"
    Set CreateApptItem = objNewMsg
End Function

bstrFolderName = ""

Function GetFolderName(bstrFldrID)
   On Error Resume Next
   If bstrFolderName <> "" then
      GetFolderName = bstrFolderName
   Else
      Set objFolder = OpenFolder(bstrFldrID)
      bstrFolderName = objFolder.Name
      GetFolderName = bstrFolderName   
   End If
End Function

Function bFindDuration(bstrValues, dRawValue)
  On Error Resume Next
  bFound = False
  If dRawValue = 0 Then
    bFindDuration = True
    Exit Function
  End If
  sBuffer = Right(bstrValues, Len(bstrValues) - 1)
  Do
    iPos = InStr(sBuffer, ",")
    If iPos > 0 Then
      sValue = Left(sBuffer, iPos - 1)
      sBuffer = Right(sBuffer, Len(sBuffer) - iPos)
      dRawCompare = 0
      iPos2 = Instr(1, sValue, "m", 1)
      If iPos2 > 0 Then
        ' Minutes
        dRawCompare = cDbl(Left(sValue, iPos2 - 1))
      Else
        iPos2 = Instr(1, sValue, "h", 1)
        If iPos2 > 0 then
          ' Hours
          dRawCompare = cDbl(Left(sValue, iPos2 - 1)) * 60
        Else
          iPos2 = Instr(1, sValue, "d", 1)
          If iPos2 > 0 Then
            ' Days
            dRawCompare = cDbl(Left(sValue, iPos2 - 1)) * 1440
          Else
            iPos2 = Instr(1, sValue, "w", 1)
            If iPos2 > 0 Then
              ' Weeks
              dRawCompare = cDbl(Left(sValue, iPos2 - 1)) * 10080
            Else
              ' Hours is default
              dRawCompare = cDbl(sValue) * 60
            End If
          End If
        End If
      End If
      If dRawValue = dRawCompare Then
        bFound = True
      End If
    End If
  Loop Until (bFound Or iPos <= 0)
  bFindDuration = bFound
End Function

Function bFindComputer(bstrValues, dRawValue)
  On Error Resume Next
  bFound = False
  If dRawValue = 0 Then
    bFindComputer = True
    Exit Function
  End If
  sBuffer = Right(bstrValues, Len(bstrValues) - 1)
  Do
    iPos = InStr(sBuffer, ",")
    If iPos > 0 Then
      sValue = Left(sBuffer, iPos - 1)
      sBuffer = Right(sBuffer, Len(sBuffer) - iPos)
      dRawCompare = 0
      iPos2 = Instr(1, sValue, "g", 1)
      If iPos2 > 0 Then
        ' Gigabytes
        dRawCompare = cDbl(Left(sValue, iPos2 - 1)) * 1073741824
      Else
        iPos2 = Instr(1, sValue, "m", 1)
        If iPos2 > 0 then
          ' Megabytes
          dRawCompare = cDbl(Left(sValue, iPos2 - 1)) * 1048576
        Else
          iPos2 = Instr(1, sValue, "k", 1)
          If iPos2 > 0 Then
            ' Kilobytes
            dRawCompare = cDbl(Left(sValue, iPos2 - 1)) *  1024
          Else
            iPos2 = Instr(1, sValue, "b", 1)
            If iPos2 > 0 Then
              ' Bytes
              dRawCompare = cDbl(Left(sValue, iPos2 - 1))
            Else
              ' Bytes is default
              dRawCompare = cDbl(sValue)
            End If
          End If
        End If
      End If
      If Abs(dRawValue - dRawCompare) < 1 Then
        bFound = True
      End If
    End If
  Loop Until (bFound Or iPos <= 0)
  bFindComputer = bFound
End Function

Function TranslateDuration(bstrValue)
  If abs(bstrValue) >= 60 Then
    sValue = (bstr__Value / 60) & " h"
  Else
    If bstr__Value <> 0 Then
      sValue = bstr__Value & " m"
    End If
  End If
  TranslateDuration = sValue
End Function
%>