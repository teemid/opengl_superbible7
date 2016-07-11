#include "chapters.h"


void C21Render (double currentTime)
{
    static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, red);
}
