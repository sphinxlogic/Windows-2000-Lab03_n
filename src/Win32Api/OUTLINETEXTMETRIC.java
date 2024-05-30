// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved

// These classes provide direct, low-overhead access to commonly used
// Windows api. These classes use the new J/Direct feature.
//
// Information on how to use J/Direct to write your own declarations
// can be found in the Microsoft SDK for Java 2.0.

package com.ms.win32;


/** @dll.struct(auto) */
public class OUTLINETEXTMETRIC {
	public int	otmSize = com.ms.dll.DllLib.sizeOf(this);
	// otmTextMetrics was a by-value TEXTMETRIC structure
	public int	otmTextMetrics_tmHeight;
	public int	otmTextMetrics_tmAscent;
	public int	otmTextMetrics_tmDescent;
	public int	otmTextMetrics_tmInternalLeading;
	public int	otmTextMetrics_tmExternalLeading;
	public int	otmTextMetrics_tmAveCharWidth;
	public int	otmTextMetrics_tmMaxCharWidth;
	public int	otmTextMetrics_tmWeight;
	public int	otmTextMetrics_tmOverhang;
	public int	otmTextMetrics_tmDigitizedAspectX;
	public int	otmTextMetrics_tmDigitizedAspectY;
	public char	otmTextMetrics_tmFirstChar;
	public char	otmTextMetrics_tmLastChar;
	public char	otmTextMetrics_tmDefaultChar;
	public char	otmTextMetrics_tmBreakChar;
	public byte	otmTextMetrics_tmItalic;
	public byte	otmTextMetrics_tmUnderlined;
	public byte	otmTextMetrics_tmStruckOut;
	public byte	otmTextMetrics_tmPitchAndFamily;
	public byte	otmTextMetrics_tmCharSet;
	public byte	otmFiller1;
	public byte	otmFiller2;
	public byte	otmFiller3;

        // otmPanoseNumber was a by-value PANOSE structure
	public byte	otmPanoseNumber_bFamilyType;
	public byte	otmPanoseNumber_bSerifStyle;
	public byte	otmPanoseNumber_bWeight;
	public byte	otmPanoseNumber_bProportion;
	public byte	otmPanoseNumber_bContrast;
	public byte	otmPanoseNumber_bStrokeVariation;
	public byte	otmPanoseNumber_bArmStyle;
	public byte	otmPanoseNumber_bLetterform;
	public byte	otmPanoseNumber_bMidline;
	public byte	otmPanoseNumber_bXHeight;

        public byte     otmFiller4;
        public byte     otmFiller5;
        public int	otmfsSelection;
	public int	otmfsType;
	public int	otmsCharSlopeRise;
	public int	otmsCharSlopeRun;
	public int	otmItalicAngle;
	public int	otmEMSquare;
	public int	otmAscent;
	public int	otmDescent;
	public int	otmLineGap;
	public int	otmsCapEmHeight;
	public int	otmsXHeight;
	// otmrcFontBox was a by-value RECT structure
	public int	otmrcFontBox_left;
	public int	otmrcFontBox_top;
	public int	otmrcFontBox_right;
	public int	otmrcFontBox_bottom;
	public int	otmMacAscent;
	public int	otmMacDescent;
	public int	otmMacLineGap;
	public int	otmusMinimumPPEM;
	// otmptSubscriptSize was a by-value POINT structure
	public int	otmptSubscriptSize_x;
	public int	otmptSubscriptSize_y;
	// otmptSubscriptOffset was a by-value POINT structure
	public int	otmptSubscriptOffset_x;
	public int	otmptSubscriptOffset_y;
	// otmptSuperscriptSize was a by-value POINT structure
	public int	otmptSuperscriptSize_x;
	public int	otmptSuperscriptSize_y;
	// otmptSuperscriptOffset was a by-value POINT structure
	public int	otmptSuperscriptOffset_x;
	public int	otmptSuperscriptOffset_y;
	public int	otmsStrikeoutSize;
	public int	otmsStrikeoutPosition;
	public int	otmsUnderscoreSize;
	public int	otmsUnderscorePosition;
	public int /* PSTR */	otmpFamilyName;
	public int /* PSTR */	otmpFaceName;
	public int /* PSTR */	otmpStyleName;
	public int /* PSTR */	otmpFullName;
}

