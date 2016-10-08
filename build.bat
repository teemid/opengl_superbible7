@echo off

IF "%1" == "tools" GOTO tools
IF "%1" == "opengl" GOTO opengl

REM This is on top because it's the default action
:opengl
    SET COMPILER_OPTIONS=/nologo /c /FS /Od /EHsc /MTd /Fdbuild\ /Fobuild\ /Zi /W3 /wd4996
    SET INCLUDE_DIR=include
    SET LIB_FILES=user32.lib gdi32.lib opengl32.lib
    SET LINKER_FLAGS=/NOLOGO /DEBUG /OUT:openglsb.exe

    FOR /r src\ %%f IN ("*.cpp") DO cl %COMPILER_OPTIONS% /I %INCLUDE_DIR% "%%f"

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
