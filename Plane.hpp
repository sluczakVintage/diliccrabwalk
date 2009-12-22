/**
*
*	Klasa opisujaca model kraba
*
*
**/
#ifndef PLANE_H
#define PLANE_H


#include "glut.h"
#include "glutFunc.hpp"
#include "Drawable.hpp"

class Plane //: public Drawable
{
public:
	Plane();
	~Plane();

	void Draw(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f);

private:
	GLfloat w_;
	GLfloat d_;

};

#endif
