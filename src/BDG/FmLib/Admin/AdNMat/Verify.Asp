<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<% ' CLIENT-SIDE input verification scripts. %>

<script LANGUAGE=VBScript>
Private Function IIf(boolPart, ifTrue, ifFalse)
   If boolPart Then
      IIf = ifTrue
   Else
      IIf = ifFalse
   End If
End Function

Function IsValidNumber(strNumber)
   IsValidNumber = IsNumeric(strNumber)
End Function

Function IsValidDate(strDate)
   IsValidDate = IsDate(strDate)
   
   '--- Try again, but assume strDate is YEAR only
   If Not IsValidDate Then
      strDate = "1-1-" & strDate
      IsValidDate = IsDate(strDate)
   End If
   
   If IsValidDate Then
      Dim d
      On Error Resume Next
      d = CDate(strDate)
      If Err.Number = 0 Then
         If Year(d) < 1940 Then
            IsValidDate = IIf(vbYes = MsgBox("Date converts to a year prior to 1940.  Is this OK?", _
                                             vbQuestion + vbYesNo, "Confirm Date Entry"), True, False)
         End If
      Else
         IsValidDate = False
      End If
   End If
End Function

' ISBN's (International Standard Book Number) are ten-digit numbers
' (alternately, the last digit can be the letter X) divided
' into four variable length parts separated by hyphens.

Const csHyphen = "-"

Function IsValidISBN(ByVal strISBN)
   Dim len1, len2
   
   ' First check for really strange input...
   If (Left(strISBN,1) <> csHyphen) And (Right(strISBN,1) <> csHyphen) Then
      ' ...then get the length before and after replacing all hyphens
      len1 = Len(strISBN)
      strISBN = Replace(strISBN, csHyphen, "")
      len2 = Len(strISBN)
   End If

   ' Should have found 3 hyphens, and a remaining length of 10
   If (len1 = 13) And (len2 = 10) Then
      IsValidISBN = IsValidNumber(strISBN)
      ' If failure, check once more for a trailing 'X'
      If IsValidISBN = False Then
         IsValidISBN = (Right(strISBN,1) = "X") And (IsValidNumber(Left(strISBN,9)))
      End If
   Else
      IsValidISBN = False
   End If
End Function

' ISSN's (International Standard Serials Number) have the form
' NNNN-NNNN where N is a digit. The last digit may be an upper-case X.

Function IsValidISSN(ByVal strISSN)
   Dim len1, ix

   ' Get the length of string and location of hyphen
   len1 = Len(strISSN)
   ix = InStr(strISSN,csHyphen)
   
   ' Should have found 9 characters with a hyphen in the middle
   If (len1=9) And (ix=5) Then
      strISSN = Replace(strISSN,csHyphen,"")
      IsValidISSN = IsValidNumber(strISSN)
      ' If failure, check once more for trailing 'X'
      If IsValidISSN = False Then
         IsValidISSN = (Right(strISSN,1) = "X") And (IsValidNumber(Left(strISSN,7)))
      End If
   Else
      IsValidISSN = False
   End If
End Function

</script>
