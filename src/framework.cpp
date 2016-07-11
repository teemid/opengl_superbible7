#include <cstdio>
#include <cmath>
#include <cstdarg>

#include "framework.h"
#include "glfunctions.h"


void DefaultInit (void) { };
void DefaultRender (double currentTime) { };
void DefaultShutdown (void) { };


static GLint extension_count = 0;
static GLubyte ** extensions = NULL;


void GetCurrentGLVersion (int * major, int * minor)
{
    glGetIntegerv(GL_MAJOR_VERSION, major);
    glGetIntegerv(GL_MINOR_VERSION, minor);
}


int GetExtensionCount (void)
{
    GLint count;

    glGetIntegerv(GL_NUM_EXTENSIONS, &count);

    return (int)count;
}

bool IsExtensionSupported (const char * extension_name)
{
    for (int i = 0; i < extension_count; i++)
    {
        const GLubyte * extension = glGetStringi(GL_EXTENSIONS, i);

        if (strcmp((char *)extension, extension_name) == 0)
        {
            return true;
        }
    }

    return false;
}


GLuint CompileShader (GLenum type, const GLchar * source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (GL_FALSE == status)
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        GLchar * log = ALLOCATE(GLchar *, length + 1);
        glGetShaderInfoLog(shader, length, NULL, log);

        printf("Shader fail to compile:\n%s\n", log);

        DEALLOCATE(log);

        glDeleteShader(shader);
    }

    return shader;
}


GLuint CreateProgram (int shader_count, ...)
{
    GLuint program = glCreateProgram();

    va_list arguments;
    va_start(arguments, shader_count);

    for (int i = 0; i < shader_count; i++)
    {
        GLuint shader = va_arg(arguments, GLuint);

        glAttachShader(program, shader);
    }

    va_end(arguments);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (GL_FALSE == status)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        GLchar * log = ALLOCATE(GLchar *, length + 1);
        glGetProgramInfoLog(program, length, &length, log);

        printf("Program failed to link:\n%s\n", log);

        DEALLOCATE(log);

        glDeleteProgram(program);
    }

    return program;
}
