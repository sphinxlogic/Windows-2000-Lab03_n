// PrValAry.H ------------------------------------------------------------------
// Declaration of a structure and set of functions that maintain a MAPI
// allocated array of property values.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __PRVALARY_H__
#define __PRVALARY_H__

// -----------------------------------------------------------------------------

#ifdef THIS
#undef THIS
#define THIS    // Documents a parameter type.
#endif

// -----------------------------------------------------------------------------

typedef struct
{
    ULONG           cExpandAmt; // Expand array by this ammount when full.
    ULONG           cTotal;     // Current array total.
    ULONG           cMax;       // Current maximum array will hold.
    LPSPropValue    lpPVOrig;   // Original MAPI allocated array.
    LPSPropValue    lpPropVal;  // Actual array without data unless it equals lpPVOrig.
} PropValArray, *LPPropValArray;

// -----------------------------------------------------------------------------

HRESULT PVA_HrInit(
    THIS LPPropValArray pva,          // Uninitialized structure to be initialized.
    IN   ULONG          cExpandAmt,   // Amount to expand array by when it gets full.
    IN   ULONG          cProps,       // Count of properties in array.
    IN   LPSPropValue   lpPropVal);   // A MAPI allocated array of properties, or NULL.

void PVA_Destroy(
    THIS LPPropValArray pva);         // Structure to be destroyed

HRESULT PVA_HrInsert(
    THIS LPPropValArray pva,          // Array to manipulate
    IN   ULONG          iProp,        // Index of insertion point.
    IN   LPSPropValue   lppPropVal);  // Property value to insert.

HRESULT PVA_HrModify(
    THIS LPPropValArray pva,          // Array to manipulate
    IN   ULONG          iProp,        // Index of insertion point.
    IN   LPSPropValue   lpPropVal);   // Property value to insert.

HRESULT PVA_HrDelete(
    THIS LPPropValArray pva,          // Array to manipulate
    IN   ULONG          iProp);       // Index of property to delete.

// -----------------------------------------------------------------------------

#endif // __PRVALARY_H__
