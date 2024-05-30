//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.image.RGBImageFilter;

/**
*	GrayImageFilter
*
*	Image filter to gray out an image. Used to create disabled button images
*	in JNoteToolbar.
*
*	@version	1.0, 8/11/97
*	@see		JNoteToolbar
*/

public class GrayImageFilter extends RGBImageFilter
{
	
/**
*	Creats a GrayImageFilter. Sets the color model to indexed color.	
	*/
	public GrayImageFilter()
	{
		super();
		canFilterIndexColorModel = true;
	}
	
	/**
	*	Called for each color in the image we are to filter, and returns
	*	the new color.
	*	
	*	@param	x	x coordinate of pixel to filter. Since we're in indexed
	*				color mode, this is always -1.
	*	@param	y	y coordinate of pixel to filter. Since we're in indexed
	*				color mode, this is always -1.
	*	@param	rgb	RGB color value of color to filter.
	*/
	public int filterRGB(int x, int y, int rgb)
	{			
		int gray = (((rgb & 0xff0000) >> 16) +
			((rgb & 0x00ff00) >> 8) +
			((rgb & 0x0000ff)) / 3);
		
		int alpha = 0xff000000 & rgb;
		
		return (alpha | (gray << 16) | (gray << 8) | gray);			
	}
	
}

