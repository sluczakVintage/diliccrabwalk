#ifndef GLUTFUNC_H
#define GLUTFUNC_H

#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include "stdlib.h"

#include "glut.h"
#include "Drawable.hpp"
#include "camLights.hpp"
#include <math.h>


// zestaw struktura + funkcje operacji na wektorach w celu wyliczenia

struct Vector3f {
	Vector3f() : x_(0), y_(0), z_(0) {};
	Vector3f(float x, float y, float z) : x_(x), y_(y), z_(z) {};
	float x_;
	float y_;
	float z_;
};

Vector3f substractV3f(Vector3f v1, Vector3f v2);
Vector3f crossProduct(Vector3f v1, Vector3f v2);
Vector3f normalize(Vector3f v); 

//wyliczanie wartosci w stopniach <=> radianach
GLfloat Deg2Rad (GLfloat Rad);
GLfloat Rad2Deg (GLfloat Angle);

namespace glut
{
	//metody do obslugi przez glut
	void myTimer(int value);
	void mouse (int button, int state, int x, int y);
	void motion (int x, int y);
	void pmotion (int x, int y);
	void keyboard (unsigned char key, int x, int y);
	void special (int key, int x, int y);
};

#endif
