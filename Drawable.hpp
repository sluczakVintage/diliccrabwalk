/**
*
*	Klasa opisujaca klasy rysowalne
*
*
**/
#ifndef DRAWABLE_H
#define DRAWABLE_H


#include "glut.h"
#include "glutFunc.hpp"

enum{ CRAB = 1 , SH_LEG, NOR_LEG , SH_COMP , LONG_COMP, PROJECTION = 10 };



class Drawable
{
public:
	//Drawable();
	//virtual ~Drawable();

	virtual void Draw(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f) = 0;
	virtual void CreateList() = 0;

	virtual const GLfloat ReturnH() const = 0;

};

#endif
	//struct Vertex
	//{
	//	float x, y, z;
	//};

	//struct TexCoord
	//{
	//	float tu, tv;
	//};
