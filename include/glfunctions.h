#ifndef glfunctions
#define glfunctions

#include "GL/glcorearb.h"


typedef void (*glProc) (void);


void LoadGLProcs ();


extern PFNGLGETINTEGERVPROC   SBglGetIntegerv;
extern PFNGLCLEARBUFFERFVPROC SBglClearBufferfv;

#define glGetIntegerv   SBglGetIntegerv
#define glClearBufferfv SBglClearBufferfv

#endif
