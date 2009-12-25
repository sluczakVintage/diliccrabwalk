#include "Bone.hpp"

#include <iostream>
#include <string>

#include <math.h>

extern float crab_y;

using namespace std;

Bone::Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, int flag, Drawable *mesh, string name) : father_(root), x_(x), y_(y), a_(a), flag_(flag), mesh_(mesh), name_(name), child_(NULL)
{	
	l_ = mesh_->ReturnH();
	
	cout << "Bone " << name << " has been created. Flag: " << flag << "!" << endl;
}

//void Bone::boneAddChild(GLfloat x, GLfloat y, GLfloat a, int flag, Drawable *mesh, string name)
//{
//	child_ = new Bone(this, x, y, a, flag, mesh, name);
//
//	cout << "Bone " << name << " has been added!" << endl;
//}

void Bone::boneAddChild(GLfloat a, int flag, Drawable *mesh, string name)
{
	child_ = new Bone(this, 0.0f, 0.0f, a, flag, mesh, name);
	cout << "Bone " << name << " has been added!" << endl;
}

Bone::~Bone()
{
	if(child_!=NULL){
		delete child_;
		child_ = NULL;
	}
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

 //-----------------------------------------------------------------------pi
    const float pi = 3.14159265358979323846;

//------------------------------------------------------------------deg2rad
    inline float deg2rad(float deg)
    {
        return deg * pi / 180.0;
    }
//------------------------------------------------------------------rad2deg
	inline float rad2deg(float rad)
	{
      return (180.0 * rad / pi);
	}
//------------------------------------------------------------------signum
template<typename T>
T signum(T n)
{
	if (n < 0) return -1;
	if (n > 0) return 1;
	return 0;
}
//-----------------------------------------------------------------power
template <unsigned n> inline float power(float x) {
	return x * power<n-1>(x);
}
template <> inline float power<0>(float x) {
	return 1.0;
}
//-----------------------------------------------------------------compilation time operations
template <typename T> inline float rl2(float r, float l) {
	return (2.0f*r*l);
}
void Bone::animate() //time
{
	anim_up();
		
}


bool Bone::anim_idle()
{
	return true;
}

void Bone::anim_up()
{	
	static GLfloat offsetA = 0.2f;
	static GLfloat child_offsetA = 0.2f;
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );

	float equation = ( sinf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) + ( child_->l_ ) * sin_b  * cosf( deg2rad(a_) ) );
	
	if(flag_ == FOR_ODD) {
		if(equation <= -crab_y)
			a_ = a_;
		else {
			if(a_ > 20.f || a_ < -20.f )
			{
				offsetA *= -1;
				a_ = static_cast<GLfloat>(floorf(static_cast<int>(a_)));
				cout << offsetA << " " << a_ << endl;
			}		
		
			a_ += offsetA;
		}
		cout << "father a_: " << a_ << endl;

		if(child_->a_ > -45.f )
		{
			child_offsetA *= -1;
			child_->a_ = static_cast<GLfloat>(floorf(child_->a_));
		}
		else if(child_->a_ < -90.f )
		{
			child_offsetA *= -1;
			child_->a_ = static_cast<GLfloat>(floorf(static_cast<int>(child_->a_)));
		}
		if( equation <= -crab_y ){
			a_ = rad2deg( ( pi*signum<float>( child_->l_*sin_b ) )/2 - asinf( crab_y/sqrtf( ( rl2<float>(child_->l_,l_) * cos_b ) + ( power<2>(l_) )+( power<2>(child_->l_) ) ) ) + atanf( ( child_->l_*cos_b  + l_) /( child_->l_*sin_b ) ) + pi) ; 
			cout << "next father a_: " << a_ << endl;
			}
		cout << "child a_: " << child_->a_ << endl;
		cout << "equation: " << equation << endl << endl;
	
		child_->a_ += child_offsetA;	
	}

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

