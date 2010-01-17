/**
*
*	Klasa opisujaca model d³ugiej sk³adowej nogi kraba
*
*
**/

#ifndef LEGCOMPLONG_H
#define LEGCOMPLONG_H

#include "glut.h"
#include "glutFunc.hpp"
#include "Drawable.hpp"

class LegCompLong : public Drawable
{
public:
	LegCompLong();
	
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