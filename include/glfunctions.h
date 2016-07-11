#ifndef SBGL_GLFUNCTIONS_H
#define SBGL_GLFUNCTIONS_H

#include "GL/glcorearb.h"


typedef void (*glProc) (void);


void LoadGLProcs ();

#include "gen/gl_header.inc"

#endif
