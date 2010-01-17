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
	LegNormal(int flag);
	~LegNormal();

	void Draw();
	//rysowanie bez animacji
	void StaticDraw();
	//adapter do zmiany stanu animacji nogi
	void animToggle();

private:
	// czesci skladowe nogi
	LegCompShort* compShort;
	LegCompLong* compLong;
	Bone* bone;

};

#endif
