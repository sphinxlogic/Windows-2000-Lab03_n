Attribute VB_Name = "Module1"
Option Explicit

' Constants needed for GlobalAlloc
Global Const GMEM_FIXED = &H0
Global Const GMEM_ZEROINIT = &H40
Global Const GPTR = (GMEM_FIXED Or GMEM_ZEROINIT)

Global Const APINULL = 0&
Global Const NOT_SUPPORTED = 120&

' Constant needed for RASENTRYNAME
Global Const MaxEntryName = 256

' Function prototype for RasEnumEntries
Declare Function RasEnumEntries Lib "rasapi32.dll" Alias "RasEnumEntriesA" ( _
            ByVal reserved As String, _
            ByVal szPhoneBook As String, _
            lpRasEntries As Any, _
            lpcb As Long, _
            lpcEntries As Long) As Long
    
' Type definition for RASENTRYNAME
Type RASENTRYNAME
    dwSize As Long
    szEntryName(MaxEntryName + 1) As Byte
End Type

' Function prototype for CopyMemory
Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" ( _
            hpvDest As Any, _
            hpvSource As Any, _
            ByVal cbCopy As Long)

' Function prototype for GlobalAlloc
Declare Function GlobalAlloc Lib "kernel32" ( _
            ByVal wFlags As Long, _
            ByVal dwBytes As Long) As Long

' Function prototype for GlobalFree
Declare Function GlobalFree Lib "kernel32" ( _
            ByVal hMem As Long) As Long

' Subroutine to list the phonebook entries
Sub GetEntries(lst As ComboBox)
    Dim lpRasEntryName As RASENTRYNAME
    Dim lpcb As Long
    Dim cEntries As Long
    Dim t_Buff As Long
    Dim t_ptr As Long
    Dim t_dwSize As Long
    Dim nRet As Long
    Dim i As Long
    
    lpcb = 0
    ' Initialize the dwSize field
    lpRasEntryName.dwSize = LenB(lpRasEntryName) + (LenB(lpRasEntryName) Mod 4)
    
    ' Call RasEnumEntries with lpcb = 0 to find out the required
    ' input buffer size
    nRet = RasEnumEntries(vbNullString, vbNullString, _
                         lpRasEntryName, lpcb, cEntries)
    
    ' Allocate input buffer with required size
    t_Buff = GlobalAlloc(GPTR, lpcb)
    
    ' Initialize the first entry
    CopyMemory ByVal t_Buff, lpRasEntryName, LenB(lpRasEntryName)
    
    ' Call RasEnumEntries to enumerate the phonebook entries
    ' in the default system phonebook
    nRet = RasEnumEntries(vbNullString, vbNullString, _
                         ByVal t_Buff, lpcb, cEntries)
    
    If nRet = 0 Then ' RasEnumEntries returned success
        t_ptr = t_Buff
        
        ' Copy the values of the first entry
        CopyMemory lpRasEntryName, ByVal t_ptr, LenB(lpRasEntryName)
        
        ' Add the phone book entry to the combo box
        lst.AddItem (ByteToString(lpRasEntryName.szEntryName))
        t_dwSize = lpRasEntryName.dwSize
        t_ptr = t_ptr + t_dwSize
        
        ' Add subsequent entries to the combo box
        For i = 1 To cEntries - 1
            CopyMemory lpRasEntryName, ByVal t_ptr, LenB(lpRasEntryName)
            lst.AddItem (ByteToString(lpRasEntryName.szEntryName))
            t_ptr = t_ptr + t_dwSize
        Next i
        
    Else ' RasEnumEntries returned an error
        MsgBox nRet
    End If
    
    ' Free the allocated input buffer
    GlobalFree (t_Buff)
End Sub

' This function takes in a Byte array and converts into a String
Function ByteToString(bytearray() As Byte) As String
    Dim i As Integer, t As String
    i = 0
    t = ""
    While i < UBound(bytearray) And bytearray(i) <> 0
        t = t & Chr$(bytearray(i))
        i = i + 1
    Wend
    ByteToString = t
End Function
