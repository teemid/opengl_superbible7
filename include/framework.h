#ifndef SBGL_PLATFORM_H
#define SBGL_PLATFORM_H

#include <cstdlib>

#include "glfunctions.h"
#include "GL/wglext.h"

#define ALLOCATE(type, size) (type)malloc(size)
#define DEALLOCATE(ptr) free(ptr)

#define SHADER(version, code) "#version " #version " \n" #code


class Application
{
private:
    GLuint program;
public:
    virtual void Init (void);
    virtual void Render (double currentTime);
    virtual void Shutdown (void);
};

typedef void (*InitFunc)     (void);
typedef void (*RenderFunc)   (double currentTime);
typedef void (*ShutdownFunc) (void);


extern InitFunc     Init;
extern RenderFunc   Render;
extern ShutdownFunc Shutdown;


void DefaultInit (void);
void DefaultRender (double currentTime);
void DefaultShutdown (void);


void    GetCurrentGLVersion (int * major, int * minor);
int     GetExtensionCount (void);
bool    IsExtensionSupported (const char * extension_name);

GLuint CompileShader(GLenum type, const GLchar * source);
GLuint CreateProgram(int shader_count, ...);


#endif
