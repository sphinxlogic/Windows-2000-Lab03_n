//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.com.*;
import com.ms.com.*;
import com.ms.awt.*;
import com.ms.awt.peer.*;
import com.ms.directX.*;

class ViewerSelection
{
    private D3dVector zero;
    private D3dVector dir;

	private int				showBoxes = 0;
	Direct3dRM				d3drm;
	Direct3dRMFrame			sFrame = null;
	Direct3dRMMeshBuilder	sVisual = null;
	Direct3dRMLight			sLight = null;
	Direct3dRMMesh			selectionBox = null;
	Direct3dRMFrame			clipboardFrame = null;
	Direct3dRMMeshBuilder	clipboardVisual = null;

	int rod_faces[] = {
		8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0, /* end 1 */
	    4, 0, 0, 1, 1, 9, 1, 8, 0,  /* side 0 */
    	4, 1, 1, 2, 2, 10, 2, 9, 1, /* side 1 */
	    4, 2, 2, 3, 3, 11, 3, 10, 2, /* side 2 */
    	4, 3, 3, 4, 4, 12, 4, 11, 3, /* side 3 */
	    4, 4, 4, 5, 5, 13, 5, 12, 4, /* side 4 */
    	4, 5, 5, 6, 6, 14, 6, 13, 5, /* side 5 */
	    4, 6, 6, 7, 7, 15, 7, 14, 6, /* side 6 */
    	4, 7, 7, 0, 0, 8, 0, 15, 7,         /* side 7 */
	    8, 8, 0, 9, 1, 10, 2, 11, 3, 12, 4, 13, 5, 14, 6, 15, 7, /* end 2 */
	    0,0
		};

	int cone_faces[] = {   
		8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0, /* end 1 */
	    3, 0, 0, 1, 1, 8, 1,        /* side 0 */
    	3, 1, 1, 2, 2, 8, 1,        /* side 1 */
	    3, 2, 2, 3, 3, 8, 1, /* side 2 */
    	3, 3, 3, 4, 4, 8, 1, /* side 3 */
	    3, 4, 4, 5, 5, 8, 1, /* side 4 */
    	3, 5, 5, 6, 6, 8, 1, /* side 5 */
	    3, 6, 6, 7, 7, 8, 1, /* side 6 */
    	3, 7, 7, 0, 0, 8, 1,                /* side 7 */
	    0, 0
		};

	//////////////////////////////////////////////////////////////////////////

	D3dVector CreateVector()
	{
		D3dVector v;

		v = new D3dVector();
		v.x = 0.0F;
		v.y = 0.0F;
		v.z = 0.0F;

		return v;
	}

	//////////////////////////////////////////////////////////////////////////

	ViewerSelection(Direct3dRM i)
	{
		d3drm = i;

		zero = CreateVector();
		dir = CreateVector();
	}

	//////////////////////////////////////////////////////////////////////////

	void ShowBoxes(int show)
	{
		showBoxes = show;
		SelectVisual(sVisual, sFrame);
	}

	//////////////////////////////////////////////////////////////////////////

	int ToggleBoxes()
	{
		if(showBoxes == 0)
			ShowBoxes(1);
		else
			ShowBoxes(0);

		return showBoxes;
	}

	//////////////////////////////////////////////////////////////////////////

	Direct3dRMFrame SelectedFrame()
	{
		return sFrame;
	}

	//////////////////////////////////////////////////////////////////////////

	Direct3dRMMeshBuilder SelectedVisual()
	{
		return sVisual;
	}

	//////////////////////////////////////////////////////////////////////////

	Direct3dRMLight SelectedLight()
	{
		return sLight;
	}

	//////////////////////////////////////////////////////////////////////////

	void DeselectVisual()
	{
		if ((sFrame != null) && (selectionBox != null))
			sFrame.deleteVisualMesh(selectionBox);

		sFrame	= null;
		sVisual = null;
		selectionBox = null;
	}

	//////////////////////////////////////////////////////////////////////////

	void SelectVisual(Direct3dRMMeshBuilder visual, Direct3dRMFrame frame)
	{
		DeselectVisual();
		sVisual = visual;
		sFrame = frame;

		if (sVisual != null)
		{   
			Direct3dRMLightArray lights;

			sLight = null;
			lights = sFrame.getLights();
			if ( lights != null )
			{   
				if (lights.getSize() != 0)
					sLight = lights.getElement(0);
			}

			if ((showBoxes != 0) && (visual != null))
			{   
				D3dRMBox box = new D3dRMBox();
				Direct3dRMMeshBuilder builder;

				sVisual.getBox(box);
				builder = makeBox(box);
				selectionBox = builder.createMesh();
				sFrame.addVisualMesh(selectionBox);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void FindAndSelectVisual(Direct3dRMViewport view, int x, int y)
	{
		Direct3dRMFrame frame;
		Direct3dRMPickArray picked;
		Direct3dRMMeshBuilder mesh;

		/*
		 * Make sure we don't try to select the selection box of the current
	     * selection.
		 */
		DeselectVisual();

		picked = view.pick(x, y);
		if (picked != null)
		{   
			if (picked.getSize() != 0)
			{
				Direct3dRMFrameArray fa = picked.getPickFrame(0, null);
				Direct3dRMVisual      v = picked.getPickVisual(0, null);

				IUnknown i = v.getObjectType();
				if ( i instanceof IDirect3dRMMeshBuilder )
				{
					mesh  = v.getd3drmMeshBuilder();
					frame = fa.getElement(fa.getSize()-1);
	
					if( mesh != null )
						SelectVisual(mesh, frame);
				}
	        }
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CutVisual()
	{
		Direct3dRMFrame frame;

		if (sFrame != null) 
		{
			clipboardFrame = sFrame;
			clipboardVisual = sVisual;
						
			DeselectVisual();

			frame = clipboardFrame.getParent();
			if (frame != null) 
				frame.deleteChild(clipboardFrame);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CopyVisual()
	{
		Direct3dRMFrame frame;

		if (sFrame != null) 
		{
			clipboardFrame  = sFrame.duplicate();
			clipboardVisual = sVisual.duplicate();

			clipboardFrame.addVisualMeshBuilder(clipboardVisual);

			frame = clipboardFrame.getParent();
			if (frame != null) 
				frame.deleteChild(clipboardFrame);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void PasteVisual(Direct3dRMFrame scene)
	{
		if (clipboardFrame != null)
		{
			Direct3dRMFrame frame;
			Direct3dRMMeshBuilder visual;

			frame = clipboardFrame.duplicate();
			visual = clipboardVisual.duplicate();

			frame.addVisualMeshBuilder(visual);
			scene.addChild(frame);
		}	
	}

	//////////////////////////////////////////////////////////////////////////

	void DeleteVisual()
	{
		if (sFrame != null)
		{
			Direct3dRMFrame parent;
			Direct3dRMFrame frame = sFrame;

			DeselectVisual();
			parent = frame.getParent();
			parent.deleteChild(frame);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void ClearClipboard()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	private Direct3dRMMeshBuilder makeBox(D3dRMBox box)
	{
		Direct3dRMMeshBuilder mesh;
		D3dVector a, b;

		mesh = d3drm.createMeshBuilder();

		dir.z = box.zMax + 1.0F;
		AddRod(mesh, 0.05F, zero, dir);

		a = dir;
	    a.z += 0.6F;
		AddCone(mesh, 0.2F, dir, a);

		a.x = box.xMin; a.y = box.yMin; a.z = box.zMin;
		b = a;
		b.y = box.yMax;
		AddRod(mesh, 0.05F, a, b);

		a = b; b.x = box.xMax;
		AddRod(mesh, 0.05F, a, b);

		a = b; b.y = box.yMin;
		AddRod(mesh, 0.05F, a, b);

		a = b; b.x = box.xMin;
		AddRod(mesh, 0.05F, a, b);

		a = b; b.z = box.zMax;
		AddRod(mesh, 0.05F, a, b);

		a = b; b.x = box.xMax;
		AddRod(mesh, 0.05F, a, b);

		a = b; b.y = box.yMax;
		AddRod(mesh, 0.05F, a, b);

		a = b; b.x = box.xMin;
		AddRod(mesh, 0.05F, a, b);

		a = b; b.y = box.yMin;
		AddRod(mesh, 0.05F, a, b);

		b.y = box.yMax; a = b; b.z = box.zMin;
		AddRod(mesh, 0.05F, a, b);

		a.x = b.x = box.xMax;
		a.y = b.y = box.yMax;
		a.z = box.zMax;
		b.z = box.zMin;

		AddRod(mesh, 0.05F, a, b);

		a.y = box.yMin; b = a; b.z = box.zMin;
		AddRod(mesh, 0.05F, a, b);

		mesh.setColor(d3drm.createColorRGB(1.0F, 1.0F, 1.0F));
		return mesh;
	}

	//////////////////////////////////////////////////////////////////////////

	float D3DDivide( float a, float b)
	{
		return (float)((double) (a) / (double) (b));
	}

	float D3DMultiply( float a, float b)
	{
		return ((a) * (b));
	}

	//////////////////////////////////////////////////////////////////////////
	
	void AddRod(Direct3dRMMeshBuilder mesh, float radius, D3dVector a, D3dVector b)
	{
    	float f;
    	int i;

    	D3dVector d = new D3dVector();
		D3dVector u = new D3dVector();
		D3dVector r = new D3dVector();
    	D3dVector[] v = new D3dVector[16];

		for(i=0; i<16; i++)
			v[i] = new D3dVector();
			
    	D3dVector[] n = new D3dVector[8];
		for(i=0; i<8; i++)
			n[i] = new D3dVector();
			
	    /*
    	 * Find the unit vector along the rod.
	     */
	    d.x = b.x - a.x;
	    d.y = b.y - a.y;
	    d.z = b.z - a.z;
	    d3drm.vectorNormalise(d);

	    /*
    	 * Pick a vector normal to d
	     */
    	if (d.y != 0.0 || d.z != 0.0) 
    	{   
    		u.x = 0.0F;
        	if (d.y == 0.0F)
	        {   
	        	u.y = 1.0F;
            	u.z = 0.0F;
        	} 
        	else
        	{   
        		float n_fix = 1.0F + D3DDivide(D3DMultiply(d.z, d.z), D3DMultiply(d.y, d.y));
            	u.z = (float)Math.sqrt(D3DDivide(1.0F, n_fix));
	            u.y = -D3DMultiply(u.z, D3DDivide(d.z, d.y));
        	}
	    } 
	    else
    	{   
    		u.x = 0.0F;
	        u.y = 0.0F;
    	    u.z = 1.0F;
	    }

	    /*
    	 * Now find a vector normal to them both, to give us a coordinate
	     * system in the plane normal to the rod.
    	 */
	    d3drm.vectorCrossProduct(r, d, u);

	    /*
    	 * Scale down the coordinates to the radius of the rod.
	     */
    	u.x = D3DMultiply(u.x, radius);
	    u.y = D3DMultiply(u.y, radius);
    	u.z = D3DMultiply(u.z, radius);
	    r.x = D3DMultiply(r.x, radius);
    	r.y = D3DMultiply(r.y, radius);
	    r.z = D3DMultiply(r.z, radius);

    	/*
	     * Calculate the corners of an octagon.
    	 */
	    f = (float)Math.sqrt(2) / (2 * (1 + (float)Math.sqrt(2) / 2));
		v[0].x = 1;  // huh!! null pointer exception here
		
	    v[0].x = u.x + D3DMultiply(r.x, f);
    	v[0].y = u.y + D3DMultiply(r.y, f);
	    v[0].z = u.z + D3DMultiply(r.z, f);

        v[1].x = D3DMultiply(u.x, f) + r.x;
        v[1].y = D3DMultiply(u.y, f) + r.y;
        v[1].z = D3DMultiply(u.z, f) + r.z;

        v[2].x = D3DMultiply(-u.x, f) + r.x;
        v[2].y = D3DMultiply(-u.y, f) + r.y;
        v[2].z = D3DMultiply(-u.z, f) + r.z;

        v[3].x = -u.x + D3DMultiply(r.x, f);
        v[3].y = -u.y + D3DMultiply(r.y, f);
        v[3].z = -u.z + D3DMultiply(r.z, f);

        v[4].x = -u.x - D3DMultiply(r.x, f);
        v[4].y = -u.y - D3DMultiply(r.y, f);
        v[4].z = -u.z - D3DMultiply(r.z, f);

    	v[5].x = D3DMultiply(-u.x, f) - r.x;
	    v[5].y = D3DMultiply(-u.y, f) - r.y;
    	v[5].z = D3DMultiply(-u.z, f) - r.z;

	    v[6].x = D3DMultiply(u.x, f) - r.x;
    	v[6].y = D3DMultiply(u.y, f) - r.y;
	    v[6].z = D3DMultiply(u.z, f) - r.z;

	    v[7].x = u.x - D3DMultiply(r.x, f);
    	v[7].y = u.y - D3DMultiply(r.y, f);
	    v[7].z = u.z - D3DMultiply(r.z, f);

		/*
   		 * Add the rod endpoints and calculate the vertex normals.
	     */
    	for (i = 0; i < 8; i++)
	   	{   
   			n[i] = v[i];
   		
	        d3drm.vectorNormalise(n[i]);
        
   	    	v[i + 8].x = v[i].x + b.x;
    	   	v[i + 8].y = v[i].y + b.y;
	        v[i + 8].z = v[i].z + b.z;
   	    	v[i].x += a.x;
    	   	v[i].y += a.y;
	        v[i].z += a.z;
   		}
   		mesh.addFaces(16, v, 8, n, rod_faces);
	}

	//////////////////////////////////////////////////////////////////////////

	void AddCone(Direct3dRMMeshBuilder mesh, float radius, D3dVector a, D3dVector b)
	{
    	D3dVector d = new D3dVector();
		D3dVector u = new D3dVector();
		D3dVector r = new D3dVector();
	    D3dVector[] v = new D3dVector[16];
    	D3dVector[] n = new D3dVector[8];
	    float f;
    	int i;

		for(i=0; i<8; i++)
		{
			v[i] = new D3dVector();
			n[i] = new D3dVector();
		}
		for(i=8; i<16; i++)
			v[i] = new D3dVector();
		
	    /*
    	 * Find the unit vector along the rod.
	     */
    	d.x = b.x - a.x;
	    d.y = b.y - a.y;
    	d.z = b.z - a.z;
	    d3drm.vectorNormalise(d);

	    /*
    	 * Pick a vector normal to d
	     */
	    if (d.y != 0.0F || d.z != 0.0F)
    	{   
    		u.x = 0.0F;
        	if (d.y == 0.0F)
	        {   
	        	u.y = 1.0F;
            	u.z = 0.0F;
	        } 
	        else
        	{   
        		float n_fix = 1.0F + D3DDivide(D3DMultiply(d.z, d.z), D3DMultiply(d.y, d.y));
	            u.z = (float)Math.sqrt(1.0F / n_fix);
    	        u.y = - D3DDivide(D3DMultiply(u.z, d.z), d.y);
        	}
    	} 
    	else
    	{   
    		u.x = 0.0F;
	        u.y = 0.0F;
    	    u.z = 1.0F;
	    }

	    /*
    	 * Now find a vector normal to them both, to give us a coordinate
	     * system in the plane normal to the rod.
    	 */
	    d3drm.vectorCrossProduct(r, d, u);

    	/*
	     * Scale down the coordinates to the radius of the rod.
    	 */
	    u.x = D3DMultiply(u.x, radius);
    	u.y = D3DMultiply(u.y, radius);
	    u.z = D3DMultiply(u.z, radius);
    	r.x = D3DMultiply(r.x, radius);
	    r.y = D3DMultiply(r.y, radius);
    	r.z = D3DMultiply(r.z, radius);

	    /*
    	 * Calculate the corners of an octagon.
	     */
    	f = (float)Math.sqrt(2) / (2 * (1 + (float)Math.sqrt(2) / 2));
	    v[0].x = u.x + D3DMultiply(r.x, f);
    	v[0].y = u.y + D3DMultiply(r.y, f);
	    v[0].z = u.z + D3DMultiply(r.z, f);

	    v[1].x = D3DMultiply(u.x, f) + r.x;
    	v[1].y = D3DMultiply(u.y, f) + r.y;
	    v[1].z = D3DMultiply(u.z, f) + r.z;

	    v[2].x = D3DMultiply(-u.x, f) + r.x;
    	v[2].y = D3DMultiply(-u.y, f) + r.y;
	    v[2].z = D3DMultiply(-u.z, f) + r.z;

	    v[3].x = -u.x + D3DMultiply(r.x, f);
    	v[3].y = -u.y + D3DMultiply(r.y, f);
	    v[3].z = -u.z + D3DMultiply(r.z, f);

	    v[4].x = -u.x - D3DMultiply(r.x, f);
    	v[4].y = -u.y - D3DMultiply(r.y, f);
	    v[4].z = -u.z - D3DMultiply(r.z, f);

	    v[5].x = D3DMultiply(-u.x, f) - r.x;
    	v[5].y = D3DMultiply(-u.y, f) - r.y;
	    v[5].z = D3DMultiply(-u.z, f) - r.z;

	    v[6].x = D3DMultiply(u.x, f) - r.x;
    	v[6].y = D3DMultiply(u.y, f) - r.y;
	    v[6].z = D3DMultiply(u.z, f) - r.z;

	    v[7].x = u.x - D3DMultiply(r.x, f);
    	v[7].y = u.y - D3DMultiply(r.y, f);
	    v[7].z = u.z - D3DMultiply(r.z, f);

	    v[8] = b;

	    // Calculate the vertex normals and add the faces to the mesh
	    for (i = 0; i < 8; i++)
    	{   
    		n[i] = v[i];
    		
        	d3drm.vectorNormalise(n[0]);
	        v[i].x += a.x;
    	    v[i].y += a.y;
        	v[i].z += a.z;
	    }
	    mesh.addFaces(9, v, 8, n, cone_faces);
	}
	
	//////////////////////////////////////////////////////////////////////////
}
