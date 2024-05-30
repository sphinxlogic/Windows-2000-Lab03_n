//////////////////////////////////////////////////////////////////////////
// JAnim.java
// This brings up a canvas which shows an animated image.
// 
// (C) Copyright 1997 by Microsoft Corporation. All rights reserved
//////////////////////////////////////////////////////////////////////////

// afc
import com.ms.ui.*;
import com.ms.ui.event.*;
import com.ms.fx.*;

// standard java
import java.awt.*;
import java.awt.image.*;

//
// JAnim
//
public class JAnim extends UICanvas implements Runnable
{
	int numImages = 0;										// The number of images
	int numSkip = 0;										// The number of images to skip
	Image	image ;											// the large image
	int width;												// the width of each image
	int height;												// the height of each image
	int currentImage = -1;									// the current image being displayed

	/**
	 * This constructor of the JAnim object requires an image object and
	 * and the number of images which are concatenated in this image object
	 *
	 * @param	Image	The big concatenated image
	 * @param	int		The number of images stacked one on top of the other
	 * @param	int		The number of images to skip after all images are shown and a new round begins
	 */
	public JAnim(Image image, int numImages, int numSkip)
	{
		MediaTracker tracker = new MediaTracker(new Canvas() );

		tracker.addImage(image, 0);

		// wait for the image to be loaded
        try 
		{
			tracker.waitForAll();
		} 
		catch (InterruptedException e) 
		{
		}


		this.numImages = numImages;
		this.image = image;
		this.numSkip = numSkip;

		// calculate the width and height
		width = image.getWidth(this);
		height = image.getHeight(this) / numImages;

		currentImage = 0;
	}

	/**
	 * This returns the preferred size for the object
	 * 
	 * @param	Dimension	The preferred dimension
	 */
	public Dimension getPreferredSize()
	{
		return new Dimension(width, height);
	}


	/**
	 * This returns the minimum size for the object
	 * 
	 * @param	Dimension	The preferred dimension
	 */
	public Dimension getMinimumSize()
	{
		return new Dimension(width, height);
	}


	/**
	 * This method paints the JAnim object -- actually it just calls the update method
	 *
	 * @param	FxGraphics	The grahics context to paint with.
	 */
	public void paint(FxGraphics g)
	{
		update(g);
	}

	/**
	 * This method will draw the current image in the JAnim object
	 *
	 * @param	FxGraphics	The graphics context to paint with
	 */
	public void update(FxGraphics g)
	{
		// we have to calculate the source coordinates of the current image in the tall image
		g.drawImage(image, 0, 0, width-1, height-1, 0, currentImage*height, width-1, currentImage*height+height-1, this); 
	}

	/**
	 * This is the run method of the JAnim object it repeatedly displays the list of images
	 * in the image object. It sleeps for half a second between images
	 */
	public void run()
	{
		// first time around all the images must be shown but in subsequent
		// runs pick up after skipping the initial few.
		for(int i=0; i<numImages; i++)
		{
			currentImage = i;
			repaint();
			try
			{
				Thread.sleep(120);
			}
			catch(InterruptedException e)
			{
				e.printStackTrace();
			}
		}

		while(true)
		{
			for(int i=numSkip; i<numImages; i++)
			{
				currentImage = i;
				repaint();

				try
				{
					Thread.sleep(120);
				}
				catch(InterruptedException e)
				{
					e.printStackTrace();
				}

			}
		}

	}

	/**
	 * This method resets the JAnim object to display the first image in the list
	 */
	public void reset()
	{
		currentImage = 0;
		repaint();
	}

}