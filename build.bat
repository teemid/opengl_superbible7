@echo off


IF "%1" == "tools" GOTO tools
IF "%1" == "opengl" GOTO opengl

REM This is on top because it's the default action
:opengl
    SET COMPILER_OPTIONS=/nologo /c /Od /EHsc /MTd /Fdbuild\ /Fobuild\ /Zi /W3
    SET INCLUDE_DIR=include
    SET LIB_FILES=user32.lib gdi32.lib opengl32.lib
    SET LINKER_FLAGS=/NOLOGO /OUT:openglsb.exe


    FOR /r %%f IN ("src\*.cpp") DO cl %COMPILER_OPTIONS% /I %INCLUDE_DIR% "%%f"

    cl %COMPILER_OPTIONS% /I %INCLUDE_DIR% main.cpp

    PUSHD build

    link %LIB_FILES% %LINKER_FLAGS% *.obj

    POPD

    GOTO end

:tools
    SET COMPILER_OPTIONS=/nologo /EHsc
    SET TOOLS_FILES=glGenerate.cpp

    PUSHD tools

    cl %COMPILER_OPTIONS% %TOOLS_FILES%

    POPD

    GOTO end

:end
    ECHO "Finished!"
