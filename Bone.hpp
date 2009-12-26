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
enum{ IDLE, STEP_START, STEP_END };
using namespace std;
class Bone
{
public:
	
	Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, int flag , Drawable *mesh, string name);
	~Bone();
	
	//void boneAddChild(GLfloat x, GLfloat y, GLfloat a,int flag , Drawable *mesh, string name);
	void boneAddChild(GLfloat a, int flag, Drawable *mesh, string name);
	void Draw();
	void animate(); 
	void anim_step_end();
	void anim_step_start();
	void anim_idle();

private:
	Bone();

	GLfloat offsetA_;
	GLfloat childOffsetA_;
	GLfloat off_;
	int animFlag_;
	int idleTime_;

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
