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
void mouse (int button, int state, int x, int y);
void motion (int x, int y);
void pmotion (int x, int y);
void keyboard (unsigned char key, int x, int y);
void special (int key, int x, int y);
GLfloat Rad2Deg (GLfloat Angle);

};

#endif
