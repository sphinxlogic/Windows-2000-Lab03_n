REM Note that missing classes in log file mean tthe hat WMI cannot access them.
REM Most likely this indicates a problem with the driver.
REM See %windir%\system32\wbem\wmiprov.log and nt eventlog for more details.
REM You could also delete the line On Error Resume Next and examine the
REM specific VBScript error


On Error Resume Next

Set fso = CreateObject("Scripting.FileSystemObject")
Set a = fso.CreateTextFile("filter.log", True)
Set Service = GetObject("winmgmts:{impersonationLevel=impersonate}!root/wmi")
Rem MSSample_DiagnosticSettingList - Sample Diagnostic Test Settings List
Set enumSet = Service.InstancesOf ("MSSample_DiagnosticSettingList")
a.WriteLine("MSSample_DiagnosticSettingList")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    a.WriteLine("        instance.SettingCount=" & instance.SettingCount)
    for i1 = 0 to (instance.SettingCount-1)
    a.WriteLine("        instance.SettingList("&i1&").TestWarningLevel=" & instance.SettingList(i1).TestWarningLevel)
    a.WriteLine("        instance.SettingList("&i1&").ReportSoftErrors=" & instance.SettingList(i1).ReportSoftErrors)
    a.WriteLine("        instance.SettingList("&i1&").ReportStatusMessages=" & instance.SettingList(i1).ReportStatusMessages)
    a.WriteLine("        instance.SettingList("&i1&").HaltOnError=" & instance.SettingList(i1).HaltOnError)
    a.WriteLine("        instance.SettingList("&i1&").QuickMode=" & instance.SettingList(i1).QuickMode)
    a.WriteLine("        instance.SettingList("&i1&").PercentOfTestCoverage=" & instance.SettingList(i1).PercentOfTestCoverage)
    a.WriteLine("        instance.SettingList("&i1&").Reserved=" & instance.SettingList(i1).Reserved)
    next 'i1
next 'instance

Rem MSSample_DiagnosticTest - Sample Diagnostic Test
Set enumSet = Service.InstancesOf ("MSSample_DiagnosticTest")
a.WriteLine("MSSample_DiagnosticTest")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    a.WriteLine("        instance.IsInUse=" & instance.IsInUse)
    a.WriteLine("        instance.ResourcesUsedCount=" & instance.ResourcesUsedCount)
    a.WriteLine("        instance.CharacteristicsCount=" & instance.CharacteristicsCount)
    a.WriteLine("        instance.OtherCharacteristicDescription=" & instance.OtherCharacteristicDescription)
    for i1 = 0 to (instance.CharacteristicsCount-1)
    a.WriteLine("        instance.Characteristics("&i1&")=" & instance.Characteristics(i1))
    next 'i1
    for i1 = 0 to (instance.ResourcesUsedCount-1)
    a.WriteLine("        instance.ResourcesUsed("&i1&")=" & instance.ResourcesUsed(i1))
    next 'i1
next 'instance

Rem MSSample_OfflineDiagnosticTest - Sample Offline Diagnostic Test
Set enumSet = Service.InstancesOf ("MSSample_OfflineDiagnosticTest")
a.WriteLine("MSSample_OfflineDiagnosticTest")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    a.WriteLine("        instance.IsInUse=" & instance.IsInUse)
    a.WriteLine("        instance.ResourcesUsedCount=" & instance.ResourcesUsedCount)
    a.WriteLine("        instance.CharacteristicsCount=" & instance.CharacteristicsCount)
    a.WriteLine("        instance.OtherCharacteristicDescription=" & instance.OtherCharacteristicDescription)
    for i1 = 0 to (instance.CharacteristicsCount-1)
    a.WriteLine("        instance.Characteristics("&i1&")=" & instance.Characteristics(i1))
    next 'i1
    for i1 = 0 to (instance.ResourcesUsedCount-1)
    a.WriteLine("        instance.ResourcesUsed("&i1&")=" & instance.ResourcesUsed(i1))
    next 'i1
next 'instance

Rem MSSample_OfflineResult - Sample Diagnostic Test Settings List
Set enumSet = Service.InstancesOf ("MSSample_OfflineResult")
a.WriteLine("MSSample_OfflineResult")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    a.WriteLine("        instance.ExecutionID=" & instance.ExecutionID)
    a.WriteLine("        instance.TestResult.EstimatedTimeOfPerforming=" & instance.TestResult.EstimatedTimeOfPerforming)
    a.WriteLine("        instance.TestResult.TestState=" & instance.TestResult.TestState)
    a.WriteLine("        instance.TestResult.OtherStateDescription=" & instance.TestResult.OtherStateDescription)
    a.WriteLine("        instance.TestResult.PercentComplete=" & instance.TestResult.PercentComplete)
    a.WriteLine("        instance.TestResult.Reserved1=" & instance.TestResult.Reserved1)
    a.WriteLine("        instance.TestResult.Reserved2=" & instance.TestResult.Reserved2)
    a.WriteLine("        instance.TestResult.Reserved3=" & instance.TestResult.Reserved3)
    a.WriteLine("        instance.TestResult.TestResultsCount=" & instance.TestResult.TestResultsCount)
    for i2 = 0 to (instance.TestResult.TestResultsCount-1)
    a.WriteLine("        instance.TestResult.TestResults("&i2&")=" & instance.TestResult.TestResults(i2))
    next 'i2
next 'instance

a.Close
Wscript.Echo "filter Test Completed, see filter.log for details"
