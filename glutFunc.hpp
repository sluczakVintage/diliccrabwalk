#ifndef GLUTFUNC_H
#define GLUTFUNC_H

#include <windows.h>
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <iostream>
#include "stdlib.h"

#include "glut.h"
#include "Camera.hpp"

namespace glut
{

// Variables Necessary For FogCoordfEXT
#define GL_FOG_COORDINATE_SOURCE_EXT	0x8450					// Value Taken From GLEXT.H
#define GL_FOG_COORDINATE_EXT		0x8451					// Value Taken From GLEXT.H
typedef void (APIENTRY * PFNGLFOGCOORDFEXTPROC) (GLfloat coord);		// Declare Function Prototype

void mouse (int button, int state, int x, int y);
void motion (int x, int y);
void pmotion (int x, int y);
void keyboard (unsigned char key, int x, int y);
void special (int key, int x, int y);
GLfloat Rad2Deg (GLfloat Angle);

};

#endif
