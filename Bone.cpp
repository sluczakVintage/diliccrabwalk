#include "Bone.hpp"

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

Bone::Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, Drawable *mesh, string name) : father_(root), x_(x), y_(y), a_(a), mesh_(mesh), name_(name), child_(NULL)
{	
	l_ = mesh_->ReturnH();
	
	cout << "Bone " << name << " has been created!" << endl;
}

void Bone::boneAddChild(GLfloat x, GLfloat y, GLfloat a, Drawable *mesh, string name)
{
	child_ = new Bone(this, x, y, a, mesh, name);

	cout << "Bone " << name << " has been added!" << endl;
}

void Bone::Draw()
{
	glPushMatrix();

	glTranslatef(x_, y_, 0.0);
	glRotatef(glut::Rad2Deg(a_), 0.0, 0.0, 1.0);

	glBegin(GL_LINES);

	glColor3f(0.0, 1.0, 0.0); 	glVertex2f(0, 0);

	glColor3f(0.0, 0.0, 1.0);	glVertex2f(l_, 0);
	
	glEnd();

	mesh_->Draw();


	/* Translate to reach the new starting position */
	glTranslatef(l_, 0.0, 0.0);

	/* Call function on my children */
	if(child_!=NULL)
		child_->Draw();
		
	glPopMatrix();
}

///TODO
void Bone::animate(GLfloat a)
{
	a_ = a;
}