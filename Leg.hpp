/**
*
*	Klasa abstrakcyjna opisujaca klasy nog
*
*
**/
#ifndef LEG_H
#define LEG_H


class Leg
{
public:
	virtual void Draw() = 0;
	virtual void StaticDraw() = 0;
	virtual void animToggle() = 0;

};

#endif

