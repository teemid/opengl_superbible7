#include <cassert>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <memory>

#include "chapters.h"
#include "framework.h"
#include "memory.h"
#include "gl.h"
#include "platform/wgl.h"
#include "vmath.h"


static bool gRunning = false;
static double currentTime;
static HWND windowHandle;
static const char * windowTitle = "OpenGL Superbible 7";


static int Win32CreateWindow(HINSTANCE instance);
static void Win32AttachConsole (void);
static LRESULT CALLBACK Win32WindowProc (HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain (HINSTANCE instance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    assert(Win32CreateWindow(instance) == 0);

    HDC deviceContext = GetDC(windowHandle);

    assert(GLFramework::CreateContext(windowHandle, deviceContext, 4, 5) == 0);

    ShowWindow(windowHandle, nCmdShow);

#if 1
    Win32AttachConsole();
#endif

    GLFramework::LoadProcs();

    int major;
    int minor;

    GLFramework::GetCurrentGLVersion(&major, &minor);

    if (major < 3)
    {
        OutputDebugStringA("OpenGL major version earlier than 3.\n");

        return 1;
    }

    printf("OpenGL version: %d.%d\n\n", major, minor);

    int extension_count = GLFramework::GetExtensionCount();

    printf("Number of OpenGL extensions available: %d\n\n", extension_count);

    // for (int i = 0; i < extension_count; i++)
    // {
    //     printf("%s\n", (char *)glGetStringi(GL_EXTENSIONS, i));
    // }

    GLFramework::Application * app = new Chapter5_5();

    currentTime = 0.0f;

    LARGE_INTEGER startTime, endTime, elapsed;
    LARGE_INTEGER frequency;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startTime);

    gRunning = true;

    app->Init();

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

        app->Render(currentTime);

        SwapBuffers(deviceContext);
    }

    app->Shutdown();

    return 0;
}


static int Win32CreateWindow(HINSTANCE instance)
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

    windowHandle = CreateWindow(
        "OpenGL Superbible Class",
        windowTitle,
        WS_OVERLAPPEDWINDOW,
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

    return 0;
}


static void Win32AttachConsole (void)
{
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
}

static LRESULT CALLBACK Win32WindowProc (HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
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
