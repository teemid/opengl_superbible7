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

    glGetIntegerv           = (PFNGLGETINTEGERVPROC)GetProc("glGetIntegerv");
    glClearBufferfv         = (PFNGLCLEARBUFFERFVPROC)GetProc("glClearBufferfv");
    glCreateShader          = (PFNGLCREATESHADERPROC)GetProc("glCreateShader");
    glShaderSource          = (PFNGLSHADERSOURCEPROC)GetProc("glShaderSource");
    glCompileShader         = (PFNGLCOMPILESHADERPROC)GetProc("glCompileShader");
    glCreateProgram         = (PFNGLCREATEPROGRAMPROC)GetProc("glCreateProgram");
    glAttachShader          = (PFNGLATTACHSHADERPROC)GetProc("glAttachShader");
    glLinkProgram           = (PFNGLLINKPROGRAMPROC)GetProc("glLinkProgram");
    glDeleteShader          = (PFNGLDELETESHADERPROC)GetProc("glDeleteShader");
    glCreateVertexArrays    = (PFNGLCREATEVERTEXARRAYSPROC)GetProc("glCreateVertexArrays");
    glBindVertexArray       = (PFNGLBINDVERTEXARRAYPROC)GetProc("glBindVertexArray");
    glDeleteProgram         = (PFNGLDELETEPROGRAMPROC)GetProc("glDeleteProgram");
    glDeleteVertexArrays    = (PFNGLDELETEVERTEXARRAYSPROC)GetProc("glDeleteVertexArrays");
    glUseProgram            = (PFNGLUSEPROGRAMPROC)GetProc("glUseProgram");
    glDrawArrays            = (PFNGLDRAWARRAYSPROC)GetProc("glDrawArrays");
    glPointSize             = (PFNGLPOINTSIZEPROC)GetProc("glPointSize");

    FreeLibrary(glDLL);
}


PFNGLGETINTEGERVPROC            glGetIntegerv;
PFNGLCLEARBUFFERFVPROC          glClearBufferfv;
PFNGLCREATESHADERPROC           glCreateShader;
PFNGLSHADERSOURCEPROC           glShaderSource;
PFNGLCOMPILESHADERPROC          glCompileShader;
PFNGLCREATEPROGRAMPROC          glCreateProgram;
PFNGLATTACHSHADERPROC           glAttachShader;
PFNGLLINKPROGRAMPROC            glLinkProgram;
PFNGLDELETESHADERPROC           glDeleteShader;
PFNGLCREATEVERTEXARRAYSPROC     glCreateVertexArrays;
PFNGLBINDVERTEXARRAYPROC        glBindVertexArray;
PFNGLDELETEPROGRAMPROC          glDeleteProgram;
PFNGLDELETEVERTEXARRAYSPROC     glDeleteVertexArrays;
PFNGLUSEPROGRAMPROC             glUseProgram;
PFNGLDRAWARRAYSPROC             glDrawArrays;
PFNGLPOINTSIZEPROC              glPointSize;
