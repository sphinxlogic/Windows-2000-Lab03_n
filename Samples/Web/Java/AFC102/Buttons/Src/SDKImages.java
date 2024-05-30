//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.MediaTracker;
import java.awt.image.RGBImageFilter;
import java.awt.image.FilteredImageSource;
import java.awt.image.ImageFilter;
import java.net.URL;
import com.ms.ui.*;

//
// This class assumes that an Images directory containing NUM_IMAGES 
// images is contained in the application/applet directory.
//
public class SDKImages implements SDKConsts
{
	private static UIApplet applet = null;
	private static MediaTracker tracker = null;
	private static URL url = null;
	private static Toolkit tk = null;
	private static String filesep = System.getProperty("file.separator");

	private static Image img[] = new Image[NUM_IMAGES];
	private static Image himg[] = new Image[NUM_IMAGES];

	public final static void init(UIApplet aplt, UIFrame frame)
	{
		if ( aplt != null ) {
			applet = aplt;
			tracker = new MediaTracker(applet.getApplet());
			url = applet.getCodeBase();
		}
		else {
			tracker = new MediaTracker(frame.getFrame());
			tk = frame.getToolkit();
		}
	}

	public final static Image get(int idx)
	{
		Image image = img[idx];

		if ( image == null ) {
			if ( applet != null )
				image = applet.getImage(url, "Images" + filesep + IMG_NAMES[idx]);
			else
				image = tk.getImage("Images" + filesep + IMG_NAMES[idx]);
			tracker.addImage(image, 0);
			try { tracker.waitForID(0); } catch(InterruptedException e) { }
			img[idx] = image;
		}
		return image;
	}

	public final static Image getHot(int idx)
	{
		Image image = himg[idx];

		if ( image == null ) {
			ImageFilter filter = new SDKHotImages();

			if ( applet != null )
				image = applet.createImage( new FilteredImageSource(get(idx).getSource(), 
																	filter) );
			else
				image = tk.createImage( new FilteredImageSource(get(idx).getSource(), 
																filter) );
			tracker.addImage(image, 0);
			try { tracker.waitForAll(); } catch(InterruptedException e) { }
			himg[idx] = image;
		}
		return image;
	}
}

class SDKHotImages extends RGBImageFilter
{
	public SDKHotImages()
	{
		// The filter's operation does not depend on the pixel's location, so
		//   IndexColorModels can be filtered directly.
		canFilterIndexColorModel  =  true;
	}

    public int filterRGB(int  x,  int  y,  int  rgb)
	{
		int red, blue, green;

		red = ((rgb & 0xff0000) >> 16) - 30;
		red = (red < 0 ? 0 : red);
		red = red << 16;
		green = ((rgb & 0xff00) >> 8) + 30;
		green = (green > 0xff ? 0xff: green);
		green = green << 8;
		blue = (rgb & 0xff) - 30;
		blue = (blue < 0 ? 0 : blue);

		return ( (rgb & 0xff000000) | red | green | blue );
	}
}
