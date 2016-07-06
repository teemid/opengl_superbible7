#ifndef SBGL_GLFUNCTIONS_H
#define SBGL_GLFUNCTIONS_H

#include "GL/glcorearb.h"


typedef void (*glProc) (void);


void LoadGLProcs ();

#include "gen/gl_header.inc"
// extern PFNGLGETINTEGERVPROC         SBglGetIntegerv;
// extern PFNGLCLEARBUFFERFVPROC       SBglClearBufferfv;
// extern PFNGLCREATESHADERPROC        SBglCreateShader;
// extern PFNGLCREATEPROGRAMPROC       SBglCreateProgram;
// extern PFNGLSHADERSOURCEPROC        SBglShaderSource;
// extern PFNGLCOMPILESHADERPROC       SBglCompileShader;
// extern PFNGLATTACHSHADERPROC        SBglAttachShader;
// extern PFNGLLINKPROGRAMPROC         SBglLinkProgram;
// extern PFNGLDELETESHADERPROC        SBglDeleteShader;
// extern PFNGLCREATEVERTEXARRAYSPROC  SBglCreateVertexArrays;
// extern PFNGLBINDVERTEXARRAYPROC     SBglBindVertexArray;
// extern PFNGLDELETEPROGRAMPROC       SBglDeleteProgram;
// extern PFNGLDELETEVERTEXARRAYSPROC  SBglDeleteVertexArrays;
// extern PFNGLUSEPROGRAMPROC          SBglUseProgram;
// extern PFNGLDRAWARRAYSPROC          SBglDrawArrays;
// extern PFNGLPOINTSIZEPROC           SBglPointSize;
// extern PFNGLVERTEXATTRIB4FVPROC     SBglVertexAttrib4fv;
// extern PFNGLPATCHPARAMETERIPROC     SBglPatchParameteri;
// extern PFNGLPOLYGONMODEPROC         SBglPolygonMode;
// extern PFNGLVIEWPORTPROC            SBglViewport;
// extern PFNGLDEPTHRANGEPROC          SBglDepthRange;



// #define glGetIntegerv           SBglGetIntegerv
// #define glClearBufferfv         SBglClearBufferfv
// #define glCreateShader          SBglCreateShader
// #define glCreateProgram         SBglCreateProgram
// #define glShaderSource          SBglShaderSource
// #define glCompileShader         SBglCompileShader
// #define glAttachShader          SBglAttachShader
// #define glLinkProgram           SBglLinkProgram
// #define glDeleteShader          SBglDeleteShader
// #define glCreateVertexArrays    SBglCreateVertexArrays
// #define glBindVertexArray       SBglBindVertexArray
// #define glDeleteProgram         SBglDeleteProgram
// #define glDeleteVertexArrays    SBglDeleteVertexArrays
// #define glUseProgram            SBglUseProgram
// #define glDrawArrays            SBglDrawArrays
// #define glPointSize             SBglPointSize
// #define glVertexAttrib4fv       SBglVertexAttrib4fv
// #define glPatchParameteri       SBglPatchParameteri
// #define glPolygonMode           SBglPolygonMode
// #define glViewport              SBglViewport
// #define glDepthRange            SBglDepthRange

#endif
