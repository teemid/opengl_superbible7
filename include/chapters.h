#ifndef SB_CHAPTERS
#define SB_CHAPTERS

#include "framework.h"

#define CONCAT_IMPL(x, y) x ## y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#define CHAPTER_BEGIN(chapter, sub) \
    class CONCAT(Chapter, CONCAT(chapter, CONCAT(_, sub))) : public GLFramework::Application \
    { \
    public:

#define CHAPTER_END() }

#define DESCRIPTION(comment)

#define INIT     void Init     (void)
#define RENDER   void Render   (double currentTime)
#define SHUTDOWN void Shutdown (void)

CHAPTER_BEGIN(2, 1)
    DESCRIPTION("Clear background to red.")
    RENDER;
CHAPTER_END();

CHAPTER_BEGIN(2, 2)
    DESCRIPTION("Clear background based on time since the application started.")
    RENDER;
CHAPTER_END();

CHAPTER_BEGIN(2, 3)
    DESCRIPTION("Basic shaders for drawing a single point.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(2, 4)
    DESCRIPTION("Hello triangle.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(3, 1)
    DESCRIPTION("First shader attrib setting an offset based on time to each vertex.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(3, 2)
    DESCRIPTION("Adds color as a shader attribute.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(3, 3)
    DESCRIPTION("Uses a shader block instead of variables.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(3, 4)
    DESCRIPTION("Basic tessellation shaders for the triangle.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(3, 5)
    DESCRIPTION("Geometry shader transforming vertices in triangles to points.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(3, 6)
    DESCRIPTION("Fragment shader that gives color to each fragment based on position.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(3, 7)
    DESCRIPTION("Shows color interpolation when each vertex of a triangle is given a color.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(5, 1)
    DESCRIPTION("Memory transfer with glBufferSubData.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(5, 2)
    DESCRIPTION("Manual memory copy with glMapBuffer/glMapNamedBuffer.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(5, 3)
    DESCRIPTION("Vertex Attrib Arrays.")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(5, 4)
    DESCRIPTION("Multiple Vertex array attrib bindings (separated attributes).")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

CHAPTER_BEGIN(5, 5)
    DESCRIPTION("Multiple Vertex array attrib bindings (interleaved attributes).")
    INIT;
    RENDER;
    SHUTDOWN;
CHAPTER_END();

#endif
