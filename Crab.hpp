/**
*
*	Klasa opisujaca model kraba
*
*
**/
#ifndef CRAB_H
#define CRAB_H

#include <vector>
#include <algorithm>

#include "glut.h"
#include "glutFunc.hpp"
#include "Drawable.hpp"
#include "Leg.hpp"

#include "LegNormal.hpp"
#include "LegShort.hpp"

class Crab
{
public:
	Crab();
	~Crab();

	void Draw(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f);
	// rysowanie bez animacji
	void StaticDraw(GLfloat = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f, GLfloat roty = 0.0f);
	void DrawLegs();
	// rysowanie bez animacji
	void StaticDrawLegs();
	void CreateList();
	// przelaczanie animacji start/stop
	void toggleAnim();
	virtual const GLfloat ReturnH() const { return h_; };

private:
	GLfloat w_;
	GLfloat h_;
	GLfloat d_;

	LegShort *leg_sh;
	LegNormal* leg_for_even;
	LegNormal* leg_for_odd;
	LegNormal* leg_back_even;
	LegNormal* leg_back_odd;
		

	vector<Leg*> legs;

};

#endif
