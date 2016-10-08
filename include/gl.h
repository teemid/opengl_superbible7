#ifndef SBGL_GLFUNCTIONS_H
#define SBGL_GLFUNCTIONS_H

#include "GL/glcorearb.h"
#include "common.h"


namespace GLFramework
{
    void LoadProcs (void);
}


#define GL_FUNC(type, name) extern type name;
#include "gl.def"

#endif
