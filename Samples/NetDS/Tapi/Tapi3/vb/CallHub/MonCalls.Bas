Attribute VB_Name = "MonCalls"

'
'--------------------------------------------------------------------------
'
'  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
'
'Functions for "MONitored" Calls
'
'MCTree = Monitored Calls Tree
'
'Notes:
' - Bug in VB: can't store objects in Nodes.Tag, so store them in
' a separatecollection.
'

Option Explicit

Private Const gszAddress = "Address"

Public Function MCTree_Unload(tree As TreeView, treeCollData As Collection) As Long
    
    Dim objNode As Node
    Dim nIndex
    
    'assert
    If tree.Nodes.Count <> treeCollData.Count Then
        MsgBox ("ASSERT: MonitoredCalls: TreeNodes and TreeDataCollection have different number of elements!")
    End If
    
    'release tree data
    For Each objNode In tree.Nodes
        'Set objNode.Tag = Nothing      'doesn't work
        treeCollData.Remove (1)
    Next
    
    'release all nodes
    tree.Nodes.Clear
   
End Function

Public Function MCTree_Load( _
    tree As TreeView, _
    treeCollData As Collection, _
    varArrAddresses As Variant) As Long

    Dim nIndex
    Dim collAddresses As ITCollection
    Dim objCrtAddress  As ITAddress
    Dim objCrtNode  As Node
    
    Set collAddresses = varArrAddresses
    
    For nIndex = 1 To collAddresses.Count
        Set objCrtAddress = collAddresses.Item(nIndex)
        
        '
        'create new node for this address
        '
        Set objCrtNode = tree.Nodes.Add(Text:=gszAddress)
        objCrtNode.EnsureVisible
        
        '
        'save a reference of Address right in the node
        '
        'Set objCrtNode.Tag = objCrtAddress     'doesn't work
        If objCrtNode.Index = 1 Then
            Call treeCollData.Add(Item:=objCrtAddress)  'it is the 1st node
        Else
            Call treeCollData.Add(Item:=objCrtAddress, after:=objCrtNode.Index - 1)
        End If
        
        'assert: check that the node and its data have the same index
        If Not (objCrtAddress Is treeCollData(objCrtNode.Index)) Then
            MsgBox ("ASSERT: " & "MonitoredCalls: " & _
            "Tree's Node-Collection and Data-Collection do not have the same index! ")
        End If
        
        '
        'create "call" nodes
        '
        Call LoadCalls(tree, treeCollData, objCrtNode.Index, objCrtAddress)
        
        Set objCrtNode = Nothing
        Set objCrtAddress = Nothing
    Next nIndex
    
    Set collAddresses = Nothing

End Function

Public Function MCTree_DisplayNode( _
    ByVal objNode As ComctlLib.Node, _
    treeCollData As Collection) As Long
    
    '
    'find the data corresponding to this node
    '
    
    Dim objData As Object
    
    'Set objData = objNode.Tag              'doesn't work
    Set objData = treeCollData.Item(objNode.Index)
    
    If objData Is Nothing Then
        
        frmCallHubs.txtDescriptionMC.Text = "Not Available"
        frmCallHubs.txtDescriptionMC.Refresh
        
        Set objData = Nothing
        
        MCTree_DisplayNode = 0
        Exit Function
    End If
    
    '
    'detect what kind of object is stored in node
    'by using its title
    '
    
    Select Case objNode.Text
        Case gszAddress
            Dim objAddress As ITAddress
            Set objAddress = objData
            Call DisplayAddress(objAddress)
            Set objAddress = Nothing
    
        Case gszCallInfo
            Dim objCallInfo As ITCallInfo
            Set objCallInfo = objData
            Call DisplayCallInfo(objCallInfo, frmCallHubs.txtDescriptionMC)
            Set objCallInfo = Nothing
    
        Case gszCallControl
            Dim objCallControl As ITBasicCallControl
            Set objCallControl = objData
            Call DisplayCallControl(objCallControl, frmCallHubs.txtDescriptionMC)
            Set objCallControl = Nothing
        
        Case gszLegacyCallMediaControl
            Dim objLegacyCallMediaControl As ITLegacyCallMediaControl
            Set objLegacyCallMediaControl = objData
            Call DisplayLegacyCallMediaControl(objLegacyCallMediaControl, frmCallHubs.txtDescriptionMC)
            Set objLegacyCallMediaControl = Nothing
    
        Case gszStreamControl
            Dim objStreamControl As ITStreamControl
            Set objStreamControl = objData
            Call DisplayStreamControl(objStreamControl, frmCallHubs.txtDescriptionMC)
            Set objStreamControl = Nothing
    
        Case Else
            'assert
            MsgBox ("ASSERT: unkown type of node in <Monitored Calls> tree")
            
    End Select
    
    Set objData = Nothing
End Function

Public Function MCTree_AddNewCall( _
    tree As TreeView, _
    treeCollData As Collection, _
    objCallInfo As ITCallInfo) As Long
    
    Dim nParentNodeIndex As Variant
    nParentNodeIndex = Empty
    
    '
    'search in tree the address that owns the call, and remember its "node" index
    '
    Dim objCrtAddress As ITAddress
    Dim nIndex As Long
    
    For nIndex = 1 To tree.Nodes.Count
        If tree.Nodes.Item(nIndex).Text = gszAddress Then
            
            'Set objCrtAddress = tree.Nodes.Item(nIndex).Tag    'doesn't work
            Set objCrtAddress = treeCollData.Item(nIndex)
            
            If objCrtAddress Is objCallInfo.Address Then
                nParentNodeIndex = tree.Nodes.Item(nIndex).Index
                
                Set objCrtAddress = Nothing
                Exit For
            End If
            
            Set objCrtAddress = Nothing
        End If
    Next nIndex
    
    If IsEmpty(nParentNodeIndex) Then
        MsgBox ("ERROR: can't find parent address of new call in <Monitored Calls> tree")
        MCTree_AddNewCall = 1   '1 = error code
        Exit Function
    End If
    
    '
    'add the call as a "child node" of the found address; use the found "index"
    '
    Call LoadCall(tree, treeCollData, nParentNodeIndex, objCallInfo)
    
End Function

Public Function MCTree_RemoveCall( _
    tree As TreeView, _
    treeCollData As Collection, _
    objCallInfo As ITCallInfo) As Long
    
    Dim nNodeIndex As Variant
    nNodeIndex = Empty
    
    '
    'search in tree the node that contains this call and remember its index
    '
    Dim objCrtCallInfo As ITCallInfo
    Dim nIndex As Long
    
    For nIndex = 1 To tree.Nodes.Count
        If tree.Nodes.Item(nIndex).Text = gszCallInfo Then
            'Set objCrtCallInfo = tree.Nodes.Item(nIndex).Tag   'doesn't work
            Set objCrtCallInfo = treeCollData.Item(nIndex)
            
            If objCrtCallInfo Is objCallInfo Then
                nNodeIndex = tree.Nodes.Item(nIndex).Index
                
                Set objCrtCallInfo = Nothing
                Exit For
            End If
            
            Set objCrtCallInfo = Nothing
        End If
    Next nIndex
    
    If IsEmpty(nNodeIndex) Then
        MsgBox ("ERROR: can't find node that contains this call")
        MCTree_RemoveCall = 1   '1 = error code
        Exit Function
    End If
        
    '
    'remove node
    '
    
    Call RemoveNode(tree, treeCollData, nNodeIndex)
    
End Function

Public Function MCTree_IsCallSelected( _
    tree As TreeView, _
    treeCollData As Collection, _
    objCallInfo As ITCallInfo) As Boolean

    MCTree_IsCallSelected = False
    
    Dim objSelNode As Node
    
    Set objSelNode = tree.SelectedItem
    
    If Not (objSelNode Is Nothing) Then
        If objCallInfo Is treeCollData.Item(objSelNode.Index) Then
            MCTree_IsCallSelected = True
        End If
    End If
        
    Set objSelNode = Nothing
    
End Function
                
Public Function MCTree_DisplaySelectedNode( _
    tree As TreeView, _
    treeCollData As Collection) As Long

    Dim objSelNode As Node
    
    Set objSelNode = tree.SelectedItem
    
    're-display information about node (refresh)
    If Not (objSelNode Is Nothing) Then
        Call MCTree_DisplayNode(objSelNode, treeCollData)
    End If
    
    Set objSelNode = Nothing

End Function

Private Function LoadCalls( _
    tree As TreeView, _
    treeCollData As Collection, _
    nParentNodeIndex, _
    objAddress As ITAddress) As Long

    Dim nIndex
    Dim collCalls As ITCollection
    Dim objCrtCallInfo As ITCallInfo
    
    On Error Resume Next
    Set collCalls = objAddress.Calls
    If Err.Number <> 0 Then
        MsgBox ("ERROR: Accessing objAddress.Calls fails!")
        'Err.Clear
        On Error GoTo 0
        Exit Function
    End If
    On Error GoTo 0
    
    For nIndex = 1 To collCalls.Count
        
        Set objCrtCallInfo = collCalls.Item(nIndex)
        
        '
        'check that objCall.Address is the same as objAddress
        '
        If Not (objAddress Is objCrtCallInfo.Address) Then
            MsgBox ("ERROR: MC LoadCalls: invalid objCallInfo.Address")
        End If
        
        '
        'create new node for this call
        '
        Call LoadCall(tree, treeCollData, nParentNodeIndex, objCrtCallInfo)
        
        Set objCrtCallInfo = Nothing
    Next nIndex
    
    Set collCalls = Nothing

End Function

Private Function LoadCall( _
    tree As TreeView, _
    treeCollData As Collection, _
    nParentNodeIndex, _
    objCallInfo As ITCallInfo) As Long
    
    Dim objNewNode As Node
    
    'create new node
    
    Set objNewNode = tree.Nodes.Add( _
        Relative:=nParentNodeIndex, _
        Relationship:=tvwChild, _
        Text:=gszCallInfo)
    objNewNode.EnsureVisible
    
    'save a reference of Call right in the node
    'Set objNewNode.Tag = objCallInfo           'doesn't work
    If objNewNode.Index = 1 Then
        Call treeCollData.Add(Item:=objCallInfo)        'it is the 1st node
    Else
        Call treeCollData.Add(Item:=objCallInfo, after:=objNewNode.Index - 1)
    End If
    
    'assert
    If Not (objCallInfo Is treeCollData.Item(objNewNode.Index)) Then
        MsgBox ("ASSERT: Monitor calls: LoadCalls: node and data have different index")
    End If
        
    'create nodes for all call interfaces that can be queried
    'from this call
    Call LoadCallInterfaces(tree, treeCollData, objNewNode.Index, objCallInfo)

    Set objNewNode = Nothing
End Function

Private Function DisplayAddress(objAddress As ITAddress) As Long
    
    Dim strText As String
    
    strText = _
        "AddressName = " & objAddress.AddressName & _
            Chr(13) & Chr(10) & _
        "ServiceProviderName = " & objAddress.ServiceProviderName & _
            Chr(13) & Chr(10) & _
        "State = " & objAddress.State

    frmCallHubs.txtDescriptionMC.Text = strText
    frmCallHubs.txtDescriptionMC.Refresh

End Function
