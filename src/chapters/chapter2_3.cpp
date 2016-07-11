#include <cmath>

#include "chapters.h"


static GLchar * vertex_source = SHADER(450 core,
    void main (void)
    {
        gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
    }
);

static GLchar * fragment_source = SHADER(450 core,
    out vec4 color;

    void main (void)
    {
        color = vec4(0.0, 1.0, 1.0, 1.0);
    }
);


static GLuint program;
static GLuint vertex_array_object;


void C23Init (void)
{
    GLuint vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_source);

    program = CreateProgram(2, vertex_shader, fragment_shader);

    glCreateVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}


void C23Render (double currentTime)
{
    const GLfloat color[] = {
        (float)sin(currentTime) * 0.5f + 0.5f,
        (float)cos(currentTime) * 0.5f + 0.5f,
        0.0f, 1.0f
    };

    glClearBufferfv(GL_COLOR, 0, color);

    glPointSize(40.0f);

    glUseProgram(program);

    glDrawArrays(GL_POINTS, 0, 1);
}


void C23Shutdown (void)
{
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertex_array_object);
}
