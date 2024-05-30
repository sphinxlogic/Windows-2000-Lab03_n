#ifndef _e100bdat_h_
#define _e100bdat_h_

// E100BExampleSetUINT_OID - E100BExampleSetUINT_OID
// A UINT to set
#define E100BExampleSetUINT_OIDGuid \
    { 0xf4a80276,0x23b7,0x11d1, { 0x9e,0xd9,0x00,0xa0,0xc9,0x01,0x00,0x57 } }

DEFINE_GUID(E100BExampleSetUINT_OID_GUID, \
            0xf4a80276,0x23b7,0x11d1,0x9e,0xd9,0x00,0xa0,0xc9,0x01,0x00,0x57);


typedef struct _E100BExampleSetUINT_OID
{
    // Set this UINT then query it.
    ULONG ExampleSetUINT_OID;
    #define E100BExampleSetUINT_OID_ExampleSetUINT_OID_SIZE sizeof(ULONG)
    #define E100BExampleSetUINT_OID_ExampleSetUINT_OID_ID 1

} E100BExampleSetUINT_OID, *PE100BExampleSetUINT_OID;

// E100BExampleQueryUINT_OID - E100BExampleQueryUINT_OID
// A UINT to Query
#define E100BExampleQueryUINT_OIDGuid \
    { 0xf4a80277,0x23b7,0x11d1, { 0x9e,0xd9,0x00,0xa0,0xc9,0x01,0x00,0x57 } }

DEFINE_GUID(E100BExampleQueryUINT_OID_GUID, \
            0xf4a80277,0x23b7,0x11d1,0x9e,0xd9,0x00,0xa0,0xc9,0x01,0x00,0x57);


typedef struct _E100BExampleQueryUINT_OID
{
    // Query this UINT and get back the set UINT + 1.
    ULONG ExampleQueryUINT_OID;
    #define E100BExampleQueryUINT_OID_ExampleQueryUINT_OID_SIZE sizeof(ULONG)
    #define E100BExampleQueryUINT_OID_ExampleQueryUINT_OID_ID 1

} E100BExampleQueryUINT_OID, *PE100BExampleQueryUINT_OID;

// E100BExampleQueryArrayOID - E100BExampleQueryArrayOID
// An Array to query (should be 4 bytes of MAC address)
#define E100BExampleQueryArrayOIDGuid \
    { 0xf4a80278,0x23b7,0x11d1, { 0x9e,0xd9,0x00,0xa0,0xc9,0x01,0x00,0x57 } }

DEFINE_GUID(E100BExampleQueryArrayOID_GUID, \
            0xf4a80278,0x23b7,0x11d1,0x9e,0xd9,0x00,0xa0,0xc9,0x01,0x00,0x57);


typedef struct _E100BExampleQueryArrayOID
{
    // Number of array elements.
    ULONG NumberElements;
    #define E100BExampleQueryArrayOID_NumberElements_SIZE sizeof(ULONG)
    #define E100BExampleQueryArrayOID_NumberElements_ID 1

    // Query this array to get 4 bytes of MAC address.
    UCHAR ExampleQueryArray[1];
    #define E100BExampleQueryArrayOID_ExampleQueryArray_ID 2

} E100BExampleQueryArrayOID, *PE100BExampleQueryArrayOID;

// E100BExampleQueryStringOID - E100BExampleQueryStringOID
// An ANSI string to Query
#define E100BExampleQueryStringOIDGuid \
    { 0xf4a80279,0x23b7,0x11d1, { 0x9e,0xd9,0x00,0xa0,0xc9,0x01,0x00,0x57 } }

DEFINE_GUID(E100BExampleQueryStringOID_GUID, \
            0xf4a80279,0x23b7,0x11d1,0x9e,0xd9,0x00,0xa0,0xc9,0x01,0x00,0x57);


typedef struct _E100BExampleQueryStringOID
{
    // Query this to get an ANSI string back (it will be the VENDORDESCRIPTOR string).
    CHAR VariableData[1];
    #define E100BExampleQueryStringOID_ExampleQueryStringOID_ID 1

} E100BExampleQueryStringOID, *PE100BExampleQueryStringOID;

#endif
