/**
*
*	Klasa abstrakcyjna opisujaca klasy rysowalne
*
*
**/
#ifndef DRAWABLE_H
#define DRAWABLE_H


#include "glut.h"
#include "glutFunc.hpp"

enum{ STATIC_CRAB = 1, CRAB, SH_LEG, NOR_LEG , SH_COMP , LONG_COMP, PLANE, PROJECTION = 10 };



class Drawable
{
public:
	virtual void Draw() = 0;
	virtual void CreateList() = 0;
	

	virtual const GLfloat ReturnH() const = 0;
	virtual const GLfloat ReturnW() const = 0;
	virtual const GLfloat ReturnD() const = 0;

};

#endif

