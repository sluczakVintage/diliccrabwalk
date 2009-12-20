/**
*
*	Klasa opisujaca model kraba
*
*
**/
#ifndef CRAB_H
#define CRAB_H

#include <vector>

#include "glut.h"
#include "glutFunc.hpp"
#include "Drawable.hpp"
#include "Leg.hpp"

#include "LegNormal.hpp"
#include "LegShort.hpp"

class Crab //: public Drawable
{
public:
	Crab();
	~Crab();

	void Draw(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f);
	void drawLegs();
	void CreateList();
	virtual const GLfloat ReturnH() const { return h_; };

private:
	GLfloat w_;
	GLfloat h_;
	GLfloat d_;

	vector<Leg*> legs;

};

#endif
