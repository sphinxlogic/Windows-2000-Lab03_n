// Here's the magic... It reads in the type library and makes easy
// interfaces to use automatically.
#import "danim.tlb" \
  exclude( "_RemotableHandle", "IMoniker", "IPersist", "ISequentialStream", \
  "IParseDisplayName", "IOleClientSite", "_FILETIME", "tagSTATSTG" ) \
  rename( "GUID", "DAGUID" ) \
  rename_namespace( "DAnim" )


#include <stdio.h>
#include <stdlib.h>
#include <sys\timeb.h>
#include <tchar.h>
#include <malloc.h>        // Required by memset call
#include <d3drmwin.h>
using namespace DAnim;

class CDAViewerCtl {
public:
  // Construction of the control.  We use COM smart pointers in the
  // viewer control, the pointers are released when they're out of the
  // scope, so we don't need (the destructor) to release them.
  CDAViewerCtl();

  // For constructing the model.
  void CreateModel();


  // Return the IUnknown pointer of the control.
  HRESULT GetIUnknown(IUnknown **pUnk);

private:
  void cleanD3DRM();
	HRESULT hr; 
  IDAViewerControlPtr _vc;  
  IDAEventPtr PICKEVENTL;
  IDAEventPtr PICKEVENTR;
  IDANumberPtr SPEED;
  IDATransform3Ptr SIZE;
	LPDIRECT3DRM lpD3DRM; // Direct3DRM object 
	LPDIRECT3DRM3 lpD3DRM3; // Direct3DRM object 
  LPDIRECT3DRMMESHBUILDER3 lpSphere3_builder;
  D3DRMBOX boundingBox;
  IDAColorPtr globeColor;
  double PI;
  // Create a function to convert geometries into images.
  IDAImagePtr geometryImage(IDAGeometryPtr geo, IDA2StaticsPtr e2);
  // This function changes the color of a geometry when users clicks on
  // it with their mouse.
  IDAGeometryPtr activate(IDAGeometryPtr unpickedGeo, IDAColorPtr col, IDA2StaticsPtr e2);
};
