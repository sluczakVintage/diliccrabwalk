/**
*
*	Klasa opisujaca model krótkiej nogi
*
*
**/

#ifndef LEGSHORT_H
#define LEGSHORT_H

#include "glut.h"
#include "glutFunc.hpp"

#include "LegCompShort.hpp"

class LegShort
{
public:
	LegShort();
	~LegShort();

	void Draw(GLfloat x, GLfloat y, GLfloat z);

private:
	LegCompShort compShort0;
	LegCompShort compShort1;
};

#endif