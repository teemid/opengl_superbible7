#include <cmath>

#include "chapters.h"


static GLchar * vertex_source = SHADER(450 core,
    void main (void)
    {
        const vec4 verticies[3] = vec4[3](
            vec4( 0.25,  -0.25, 0.5, 1.0),
            vec4(-0.25,  -0.25, 0.5, 1.0),
            vec4( 0.25,   0.25, 0.5, 1.0)
        );

        gl_Position = verticies[gl_VertexID];
    }
);

static GLchar * fragment_source = SHADER(450 core,
    out vec4 color;

    void main (void)
    {
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }
);


static GLchar * tess_control_source = SHADER(450 core,
    layout(vertices = 3) out;


    void main (void)
    {
        if (gl_InvocationID == 0)
        {
            gl_TessLevelInner[0] = 5.0;
            gl_TessLevelOuter[0] = 5.0;
            gl_TessLevelOuter[1] = 5.0;
            gl_TessLevelOuter[2] = 5.0;
        }

        gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    }
);


static GLchar * tess_eval_source = SHADER(450 core,
    layout (triangles, equal_spacing, cw) in;


    void main (void)
    {
        gl_Position = (
            gl_TessCoord.x * gl_in[0].gl_Position +
            gl_TessCoord.y * gl_in[1].gl_Position +
            gl_TessCoord.z * gl_in[2].gl_Position
        );
    }
);


static GLuint program;
static GLuint vertex_array_object;


void C34Init (void)
{
    GLuint vertex_shader       = CompileShader(GL_VERTEX_SHADER,          vertex_source);
    GLuint fragment_shader     = CompileShader(GL_FRAGMENT_SHADER,        fragment_source);
    GLuint tess_control_shader = CompileShader(GL_TESS_CONTROL_SHADER,    tess_control_source);
    GLuint tess_eval_shader    = CompileShader(GL_TESS_EVALUATION_SHADER, tess_eval_source);

    program = CreateProgram(4, vertex_shader, fragment_shader, tess_control_shader, tess_eval_shader);

    glCreateVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void C34Render (double currentTime)
{
    const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(program);

    glDrawArrays(GL_PATCHES, 0, 3);
}


void C34Shutdown (void)
{
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertex_array_object);
}
