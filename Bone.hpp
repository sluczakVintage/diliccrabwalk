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

enum{ FOR_ODD = 10, BACK_ODD, FOR_EVEN, BACK_EVEN };

using namespace std;
class Bone
{
public:
	
	Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, int flag , Drawable *mesh, string name);
	~Bone();
	
	//void boneAddChild(GLfloat x, GLfloat y, GLfloat a,int flag , Drawable *mesh, string name);
	void boneAddChild(GLfloat a, int flag, Drawable *mesh, string name);
	void Draw();
	void animate(); ///TODo
	void anim_up();
	bool anim_down();
	bool anim_idle();

private:
	Bone();

	GLfloat x_;
	GLfloat y_;
	GLfloat a_;
	GLfloat l_;
	int flag_;
	std::string name_;

	Bone *father_;
	Bone *child_;
	Drawable *mesh_;
	
};

#endif
