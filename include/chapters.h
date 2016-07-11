#ifndef SB_CHAPTERS
#define SB_CHAPTERS

#include "framework.h"

#define CONCAT_IMPL(x, y) x ## y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#define SET_INIT(func) InitFunc Init = (func)
#define SET_RENDER(func) RenderFunc Render = (func)
#define SET_SHUTDOWN(func) ShutdownFunc Shutdown = (func)

#define CHAPTER_INIT(chapter, n)     CONCAT(C, CONCAT(chapter, CONCAT(n, Init)))
#define CHAPTER_RENDER(chapter, n)   CONCAT(C, CONCAT(chapter, CONCAT(n, Render)))
#define CHAPTER_SHUTDOWN(chapter, n) CONCAT(C, CONCAT(chapter, CONCAT(n, Shutdown)))

#define DECLARE_INIT(chapter, n)      void CHAPTER_INIT(chapter, n) (void)
#define DECLARE_RENDER(chapter, n)    void CHAPTER_RENDER(chapter, n) (double currentTime)
#define DECLARE_SHUTDOWN(chapter, n)  void CHAPTER_SHUTDOWN(chapter, n) (void)

#define DECLARE_FUNCTIONS(chapter, n) DECLARE_INIT(chapter, n); DECLARE_RENDER(chapter, n); DECLARE_SHUTDOWN(chapter, n)
#define SET_FUNCTIONS(init, render, shutdown) SET_INIT(init); SET_RENDER(render); SET_SHUTDOWN(shutdown)


DECLARE_RENDER(2, 1);
DECLARE_RENDER(2, 2);
DECLARE_FUNCTIONS(2, 3);
DECLARE_FUNCTIONS(2, 4);

DECLARE_FUNCTIONS(3, 1);
DECLARE_FUNCTIONS(3, 2);
DECLARE_FUNCTIONS(3, 3);
DECLARE_FUNCTIONS(3, 4);
DECLARE_FUNCTIONS(3, 5);
DECLARE_FUNCTIONS(3, 6);
DECLARE_FUNCTIONS(3, 7);


#endif
