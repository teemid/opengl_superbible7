#include <windows.h>

#include "glfunctions.h"


static HMODULE glDLL;


static glProc GetProc (const char * proc)
{
    glProc result;

    result = (glProc)wglGetProcAddress(proc);

    if (!result)
    {
        result = (glProc)GetProcAddress(glDLL, proc);
    }

    return result;
}

void LoadGLProcs ()
{
    glDLL = LoadLibraryA("opengl32.dll");

    glGetIntegerv  = (PFNGLGETINTEGERVPROC)GetProc("glGetIntegerv");
    glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)GetProc("glClearBufferfv");

    FreeLibrary(glDLL);
}


PFNGLGETINTEGERVPROC   SBglGetIntegerv;
PFNGLCLEARBUFFERFVPROC SBglClearBufferfv;
