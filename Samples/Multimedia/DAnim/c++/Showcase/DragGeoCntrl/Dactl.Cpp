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
    _dragPtr->Cleanup();
    _releasePtr->Cleanup();
}

void CDAViewerCtl::CreateModel() {
    try {
        // Create the statics object
        IDAStaticsPtr e;
        e = _vc->GetMeterLibrary();

        // Import Media (geometries in this case).  The
        // GetCurrentDirectory() is used as a starting
        // point for relative file importing.
        TCHAR szMediaBase[_MAX_PATH];
        TCHAR szGeo[_MAX_PATH];

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

        _tcscpy(szGeo,szMediaBase);

        _tcscat(szGeo,_T("geometry/"));

        // Import the cube rotate it and scale it down.
        _geo = e->ImportGeometry(_bstr_t(szGeo) + _bstr_t("cow.x"));
        _geo = _geo->Transform(e->Compose3(e->Rotate3Anim(e->Vector3(1,1,1), e->LocalTime),
          e->Scale3Uniform(0.005)));
		
        // Make geo draggable by creating a DraggableGeometry class
        // object (_dragPtr and _releasePtr).

        _dragPtr = new CDADrag(); 
        _releasePtr = new CDARelease();       
        _dragPtr->initNotify(_geo, _releasePtr, e->Origin3, e);

        // Initialize clr.  Let it start out as red, change it to blue,
        // when the cube is grabbed, and return to red when the cube
        // is released.  The grab and release events are obtained from the
		    // getGrabEvent() and getReleaseEvent() methods of the CDADrag
		    // class respectively.
        IDAColorPtr clr;
        clr.CreateInstance( L"DirectAnimation.DAColor");
        clr->Init(e->Until(e->Red, _dragPtr->getGrabEvent(), 
			    e->Until(e->Blue, _dragPtr->getReleaseEvent(), clr)));

        // Get the GeometryBvr part of _dragPtr, by calling the getGeometryPtr
        // function of CDADrag.
        IDAGeometryPtr pickableGeo = _dragPtr->getGeometryPtr();
        IDACameraPtr cam = e->PerspectiveCamera(0.1,0.05);
		
        // Apply clr to pickableGeo.   
        pickableGeo = pickableGeo->DiffuseColor(clr);
        pickableGeo = e->UnionGeometry(pickableGeo, e->DirectionalLight);
              		
        // overlay the rendered image on a black background.
        IDAImagePtr model = e->Overlay(pickableGeo->Render(cam), e->SolidColorImage(e->Black));                
        
        // And set the model's image to this image.
        _vc->PutImage( model );

        // Set the cap for the frame rate.  If we don't do this, DA
        // will hog the cpu and the mouse and keyboard won't be very
        // responsive.  If you're running in full screen mode, you may
        // want to remove this line to get better frame rate.
        _vc->put_UpdateInterval(0.2);

        // Start the model on the view.  The WndProc will
        // generate the frames.
        _vc->Start();

    } catch( _com_error &e ) {
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
