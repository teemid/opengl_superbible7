#ifndef SBGL_GLFUNCTIONS_H
#define SBGL_GLFUNCTIONS_H

#include "GL/glcorearb.h"


typedef void (*glProc) (void);


void LoadGLProcs ();


extern PFNGLGETINTEGERVPROC         SBglGetIntegerv;
extern PFNGLCLEARBUFFERFVPROC       SBglClearBufferfv;
extern PFNGLCREATESHADERPROC        SBglCreateShader;
extern PFNGLCREATEPROGRAMPROC       SBglCreateProgram;
extern PFNGLSHADERSOURCEPROC        SBglShaderSource;
extern PFNGLCOMPILESHADERPROC       SBglCompileShader;
extern PFNGLATTACHSHADERPROC        SBglAttachShader;
extern PFNGLLINKPROGRAMPROC         SBglLinkProgram;
extern PFNGLDELETESHADERPROC        SBglDeleteShader;
extern PFNGLCREATEVERTEXARRAYSPROC  SBglCreateVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC     SBglBindVertexArray;
extern PFNGLDELETEPROGRAMPROC       SBglDeleteProgram;
extern PFNGLDELETEVERTEXARRAYSPROC  SBglDeleteVertexArrays;
extern PFNGLUSEPROGRAMPROC          SBglUseProgram;
extern PFNGLDRAWARRAYSPROC          SBglDrawArrays;
extern PFNGLPOINTSIZEPROC           SBglPointSize;



#define glGetIntegerv           SBglGetIntegerv
#define glClearBufferfv         SBglClearBufferfv
#define glCreateShader          SBglCreateShader
#define glCreateProgram         SBglCreateProgram
#define glShaderSource          SBglShaderSource
#define glCompileShader         SBglCompileShader
#define glAttachShader          SBglAttachShader
#define glLinkProgram           SBglLinkProgram
#define glDeleteShader          SBglDeleteShader
#define glCreateVertexArrays    SBglCreateVertexArrays
#define glBindVertexArray       SBglBindVertexArray
#define glDeleteProgram         SBglDeleteProgram
#define glDeleteVertexArrays    SBglDeleteVertexArrays
#define glUseProgram            SBglUseProgram
#define glDrawArrays            SBglDrawArrays
#define glPointSize             SBglPointSize

#endif
