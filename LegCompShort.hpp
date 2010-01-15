/**
*
*	Klasa opisujaca model krótkiej sk³adowej nogi kraba
*
*
**/
#ifndef LEGCOMPSHORT_H
#define LEGCOMPSHORT_H

#include "glut.h"
#include "glutFunc.hpp"
#include "Drawable.hpp"

class LegCompShort : public Drawable
{
	
public:
	LegCompShort();
	
	void Draw();
	void CreateList();
	virtual const GLfloat ReturnH() const { return h_; };
	virtual const GLfloat ReturnW() const { return w_; };
	virtual const GLfloat ReturnD() const { return d_; };

private:
	GLfloat w_;
	GLfloat h_;
	GLfloat d_;
};

#endif

