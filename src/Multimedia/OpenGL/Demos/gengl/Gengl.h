
#include "glos.h"
#include <gl.h>
#include <glu.h>
#include "genglrc.h"

#define WM_INIT		WM_USER

GLvoid initialize(HWND);
GLvoid draw_scene(HWND);
GLvoid resize(HWND);
BOOL bSetupPixelFormat(HDC);
