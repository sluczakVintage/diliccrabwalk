/**
*
*	Klasa opisujaca model kraba
*
*
**/
#ifndef BONE_H
#define BONE_H

#include <iostream>
#include <string>
#include "glut.h"
#include "glutFunc.hpp"

#include "Drawable.hpp"

using namespace std;
class Bone
{
public:
	
	Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, GLfloat b, Drawable *mesh, string name);
	~Bone();
	
	void boneAddChild(GLfloat x, GLfloat y, GLfloat a, GLfloat b, Drawable *mesh, string name);
	void boneAddChild(GLfloat a, GLfloat b, Drawable *mesh, string name);
	void Draw();
	void animate(GLfloat a); ///TODo
	void animate_child(GLfloat a);

	GLfloat a_;
	GLfloat b_;
private:
	Bone();

	GLfloat x_;
	GLfloat y_;
	GLfloat l_;
	std::string name_;

	Bone *father_;
	Bone *child_;
	Drawable *mesh_;
	
};

#endif