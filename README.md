While reading and learning from OpenGL SuperBible 7th Edition this will be home to some OpenGL code.


Introduction
------------

    These instructions are only for windows since they make use of a batch file for building the project.


    1. Build the tool for generating opengl function declarations, loads etc. with:

            build tools

    Note: The options are defined in the glGenerat

    2. Make a text file with all the opengl functions needed. Ex:

        glFrontFace
        glCreateShader
        ...

    3. Run the tool for generating files feeding it the filename with opengl names

        glGenerate [text_filename]

    4. Build the application

        build [opengl]
