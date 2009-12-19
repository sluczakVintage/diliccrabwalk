/**
*
*	Klasa opisujaca model kraba
*
*
**/
#ifndef CRAB_H
#define CRAB_H


#include "glut.h"
#include "glutFunc.hpp"

#include "Drawable.hpp"
#include "LegNormal.hpp"
#include "LegShort.hpp"

class Crab
{
public:
	Crab();
	//~Crab();

	void Draw(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f);
	void drawLegs(GLfloat x, GLfloat y, GLfloat z);
	void CreateList();

private:
	GLfloat w_;
	GLfloat h_;
	GLfloat d_;
	/*LegShort firstLeft, firstRight;
	LegNormal secondLeft, secondRight;
	LegNormal thirdLeft, thirdRight;
	LegNormal forthLeft, forthRight;
	LegNormal fifthLeft, fifthRight;*/

};

#endif
