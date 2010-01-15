#ifndef GLUTFUNC_H
#define GLUTFUNC_H

#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include "stdlib.h"

#include "glut.h"
#include "Camera.hpp"

namespace glut
{

// mgla
#define GL_FOG_COORDINATE_SOURCE_EXT	0x8450					
#define GL_FOG_COORDINATE_EXT		0x8451					
typedef void (APIENTRY * PFNGLFOGCOORDFEXTPROC) (GLfloat coord);		



void createProjection();
void mouse (int button, int state, int x, int y);
void motion (int x, int y);
void pmotion (int x, int y);
void keyboard (unsigned char key, int x, int y);
void special (int key, int x, int y);
GLfloat Rad2Deg (GLfloat Angle);

};

#endif
