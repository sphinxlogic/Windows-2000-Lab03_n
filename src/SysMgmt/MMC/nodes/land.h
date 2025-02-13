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

#ifndef _LAND_H
#define _LAND_H

#include "DeleBase.h"

class CLandBasedVehicle : public CDelegationBase {
public:
    CLandBasedVehicle() { }
    
    virtual ~CLandBasedVehicle() {}
    
    virtual const _TCHAR *GetDisplayName(int nCol = 0) { return _T("Land-based Vehicles"); }
    virtual const GUID & getNodeType() { return thisGuid; }
    virtual const int GetBitmapIndex() { return INDEX_LANDICON; }
    
private:
    enum { IDM_NEW_LAND = 2 };
    
    // {2974380E-4C4B-11d2-89D8-000021473128}
    static const GUID thisGuid;
};


#endif // _LAND_H
