// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct() */
public class DCB {
        public int DCBlength;
        public int BaudRate;
        public int fBitFields;
        public short wReserved;
        public short XonLim;
        public short XoffLim;
        public byte ByteSize;
        public byte Parity;
        public byte StopBits;
        public char XonChar;
        public char XoffChar;
        public char ErrorChar;
        public char EofChar;
        public char EvtChar;
        public short wReserved1;



        public static final int fBinary           = 0x00000001;
        public static final int fParity           = 0x00000002;
        public static final int fOutxCtsFlow      = 0x00000004;
        public static final int fOutxDsrFlow      = 0x00000008;
        public static final int fDtrControl       = 0x00000030;
        public static final int fDsrSensitivity   = 0x00000040;
        public static final int fTXContinueOnXoff = 0x00000080;
        public static final int fOutX             = 0x00000100;
        public static final int fInX              = 0x00000200;
        public static final int fErrorChar        = 0x00000400;
        public static final int fNull             = 0x00000800;
        public static final int fRtsControl       = 0x00003000;
        public static final int fAbortOnError     = 0x00004000;


}


