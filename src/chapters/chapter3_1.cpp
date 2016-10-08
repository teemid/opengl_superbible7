#include <cmath>

#include "chapters.h"

using namespace GLFramework;


static GLchar * vertex_source = SHADER(450 core,
    layout (location = 0) in vec4 offset;


    void main (void)
    {
        const vec4 verticies[3] = vec4[3](
            vec4( 0.25,  -0.25, 0.5, 1.0),
            vec4(-0.25,  -0.25, 0.5, 1.0),
            vec4( 0.25,   0.25, 0.5, 1.0)
        );

        gl_Position = verticies[gl_VertexID] + offset;
    }
);

static GLchar * fragment_source = SHADER(450 core,
    out vec4 color;

    void main (void)
    {
        color = vec4(0.0, 0.0, 1.0, 1.0);
    }
);

static GLuint program;
static GLuint vertex_array_object;


void Chapter3_1::Init (void)
{
    GLuint vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_source);

    program = CreateProgram(2, vertex_shader, fragment_shader);

    glCreateVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}


void Chapter3_1::Render (double currentTime)
{
    static const GLfloat color[] = {
        (float)sin(currentTime) * 0.5f + 0.5f,
        (float)cos(currentTime) * 0.5f + 0.5f,
        0.0f, 1.0f
    };

    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(program);

    GLfloat attrib[] = {
        (float)sin(currentTime) * 0.5f,
        (float)cos(currentTime) * 0.6f,
        0.0f, 0.0f
    };

    glVertexAttrib4fv(0, attrib);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Chapter3_1::Shutdown (void)
{
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertex_array_object);
}
