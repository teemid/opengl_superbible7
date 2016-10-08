#include <cmath>
#include <cstring>

#include "chapters.h"
#include "vmath.h"

using namespace GLFramework;


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
static GLuint buffer;

struct vertex
{
    float x;
    float y;
    float z;

    float r;
    float g;
    float b;
};


static const float vertices[] =
{
     0.25, -0.25, 0.5, 1.0, 0.0, 0.0,
    -0.25, -0.25, 0.5, 0.0, 1.0, 0.0,
     0.25,  0.25, 0.5, 0.0, 0.0, 1.0
};


void Chapter5_5::Init (void)
{
    GLuint vertex_shader       = CompileShader(GL_VERTEX_SHADER,          vertex_source);
    GLuint fragment_shader     = CompileShader(GL_FRAGMENT_SHADER,        fragment_source);

    program = CreateProgram(2, vertex_shader, fragment_shader);

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glCreateBuffers(1, &buffer);
    glNamedBufferStorage(buffer, sizeof(vertices), vertices, 0);

    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayAttribBinding(vao, 1, 0);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3);
    glEnableVertexArrayAttrib(vao, 1);

    glVertexArrayVertexBuffer(vao, 0, buffer, 0, sizeof(vertex));
}


void Chapter5_5::Render (double currentTime)
{
    static const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(program);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Chapter5_5::Shutdown (void)
{
    glDisableVertexArrayAttrib(vao, 0);
    glDisableVertexArrayAttrib(vao, 1);

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vao);
}
