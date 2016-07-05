#include <cmath>

#include "framework.h"
#include "glfunctions.h"


#define SHADER(version, code) "#version " #version " core \n" #code


static const GLchar * vertex_shader_source = SHADER(450,
    void main(void)
    {
        const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25,  0.5,  1.0),
                                         vec4(-0.25, -0.25,  0.5,  1.0),
                                         vec4( 0.25,  0.25,  0.5,  1.0));

        gl_Position = vertices[gl_VertexID];
    }
);

static const GLchar * fragment_shader_source = SHADER(450,
    out vec4 color;

    void main(void)
    {
        color = vec4(0.0, 0.8, 1.0, 1.0);
    }
);

static GLuint program;
static GLuint vertex_array_object;

static GLuint CompileShaders (const GLchar * vertex_source, const GLchar * fragment_source);





void Render (double currentTime)
{
    const GLfloat color[] = {
        (float)sin(currentTime) * 0.5f + 0.5f,
        (float)cos(currentTime) * 0.5f + 0.5f,
        0.0f, 1.0f
    };

    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(program);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Init (void)
{
    program = CompileShaders(vertex_shader_source, fragment_shader_source);
    glCreateVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}


void Shutdown (void)
{
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertex_array_object);
}


static GLuint CompileShaders (const GLchar * vertex_source, const GLchar * fragment_source)
{
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}
