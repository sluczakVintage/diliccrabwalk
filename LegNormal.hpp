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
	LegNormal(int flag);//, GLfloat x = 0.f, GLfloat y = 0.f);
	~LegNormal();

	void Draw();
	void StaticDraw();
	void animToggle();

private:
	LegCompShort* compShort;
	LegCompLong* compLong;
	Bone* bone;

};

#endif
