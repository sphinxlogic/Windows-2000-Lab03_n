#import "danim.tlb" \
  exclude( "_RemotableHandle", "IMoniker", "IPersist", "ISequentialStream", \
  "IParseDisplayName", "IOleClientSite", "_FILETIME", "tagSTATSTG" ) \
  rename( "GUID", "DAGUID" ) \
  rename_namespace( "DAnim" )

#include <stdio.h>
#include <sys\timeb.h>
#include <tchar.h>

#define WINDOW_WIDTH    300
#define WINDOW_HEIGHT   300

using namespace DAnim;

// Create the DirectAnimation class that will render to the primary DirectDraw
// surface.
class DXA  {
  
  public:
	BOOL initDXAViewObj(IUnknown *ddsurf);
	BOOL resetDXASurfaces(IUnknown *ddsurf);
  BOOL DXA::destroyDXAViewObj();
	void tick();
  double startTime;
  protected:
	static IDA2ViewPtr _view;
    IDAImagePtr geometryImage( IDAGeometryPtr geo, IDAStaticsPtr e );
    IDAColorPtr myColor( double hue, double saturationRate, IDAStaticsPtr e );
};