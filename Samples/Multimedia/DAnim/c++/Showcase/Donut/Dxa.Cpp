/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       dxa.cpp
 *
 *  This file contains functions that make use of DirectX Animation
 *  to render animation to a ddraw surface.
 *
 ***************************************************************************/

#include "dxa.h"
#include <stdio.h>
#include <sys\timeb.h>
#include <tchar.h>

IDA2ViewPtr view1 = NULL;
IDA2ViewPtr view2 = NULL;
double startTime = 0;
/*
 * StartOle
 *
 * Start the Ole services.
 */
struct StartOle {
    StartOle() { CoInitialize( NULL ); }
    ~StartOle() { CoUninitialize(); }
} _inst_StartOle;

/*
 * dump_com_error
 *
 * Dump the com error should an exception occurs in InitDXAViewObj.
 * This is mainly for debugging purpose.
 */
void dump_com_error( _com_error &e )
{
    char buf[2048];

    sprintf(buf, _T( "Oops - hit an error!\n\tCode = %08lx\n\tCode meaning = %s\n" ),
            e.Error(), e.ErrorMessage());
    OutputDebugString(buf);
}

/*
 * initDXAViewObj
 *
 * Create the DAView object, construct the model, then start the model.
 *
 */
BOOL initDXAViewObj(IUnknown *ddsurf)
{
    try {
      IDAStaticsPtr e;

      // Create the statics object.
      e.CreateInstance(L"DirectAnimation.DAStatics");

      // Create the two DAView objects.  One will be rendered under
      // the donut, the other above it.
      view1.CreateInstance(L"DirectAnimation.DAView");
      view2.CreateInstance(L"DirectAnimation.DAView");

      // Construct the image for model1, which will be rendered
      // under the donut.  
      IDAColorPtr col1 = e->ColorHslAnim(e->LocalTime, e->DANumber(0.5),
                                                       e->DANumber(0.5));
      IDAFontStylePtr font = e->Font("Helvetica", 14, col1);
      IDAImagePtr txtImg1 = e->StringImage("DXA Under Donut", font);       
      IDAImagePtr model1 = txtImg1->Transform(e->Rotate2Anim(e->LocalTime));

      struct _timeb timebuffer;
      _ftime( &timebuffer );
      startTime = timebuffer.time + ( timebuffer.millitm / 1000.0 );

      // Tell the DAView object where to render the model.
      view1->SetViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
      view1->IDirectDrawSurface = ddsurf;
      view1->CompositeDirectlyToTarget = TRUE;
      view1->StartModel(e->Overlay(model1, e->SolidColorImage(e->Black)), e->Silence, 0);

      // Construct the image for model2, which will be rendered
      // above the donut.  
      IDAImagePtr txtImg2 = e->StringImage("DXA Above Donut", font);                
      IDAImagePtr model2 = txtImg2->Transform(e->Translate2Anim(
                                              e->DANumber(0),       
                                              e->Mul(e->Sin(e->LocalTime), 
                                                     e->DANumber(0.01))));
   
   
     // view2->SetViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
      view2->IDirectDrawSurface = ddsurf;
      view2->CompositeDirectlyToTarget = TRUE;
      view2->StartModel(model2, e->Silence, 0);
    } catch (_com_error &e) {
        dump_com_error( e );
        return false;
    }
    return true;
}

BOOL resetDXASurfaces(IUnknown *ddsurf)
{
    try {
        view1->IDirectDrawSurface = ddsurf;
        view2->IDirectDrawSurface = ddsurf;
    } catch (_com_error &e) {
        dump_com_error( e );
        return false;
    }
    return true;
}

/*
 * destroyDXAViewObj
 *
 * Tell the DAView object to stop the model, this will garbage collect all
 * elements of the model that were constructed in initDXAViewObj.
 *
 */
BOOL destroyDXAViewObj()  {
    try {
      view1->StopModel();
      view2->StopModel();
    } catch (_com_error &e) {
      dump_com_error( e );
      return FALSE;
    }
    return TRUE;    
}


/*
 * tick
 *
 * Ask DA to sample and display the model.
 *
 */
void tick(IDA2ViewPtr view) {
  HRESULT hr;
  int a =0;
  long numRects;
  if (view != NULL) {
    struct _timeb timebuffer;
    _ftime( &timebuffer );
    double thisTime = timebuffer.time + ( timebuffer.millitm / 1000.0 );

    thisTime -= startTime;

    BOOL render;
    hr = view->raw_Tick(thisTime, (short*)&render);

	  if(!SUCCEEDED(hr))
      return;

	  if(render)  {
      hr = view->raw_GetInvalidatedRects(NULL, 0, NULL, &numRects);
      if(!SUCCEEDED(hr))
        return;

      RECT *rectInvalid = new RECT[numRects];

      // (DAnim::tagRECT *) below needs to be commented out if you use VC++ 6.0
      hr = view->raw_GetInvalidatedRects(NULL, numRects, 
        /*(DAnim::tagRECT *)*/ rectInvalid, &numRects);
      if(!SUCCEEDED(hr))
        return;

      while(a<numRects)  {
        hr = view->RePaint(rectInvalid[a].left, rectInvalid[a].top, 
	        (rectInvalid[a].right - rectInvalid[a].left), 
            (rectInvalid[a].bottom - rectInvalid[a].top));
        if(!SUCCEEDED(hr))
          return;
      }

      hr = view->Render(); 	    
      if(!SUCCEEDED(hr))
        return;
      delete rectInvalid;
    }
  }
}

