#include "dactl.h"

void dump_com_error( _com_error &e )
{
    char buf[2048];

    sprintf(buf, _T( "Oops - hit an error!\n\tCode = %08lx\n\tCode meaning = %s\n" ),
            e.Error(), e.ErrorMessage());
    OutputDebugString(buf);
}

// If this is placed in the scope of the smart pointers, they must be
// explicitly Release(d) before CoUninitialize() is called.  If any reference
// count is non-zero, a protection fault will occur.

CDAViewerCtl::CDAViewerCtl()
    :_vc(NULL)
{
    try   {
        _vc.CreateInstance(__uuidof(DAViewerControlWindowed));
    } catch( _com_error &e ) {
        dump_com_error( e );
    }
}

void CDAViewerCtl::DestroyModel() {    
    // Unload our cached behaviors and cross references so
    // that proper cleanup can occur.
    _b0->Cleanup();
    _pPickHandle->Cleanup();
    _pDownHandle->Cleanup();
}

void CDAViewerCtl::CreateModel() {
    try {
      // Create the statics object
      IDAStaticsPtr e;
      e = _vc->GetMeterLibrary();

      // Import Media (images in this case).  The
      // GetCurrentDirectory() is used as a starting
      // point for relative file importing.
      TCHAR szMediaBase[_MAX_PATH];
      TCHAR szImg[_MAX_PATH];

      GetModuleFileName(GetModuleHandle(NULL),
        szMediaBase,sizeof(szMediaBase));
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

      _tcscpy(szImg,szMediaBase);

      _tcscat(szImg,_T("image/"));
      
      IDAImagePtr arrowImg = e->ImportImage(_bstr_t(szImg) +  _bstr_t("arrowIcon.gif"));
      
      IDANumberPtr h = e->Mul(e->DANumber(3), e->Pixel);
      
      IDAImagePtr squareImg = e->SolidColorImage(e->Red)->Crop(e->Point2Anim(e->Neg(h), e->Neg(h)), 
        e->Point2Anim(h, h));
      
      _pPickHandle = new CPickHandler();
      _pDownHandle = new CDownHandler();

		  _b0 = new CControlPoint2();
      _b0->initNotify(squareImg, arrowImg, _pPickHandle, _pDownHandle, 0, 0, e);

      int n = 12;
		  IDAPoint2Ptr pntBvr[12];

      double cx = 0;
      double cy = 0;
      double r = 0.025;
		  double x0 = cx + r;

		  double y0 = cy;
      for (int i = 0; i < n; i++)  {
			  double x1 = cx + r*cos(2*(i+1)*3.1416/n);
			  double y1 = cy + r*sin(2*(i+1)*3.1416/n);

        CConsLinear* cons = new CConsLinear(x0, y0, x1, y1, FALSE);

			  _b0->add(*cons);
        
        pntBvr[i] = e->Point2(x0, y0);

			  x0 = x1;
			  y0 = y1;
        delete cons;
      }

		  _b0->obeyConstraints();

		  IDAImagePtr polygonImage = e->PolylineEx(n, (IDAPoint2**)pntBvr)->Close()->Fill(
        e->DefaultLineStyle->Color(e->Blue), e->SolidColorImage(e->White));

      IDAImagePtr finalImg[3] = {_b0->_img, polygonImage, e->SolidColorImage(e->Gray)};
              
      // And set the model's image to this image.
      _vc->PutImage(  e->OverlayArrayEx(3, (IDAImage**)finalImg) ); 

      // Set the cap for the frame rate.  If we don't do this, DA
      // will hog the cpu and the mouse and keyboard won't be very
      // responsive.  If you're running in full screen mode, you may
      // want to remove this line to get better frame rate.
      _vc->put_UpdateInterval(0.1);

      // Start the model on the view.  The WndProc will
      // generate the frames.
      _vc->Start();
    } 
    catch( _com_error &e ) {
      dump_com_error( e );
    }
}

HRESULT CDAViewerCtl::GetIUnknown(IUnknown **pUnk) {
    if (!pUnk)
        return E_POINTER;

    if (_vc == NULL)
        return E_NOINTERFACE;

    return _vc->QueryInterface(IID_IUnknown, (LPVOID *)pUnk);
}
