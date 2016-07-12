#ifndef SB_CHAPTERS
#define SB_CHAPTERS

#include "framework.h"

#define CONCAT_IMPL(x, y) x ## y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#define SET_INIT(func) InitFunc Init = (func)
#define SET_RENDER(func) RenderFunc Render = (func)
#define SET_SHUTDOWN(func) ShutdownFunc Shutdown = (func)

#define CHAPTER_INIT(chapter, n)      CONCAT(C, CONCAT(chapter, CONCAT(n, Init)))
#define CHAPTER_RENDER(chapter, n)    CONCAT(C, CONCAT(chapter, CONCAT(n, Render)))
#define CHAPTER_SHUTDOWN(chapter, n)  CONCAT(C, CONCAT(chapter, CONCAT(n, Shutdown)))

#define DECLARE_INIT(chapter, n)      void CHAPTER_INIT(chapter, n) (void)
#define DECLARE_RENDER(chapter, n)    void CHAPTER_RENDER(chapter, n) (double currentTime)
#define DECLARE_SHUTDOWN(chapter, n)  void CHAPTER_SHUTDOWN(chapter, n) (void)

#define DECLARE_FUNCTIONS(chapter, n) DECLARE_INIT(chapter, n); DECLARE_RENDER(chapter, n); DECLARE_SHUTDOWN(chapter, n)
#define SET_FUNCTIONS(init, render, shutdown) SET_INIT(init); SET_RENDER(render); SET_SHUTDOWN(shutdown)

// Clear background to red
DECLARE_RENDER(2, 1);
// Clear background based on time since the application started.
DECLARE_RENDER(2, 2);
// Basic shaders for drawing a single point.
DECLARE_FUNCTIONS(2, 3);
// Hello triangle.
DECLARE_FUNCTIONS(2, 4);

// First shader attrib, setting an offset based on time to each vertex.
DECLARE_FUNCTIONS(3, 1);
// Adds color as a shader attribute.
DECLARE_FUNCTIONS(3, 2);
// Uses a shader block instead of variables.
DECLARE_FUNCTIONS(3, 3);
// Basic tessellation shaders for the triangle.
DECLARE_FUNCTIONS(3, 4);
// Geometry shader transforming vertices in triangles to points.
DECLARE_FUNCTIONS(3, 5);
// Fragment shader that gives color to each fragment based on position.
DECLARE_FUNCTIONS(3, 6);
// Shows color interpolation when each vertex of a triangle is given a color.
DECLARE_FUNCTIONS(3, 7);

// Memory transfer with glBufferSubData.
DECLARE_FUNCTIONS(5, 1);
// Manual memory copy with glMapBuffer/glMapNamedBuffer.
DECLARE_FUNCTIONS(5, 2);
// Vertex Attrib Arrays
DECLARE_FUNCTIONS(5, 3);
// Multiple Vertex array attrib bindings (separated attributes).
DECLARE_FUNCTIONS(5, 4);
// Multiple Vertex array attrib bindings (interleaved attributes).
DECLARE_FUNCTIONS(5, 5);

#endif
