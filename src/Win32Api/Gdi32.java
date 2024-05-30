// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;

/** @security(checkClassLinking=on) */
public class Gdi32 {
        /** @dll.import("GDI32",auto) */
        public native static int AbortDoc (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean AbortPath (int anonymous0);

        /** @dll.import("GDI32", auto) */
        public native static int AddFontResource (String anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean AngleArc (int anonymous0, int anonymous1, int anonymous2, int anonymous3, float anonymous4, float anonymous5);

        /** @dll.import("GDI32",auto) */
        public native static boolean AnimatePalette (int anonymous0, int anonymous1, int anonymous2, byte[] anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean Arc (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5, int anonymous6, int anonymous7, int anonymous8);

        /** @dll.import("GDI32",auto) */
        public native static boolean ArcTo (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5, int anonymous6, int anonymous7, int anonymous8);

        /** @dll.import("GDI32",auto) */
        public native static boolean BeginPath (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean BitBlt (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5, int anonymous6, int anonymous7, int anonymous8);

        /** @dll.import("GDI32",auto) */
        public native static boolean CancelDC (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean CheckColorsInGamut (int anonymous0, int anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int ChoosePixelFormat (int anonymous0, PIXELFORMATDESCRIPTOR anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean Chord (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5, int anonymous6, int anonymous7, int anonymous8);

        /** @dll.import("GDI32",auto) */
        public native static int CloseEnhMetaFile (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean CloseFigure (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CloseMetaFile (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean ColorMatchToTarget (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int CombineRgn (int anonymous0, int anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean CombineTransform (XFORM anonymous0, XFORM anonymous1, XFORM anonymous2);

        /** @dll.import("GDI32", auto) */
        public native static int CopyEnhMetaFile (int anonymous0, String anonymous1);

        /** @dll.import("GDI32", auto) */
        public native static int CopyMetaFile (int anonymous0, String anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int CreateBitmap (int anonymous0, int anonymous1, int anonymous2, int anonymous3, byte[] anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static int CreateBitmap (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static int CreateBitmapIndirect (BITMAP anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreateBrushIndirect (LOGBRUSH anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreateColorSpace (LOGCOLORSPACE anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreateCompatibleBitmap (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int CreateCompatibleDC (int anonymous0);

        /** @dll.import("GDI32", auto) */
        public native static int CreateDC (String anonymous0, String anonymous1, String anonymous2, DEVMODE anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int CreateDIBPatternBrush (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int CreateDIBPatternBrushPt (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int CreateDIBSection (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5);

        /** @dll.import("GDI32",auto) */
        public native static int CreateDIBitmap (int anonymous0, int anonymous1, int anonymous2, int[] anonymous3, int anonymous4, int anonymous5);

        /** @dll.import("GDI32",auto) */
        public native static int CreateDiscardableBitmap (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int CreateEllipticRgn (int anonymous0, int anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int CreateEllipticRgnIndirect (RECT anonymous0);

        /** @dll.import("GDI32", auto) */
        public native static int CreateEnhMetaFile (int anonymous0, String anonymous1, RECT anonymous2, String anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int CreateFontIndirect (LOGFONT anonymous0);

        /** @dll.import("GDI32", auto) */
        public native static int CreateFont (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5, int anonymous6, int anonymous7, int anonymous8, int anonymous9, int anonymous10, int anonymous11, int anonymous12, String anonymous13);

        /** @dll.import("GDI32",auto) */
        public native static int CreateHalftonePalette (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreateHatchBrush (int anonymous0, int anonymous1);

        /** @dll.import("GDI32", auto) */
        public native static int CreateIC (String anonymous0, String anonymous1, String anonymous2, DEVMODE anonymous3);

        /** @dll.import("GDI32", auto) */
        public native static int CreateMetaFile (String anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreatePalette (LOGPALETTE anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreatePatternBrush (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreatePen (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int CreatePenIndirect (LOGPEN anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreatePolyPolygonRgn (int[] anonymous0, int[] anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int CreatePolygonRgn (int[] anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int CreateRectRgn (int anonymous0, int anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int CreateRectRgnIndirect (RECT anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int CreateRoundRectRgn (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5);

        /** @dll.import("GDI32", auto) */
        public native static boolean CreateScalableFontResource (int anonymous0, String anonymous1, String anonymous2, String anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int CreateSolidBrush (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean DPtoLP (int anonymous0, POINT anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean DPtoLP (int anonymous0, int[] anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean DeleteColorSpace (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean DeleteDC (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean DeleteEnhMetaFile (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean DeleteMetaFile (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean DeleteObject (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int DescribePixelFormat (int anonymous0, int anonymous1, int anonymous2, PIXELFORMATDESCRIPTOR anonymous3);

        /** @dll.import("GDI32", ansi) */
        public native static int DrawEscape (int anonymous0, int anonymous1, int anonymous2, String anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean Ellipse (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static int EndDoc (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int EndPage (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean EndPath (int anonymous0);

//        /** @dll.import("GDI32",auto) */
//        public native static boolean EnumEnhMetaFile (int hdc, int henf, ENHMFENUMPROC lpEnhMetaFunc, int lpData, RECT lpcRect);

        /** @dll.import("GDI32",auto) */
        public native static int EnumFontFamiliesEx (int hdc, LOGFONT lpLogfont, EnumFontFamExProc lpEnumFontFamExProc, int lParam, int dwFlags);

        /** @dll.import("GDI32", auto) */
        public native static int EnumFontFamilies (int hdc, String lpszFamily, FONTENUMPROC lpEnumFontFamProc, int lParam);

        /** @dll.import("GDI32", auto) */
        public native static int EnumFonts (int hdc, String lpFaceName, FONTENUMPROC lpFontFunc, int lParam);

        /** @dll.import("GDI32",auto) */
        public native static int EnumICMProfiles (int hdc, ICMENUMPROC lpICMEnumFunc, int lParam);

//        /** @dll.import("GDI32",auto) */
//        public native static boolean EnumMetaFile (int hdc, int hmf, MFENUMPROC lpMetaFunc, int lParam);

        /** @dll.import("GDI32",auto) */
        public native static int EnumObjects (int hdc, int nObjectType, GOBJENUMPROCBRUSH lpBrushFunc, int lParam);

        /** @dll.import("GDI32",auto) */
        public native static int EnumObjects (int hdc, int nObjectType, GOBJENUMPROCPEN lpPenFunc, int lParam);

        /** @dll.import("GDI32",auto) */
        public native static boolean EqualRgn (int anonymous0, int anonymous1);

        /** @dll.import("GDI32", setLastError) */
        public native static int Escape (int hdc, int nEscape, int cbInput, Object lpvInData, Object lpvOutData);

        /** @dll.import("GDI32",auto) */
        public native static int ExcludeClipRect (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static int ExtCreatePen (int anonymous0, int anonymous1, LOGBRUSH anonymous2, int anonymous3, int[] anonymous4);



        /** @dll.import("GDI32", setLastError) */
        public native static int ExtEscape (int hdc, int nEscape, int cbInput, Object lpszInData, int cbOutput, Object lpszOutData);

        /** @dll.import("GDI32",auto) */
        public native static boolean ExtFloodFill (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static int ExtSelectClipRgn (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32", auto) */
        public native static boolean ExtTextOut (int anonymous0, int anonymous1, int anonymous2, int anonymous3, RECT anonymous4, String anonymous5, int anonymous6, int[] anonymous7);

        /** @dll.import("GDI32",auto) */
        public native static boolean FillPath (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean FillRgn (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean FixBrushOrgEx (int anonymous0, int anonymous1, int anonymous2, POINT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean FlattenPath (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean FloodFill (int anonymous0, int anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean FrameRgn (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static boolean GdiComment (int anonymous0, int anonymous1, byte[] anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean GdiFlush ();

        /** @dll.import("GDI32",auto) */
        public native static int GdiGetBatchLimit ();

        /** @dll.import("GDI32",auto) */
        public native static int GdiSetBatchLimit (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetArcDirection (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetAspectRatioFilterEx (int anonymous0, SIZE anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetBitmapBits (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetBitmapDimensionEx (int anonymous0, SIZE anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetBkColor (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetBkMode (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetBoundsRect (int anonymous0, RECT anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetBrushOrgEx (int anonymous0, POINT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetCharABCWidthsFloat (int anonymous0, int anonymous1, int anonymous2, ABCFLOAT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetCharABCWidths (int anonymous0, int anonymous1, int anonymous2, ABC anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetCharWidth32 (int anonymous0, int anonymous1, int anonymous2, int[] anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetCharWidthFloat (int anonymous0, int anonymous1, int anonymous2, float[] anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetCharWidth (int anonymous0, int anonymous1, int anonymous2, int[] anonymous3);

        /** @dll.import("GDI32", auto) */
        public native static int GetCharacterPlacement (int anonymous0, String anonymous1, int anonymous2, int anonymous3, GCP_RESULTS anonymous4, int anonymous5);

        /** @dll.import("GDI32",auto) */
        public native static int GetClipBox (int anonymous0, RECT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetClipRgn (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetColorAdjustment (int anonymous0, COLORADJUSTMENT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetColorSpace (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetCurrentObject (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetCurrentPositionEx (int anonymous0, POINT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetDCOrgEx (int anonymous0, POINT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetDIBColorTable (int anonymous0, int anonymous1, int anonymous2, byte[] anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int GetDIBits (int hdc, int hbmp, int uStartScan, int cScanLines, int /* ptr to bit buffer */ lpvBits, int /* BITMAPINFO */ lpbi, int uUsage);

        /** @dll.import("GDI32",auto) */
        public native static int GetDeviceCaps (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetDeviceGammaRamp (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetEnhMetaFileBits (int hemf, int cbBuffer, byte[] lpbBuffer);

        /** @dll.import("GDI32", auto) */
        public native static int GetEnhMetaFileDescription (int anonymous0, int anonymous1, StringBuffer anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int GetEnhMetaFileHeader (int anonymous0, int anonymous1, ENHMETAHEADER anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int GetEnhMetaFilePaletteEntries (int anonymous0, int anonymous1, byte[] anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int GetEnhMetaFilePixelFormat (int anonymous0, int anonymous1, PIXELFORMATDESCRIPTOR anonymous2);

        /** @dll.import("GDI32", auto) */
        public native static int GetEnhMetaFile (String anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetFontData (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static int GetFontLanguageInfo (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetGlyphOutline (int anonymous0, int anonymous1, int anonymous2, GLYPHMETRICS anonymous3, int anonymous4, int anonymous5, MAT2 anonymous6);

        /** @dll.import("GDI32",auto) */
        public native static int GetGraphicsMode (int anonymous0);

        /** @dll.import("GDI32", auto) */
        public native static boolean GetICMProfile (int anonymous0, int[] anonymous1, StringBuffer anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int GetKerningPairs (int hdc, int nNumPairs, Object lpkrnpair);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetLogColorSpace (int anonymous0, LOGCOLORSPACE anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int GetMapMode (int hdc);

        /** @dll.import("GDI32",auto) */
        public native static int GetMetaFileBitsEx (int hmf, int nSize, Object lpvData);

        /** @dll.import("GDI32", auto) */
        public native static int GetMetaFile (String anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetMetaRgn (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetMiterLimit (int anonymous0, float[] anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetNearestColor (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetNearestPaletteIndex (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetObjectType (int h);

        /** @dll.import("GDI32",auto) */
        public native static int GetObject (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int GetOutlineTextMetrics (int anonymous0, int anonymous1, Object anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int GetPaletteEntries (int anonymous0, int anonymous1, int anonymous2, byte[] anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int GetPath (int anonymous0, int[] anonymous1, byte[] anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int GetPixel (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int GetPixelFormat (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetPolyFillMode (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetROP2 (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetRasterizerCaps (RASTERIZER_STATUS anonymous0, int anonymous1);



        /** @dll.import("GDI32",auto) */
        public native static int GetRgnBox (int anonymous0, RECT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetStockObject (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetStretchBltMode (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetSystemPaletteEntries (int anonymous0, int anonymous1, int anonymous2, byte[] anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int GetSystemPaletteUse (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetTextAlign (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetTextCharacterExtra (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int GetTextCharset (int hdc);

        /** @dll.import("GDI32",auto) */
        public native static int GetTextCharsetInfo (int hdc, FONTSIGNATURE lpSig, int dwFlags);

        /** @dll.import("GDI32",auto) */
        public native static int GetTextColor (int anonymous0);

        /** @dll.import("GDI32", auto) */
        public native static boolean GetTextExtentExPoint (int anonymous0, String anonymous1, int anonymous2, int anonymous3, int[] anonymous4, int[] anonymous5, SIZE anonymous6);

        /** @dll.import("GDI32", auto) */
        public native static boolean GetTextExtentPoint32 (int anonymous0, String anonymous1, int anonymous2, SIZE anonymous3);

        /** @dll.import("GDI32", auto) */
        public native static boolean GetTextExtentPoint (int anonymous0, String anonymous1, int anonymous2, SIZE anonymous3);

        /** @dll.import("GDI32", auto) */
        public native static int GetTextFace (int anonymous0, int anonymous1, StringBuffer anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetTextMetrics (int anonymous0, TEXTMETRIC anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetViewportExtEx (int anonymous0, SIZE anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetViewportOrgEx (int anonymous0, POINT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int GetWinMetaFileBits (int hemf, int cbBuffer, byte[] lpbBuffer, int fnMapMode, int hdcRef);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetWindowExtEx (int anonymous0, SIZE anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetWindowOrgEx (int anonymous0, POINT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean GetWorldTransform (int anonymous0, XFORM anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int IntersectClipRect (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static boolean InvertRgn (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean LPtoDP (int anonymous0, POINT anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean LPtoDP (int anonymous0, int[] anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean LineDDA (int nXStart, int nYStart, int nXEnd, int nYEnd, LINEDDAPROC lpLineFunc, int lpData);

        /** @dll.import("GDI32",auto) */
        public native static boolean LineTo (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean MaskBlt (int hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int hdcSrc, int nXSrc, int nYSrc, int hbmMask, int xMask, int yMask, int dwRop);

        /** @dll.import("GDI32",auto) */
        public native static boolean ModifyWorldTransform (int anonymous0, XFORM anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean MoveToEx (int anonymous0, int anonymous1, int anonymous2, POINT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int OffsetClipRgn (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int OffsetRgn (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean OffsetViewportOrgEx (int anonymous0, int anonymous1, int anonymous2, POINT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean OffsetWindowOrgEx (int anonymous0, int anonymous1, int anonymous2, POINT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean PaintRgn (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean PatBlt (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5);

        /** @dll.import("GDI32",auto) */
        public native static int PathToRegion (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean Pie (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5, int anonymous6, int anonymous7, int anonymous8);

        /** @dll.import("GDI32",auto) */
        public native static boolean PlayEnhMetaFile (int anonymous0, int anonymous1, RECT anonymous2);



        /** @dll.import("GDI32",auto) */
        public native static boolean PlayMetaFile (int anonymous0, int anonymous1);



        /** @dll.import("GDI32",auto) */
        public native static boolean PlgBlt (int anonymous0, int[] anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5, int anonymous6, int anonymous7, int anonymous8, int anonymous9);

        /** @dll.import("GDI32",auto) */
        public native static boolean PolyBezier (int hdc, int[] lppt, int cPoints);

        /** @dll.import("GDI32",auto) */
        public native static boolean PolyBezierTo (int hdc, int[] lppt, int cCount);

        /** @dll.import("GDI32",auto) */
        public native static boolean PolyDraw (int hdc, int[] lppt, byte[] lpbTypes, int cCount);

        /** @dll.import("GDI32",auto) */
        public native static boolean PolyPolygon (int hdc, int[] lpPoints, int[] lpPolyCounts, int nCount);

        /** @dll.import("GDI32",auto) */
        public native static boolean PolyPolyline (int hdc, int[] lppt, int[] lpdwPolyPoints, int cCount);

        /** @dll.import("GDI32",auto) */
        public native static boolean PolyTextOut (int hdc, Object pptxt, int cStrings);

        /** @dll.import("GDI32",auto) */
        public native static boolean Polygon (int hdc, int[] lpPoints, int nCount);

        /** @dll.import("GDI32",auto) */
        public native static boolean Polyline (int hdc, int[] lppt, int cPoints);

        /** @dll.import("GDI32",auto) */
        public native static boolean PolylineTo (int hdc, int[] lppt, int cCount);

        /** @dll.import("GDI32",auto) */
        public native static boolean PtInRegion (int hrgn, int X, int Y);

        /** @dll.import("GDI32",auto) */
        public native static boolean PtVisible (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int RealizePalette (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean RectInRegion (int anonymous0, RECT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean RectVisible (int anonymous0, RECT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean Rectangle (int hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

        /** @dll.import("GDI32", auto) */
        public native static boolean RemoveFontResource (String anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static int ResetDC (int anonymous0, DEVMODE anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean ResizePalette (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean RestoreDC (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean RoundRect (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, int anonymous5, int anonymous6);

        /** @dll.import("GDI32",auto) */
        public native static int SaveDC (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean ScaleViewportExtEx (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, SIZE anonymous5);

        /** @dll.import("GDI32",auto) */
        public native static boolean ScaleWindowExtEx (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4, SIZE anonymous5);

        /** @dll.import("GDI32",auto) */
        public native static boolean SelectClipPath (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SelectClipRgn (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SelectObject (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SelectPalette (int anonymous0, int anonymous1, boolean anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int SetAbortProc (int hdc, ABORTPROC lpAbortProc);

        /** @dll.import("GDI32",auto) */
        public native static int SetArcDirection (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetBitmapBits (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetBitmapDimensionEx (int anonymous0, int anonymous1, int anonymous2, SIZE anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int SetBkColor (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetBkMode (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetBoundsRect (int anonymous0, RECT anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetBrushOrgEx (int anonymous0, int anonymous1, int anonymous2, POINT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetColorAdjustment (int anonymous0, COLORADJUSTMENT anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetColorSpace (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetDIBColorTable (int anonymous0, int anonymous1, int anonymous2, byte[] anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int SetDIBits (int hdc, int hbmp, int uStartScan, int cScanLines, int[] /* void* */ lpvBits, int[] /* union BITMAPINFO* */ lpbmi, int fuColorUse);

        /** @dll.import("GDI32",auto) */
        public native static int SetDIBitsToDevice (int hdc, int XDest, int YDest, int dwWidth, int dwHeight, int XSrc, int YSrc, int uStartScan, int cScanLines, int[] lpvBits, int /* BITMAPINFO* */ lpbmi, int fuColorUse);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetDeviceGammaRamp (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetEnhMetaFileBits (int cbBuffer, byte[] lpData);

        /** @dll.import("GDI32",auto) */
        public native static int SetGraphicsMode (int hdc, int iMode);

        /** @dll.import("GDI32",auto) */
        public native static int SetICMMode (int anonymous0, int anonymous1);

        /** @dll.import("GDI32", auto) */
        public native static boolean SetICMProfile (int anonymous0, String anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetMapMode (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetMapperFlags (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetMetaFileBitsEx (int nSize, byte[] lpData);

        /** @dll.import("GDI32",auto) */
        public native static int SetMetaRgn (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetMiterLimit (int anonymous0, float anonymous1, float[] anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static int SetPaletteEntries (int anonymous0, int anonymous1, int anonymous2, byte[] anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int SetPixel (int anonymous0, int anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetPixelFormat (int anonymous0, int anonymous1, PIXELFORMATDESCRIPTOR anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetPixelV (int anonymous0, int anonymous1, int anonymous2, int anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int SetPolyFillMode (int hdc, int iPolyFillMode);

        /** @dll.import("GDI32",auto) */
        public native static int SetROP2 (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetRectRgn (int anonymous0, int anonymous1, int anonymous2, int anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static int SetStretchBltMode (int hdc, int iStretchMode);

        /** @dll.import("GDI32",auto) */
        public native static int SetSystemPaletteUse (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetTextAlign (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetTextCharacterExtra (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int SetTextColor (int anonymous0, int anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetTextJustification (int anonymous0, int anonymous1, int anonymous2);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetViewportExtEx (int anonymous0, int anonymous1, int anonymous2, SIZE anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetViewportOrgEx (int anonymous0, int anonymous1, int anonymous2, POINT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static int SetWinMetaFileBits (int anonymous0, byte[] anonymous1, int anonymous2, METAFILEPICT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetWindowExtEx (int anonymous0, int anonymous1, int anonymous2, SIZE anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetWindowOrgEx (int anonymous0, int anonymous1, int anonymous2, POINT anonymous3);

        /** @dll.import("GDI32",auto) */
        public native static boolean SetWorldTransform (int anonymous0, XFORM anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int StartDoc (int anonymous0, DOCINFO anonymous1);

        /** @dll.import("GDI32",auto) */
        public native static int StartPage (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean StretchBlt (int hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int dwRop);

        /** @dll.import("GDI32",auto) */
        public native static int StretchDIBits (int hdc, int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, int[] lpBits, int /* BITMAPINFO* */ lpBitsInfo, int iUsage, int dwRop);

        /** @dll.import("GDI32",auto) */
        public native static boolean StrokeAndFillPath (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean StrokePath (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean SwapBuffers (int anonymous0);

        /** @dll.import("GDI32", auto) */
        public native static boolean TextOut (int anonymous0, int anonymous1, int anonymous2, String anonymous3, int anonymous4);

        /** @dll.import("GDI32",auto) */
        public native static boolean TranslateCharsetInfo (Object lpSrc, CHARSETINFO lpCs, int dwFlags);

        /** @dll.import("GDI32",auto) */
        public native static boolean UnrealizeObject (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean UpdateColors (int anonymous0);

        /** @dll.import("GDI32",auto) */
        public native static boolean WidenPath (int anonymous0);
}

