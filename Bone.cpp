#include "Bone.hpp"

#include <iostream>
#include <string>

#include <math.h>

using namespace std;

Bone::Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, int flag, Drawable *mesh, string name) : father_(root), x_(x), y_(y), a_(a), flag_(flag), mesh_(mesh), name_(name), child_(NULL)
{	
	l_ = mesh_->ReturnH();
	
	cout << "Bone " << name << " has been created. Flag: " << flag << "!" << endl;
}

void Bone::boneAddChild(GLfloat x, GLfloat y, GLfloat a, int flag, Drawable *mesh, string name)
{
	child_ = new Bone(this, x, y, a, flag, mesh, name);

	cout << "Bone " << name << " has been added!" << endl;
}

void Bone::boneAddChild(GLfloat a, int flag, Drawable *mesh, string name)
{
	//GLfloat x = 0, y = 0;
	//x = static_cast<GLfloat>( l_*cosf( glut::Rad2Deg(a_) ) );
	//y = static_cast<GLfloat>( l_*sinf( glut::Rad2Deg(a_) ) );
	child_ = new Bone(this, 0.0f, 0.0f, a, flag, mesh, name);

	cout << "Bone " << name << " has been added!" << endl;
}

void Bone::Draw()
{
	glPushMatrix();
	
	glRotatef(a_, 0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0); 	glVertex2f(0, 0);
	glColor3f(0.0, 0.0, 1.0);	glVertex2f(l_, 0);
	glEnd();

	mesh_->Draw();

	/* Translate to reach the new starting position */
	glTranslatef(l_, 0.0, 0.0);

	/* Call function on my children */
	if(child_!=NULL){
		glRotatef(0.0f, 0.0, 0.0, 1.0);/////
		child_->Draw();
	}
		
	glPopMatrix();
}

void Bone::animate() //time
{
	//static int an_step;
	static GLfloat offsetA = 0.1f;
	if(flag_ == FOR_ODD) {
		if(a_ > 45.f || a_ < -30.f )
		{
			offsetA *= -1;
			a_ = static_cast<GLfloat>(floorf(static_cast<int>(a_)));
			cout << offsetA << " " << a_ << endl;
		}		
		a_ += offsetA;
	}

	//if(flag_ == FOR_EVEN) {
	//	if(a_ > 45.f || a_ < -30 )
	//	{
	//		offsetA *= -1;
	//		a_ = static_cast<GLfloat>(floorf(static_cast<int>(a_)));
	//		cout << offsetA << " " << a_ << endl;
	//	}		
	//	a_ += offsetA;
	//}
	if(child_!=NULL){
		child_->animate_child();
	}
		
}

 //-----------------------------------------------------------------------pi
    const double pi = 3.14159265358979323846;

//------------------------------------------------------------------deg2rad
    inline float deg2rad(float deg)
    {
        return deg * pi / 180.0;
    }


void Bone::animate_child()
{ 
	static GLfloat child_offsetA = 0.1f;
	//float equation = (10.0f + ( father_->l_ ) * sinf( deg2rad(father_->a_) )  + l_* sinf( deg2rad(a_) ) );
	float equation = (sinf( deg2rad(father_->a_) ) * ( father_->l_ + l_* cosf( deg2rad(a_) ) ) + ( father_->l_ ) * sinf( deg2rad(a_)  * cosf( deg2rad(father_->a_) ) ) );
	//cout << father_->y_ << " " << father_->a_ << " " << a_ << endl;
	cout << "equation: " << equation << endl << endl;
	if( equation <= 0.f)
		cout << "KOLIZJAAAA!!" << endl;
	
	if(flag_ == FOR_ODD) {
		if(a_ > -15.f )
		{
			child_offsetA *= -1;
			a_ = static_cast<GLfloat>(floorf(a_));
			cout << child_offsetA << " " << a_ << endl;
		}
		else if(a_ < -60.f )
		{
			child_offsetA *= -1;
			a_ = static_cast<GLfloat>(floorf(static_cast<int>(a_)));
			cout << child_offsetA << " " << a_ << endl;
		}
		a_ += child_offsetA;
	}
	/*if(flag_ == FOR_EVEN) {
		if(a_ > 45.f || a_ < -30 )
		{
			child_offsetA *= -1;
			a_ = static_cast<GLfloat>(floorf(static_cast<int>(a_)));
			cout << child_offsetA << " " << a_ << endl;
		}		
		a_ += child_offsetA;
	}*/
}

bool Bone::anim_idle()
{
	return true;
}

bool Bone::anim_up()
{	
	GLfloat offA = 0.1f;
	if(a_ < 45.f )
		{
			a_ += offA;
			cout << offA << " " << a_ << endl;
			return false;
		}		
	else
		return true;
}

bool Bone::anim_down()
{	
	GLfloat offA = -0.1f;
	if(a_ > -30.f )
		{
			a_ += offA;
			cout << offA << " " << a_ << endl;
			return false;
		}		
	else
		return true;
}

