//==========================================================================;
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (c) 1997 - 1998  Microsoft Corporation.  All Rights Reserved.
//
//--------------------------------------------------------------------------;

/*  Declare GUIDs */
DEFINE_GUID(CLSID_MultiFileReader,
0xc7de49c0, 0xc750, 0x11d1, 0xb3, 0x0b, 0x24, 0x97, 0x10, 0xc1, 0xaa, 0x07);

DEFINE_GUID(IID_IMultiFileReader,
0x8a0dda00, 0xf3e7, 0x11d1, 0xab, 0xe9, 0x00, 0xa0, 0xc9, 0x05, 0xf3, 0x75);

//  Values for dwFlags
#define AM_MULTIFILE_READER_SEAMLESS 0x01 //  Content matches seamlessly
#define AM_MULTIFILE_READER_LAST     0x02 //  Last file - source
                                          //  will initiate EndOfStream
#define AM_MULTIFILE_READER_FLUSH    0x04 //  Flush for faster switch

DECLARE_INTERFACE_(IMultiFileReader, IUnknown)
{
    STDMETHOD(SetFile) (THIS_ LPCWSTR lpszFile,
                        LONGLONG llOffset,
                        LONGLONG llLength,
                        LONGLONG rtOffset,
                        HWND hwndNotify,
                        UINT uiMsgNotify,
                        WPARAM wParam,
                        HANDLE hEvent,
                        DWORD dwFlags
                        ) PURE;
};
