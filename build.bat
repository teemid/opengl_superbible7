@echo off

SET COMPILER_OPTIONS=/nologo /c /Od /EHsc /MTd /Fdbuild\ /Fobuild\ /Zi /W3
SET INCLUDE_DIR=include
SET LIB_FILES=user32.lib gdi32.lib opengl32.lib
SET LINKER_FLAGS=/NOLOGO /OUT:openglsb.exe


FOR /r %%f IN ("src\*.cpp") DO cl %COMPILER_OPTIONS% /I %INCLUDE_DIR% "%%f"

cl %COMPILER_OPTIONS% /I %INCLUDE_DIR% main.cpp

PUSHD build

link %LIB_FILES% %LINKER_FLAGS% *.obj

POPD
