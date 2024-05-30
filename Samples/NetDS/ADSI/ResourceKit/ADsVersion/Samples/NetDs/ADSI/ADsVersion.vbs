 '---- usage:   ADsVersion [computerName]-----

  Set oArgs = wscript.Arguments

  Set vs = CreateObject("ADsVersion")

  '-------------------------------------------------------------------
  'You can also connect remotely to find out the ADSI version number
  'e.g vs.Connect "mycomputer"
  '-------------------------------------------------------------------
  if oArgs.Count = 1 Then
      wscript.echo "Connecting to " & oArgs(0) & "..."
      vs.Connect oArgs(0)
  end if 

  '--- Get the version number
  wscript.echo "ADSI Version : " & vs.GetVersion
  wscript.echo "Major Version: " & vs.GetMajorVersion
  wscript.echo "Minor Version: " & vs.GetMinorVersion
  wscript.echo "Locale:        " & vs.GetLocale
