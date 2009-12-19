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
	~LegCompShort();

	void Draw(GLfloat x, GLfloat y, GLfloat z);
	void CreateList();
	virtual const GLfloat ReturnH() const { return h_; };

private:
	GLfloat w_;
	GLfloat h_;
	GLfloat d_;
};

#endif

