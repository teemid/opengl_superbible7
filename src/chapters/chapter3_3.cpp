#include <cmath>

#include "chapters.h"


static GLchar * vertex_source = SHADER(450 core,
    layout (location = 0) in vec4 offset;
    layout (location = 1) in vec4 color;


    out VS_OUT
    {
        vec4 color;
    } vs_out;


    void main (void)
    {
        const vec4 verticies[3] = vec4[3](
            vec4( 0.25,  -0.25, 0.5, 1.0),
            vec4(-0.25,  -0.25, 0.5, 1.0),
            vec4( 0.25,   0.25, 0.5, 1.0)
        );

        gl_Position = verticies[gl_VertexID] + offset;

        vs_out.color = color;
    }
);

static GLchar * fragment_source = SHADER(450 core,
    in VS_OUT
    {
        vec4 color;
    } fs_in;

    out vec4 color;

    void main (void)
    {
        color = fs_in.color;
    }
);


static GLuint program;
static GLuint vertex_array_object;


void C33Init (void)
{
    GLuint vertex_shader = CompileShader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = CompileShader(GL_FRAGMENT_SHADER, fragment_source);

    program = CreateProgram(2, vertex_shader, fragment_shader);

    glCreateVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}


void C33Render (double currentTime)
{
    const GLfloat color[] = {
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

    GLfloat fragment_color[] = { 0.0f, 1.0f, 1.0f, 1.0f };

    glVertexAttrib4fv(0, attrib);
    glVertexAttrib4fv(1, fragment_color);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void C33Shutdown (void)
{
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertex_array_object);
}
