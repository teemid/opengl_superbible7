#include "GL/wglext.h"


#define WGL_FUNC(type, name) extern type name;
#include "Platform/wgl.def"


namespace GLFramework
{
    int CreateContext(HWND windowHandle, HDC deviceContext, int32_t major, int32_t minor);
}

