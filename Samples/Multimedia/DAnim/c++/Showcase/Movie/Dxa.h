
#include <atlbase.h>
#include <comdef.h>
#include <danim.h>
#include <stdio.h>
#include <sys\timeb.h>
#include <tchar.h>

#define WINDOW_WIDTH    375
#define WINDOW_HEIGHT   375

// Create the DirectAnimation class that will render to the primary DirectDraw
// surface.
class DXA  {
  public:
    DXA();
	  BOOL initDXAViewObj(IUnknown *ddsurf);
	  BOOL resetDXASurfaces(IUnknown *ddsurf);
	  void tick();
	  void cleanupDXA();
  protected:
	  HRESULT hr;
	  IDAView* _view;
	  IDAStatics* e;
	  IDAImage* pFinalImg;
	  IDASound* pFinalSound;
    IDAImage* pRotatingMovieImg;
    IDAImportationResult* pMovieImport;
    IDASound* pSilence;
    IDANumber* pLocalTime;
    IDASound* pMovieSound;
    IDAImage* pBackgroundImg;
    IDAColor* pBackClr;
    IDAImage* pStandInImg;
    IDAImage* pRotatingMovieImg1;
    IDAImage* pRotatingMovieImg2;
    IDAImage* pRotatingMovieImg3;
    IDAImage* pRotatingMovieImg4;
    IDATransform2* pMovie2DXform;
    IDATransform3* pMovie3DXform;
    IDAVector3* yVector3;
    IDANumber* pMovieDuration;
    IDANumber* pRepeatTime;
	  double startTime;
};