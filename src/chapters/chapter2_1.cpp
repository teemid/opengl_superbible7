#include <iostream>

#include "chapters.h"

using namespace GLFramework;


void Chapter2_1::Render (double currentTime)
{
    std::cout << "Chapter2_1::Render\n";

    static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, red);
}
