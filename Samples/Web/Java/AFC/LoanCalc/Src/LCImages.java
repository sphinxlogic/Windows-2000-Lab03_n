//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.MediaTracker;
import java.net.URL;
import com.ms.ui.*;

//
// This class assumes that an Images directory containing NUM_IMAGES 
// images is contained in the application/applet directory.
//
public class LCImages implements LCConsts
{
	private static UIApplet applet = null;
	private static MediaTracker tracker = null;
	private static URL url = null;
	private static Toolkit tk = null;
	private static String filesep = System.getProperty("file.separator");

	private static Image img[] = new Image[NUM_IMAGES];

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
			try { tracker.waitForAll(); } catch(InterruptedException e) { }
			img[idx] = image;
		}
		return image;
	}
}
