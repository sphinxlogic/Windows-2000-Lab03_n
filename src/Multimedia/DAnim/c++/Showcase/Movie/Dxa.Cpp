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
void dump_com_error( _com_error &e )  {
  char buf[2048];
  sprintf(buf, _T( "Oops - hit an error!\n\tCode = %08lx\n\tCode meaning = %s\n" ), 
    e.Error(), e.ErrorMessage());
  OutputDebugString(buf);
}

DXA::DXA()  {
  _view = NULL;
  e = NULL;
  pFinalImg = NULL;
  pFinalSound = NULL;
  pRotatingMovieImg = NULL;
  pMovieImport = NULL;
  pSilence = NULL;
  pLocalTime  = NULL;
  pMovieSound = NULL;
  pBackgroundImg = NULL;
  pBackClr = NULL;
  pStandInImg = NULL;
  pRotatingMovieImg1 = NULL;
  pRotatingMovieImg2 = NULL;
  pRotatingMovieImg3 = NULL;
  pRotatingMovieImg4 = NULL;
  pMovie2DXform = NULL;
  pMovie3DXform = NULL;
  yVector3 = NULL;
  pMovieDuration = NULL;
  pRepeatTime = NULL;
}

/*
 * initDXAViewObj
 *
 * Create the DAView object, construct the model, then start the model.
 *
 */
BOOL DXA::initDXAViewObj(IUnknown *ddsurf)  {

  // Import Media (images and sound in this case).  The
  // GetCurrentDirectory() (which will return the path to either
  // the debug or release sub directory) is used as a starting
  // point for relative file importing.
  TCHAR szMediaBase[_MAX_PATH];
  TCHAR szMov[_MAX_PATH];
  TCHAR szImg[_MAX_PATH];

  GetModuleFileName(GetModuleHandle(NULL), szMediaBase,sizeof(szMediaBase));
  char *pos = strrchr( szMediaBase, (int)'\\' );
  int result = pos - szMediaBase + 1;
  szMediaBase[result]= NULL;

  // Find out if your are in the bin directory of the SDK, 
  // and append the path accordingly.
  TCHAR *	bin  = NULL;
  TCHAR * lwszMediaBase = NULL;
  lwszMediaBase = _tcslwr( szMediaBase );
  bin = _tcsstr(lwszMediaBase, "\\bin\\");

  if(bin)
    _tcscat(szMediaBase,_T("../../../media/"));
  else
    _tcscat(szMediaBase,_T("../../../../media/"));

  _tcscpy(szMov,szMediaBase);
  _tcscpy(szImg,szMediaBase);


  _tcscat(szMov,_T("movie/"));
  _tcscat(szImg,_T("image/"));

	hr = CoCreateInstance(CLSID_DAView, 
	  NULL, CLSCTX_INPROC, IID_IDAView, (void**) &_view);
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

	hr = CoCreateInstance(CLSID_DAStatics, 
	  NULL, CLSCTX_INPROC, IID_IDAStatics, (void**) &e);
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = e->get_Silence(&pSilence);
  if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = e->get_LocalTime(&pLocalTime);
  if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = e->ImportImage( _bstr_t(szImg) + _bstr_t("cherries.gif"), &pStandInImg);
  if(!SUCCEEDED(hr))  {
    cleanupDXA();
    return FALSE;
  }

  // Import the Movie.
  hr = e->ImportMovieAsync( _bstr_t(szMov) + _bstr_t("movie.avi"), 
    pStandInImg, pSilence, &pMovieImport );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  // Make it rotate in 3D.
  hr = e->get_YVector3( &yVector3 );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = e->Rotate3RateDegrees( yVector3, 60, &pMovie3DXform );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  // Get a 2D transform to apply to the 2D image.
  hr = pMovie3DXform->ParallelTransform2( &pMovie2DXform );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = pMovieImport->get_Image( &pRotatingMovieImg );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = pRotatingMovieImg->Transform( pMovie2DXform, &pRotatingMovieImg1 );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = pMovieImport->get_Duration( &pMovieDuration );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = e->Mod( pLocalTime, pMovieDuration, &pRepeatTime );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = pRotatingMovieImg1->DurationAnim( pMovieDuration, (IDABehavior**)&pRotatingMovieImg2 );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = pRotatingMovieImg2->RepeatForever( (IDABehavior**)&pRotatingMovieImg3 );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = pRotatingMovieImg3->SubstituteTime( pRepeatTime, (IDABehavior**)&pRotatingMovieImg4 );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = pMovieImport->get_Sound( &pMovieSound );
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = pMovieSound->Loop( &pFinalSound );
  if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  hr = _view->put_IDirectDrawSurface(ddsurf);
  if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
  }

  hr = _view->put_CompositeDirectlyToTarget(TRUE);
  if(!SUCCEEDED(hr))  {
    cleanupDXA();
		return FALSE;
  }

  hr = e->get_Black( &pBackClr );
  if(!SUCCEEDED(hr))  {
    cleanupDXA();
		return FALSE;
  }

  hr = e->SolidColorImage( pBackClr, &pBackgroundImg );
  if(!SUCCEEDED(hr))  {
    cleanupDXA();
		return FALSE;
  }

  hr = e->Overlay(pRotatingMovieImg4, pBackgroundImg, &pFinalImg );
  if(!SUCCEEDED(hr))  {
    cleanupDXA();
		return FALSE;
  }

  struct _timeb timebuffer;
  _ftime( &timebuffer );
  startTime = timebuffer.time + ( timebuffer.millitm / 1000.0 );

	hr = _view->StartModel(pFinalImg, pFinalSound, 0);
	if(!SUCCEEDED(hr))  {
	  cleanupDXA();
    return FALSE;
	}

  return TRUE;
}

BOOL DXA::resetDXASurfaces(IUnknown *ddsurf)
{
    try {
	  hr = _view->put_IDirectDrawSurface(ddsurf);
	  if(!SUCCEEDED(hr))  {
	    cleanupDXA();
		return FALSE;
	  }
    } catch (_com_error &e) {
        dump_com_error( e );
		cleanupDXA();
        return FALSE;
    }
    return TRUE;
}

void DXA::cleanupDXA()  {
  if(_view != NULL)  {
    _view->StopModel();
    _view->Release();
    _view = NULL;
  }

  if(e != NULL)  {
	  e->Release();
	  e = NULL;
  }

  if(pFinalImg != NULL)  {
	  pFinalImg->Release();
	  pFinalImg = NULL;
  }

  if(pFinalSound != NULL)  {
	  pFinalSound->Release();
	  pFinalSound = NULL;
  }

  if(pRotatingMovieImg != NULL)  {
    pRotatingMovieImg->Release();
    pRotatingMovieImg = NULL;
  }

  if(pMovieImport != NULL)  {
    pMovieImport->Release();
    pMovieImport = NULL;
  }

  if(pSilence != NULL)  {
    pSilence->Release();
    pSilence = NULL;
  }

  if(pLocalTime != NULL)  {
    pLocalTime->Release();
    pLocalTime = NULL;
  }

  if(pBackClr != NULL)  {
    pBackClr->Release();
    pBackClr = NULL;
  }

  if(pBackgroundImg != NULL)  {
    pBackgroundImg->Release();
    pBackgroundImg = NULL;
  }

  if(pStandInImg != NULL)  {
    pStandInImg->Release();
    pStandInImg = NULL;
  }

  if(pRotatingMovieImg1 != NULL)  {
    pRotatingMovieImg1->Release();
    pRotatingMovieImg1 = NULL;
  }

  if(pRotatingMovieImg2 != NULL)  {
    pRotatingMovieImg2->Release();
    pRotatingMovieImg2 = NULL;
  }

  if(pRotatingMovieImg3 != NULL)  {
    pRotatingMovieImg3->Release();
    pRotatingMovieImg3 = NULL;
  }

  if(pRotatingMovieImg4 != NULL)  {
    pRotatingMovieImg4->Release();
    pRotatingMovieImg4 = NULL;
  }

  if(pMovie3DXform != NULL)  {
    pMovie3DXform->Release();
    pMovie3DXform = NULL;
  }

  if(pMovie2DXform != NULL)  {
    pMovie2DXform->Release();
    pMovie2DXform = NULL;
  }

  if(yVector3 != NULL)  {
    yVector3->Release();
    yVector3 = NULL;
  }

  if(pMovieDuration != NULL)  {
    pMovieDuration->Release();
    pMovieDuration = NULL;
  }

  if(pMovieDuration != NULL)  {
    pMovieDuration->Release();
    pMovieDuration = NULL;
  }

  if(pRepeatTime != NULL)  {
    pRepeatTime->Release();
    pRepeatTime = NULL;
  }
}


/*
 * tick
 * Ask DA to sample and display the model.
 */
void DXA::tick() {
  if (_view != NULL) {
    struct _timeb timebuffer;

    _ftime( &timebuffer );
    double thisTime = timebuffer.time + ( timebuffer.millitm / 1000.0 );

    thisTime -= startTime;

    BOOL bRender = FALSE;
    hr = _view->Tick(thisTime, (short*)&bRender);

    if(!SUCCEEDED(hr))  {
	    cleanupDXA();
	    return;
    }

    if(bRender)  {
      hr = _view->Render();
	    if(!SUCCEEDED(hr))  {
	      cleanupDXA();
	      return;
      }
    }
	}
}


