// -----------------------------------------------------------------------------
// DynArray.h: Template Class that allows you to make a dynamic array of almost 
//             any type or class.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_

// -----------------------------------------------------------------------------
// Use this class to create an array of almost any type or class.  The exception
// is with classes that have construction that does not initialize all data to 
// zero, classes that need destructors, or classes that can not be binary copied.
//
// Once the object is created usage of it is nearly identical to using a regular
// array of that type or class.  See example of usage at the end of this file.
//
// NOTE: When passing an object of CDynamicArray< type> as a parameter for a
//       variable argument list you must type cast it.  This is different usage 
//       from when the parameter is fixed and the compiler knows the type.  
//       See and example of this at the very end of this file.
// 
// -----------------------------------------------------------------------------

template< class TYPE>
class CDynamicArray
{
public:
    // CONSTRUCTOR: Dynamicly creates an array.
    CDynamicArray( ULONG nCnt = 0);
    
    // DESTRUCTOR: Frees the memory that was allocated.
    ~CDynamicArray() {Delete();}

    // Returns a pointer to the TYPE by just specifying the object.
    operator TYPE*() {return( m_ptr);}
    
    // Frees the memory that was allocated.
    void Delete();

    // Frees the memory that was allocated and then allocates a new block.
    void New( ULONG nCnt);

    // Expand the array by nCnt.  Return TRUE if it was expanded.
    BOOL bExpand( ULONG nCnt);

protected:
    TYPE*   m_ptr;  // Pointer to the array you ordered.
    ULONG   m_Size; // Number of items allocated.
};

// $--CDynamicArray< TYPE>::CDynamicArray()-------------------------------------
// CONSTRUCTOR: Dynamicly creates an array.
// -----------------------------------------------------------------------------

template< class TYPE>
CDynamicArray< TYPE>::CDynamicArray(
    ULONG nCnt)     // Initial size of array.  It is okay to pass zero.
{
    m_ptr = NULL;
    m_Size = 0;
    New( nCnt);
}

// $--CDynamicArray< TYPE>::Delete()--------------------------------------------
// Frees the memory that was allocated.
// -----------------------------------------------------------------------------

template< class TYPE>
void CDynamicArray< TYPE>::Delete()
{
    if( m_ptr)
    {
        delete [] m_ptr;
        m_ptr = NULL;
        m_Size = 0;
    }
}

// $--CDynamicArray< TYPE>::New()-----------------------------------------------
// Frees the memory that was allocated and then allocates a new block.
// NOTE: If you already had copy of a pointer to this array you must reload it.
// -----------------------------------------------------------------------------

template< class TYPE>
void CDynamicArray< TYPE>::New( 
    ULONG nCnt)     // Initial size of array.  It is okay to pass zero.
{
    Delete();   // If there was data delete it.
    bExpand( nCnt);
}

// $--CDynamicArray< TYPE>::bExpand()-------------------------------------------
// Expand the array by nCnt.  Return TRUE if it was expanded.
// NOTE: If you already had copy of a pointer to this array you must reload it.
// -----------------------------------------------------------------------------

template< class TYPE>
BOOL CDynamicArray< TYPE>::bExpand( // RETURNS: TRUE if successful.
    ULONG nCnt)                     // Amount to expand array by.
{
    if( !nCnt)
        return( TRUE);  // It is okay to pass zero.

    // Allocate the additonal memory.
    TYPE* pNew = new TYPE[ m_Size + nCnt];
    if( !pNew)
    {   // Could not allocate that much memory.
        HR_LOG( E_OUTOFMEMORY);
        return( FALSE);
    }

    // Is this the first allocation?
    if( m_ptr)
    {   // NO, so copy previous allocation into this block.
        memcpy( pNew, m_ptr, m_Size * sizeof( TYPE));
        delete [] m_ptr;
    }
    
    // Initialize new block of data to zero.
    memset( pNew + m_Size, 0, nCnt * sizeof( TYPE));

    // Adjust working pointers.
    m_ptr = pNew;
    m_Size += nCnt;
    
    return( TRUE);
}

// -----------------------------------------------------------------------------

#ifdef _EXAMPLES_
void TestCDynamicArray()
{
    CDynamicArray< char> Str( 20);      // Construct an array of 20 characters.
    CDynamicArray< int> IntArray( 3);   // Construct an array of 3 integers.

    if( !IntArray || !Str)
        return; // Could not allocate memory.
        
    strcpy( Str, "This is a dynamic test.");

    IntArray[0] = 1;
    IntArray[1] = 2;
    IntArray[2] = 3;

    IntArray.New( 6);       // Free old memory and reallocate 6 integers.
    if( !IntArray)
        return; // Could not allocate memory.

    IntArray[0] = 11;
    IntArray[1] = 12;
    IntArray[2] = 13;
    IntArray[3] = 14;
    IntArray[4] = 15;
    IntArray[5] = 16;

    // Expand array by 4 and bring it to a total size of 10.
    if( !IntArray.bExpand( 4))
        return; // Could not allocate memory.

    IntArray[6] = 17;
    IntArray[7] = 18;
    IntArray[8] = 19;
    IntArray[9] = 20;
        
    CDynamicArray< char> Buf( 100);     // Construct an array of 100 characters.
    if( !Buf)
        return; // Could not allocate memory.
    
    // NOTE: When passing an object of CDynamicArray< type> as a parameter for a
    //       variable argument list you must either type cast it.  This is different 
    //       usage from when the parameter is fixed and the compiler knows the type.  
    //
    //       Notice the difference in the way Buf is used and the way Str is used. The
    //       compiler knows the first parameter is a char* so it can use the opperator
    //       defined in our class to place m_ptr on the stack.  But in the case of Str
    //       The compiler does not know what the expected parameter is supposed to be
    //       so by default it will place the entire class on the stack.  In this case
    //       it would be m_ptr and m_Size.
    sprintf( Buf, "Look at some of the data. %s %d %d", (char*) Str, IntArray[3], IntArray[9]);
}

#endif _EXAMPLES_

// -----------------------------------------------------------------------------
#endif // _DYNARRAY_H_
