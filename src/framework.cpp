#include <cmath>

#include "framework.h"
#include "glfunctions.h"


#define SHADER(version, code) "#version " #version " core \n" #code


// #define SB_TESSELLATION 1


static const GLchar * vertex_shader_source = SHADER(450,
    layout (location = 0) in vec4 offset;
    layout (location = 1) in vec4 color;

    out VS_OUT
    {
        vec4 color;
    } vs_out;


    void main(void)
    {
        const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25,  0.5,  1.0),
                                         vec4(-0.25, -0.25,  0.5,  1.0),
                                         vec4( 0.25,  0.25,  0.5,  1.0));

        gl_Position = vertices[gl_VertexID] + offset;

        vs_out.color = color;
    }
);

static const GLchar * fragment_shader_source = SHADER(450,
    in VS_OUT
    {
        vec4 color;
    } fs_in;

    out vec4 color;

    void main(void)
    {
        color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
);

#if defined(SB_TESSELLATION)

static const GLchar * tess_control_source = SHADER(450,
    layout (vertices = 3) out;


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

static const GLchar * tess_eval_source = SHADER(450,
    layout (triangles, equal_spacing, cw) in;


    void main (void)
    {
        gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
                       gl_TessCoord.y * gl_in[1].gl_Position +
                       gl_TessCoord.z * gl_in[2].gl_Position);
    }
);

#endif


static const GLchar * geometry_source = SHADER(450,
    layout (triangles) in;
    layout (points, max_vertices = 3) out;

    void main (void)
    {
        int i;

        for (i = 0; i < gl_in.length(); i++)
        {
            gl_Position = gl_in[i].gl_Position;
            EmitVertex();
        }
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

    GLfloat attrib[] = {
        (float)sin(currentTime) * 0.5f,
        (float)cos(currentTime) * 0.6f,
        0.0f,
        0.0f
    };

    GLfloat attribColor[] = { 0.8f, 0.0f, 1.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(program);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glVertexAttrib4fv(0, attrib);
    glVertexAttrib4fv(1, attribColor);

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
    GLuint vertex_shader, fragment_shader;
#if defined(SB_TESSELLATION)
    GLuint tess_control_shader, tess_eval_shader;
#endif
    GLuint program;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);

#if defined(SB_TESSELLATION)
    tess_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tess_control_shader, 1, &tess_control_source, NULL);
    glCompileShader(tess_control_shader);

    tess_eval_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tess_eval_shader, 1, &tess_eval_source, NULL);
    glCompileShader(tess_eval_shader);
#endif
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
#if defined(SB_TESSELLATION)
    glAttachShader(program, tess_control_shader);
    glAttachShader(program, tess_eval_shader);
#endif
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}
