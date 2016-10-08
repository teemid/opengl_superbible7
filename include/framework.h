#ifndef SB_FRAMEWORK_H
#define SB_FRAMEWORK_H

#include "gl.h"


namespace GLFramework
{
    #define SHADER(version, code) "#version " #version " \n" #code

    class Application
    {
    public:
        virtual void Init     (void);
        virtual void Render   (double currentTime);
        virtual void Shutdown (void);
    protected:
        GLuint program;
    };

    void GetCurrentGLVersion (int * major, int * minor);
    int  GetExtensionCount (void);
    bool IsExtensionSupported (const char * extension_name);

    GLuint CompileShader(GLenum type, const GLchar * source);
    GLuint CreateProgram(int shader_count, ...);
}


#endif
