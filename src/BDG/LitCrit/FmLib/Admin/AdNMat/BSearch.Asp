<script LANGUAGE=VBScript>
Private Function BSearch(ByRef opts, ByVal txt, ByVal near, ByRef found)
   Dim btm,top,mid,cmp
   btm = 0
   mid = 0
   top = opts.length-1
   cmp = 0
   found = false
   
   ' Returns negative number if not found
   BSearch = -1
   
   Do While top >= btm And Not found
      mid = CLng((top + btm)/2)
      cmp = StrComp(opts(mid).text,txt,vbTextCompare)
      If cmp = 0 Then
         BSearch = mid
         found = True
      Else
         If cmp < 0 Then
            btm = mid + 1 ' Narrow search to upper half
         Else
            top = mid - 1 ' Narrow search to lower half
         End If
      End If
   Loop
   
   ' Return the nearest match
   If near And Not found Then
      If cmp < 0 Then mid = mid + 1
      BSearch = mid
   End If
End Function
</script>