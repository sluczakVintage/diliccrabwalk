/**
*
*	Klasa opisujaca model normalnej nogi kraba
*
*
**/
#ifndef LEGNORMAL_H
#define LEGNORMAL_H

#include "glut.h"
#include "glutFunc.hpp"

#include "LegCompShort.hpp"
#include "LegCompLong.hpp"


class LegNormal
{
public:
	LegNormal();
	~LegNormal();

	void Draw(GLfloat x, GLfloat y, GLfloat z);

private:
	LegCompShort compShort;
	LegCompLong compLong;

};

#endif
