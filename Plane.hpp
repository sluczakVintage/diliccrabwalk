/**
*
*	Klasa opisujaca model podloza
*
*
**/
#ifndef PLANE_H
#define PLANE_H


#include "glut.h"
#include "glutFunc.hpp"
#include "Drawable.hpp"

class Plane 
{
public:
	Plane();

	void CreateList();

	void Draw(GLfloat x = 0.0f, GLfloat y = -0.2f, GLfloat z = 0.0f);

private:
	GLfloat w_;
	GLfloat d_;

};

#endif
