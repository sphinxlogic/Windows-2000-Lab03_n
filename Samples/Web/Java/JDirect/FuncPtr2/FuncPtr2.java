/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example demonstrates a more advanced use of the Callback class.
 * In particular, it shows how the DllLib.ptrToStruct() method can be
 * used to get around the limitation that the callback can only take
 * integer parameters. The ptrToStruct() method acts like a C-style cast.
 *
 * 
 */

import com.ms.dll.*;

/** @dll.import("USER32",auto) */
public class FuncPtr2
{
    public static void main(String args[])
    {
        EnumFonts(GetDC(GetDesktopWindow()),
                  null,
                  new SampleEnumFontsProc(),
                  0);
    }



    private static native int GetDesktopWindow();
    private static native int GetDC(int hwnd);

    /** @dll.import("GDI32") */
    private static native int EnumFonts(int           hdc,
                                        String        faceName,
                                        EnumFontsProc wndenfprc,
                                        int           lparam);

}



//----------------------------------------------------------------------
// A specific ENUMFONTPROC. All this does is print the font face name.
//----------------------------------------------------------------------
class SampleEnumFontsProc extends EnumFontsProc
{
    public int enumFontsProc(LOGFONT    pLOGFONT,
                             TEXTMETRIC pTEXTMETRIC,
                             int        dwType,
                             int        lparam)
    {
        System.out.println(pLOGFONT.lfFaceName);
        return 1;  // returning non-zero to continue enumeration.
    }



}


//----------------------------------------------------------------------
// An abstract class used to describe ENUMFONTPROC's in general.
// In particular, it takes care of converting the "callback" arguments
// (which must all be declared as integers), into @dll.struct's for
// easy parsing by the real callback function ("enumFontsProc").
//----------------------------------------------------------------------
abstract class EnumFontsProc extends com.ms.dll.Callback
{
    // It is required that this method be named "callback".
    public int callback(int pLOGFONT, int pTEXTMETRIC, int dwType, int lparam)
    {
        return enumFontsProc((LOGFONT)DllLib.ptrToStruct(LOGFONT.class, pLOGFONT),
                             (TEXTMETRIC)DllLib.ptrToStruct(TEXTMETRIC.class, pTEXTMETRIC),
                             dwType,
                             lparam);
    }

    public abstract int enumFontsProc(LOGFONT    pLOGFONT,
                                      TEXTMETRIC pTEXTMETRIC,
                                      int        dwType,
                                      int        lparam);
}




/** @dll.struct(auto) */
class LOGFONT {
    int     lfHeight;
    int     lfWidth;
    int     lfEscapement;
    int     lfOrientation;
    int     lfWeight;
    byte    lfItalic;
    byte    lfUnderline;
    byte    lfStrikeOut;
    byte    lfCharSet;
    byte    lfOutPrecision;
    byte    lfClipPrecision;
    byte    lfQuality;
    byte    lfPitchAndFamily;

    /** @dll.structmap([type=TCHAR[32]]) */
    String  lfFaceName;
}



/** @dll.struct(auto) */
class TEXTMETRIC
{
    int        tmHeight;
    int        tmAscent;
    int        tmDescent;
    int        tmInternalLeading;
    int        tmExternalLeading;
    int        tmAveCharWidth;
    int        tmMaxCharWidth;
    int        tmWeight;
    int        tmOverhang;
    int        tmDigitizedAspectX;
    int        tmDigitizedAspectY;
    char       tmFirstChar;
    char       tmLastChar;
    char       tmDefaultChar;
    char       tmBreakChar;
    byte       tmItalic;
    byte       tmUnderlined;
    byte       tmStruckOut;
    byte       tmPitchAndFamily;
    byte       tmCharSet;
}

