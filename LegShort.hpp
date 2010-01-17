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
#include "Bone.hpp"
#include "Leg.hpp"

class LegShort : public Leg
{
public:
	LegShort();
	~LegShort();

	/// Metoda rysujaca krotka noge
	void Draw();
	void StaticDraw() { Draw(); };
	void animToggle() {};
	

private:
	LegCompShort* compShort0;
	LegCompShort* compShort1;
	Bone* bone;
};

#endif