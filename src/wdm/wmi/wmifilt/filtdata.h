#ifndef _filtdata_h_
#define _filtdata_h_

// Vendor_EC1 - EC1
// Description of embedeed class 1
#define Vendor_EC1Guid \
    { 0xa1c15015,0xb069,0x11d1, { 0x92,0x90,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EC1_GUID, \
            0xa1c15015,0xb069,0x11d1,0x92,0x90,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _EC1
{
    // boolean data
    BOOLEAN Xboolean;
    #define EC1_Xboolean_SIZE sizeof(BOOLEAN)
    #define EC1_Xboolean_ID 1

    // unsigned character data
    UCHAR Xuint8;
    #define EC1_Xuint8_SIZE sizeof(UCHAR)
    #define EC1_Xuint8_ID 2

    // unsigned short data
    USHORT Xuint16;
    #define EC1_Xuint16_SIZE sizeof(USHORT)
    #define EC1_Xuint16_ID 3

    // unsigned long data
    ULONG Xuint32;
    #define EC1_Xuint32_SIZE sizeof(ULONG)
    #define EC1_Xuint32_ID 4

    // unsigned long long data
    ULONGLONG Xuint64;
    #define EC1_Xuint64_SIZE sizeof(ULONGLONG)
    #define EC1_Xuint64_ID 5

    // signed byte data
    CHAR Xint8;
    #define EC1_Xint8_SIZE sizeof(CHAR)
    #define EC1_Xint8_ID 6

    // singed short data
    SHORT Xint16;
    #define EC1_Xint16_SIZE sizeof(SHORT)
    #define EC1_Xint16_ID 7

    // singed long data
    LONG Xint32;
    #define EC1_Xint32_SIZE sizeof(LONG)
    #define EC1_Xint32_ID 8

    // signed long long data
    LONGLONG Xint64;
    #define EC1_Xint64_SIZE sizeof(LONGLONG)
    #define EC1_Xint64_ID 9

    // absolute or relative date and time
    WCHAR Xdatetime[25];
    #define EC1_Xdatetime_SIZE sizeof(WCHAR[25])
    #define EC1_Xdatetime_ID 10

} EC1, *PEC1;

// Vendor_EC2 - EC2
// Description of embedeed class 2
#define Vendor_EC2Guid \
    { 0xa1c15016,0xb069,0x11d1, { 0x92,0x90,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EC2_GUID, \
            0xa1c15016,0xb069,0x11d1,0x92,0x90,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _EC2
{
    // Fixed length array of 8 booleans
    BOOLEAN Xboolean[8];
    #define EC2_Xboolean_SIZE sizeof(BOOLEAN[8])
    #define EC2_Xboolean_ID 1

    // Fixed length array of 8 unsigned characters
    UCHAR Xuint8[8];
    #define EC2_Xuint8_SIZE sizeof(UCHAR[8])
    #define EC2_Xuint8_ID 2

    // Fixed length array of 4 unsigned shorts
    USHORT Xuint16[4];
    #define EC2_Xuint16_SIZE sizeof(USHORT[4])
    #define EC2_Xuint16_ID 3

    // Fixed length array of 2 usingned long
    ULONG Xuint32[2];
    #define EC2_Xuint32_SIZE sizeof(ULONG[2])
    #define EC2_Xuint32_ID 4

    // Unsigned long long
    ULONGLONG Xuint64;
    #define EC2_Xuint64_SIZE sizeof(ULONGLONG)
    #define EC2_Xuint64_ID 5

    // Fixed length array of 8 signed characters
    CHAR Xint8[8];
    #define EC2_Xint8_SIZE sizeof(CHAR[8])
    #define EC2_Xint8_ID 6

    // Fixed length array of 4 signed short
    SHORT Xint16[4];
    #define EC2_Xint16_SIZE sizeof(SHORT[4])
    #define EC2_Xint16_ID 7

    // Fixed length array of 2 signed long
    LONG Xint32[2];
    #define EC2_Xint32_SIZE sizeof(LONG[2])
    #define EC2_Xint32_ID 8

    // Signed long long
    LONGLONG Xint64;
    #define EC2_Xint64_SIZE sizeof(LONGLONG)
    #define EC2_Xint64_ID 9

    // absolute or relative date and time
    WCHAR Xdatetime[25];
    #define EC2_Xdatetime_SIZE sizeof(WCHAR[25])
    #define EC2_Xdatetime_ID 10

} EC2, *PEC2;

// Vendor_SampleClass1 - Vendor_SampleClass1
// Description of sample class 1
#define Vendor_SampleClass1Guid \
    { 0x15d851f1,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_SampleClass1_GUID, \
            0x15d851f1,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_SampleClass1
{
    // boolean data
    BOOLEAN Xboolean;
    #define Vendor_SampleClass1_Xboolean_SIZE sizeof(BOOLEAN)
    #define Vendor_SampleClass1_Xboolean_ID 1

    // unsigned character data
    UCHAR Xuint8;
    #define Vendor_SampleClass1_Xuint8_SIZE sizeof(UCHAR)
    #define Vendor_SampleClass1_Xuint8_ID 2

    // unsigned short data
    USHORT Xuint16;
    #define Vendor_SampleClass1_Xuint16_SIZE sizeof(USHORT)
    #define Vendor_SampleClass1_Xuint16_ID 3

    // unsigned long data
    ULONG Xuint32;
    #define Vendor_SampleClass1_Xuint32_SIZE sizeof(ULONG)
    #define Vendor_SampleClass1_Xuint32_ID 4

    // unsigned long long data
    ULONGLONG Xuint64;
    #define Vendor_SampleClass1_Xuint64_SIZE sizeof(ULONGLONG)
    #define Vendor_SampleClass1_Xuint64_ID 5

    // signed byte data
    CHAR Xint8;
    #define Vendor_SampleClass1_Xint8_SIZE sizeof(CHAR)
    #define Vendor_SampleClass1_Xint8_ID 6

    // singed short data
    SHORT Xint16;
    #define Vendor_SampleClass1_Xint16_SIZE sizeof(SHORT)
    #define Vendor_SampleClass1_Xint16_ID 7

    // singed long data
    LONG Xint32;
    #define Vendor_SampleClass1_Xint32_SIZE sizeof(LONG)
    #define Vendor_SampleClass1_Xint32_ID 8

    // signed long long data
    LONGLONG Xint64;
    #define Vendor_SampleClass1_Xint64_SIZE sizeof(LONGLONG)
    #define Vendor_SampleClass1_Xint64_ID 9

    // absolute or relative date and time
    WCHAR Xdatetime[25];
    #define Vendor_SampleClass1_Xdatetime_SIZE sizeof(WCHAR[25])
    #define Vendor_SampleClass1_Xdatetime_ID 10

} Vendor_SampleClass1, *PVendor_SampleClass1;

// Vendor_SampleClass2 - Vendor_SampleClass2
// Description of Sample Class 2
#define Vendor_SampleClass2Guid \
    { 0x15d851f2,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_SampleClass2_GUID, \
            0x15d851f2,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_SampleClass2
{
    // Embedded class data
    EC1 EmbeddedClass1;
    #define Vendor_SampleClass2_EmbeddedClass1_SIZE sizeof(EC1)
    #define Vendor_SampleClass2_EmbeddedClass1_ID 1

} Vendor_SampleClass2, *PVendor_SampleClass2;

// Vendor_SampleClass3 - Vendor_SampleClass3
// Description of Sample Class 3
#define Vendor_SampleClass3Guid \
    { 0x15d851f3,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_SampleClass3_GUID, \
            0x15d851f3,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_SampleClass3
{
    // FIxed length array of 4 embedded classes
    EC1 EmbeddedClass1[4];
    #define Vendor_SampleClass3_EmbeddedClass1_SIZE sizeof(EC1[4])
    #define Vendor_SampleClass3_EmbeddedClass1_ID 1

} Vendor_SampleClass3, *PVendor_SampleClass3;

// Vendor_SampleClass4 - Vendor_SampleClass4
// Description of Sample Class 4
#define Vendor_SampleClass4Guid \
    { 0x15d851f4,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_SampleClass4_GUID, \
            0x15d851f4,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_SampleClass4
{
    // Number of elements in array
    ULONG Count;
    #define Vendor_SampleClass4_Count_SIZE sizeof(ULONG)
    #define Vendor_SampleClass4_Count_ID 1

    // Variable length array of embedded classes. Count specifies the number of elements in the array
    EC1 EmbeddedClass1[1];
    #define Vendor_SampleClass4_EmbeddedClass1_ID 2

} Vendor_SampleClass4, *PVendor_SampleClass4;

// Vendor_SampleClass5 - Vendor_SampleClass5
// Description of Sample Class 5
#define Vendor_SampleClass5Guid \
    { 0x15d851f5,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_SampleClass5_GUID, \
            0x15d851f5,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_SampleClass5
{
    // Embedded class data
    EC2 EmbeddedClass2;
    #define Vendor_SampleClass5_EmbeddedClass2_SIZE sizeof(EC2)
    #define Vendor_SampleClass5_EmbeddedClass2_ID 1

} Vendor_SampleClass5, *PVendor_SampleClass5;

// Vendor_SampleClass6 - Vendor_SampleClass6
// Description of Sample Class 6
#define Vendor_SampleClass6Guid \
    { 0x15d851f6,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_SampleClass6_GUID, \
            0x15d851f6,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_SampleClass6
{
    // Fixed length array of 4 embedded classes
    EC2 EmbeddedClass2[4];
    #define Vendor_SampleClass6_EmbeddedClass2_SIZE sizeof(EC2[4])
    #define Vendor_SampleClass6_EmbeddedClass2_ID 1

} Vendor_SampleClass6, *PVendor_SampleClass6;

// Vendor_SampleClass7 - Vendor_SampleClass7
// Description of Sample Class 7
#define Vendor_SampleClass7Guid \
    { 0x15d851f7,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_SampleClass7_GUID, \
            0x15d851f7,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_SampleClass7
{
    // Number of elements in array
    ULONG Count;
    #define Vendor_SampleClass7_Count_SIZE sizeof(ULONG)
    #define Vendor_SampleClass7_Count_ID 1

    // Variable length array of embedded classes. Count specifies the number of elements in the array
    EC2 EmbeddedClass2[1];
    #define Vendor_SampleClass7_EmbeddedClass2_ID 2

} Vendor_SampleClass7, *PVendor_SampleClass7;

// Vendor_GetSetData - Vendor_GetSetData
// Methods that can get and set data
#define Vendor_GetSetDataGuid \
    { 0x15d851f8,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_GetSetData_GUID, \
            0x15d851f8,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);

//
// Method id definitions for Vendor_GetSetData
#define SetEC1     1
#define SetEC2     2
#define GetEC1     3
#define GetEC2     4
#define DisableSampleClass7     5
#define EnableSampleClass7     6
#define SetEC1AsEc     7
#define SetEC2AsEc     8
#define GetEC1AsEc     9
#define GetEC2AsEc     10
#define UnregisterFromWmi     11

// Warning: Header for class Vendor_GetSetData cannot be created
typedef struct _Vendor_GetSetData
{
    char VariableData[1];

} Vendor_GetSetData, *PVendor_GetSetData;

// Vendor_EventClass1 - Vendor_EventClass1
// Event containing data
#define Vendor_EventClass1Guid \
    { 0x15d851e1,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EventClass1_GUID, \
            0x15d851e1,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_EventClass1
{
    // boolean data
    BOOLEAN Xboolean;
    #define Vendor_EventClass1_Xboolean_SIZE sizeof(BOOLEAN)
    #define Vendor_EventClass1_Xboolean_ID 1

    // unsigned character data
    UCHAR Xuint8;
    #define Vendor_EventClass1_Xuint8_SIZE sizeof(UCHAR)
    #define Vendor_EventClass1_Xuint8_ID 2

    // unsigned short data
    USHORT Xuint16;
    #define Vendor_EventClass1_Xuint16_SIZE sizeof(USHORT)
    #define Vendor_EventClass1_Xuint16_ID 3

    // unsigned long data
    ULONG Xuint32;
    #define Vendor_EventClass1_Xuint32_SIZE sizeof(ULONG)
    #define Vendor_EventClass1_Xuint32_ID 4

    // unsigned long long data
    ULONGLONG Xuint64;
    #define Vendor_EventClass1_Xuint64_SIZE sizeof(ULONGLONG)
    #define Vendor_EventClass1_Xuint64_ID 5

    // signed byte data
    CHAR Xint8;
    #define Vendor_EventClass1_Xint8_SIZE sizeof(CHAR)
    #define Vendor_EventClass1_Xint8_ID 6

    // singed short data
    SHORT Xint16;
    #define Vendor_EventClass1_Xint16_SIZE sizeof(SHORT)
    #define Vendor_EventClass1_Xint16_ID 7

    // singed long data
    LONG Xint32;
    #define Vendor_EventClass1_Xint32_SIZE sizeof(LONG)
    #define Vendor_EventClass1_Xint32_ID 8

    // signed long long data
    LONGLONG Xint64;
    #define Vendor_EventClass1_Xint64_SIZE sizeof(LONGLONG)
    #define Vendor_EventClass1_Xint64_ID 9

    // absolute or relative date and time
    WCHAR Xdatetime[25];
    #define Vendor_EventClass1_Xdatetime_SIZE sizeof(WCHAR[25])
    #define Vendor_EventClass1_Xdatetime_ID 10

} Vendor_EventClass1, *PVendor_EventClass1;

// Vendor_EventClass2 - Vendor_EventClass2
// Event containing embedded class 1
#define Vendor_EventClass2Guid \
    { 0x15d851e2,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EventClass2_GUID, \
            0x15d851e2,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_EventClass2
{
    // Embedded class data
    EC1 EmbeddedClass1;
    #define Vendor_EventClass2_EmbeddedClass1_SIZE sizeof(EC1)
    #define Vendor_EventClass2_EmbeddedClass1_ID 1

} Vendor_EventClass2, *PVendor_EventClass2;

// Vendor_EventClass3 - Vendor_EventClass3
// Event containing a fixed length array embedded class 1
#define Vendor_EventClass3Guid \
    { 0x15d851e3,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EventClass3_GUID, \
            0x15d851e3,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_EventClass3
{
    // Fixed length array of 4 embedded classes
    EC1 EmbeddedClass1[4];
    #define Vendor_EventClass3_EmbeddedClass1_SIZE sizeof(EC1[4])
    #define Vendor_EventClass3_EmbeddedClass1_ID 1

} Vendor_EventClass3, *PVendor_EventClass3;

// Vendor_EventClass4 - Vendor_EventClass4
// Event containing a variable length array embedded class 1
#define Vendor_EventClass4Guid \
    { 0x15d851e4,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EventClass4_GUID, \
            0x15d851e4,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_EventClass4
{
    // Number of elements in array
    ULONG Count;
    #define Vendor_EventClass4_Count_SIZE sizeof(ULONG)
    #define Vendor_EventClass4_Count_ID 1

    // Variable length array of embedded classes. Count specifies the number of elements in the array
    EC1 EmbeddedClass1[1];
    #define Vendor_EventClass4_EmbeddedClass1_ID 2

} Vendor_EventClass4, *PVendor_EventClass4;

// Vendor_EventClass5 - Vendor_EventClass5
// Event containing embedded class 2
#define Vendor_EventClass5Guid \
    { 0x15d851e5,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EventClass5_GUID, \
            0x15d851e5,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_EventClass5
{
    // 
    EC2 EmbeddedClass2;
    #define Vendor_EventClass5_EmbeddedClass2_SIZE sizeof(EC2)
    #define Vendor_EventClass5_EmbeddedClass2_ID 1

} Vendor_EventClass5, *PVendor_EventClass5;

// Vendor_EventClass6 - Vendor_EventClass6
// Event containing a fixed length array of embedded class 2
#define Vendor_EventClass6Guid \
    { 0x15d851e6,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EventClass6_GUID, \
            0x15d851e6,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_EventClass6
{
    // 
    EC2 EmbeddedClass2[4];
    #define Vendor_EventClass6_EmbeddedClass2_SIZE sizeof(EC2[4])
    #define Vendor_EventClass6_EmbeddedClass2_ID 1

} Vendor_EventClass6, *PVendor_EventClass6;

// Vendor_EventClass7 - Vendor_EventClass7
// Event containing a variable length array of embedded class 2
#define Vendor_EventClass7Guid \
    { 0x15d851e7,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EventClass7_GUID, \
            0x15d851e7,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_EventClass7
{
    // Number of elements in array
    ULONG Count;
    #define Vendor_EventClass7_Count_SIZE sizeof(ULONG)
    #define Vendor_EventClass7_Count_ID 1

    // Variable length array of embedded classes. Count specifies the number of elements in the array
    EC2 EmbeddedClass2[1];
    #define Vendor_EventClass7_EmbeddedClass2_ID 2

} Vendor_EventClass7, *PVendor_EventClass7;

// Vendor_EventReferenceClass - Vendor_EventReferenceClass
// Event used to illustrate an event reference
#define Vendor_EventReferenceClassGuid \
    { 0x15d851e8,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_EventReferenceClass_GUID, \
            0x15d851e8,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);


typedef struct _Vendor_EventReferenceClass
{
    // boolean data
    BOOLEAN Xboolean;
    #define Vendor_EventReferenceClass_Xboolean_SIZE sizeof(BOOLEAN)
    #define Vendor_EventReferenceClass_Xboolean_ID 1

    // unsigned character data
    UCHAR Xuint8;
    #define Vendor_EventReferenceClass_Xuint8_SIZE sizeof(UCHAR)
    #define Vendor_EventReferenceClass_Xuint8_ID 2

    // unsigned short data
    USHORT Xuint16;
    #define Vendor_EventReferenceClass_Xuint16_SIZE sizeof(USHORT)
    #define Vendor_EventReferenceClass_Xuint16_ID 3

    // unsigned long data
    ULONG Xuint32;
    #define Vendor_EventReferenceClass_Xuint32_SIZE sizeof(ULONG)
    #define Vendor_EventReferenceClass_Xuint32_ID 4

    // unsigned long long data
    ULONGLONG Xuint64;
    #define Vendor_EventReferenceClass_Xuint64_SIZE sizeof(ULONGLONG)
    #define Vendor_EventReferenceClass_Xuint64_ID 5

    // signed byte data
    CHAR Xint8;
    #define Vendor_EventReferenceClass_Xint8_SIZE sizeof(CHAR)
    #define Vendor_EventReferenceClass_Xint8_ID 6

    // singed short data
    SHORT Xint16;
    #define Vendor_EventReferenceClass_Xint16_SIZE sizeof(SHORT)
    #define Vendor_EventReferenceClass_Xint16_ID 7

    // singed long data
    LONG Xint32;
    #define Vendor_EventReferenceClass_Xint32_SIZE sizeof(LONG)
    #define Vendor_EventReferenceClass_Xint32_ID 8

    // signed long long data
    LONGLONG Xint64;
    #define Vendor_EventReferenceClass_Xint64_SIZE sizeof(LONGLONG)
    #define Vendor_EventReferenceClass_Xint64_ID 9

    // absolute or relative date and time
    WCHAR Xdatetime[25];
    #define Vendor_EventReferenceClass_Xdatetime_SIZE sizeof(WCHAR[25])
    #define Vendor_EventReferenceClass_Xdatetime_ID 10

} Vendor_EventReferenceClass, *PVendor_EventReferenceClass;

// Vendor_FireEvent - Vendor_FireEvent
// Method that fire events
#define Vendor_FireEventGuid \
    { 0x15d851f9,0x6539,0x11d1, { 0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10 } }

DEFINE_GUID(Vendor_FireEvent_GUID, \
            0x15d851f9,0x6539,0x11d1,0xa5,0x29,0x00,0xa0,0xc9,0x06,0x29,0x10);

//
// Method id definitions for Vendor_FireEvent
#define FireEvent     1

// Warning: Header for class Vendor_FireEvent cannot be created
typedef struct _Vendor_FireEvent
{
    char VariableData[1];

} Vendor_FireEvent, *PVendor_FireEvent;

#endif
