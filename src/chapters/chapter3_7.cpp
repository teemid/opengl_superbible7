#include <cmath>

#include "chapters.h"


static GLchar * vertex_source = SHADER(450 core,
    out vec4 vs_color;


    void main (void)
    {
        const vec4 verticies[3] = vec4[3](
            vec4( 0.25,  -0.25, 0.5, 1.0),
            vec4(-0.25,  -0.25, 0.5, 1.0),
            vec4( 0.25,   0.25, 0.5, 1.0)
        );

        const vec4 colors[] = vec4[3](
            vec4( 1.0, 0.0, 0.0, 1.0),
            vec4( 0.0, 1.0, 0.0, 1.0),
            vec4( 0.0, 0.0, 1.0, 1.0)
        );

        gl_Position = verticies[gl_VertexID];

        vs_color = colors[gl_VertexID];
    }
);

static GLchar * fragment_source = SHADER(450 core,
    in vec4 vs_color;

    out vec4 color;

    void main (void)
    {
        color = vs_color;
    }
);


static GLuint program;
static GLuint vertex_array_object;


void C37Init (void)
{
    GLuint vertex_shader       = CompileShader(GL_VERTEX_SHADER,          vertex_source);
    GLuint fragment_shader     = CompileShader(GL_FRAGMENT_SHADER,        fragment_source);

    program = CreateProgram(2, vertex_shader, fragment_shader);

    glCreateVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}


void C37Render (double currentTime)
{
    const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(program);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void C37Shutdown (void)
{
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertex_array_object);
}
