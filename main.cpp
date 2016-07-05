#include <cstdint>
#include <cstring>
#include <cstdio>

#include <windows.h>
#include <Wingdi.h>


#include "glfunctions.h"
#include "WGLExtensions.h"
#include "framework.h"

static PFNWGLGETEXTENSIONSSTRINGARB  wglGetExtensionsStringARB;
static PFNWGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;


typedef uint32_t bool32_t;
typedef void (*glProc) (void);

struct WindowInfo
{
    char title[128];
    int32_t width;
    int32_t height;
};

struct OpenGLInfo
{
    int32_t major;
    int32_t minor;
};

static WindowInfo gInfo = {
    "OpenGL Superbible 7th Edition",
    800,
    600
};

static OpenGLInfo gGLInfo = { 4, 3 };

static bool32_t gRunning = false;

static double currentTime;


LRESULT CALLBACK Win32WindowProc (HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        case WM_QUIT:
        case WM_CLOSE: {
            gRunning = false;
        } break;
        default:
        {
            return DefWindowProc(windowHandle, message, wParam, lParam);
        }
    }

    return 0;
}


int WINAPI WinMain (HINSTANCE instance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX w = {};
    w.cbSize = sizeof(WNDCLASSEX);
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = Win32WindowProc;
    w.hInstance = instance;
    w.hIcon = NULL;
    w.hCursor = NULL;
    w.lpszClassName = "OpenGL Superbible Class";
    w.hIconSm = NULL;

    if (!RegisterClassEx(&w))
    {
        OutputDebugStringA("Could not create window\n");

        return 1;
    }

    HWND windowHandle = CreateWindow(
        "OpenGL Superbible Class",
        gInfo.title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        0, 0,
        instance,
        0
    );

    if (!windowHandle)
    {
        OutputDebugStringA("Could not create window\n");

        return 1;
    }

#if 0
    BOOL console = AllocConsole();

    if (!console)
    {
        OutputDebugStringA("Failed to create console.\n");
    }
    else
    {
        AttachConsole(GetCurrentProcessId());
        freopen("CON", "w", stdout);
        SetForegroundWindow(windowHandle);
    }
#endif

    auto deviceContext = GetDC(windowHandle);

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

    auto renderContext = wglCreateContext(deviceContext);

    if (!renderContext)
    {
        OutputDebugStringA("Could not create initial render context.\n");

        return 1;
    }

    wglMakeCurrent(deviceContext, renderContext);

    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARB)wglGetProcAddress("wglGetExtensionsStringARB");

    if (!wglGetExtensionsStringARB)
    {
        OutputDebugStringA("Failed to get wglGetExtensionsStringARB address.\n");

        return 1;
    }

    // NOTE (Emil): Get all the wgl extensions supported by the current device.
    const char * extensions = wglGetExtensionsStringARB(deviceContext);

    const char * cc         = strstr(extensions, "WGL_ARB_create_context");
    const char * ccp        = strstr(extensions, "WGL_ARB_create_context_profile");
    const char * robustness = strstr(extensions, "WGL_ARB_create_context_robustness");

    if (!(cc && ccp))
    {
        OutputDebugStringA("Could not find WGL_ARB_create_context or WGL_ARB_create_context_profile in the WGL extensions.\n");

        return 1;
    }

    if (!robustness)
    {
        OutputDebugStringA("WGL_ARB_create_context_robustness not available.\n");

        return 1;
    }

    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARB)wglGetProcAddress("wglCreateContextAttribsARB");

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

    int32_t attributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, gGLInfo.major,
        WGL_CONTEXT_MINOR_VERSION_ARB, gGLInfo.minor,
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

#if 0
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARB)wglGetProcAddress("wglGetExtensionsStringARB");

    if (!wglGetExtensionsStringARB)
    {
        OutputDebugStringA("Failed to reacquire wglGetExtensionsStringARB");

        return 1;
    }

    const char * wglExtensions = wglGetExtensionsStringARB(deviceContext);

    OutputDebugStringA(wglExtensions);
#endif

    LoadGLProcs();

    if (!glGetIntegerv)
    {
        OutputDebugStringA("Could not find glGetIntegerv.\n");

        return 1;
    }

    int32_t major;
    int32_t minor;

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    if (major < 3)
    {
        OutputDebugStringA("OpenGL major version earlier than 3.\n");

        return 1;
    }

    currentTime = 0.0f;

    LARGE_INTEGER startTime, endTime, elapsed;
    LARGE_INTEGER frequency;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startTime);

    gRunning = true;

    Init();

    while (gRunning)
    {
        MSG message;

        while (PeekMessage(&message, windowHandle, 0, 0, PM_REMOVE))
        {
            switch (message.message)
            {
                case WM_KEYDOWN:
                {
                    if (message.wParam == VK_ESCAPE)
                    {
                        PostQuitMessage(0);
                        gRunning = false;
                    }
                } break;
                default:
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                } break;
            }
        }

        QueryPerformanceCounter(&endTime);

        elapsed.QuadPart = endTime.QuadPart - startTime.QuadPart;

        currentTime = elapsed.QuadPart * (1.0 / (double)frequency.QuadPart);

        Render(currentTime);

        SwapBuffers(deviceContext);
    }

    return 0;
}
