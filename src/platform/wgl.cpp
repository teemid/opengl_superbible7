#include "gl.h"
#include "platform/wgl.h"


#define WGL_FUNC(type, name) type name;
#include "Platform/wgl.def"


namespace GLFramework
{
    int CreateContext (HWND windowHandle, HDC deviceContext, int32_t major, int32_t minor)
    {
        PIXELFORMATDESCRIPTOR desired = {};
        desired.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
        desired.nVersion     = 1;
        desired.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        desired.iPixelType   = PFD_TYPE_RGBA;
        desired.cColorBits   = 24;
        desired.cAlphaBits   = 8;
        desired.cAccumBits   = 0;
        desired.cDepthBits   = 24;
        desired.cStencilBits = 8;

        int32_t pixelFormat = ChoosePixelFormat(deviceContext, &desired);

        if (!pixelFormat)
        {
            OutputDebugStringA("Could not get a pixel format.\n");

            return 1;
        }

        PIXELFORMATDESCRIPTOR suggested = {};

        if (!DescribePixelFormat(deviceContext, pixelFormat, sizeof(suggested), &suggested))
        {
            OutputDebugStringA("Could not get a pixel format descriptor.\n");

            return 1;
        }

        if (!SetPixelFormat(deviceContext, pixelFormat, &suggested))
        {
            OutputDebugStringA("Could not set the pixel format.\n");

            return 1;
        }

        // NOTE (Emil): This is a temporary context. So we don't bother with saving it.
        HGLRC renderContext = wglCreateContext(deviceContext);

        if (!renderContext)
        {
            OutputDebugStringA("Could not create initial render context.\n");

            return 1;
        }

        wglMakeCurrent(deviceContext, renderContext);

        wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");

        if (!wglGetExtensionsStringARB)
        {
            OutputDebugStringA("Failed to get wglGetExtensionsStringARB address.\n");

            return 1;
        }

        // NOTE (Emil): Get all the wgl extensions supported by the current device.
        const char * extensions = wglGetExtensionsStringARB(deviceContext);

        const char * has_create_context  = strstr(extensions, "WGL_ARB_create_context");
        const char * has_context_profile = strstr(extensions, "WGL_ARB_create_context_profile");
        const char * has_robustness      = strstr(extensions, "WGL_ARB_create_context_robustness");

        if (!(has_create_context && has_context_profile))
        {
            OutputDebugStringA("Could not find WGL_ARB_create_context or WGL_ARB_create_context_profile in the WGL extensions.\n");

            return 1;
        }

        if (!has_robustness)
        {
            OutputDebugStringA("WGL_ARB_create_context_robustness not available.\n");
        }

        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

        if (!wglCreateContextAttribsARB)
        {
            OutputDebugStringA("Could not find the wglCreateContextAttribsARB proc address.\n");

            return 1;
        }

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(renderContext);

        renderContext = 0;

        pixelFormat = ChoosePixelFormat(deviceContext, &desired);

        if (!pixelFormat)
        {
            OutputDebugStringA("Could not get a pixel format.\n");

            return 1;
        }

        suggested = {};

        if (!DescribePixelFormat(deviceContext, pixelFormat, sizeof(suggested), &suggested))
        {
            OutputDebugStringA("DescribePixelFormat failed.\n");

            return 1;
        }

        if (!SetPixelFormat(deviceContext, pixelFormat, &suggested))
        {
            OutputDebugStringA("SetPixelFormat failed.\n");

            return 1;
        }

        if (has_robustness)
        {
            int32_t attributes[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, major,
                WGL_CONTEXT_MINOR_VERSION_ARB, minor,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB | WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB,
                WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB, WGL_LOSE_CONTEXT_ON_RESET_ARB,
                0, 0
            };

            renderContext = wglCreateContextAttribsARB(deviceContext, 0, attributes);

            if (!renderContext)
            {
                OutputDebugStringA("OpenGL context creation failed.\n");

                return 1;
            }

            if (!wglMakeCurrent(deviceContext, renderContext))
            {
                OutputDebugStringA("Failed to make the render context current.\n");

                return 1;
            }
        }
        else
        {
            int32_t attributes[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, major,
                WGL_CONTEXT_MINOR_VERSION_ARB, minor,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
                0, 0
            };

            renderContext = wglCreateContextAttribsARB(deviceContext, 0, attributes);

            if (!renderContext)
            {
                OutputDebugStringA("OpenGL context creation failed.\n");

                return 1;
            }

            if (!wglMakeCurrent(deviceContext, renderContext))
            {
                OutputDebugStringA("Failed to make the render context current.\n");

                return 1;
            }
        }

        return 0;
    }
}
