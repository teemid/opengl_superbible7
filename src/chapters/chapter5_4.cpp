#include <cmath>
#include <cstring>

#include "chapters.h"
#include "vmath.h"


static GLchar * vertex_source = SHADER(450 core,
    layout (location = 0) in vec4 position;
    layout (location = 1) in vec4 color;

    out vec4 vs_color;

    void main (void)
    {
        gl_Position = position;

        vs_color = color;
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
static GLuint vao;
static GLuint buffer[2];


static const float positions[] =
{
     0.25, -0.25, 0.5, 1.0,
    -0.25, -0.25, 0.5, 1.0,
     0.25,  0.25, 0.5, 1.0
};


static const float colors[] =
{
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0
};


void C54Init (void)
{
    GLuint vertex_shader       = CompileShader(GL_VERTEX_SHADER,          vertex_source);
    GLuint fragment_shader     = CompileShader(GL_FRAGMENT_SHADER,        fragment_source);

    program = CreateProgram(2, vertex_shader, fragment_shader);

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glCreateBuffers(2, &buffer[0]);

    glNamedBufferStorage(buffer[0], sizeof(positions), positions, 0);
    glVertexArrayVertexBuffer(vao, 0, buffer[0], 0, sizeof(vmath::vec4));
    glVertexArrayAttribFormat(vao, 0, sizeof(positions[0]), GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glEnableVertexArrayAttrib(vao, 0);

    glNamedBufferStorage(buffer[1], sizeof(colors), colors, 0);
    glVertexArrayVertexBuffer(vao, 1, buffer[1], 0, sizeof(vmath::vec4));
    glVertexArrayAttribFormat(vao, 0, sizeof(colors[0]), GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 1, 1);
    glEnableVertexArrayAttrib(vao, 1);
}


void C54Render (double currentTime)
{
    const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(program);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void C54Shutdown (void)
{
    glDisableVertexArrayAttrib(vao, 0);
    glDisableVertexArrayAttrib(vao, 1);

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vao);
}
