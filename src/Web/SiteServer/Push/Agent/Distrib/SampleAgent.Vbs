' ****************************************************************************
' **
' ** Microsoft Site Server v3.00
' ** (C) Copyright 1997-1998 by Microsoft Corporation.  All rights reserved.
' **
' ** THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' ** KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' ** IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
' ** PURPOSE.
' **
' **
' ** CONTENTS
' **    Files -- a safe array of BSTRs containing filenames.
' **
' ** NOTES
' **    This file needs to reside in InstallationDirectory\Bin
' **
' ****************************************************************************

Option Explicit

'
' For htm or html files or files registered as htmlfile, we use the IFilter 
' object to extract custom htmlfile tag properties
'
On Error Resume Next
Dim g_oPushFilter
Set g_oPushFilter = CreateObject("Push.WrapSSIFilter")
On Error Goto 0
Err.Clear

If Util.IsValidData(Options("Files"), vbArray + vbVariant) AND _
   Util.IsValidData(Options("Directory"), vbString) Then

    Dim strFile, oFileSystem
    Set oFileSystem = CreateObject("Scripting.FileSystemObject")

    For Each strFile in Options("Files")
        Dim oItem
        Set oItem = Channel.AddItem()

        REM Set Item properties
        oItem.DeleteOnRefresh = TRUE
        oItem.HREF            = strFile
        oItem.Title           = strFile
        SetIFilterProperties g_oPushFilter, oItem, oFileSystem.GetFile(Options("Directory") & strFile)

        ' Please refer to the SDK for properties that can be set on Item.
    Next

End If


REM
REM This procedure sets additional Item properties found by the IFilter object
REM
Sub SetIFilterProperties(ByVal oPushFilter, ByVal oItem, ByVal oFile)

    Dim fFilterLoaded, vtData, strAuth, strKwdit

    If VarType(oPushFilter) <> vbObject Then
        oItem.Title = oFile.Name
    Else
        fFilterLoaded = TRUE

        REM
        REM Load the filename into the filter and extract HTM tag properties
        REM
        On Error Resume Next
        oPushFilter.load oFile.Path, 0
        If Err.Number <> 0 Then
            fFilterLoaded = FALSE
            Err.Clear
        End If
        On Error Goto 0

        If fFilterLoaded = FALSE Then
            oItem.Title = oFile.Name
        Else
            REM
            REM Filter is loaded, set the properties retrieved from the file Filter
            REM

            REM set the Title
            vtData = oPushFilter.GetProperty("title")
            If util.IsValidData(vtData, vbString) Then
                oItem.Title = vtData
            Else
                oItem.Title = oFile.Name
            End If

            REM set the authors
            vtData = oPushFilter.GetProperty("authors")
            If util.IsValidData(vtData, (vbArray+vbVariant)) Then
                For each strAuth in vtData
                    oItem.Authors.Add strAuth
                Next
            End If

            REM set the abstract
            vtData = oPushFilter.GetProperty("abstract")
            If util.IsValidData(vtData, vbString) Then
                oItem.Abstract = vtData
            End If

            REM set the Keywords
            vtData = oPushFilter.GetProperty("Keywords")
            If util.IsValidData(vtData, (vbArray+vbVariant)) Then
                For each strKwdit in vtData
                    oItem.Keywords.Add strKwdit
                Next
            End If
        End If 'fFilterLoaded
    End If 'g_bUseFilter
End Sub

