// PrValAry.C ------------------------------------------------------------------
// Implementation of a set of functions that maintain a MAPI
// allocated array of property values.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "PrValAry.h"

// -----------------------------------------------------------------------------

HRESULT PVA_HrInit(
    THIS LPPropValArray pva,        // Uninitialized structure to be initialized.
    IN   ULONG          cExpandAmt, // Amount to expand array by when it gets full.
    IN   ULONG          cProps,     // Count of properties in array.
    IN   LPSPropValue   lpPropVal)  // A MAPI allocated array of properties, or NULL.
{
    HRESULT hr = NOERROR;
    ULONG   cb = 0;

    // This will validate the initial property array.
    if( cProps)
    {
        hr = ScCountProps( cProps, lpPropVal, &cb);
        if( FAILED( hr))
            goto cleanup;
    }

    pva->cExpandAmt = cExpandAmt;
    pva->cTotal = cProps;
    pva->cMax = cProps;
    pva->lpPVOrig = lpPropVal;
    pva->lpPropVal = lpPropVal;

cleanup:
    if( FAILED( hr))
        memset( pva, 0, sizeof( PropValArray));

    RETURN( hr);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void PVA_Destroy(
    THIS LPPropValArray pva)        // Structure to be destroyed.
{
    if( pva->lpPropVal != pva->lpPVOrig)
        MAPIFREEBUFFER( pva->lpPropVal);
    MAPIFREEBUFFER( pva->lpPVOrig);
    memset( pva, 0, sizeof( PropValArray));
}

// -----------------------------------------------------------------------------
// This function prepares a property for placement in the property value array.
//
// If the property is a simple type that does not point to data in another 
// location we simply return.
//
// If the propery points to data contained outside of the SPropValue structure
// we make a copy of it using ScCopyProps().  This simplifies our code since 
// there are many different data types and ScCopyProps() handles them all.  We 
// will waste the sizeof( SPropValue) bytes but it is a small price to pay for 
// simple code.
// -----------------------------------------------------------------------------

static HRESULT PVA_HrPrepare(
    THIS    LPPropValArray  pva,        // Array to manipulate
    IN OUT  LPSPropValue*   lppPropVal) // Prop val to prepare for placement in array.
{
    HRESULT         hr           = NOERROR;
    ULONG           cb           = 0;
    ULONG           cBytesCopied = 0;
    LPSPropValue    lpNewPropVal = NULL;

    // Count the bytes needed for the new property.
    hr = ScCountProps( 1, *lppPropVal, &cb);
    if( FAILED( hr))
        goto cleanup;
    
    // Does this entry require extra data space?
    if( cb > sizeof( SPropValue))
    {   // YES, so prepare it.

        // Allocate a new buffer, linked to the original, to hold the copied properties.
        hr = MAPIAllocateMore( cb, pva->lpPVOrig, &lpNewPropVal);
        if( FAILED( hr))
            goto cleanup;
        memset( lpNewPropVal, 0, cb);

        // Copy the subscriber properties to the new buffer.
        hr = ScCopyProps( 1, *lppPropVal, lpNewPropVal, &cBytesCopied);
        if( FAILED( hr))
            goto cleanup;
        ASSERTERROR( cb == cBytesCopied, "ScCountProps & ScCopyProps are inconsistent!");

        // Replace the caller's buffer since we have a copy of the data.
        *lppPropVal = lpNewPropVal;
    }

cleanup:
    RETURN( hr);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

HRESULT PVA_HrInsert(
    THIS LPPropValArray pva,          // Array to manipulate
    IN   ULONG          iProp,        // Index of insertion point.
    IN   LPSPropValue   lpPropVal)    // Property value to insert.
{
    HRESULT         hr           = NOERROR;
    ULONG           cb           = 0;
    ULONG           cBytesCopied = 0;
    LPSPropValue    lpPVSlot     = NULL;
    LPSPropValue    lpNewPropVal = NULL;

    ASSERTERROR( iProp <= pva->cTotal, "Index is too large.");

    // Is the array full?
    if( pva->cTotal == pva->cMax)
    {   // YES, the array is full.
        
        // Increase the maximum size of the array.
        pva->cMax += pva->cExpandAmt;

        // Allocate a new and expanded array.
        cb = pva->cMax * sizeof( SPropValue);
        hr = MAPIAllocateBuffer( cb, &lpNewPropVal);
        if( FAILED( hr))
            goto cleanup;
    
        // Zero newly allocated memory.
        memset( lpNewPropVal, 0, cb);

        // Copy full array into it, if there is something to copy.
        if( pva->lpPropVal)
            MoveMemory( lpNewPropVal, pva->lpPropVal, pva->cTotal * sizeof( SPropValue));

        // If the full array is NOT the original MAPIAllocation free it.  By retaining
        // the original allocation we keep the extra data associated with it but waste
        // the space occupied by the original SPropValue array.  But it is worth this
        // small cost to keep the code simple.
        if( pva->lpPropVal != pva->lpPVOrig)
            MAPIFREEBUFFER( pva->lpPropVal);
        
        // Make the new array allocation the current array.
        pva->lpPropVal = lpNewPropVal;
        if( !pva->lpPVOrig)
            pva->lpPVOrig = lpNewPropVal;
    }

    // Prepare property value to be placed in array.
    hr = PVA_HrPrepare( pva, &lpPropVal);
    if( FAILED( hr))
        goto cleanup;
        
    // Slot to insert new property into.
    lpPVSlot = pva->lpPropVal + iProp;
    
    // Open up a new slot for the property to insert (if not at end).
    if( iProp < pva->cTotal)
        MoveMemory( lpPVSlot + 1, lpPVSlot, (pva->cTotal - iProp) * sizeof( SPropValue));

    // Copy the new property into the array.
    MoveMemory( lpPVSlot, lpPropVal, sizeof( SPropValue));

    // Increment the total array elements used. 
    pva->cTotal ++;

cleanup:
    RETURN( hr);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

HRESULT PVA_HrModify(
    THIS LPPropValArray pva,          // Array to manipulate
    IN   ULONG          iProp,        // Index of insertion point.
    IN   LPSPropValue   lpPropVal)    // Property value to insert.
{
    HRESULT         hr           = NOERROR;

    // Prepare property value to be placed in array.
    hr = PVA_HrPrepare( pva, &lpPropVal);
    if( FAILED( hr))
        goto cleanup;
        
    // Copy the new property into the array.
    MoveMemory( pva->lpPropVal + iProp, lpPropVal, sizeof( SPropValue));

cleanup:
    RETURN( hr);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

HRESULT PVA_HrDelete(
    THIS LPPropValArray pva,          // Array to manipulate
    IN   ULONG          iProp)        // Index of property to delete.
{
    LPSPropValue    lpPVSlot     = NULL;

    // Decrement the total array elements used. 
    pva->cTotal --;
    
    // Pointer to the element to be deleted.
    lpPVSlot = pva->lpPropVal + iProp;

    // Delete the property in the slot.
    if( iProp < pva->cTotal)
        MoveMemory( lpPVSlot, lpPVSlot + 1, (pva->cTotal - iProp) * sizeof( SPropValue));
    
    // Clear the last property in the array.
    memset( pva->lpPropVal + pva->cTotal, 0, sizeof( SPropValue));

    return( NOERROR);
}

// -----------------------------------------------------------------------------
