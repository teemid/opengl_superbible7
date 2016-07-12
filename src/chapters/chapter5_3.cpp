#include <cmath>
#include <cstring>

#include "chapters.h"
#include "vmath.h"


static GLchar * vertex_source = SHADER(450 core,
    layout (location = 0) in vec4 position;

    void main (void)
    {
        gl_Position = position;
    }
);

static GLchar * fragment_source = SHADER(450 core,
    out vec4 color;

    void main (void)
    {
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }
);


static GLuint program;
static GLuint vao;
static GLuint buffer;


static const float data[] =
{
     0.25, -0.25, 0.5, 1.0,
    -0.25, -0.25, 0.5, 1.0,
     0.25,  0.25, 0.5, 1.0
};


void C53Init (void)
{
    GLuint vertex_shader       = CompileShader(GL_VERTEX_SHADER,          vertex_source);
    GLuint fragment_shader     = CompileShader(GL_FRAGMENT_SHADER,        fragment_source);

    program = CreateProgram(2, vertex_shader, fragment_shader);

    glCreateBuffers(1, &buffer);

    glNamedBufferStorage(buffer, 1024 * 1024, NULL, GL_MAP_WRITE_BIT);

    // Note that it is generally preferred to use glMapBufferRange/glMapNamedBufferRange
    // instead of glMapBuffer/glMapNamedBuffer because of increased control and a
    // stronger contract than the latter provides.
    void * ptr = glMapNamedBuffer(buffer, GL_WRITE_ONLY);

    memcpy(ptr, data, sizeof(data));

    // Tell OpenGL that we're done with the pointer.
    glUnmapNamedBuffer(buffer);

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // First, bind a vertex buffer to the VAO
    glVertexArrayVertexBuffer(
        vao,                // Vertex array object
        0,                  // First vertex buffer binding
        buffer,             // Buffer object
        0,                  // Start from the beginning
        sizeof(vmath::vec4) // Each vertex is one vec4
    );

    // Now, describe the data to OpenGL, tell it where it is, and turn on automatic
    // vertex fetching for the specified attribute.
    glVertexArrayAttribFormat(
        vao,        // Vertex array object
        0,          // First attribute
        4,          // Four components
        GL_FLOAT,   // Floating-point data
        GL_FALSE,   // Normalized - ignored for floats
        0           // First element of the vertex
    );

    glEnableVertexArrayAttrib(vao, 0);
}


void C53Render (double currentTime)
{
    const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(program);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void C53Shutdown (void)
{
    glDisableVertexArrayAttrib(vao, 0);

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vao);
}
