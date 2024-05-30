//==============================================================;
//
//	This source code is only intended as a supplement to 
//  existing Microsoft documentation. 
//
//	Use of this code is NOT supported.  
//
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
//
//    Microsoft Premier Support for Developers
//
//==============================================================;

#include "StatNode.h"

const GUID CStaticNode::thisGuid = { 0x2974380c, 0x4c4b, 0x11d2, { 0x89, 0xd8, 0x0, 0x0, 0x21, 0x47, 0x31, 0x28 } };

//==============================================================
//
// CStaticNode implementation
//
//
CStaticNode::CStaticNode()
{
}

CStaticNode::~CStaticNode()
{
}

HRESULT CStaticNode::OnShowContextHelp(IDisplayHelp *pDisplayHelp, LPOLESTR helpFile)
{
    _TCHAR topicName[MAX_PATH];
    
    _tcscpy(topicName, helpFile);
    
    // we should read this from a resource file
    _tcscat(topicName, _T("::/default.htm"));
    
    LPOLESTR pszTopic = static_cast<LPOLESTR>(CoTaskMemAlloc((_tcslen(topicName) + 1) * sizeof(_TCHAR)));
    
    _tcscpy(pszTopic, topicName);
    
    return pDisplayHelp->ShowTopic(pszTopic);
}
