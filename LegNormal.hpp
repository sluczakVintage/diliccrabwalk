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
#include "Bone.hpp"
#include "Leg.hpp"


class LegNormal : public Leg
{
public:
	LegNormal();//(GLfloat x, GLfloat y, GLfloat a, GLfloat b);
	~LegNormal();

	void Draw();


private:
	LegCompShort* compShort;
	LegCompLong* compLong;
	Bone* bone;

};

#endif
