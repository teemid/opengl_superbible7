@echo off

SET COMPILER_OPTIONS=/nologo /c /FS /Od /EHsc /MTd /Fdbuild\ /Fobuild\ /Zi /W3 /wd4996
SET INCLUDE_DIR=include
SET LIB_FILES=user32.lib gdi32.lib opengl32.lib
SET LINKER_FLAGS=/NOLOGO /DEBUG /OUT:openglsb.exe

FOR /r src\ %%f IN ("*.cpp") DO cl %COMPILER_OPTIONS% /I %INCLUDE_DIR% "%%f"

PUSHD build

link %LIB_FILES% %LINKER_FLAGS% *.obj

POPD

ECHO "Finished!"
