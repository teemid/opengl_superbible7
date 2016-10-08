#include <windows.h>

#include "gl.h"


#define GL_FUNC(type, name) type name;
#include "gl.def"


namespace GLFramework
{
    typedef void (*glProc) (void);

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


    void LoadProcs ()
    {
        glDLL = LoadLibraryA("opengl32.dll");

        #define GL_FUNC(type, name) name = (type)GetProc(#name);
        #include "gl.def"

        FreeLibrary(glDLL);
    }
}
