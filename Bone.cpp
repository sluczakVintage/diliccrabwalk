#include "Bone.hpp"

#include <iostream>
#include <string>

#include <math.h>

extern float crab_y;

using namespace std;

bool Bone::oddHit_= false;

Bone::Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, int flag, Drawable *mesh, string name) : father_(root), x_(x), y_(y), a_(a), flag_(flag), mesh_(mesh), name_(name), child_(NULL)
{	
	GLfloat off = 0.2;
	l_ = mesh_->ReturnH();

	if(flag_ == FOR_ODD){
		animFlag_ = STEP_START;
		off_ = off;
	}
	else if(flag_ == FOR_EVEN){
		animFlag_ = STEP_END;
		off_ = off;
	}
	else if(flag_ == BACK_ODD){
		animFlag_ = STEP_START;
		off_ = -off;
	}
	else if(flag_ == BACK_EVEN){
		animFlag_ = STEP_END;
		off_ = -off;
	}
	childOffsetA_ = off_;
	offsetA_ = off_;
	cout << "Bone " << name << " has been created. Flag: " << flag_ << "!" << endl;
}

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
 	if(flag_ == FOR_ODD || flag_ == FOR_EVEN) {
		if(animFlag_ == STEP_END)
			anim_step_end();
		else if(animFlag_ == STEP_START )
			anim_step_start();
		else if(animFlag_ == IDLE)
			anim_idle();
	}
	else if(flag_ == BACK_ODD || flag_ == BACK_EVEN) {
		if(animFlag_ == STEP_END)
			anim_rear_step_end();
		else if(animFlag_ == STEP_START )
			anim_rear_step_start();
		else if(animFlag_ == IDLE)
			anim_idle();
	}

}


void Bone::anim_idle()
{
	if( (flag_ == FOR_EVEN || flag_ == BACK_EVEN ) && oddHit_ == true)
			animFlag_ = STEP_START;
	else if( (flag_ == FOR_ODD || flag_ == BACK_ODD ) && oddHit_ == false)
			animFlag_ = STEP_START;
	else;
}

void Bone::anim_step_end()
{	
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );

	float equation = ( sinf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) + ( child_->l_ ) * sin_b  * cosf( deg2rad(a_) ) );
	
	offsetA_ = -off_;
	childOffsetA_ = -off_;

	if(equation <= -crab_y)
		a_ = a_;
	else {
		if(a_ < -20.f )
		{
			offsetA_ *= -1;
			cout << offsetA_ << " " << a_ << endl;
		}			
		a_ += offsetA_;
	}
	cout << "father a_: " << a_ << endl;

	if(child_->a_ < -110.f )
	{
		animFlag_ = IDLE;
	}
	if( equation <= -crab_y ){
		if(flag_ == FOR_ODD)
			oddHit_ = true;
		if(flag_ == FOR_EVEN)
			oddHit_ = false;
		a_ = rad2deg( ( pi*signum<float>( child_->l_*sin_b ) )/2 - asinf( crab_y/sqrtf( ( rl2<float>(child_->l_,l_) * cos_b ) + ( power<2>(l_) )+( power<2>(child_->l_) ) ) ) + atanf( ( child_->l_*cos_b  + l_) /( child_->l_*sin_b ) ) + pi) ; 
		cout << "next father a_: " << a_ << endl;
		}
	cout << "child a_: " << child_->a_ << endl;
	cout << "equation: " << equation << endl << endl;

	child_->a_ += childOffsetA_;
}

void Bone::anim_step_start()
{	
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );

	float equation = ( sinf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) + ( child_->l_ ) * sin_b  * cosf( deg2rad(a_) ) );
	
	offsetA_ = off_;
	childOffsetA_ = off_;
	if(a_ > 30.f )
	{
		offsetA_ *= -1;
		cout << offsetA_ << " " << a_ << endl;
	}			
	a_ += offsetA_;

	cout << "father a_: " << a_ << endl;

	if(child_->a_ > -35.f )
	{
		animFlag_ = STEP_END;
	}

	cout << "child a_: " << child_->a_ << endl;
	cout << "equation: " << equation << endl << endl;

	child_->a_ += childOffsetA_;
}


void Bone::anim_rear_step_end()
{	
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );

	float equation = ( sinf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) + ( child_->l_ ) * sin_b  * cosf( deg2rad(a_) ) );
	
	offsetA_ = -off_;
	childOffsetA_ = -off_;

	if(equation <= -crab_y)
		a_ = a_;
	else {
		if(a_ < -20.f )
		{
			offsetA_ *= -1;
			cout << offsetA_ << " " << a_ << endl;
		}			
		a_ += offsetA_;
	}
	cout << "father a_: " << a_ << endl;

	if(child_->a_ < -110.f )
	{
		animFlag_ = IDLE;
	}
	if( equation <= -crab_y ){
		if(flag_ == FOR_ODD)
			oddHit_ = true;
		if(flag_ == FOR_EVEN)
			oddHit_ = false;
		a_ = rad2deg( ( pi*signum<float>( child_->l_*sin_b ) )/2 - asinf( crab_y/sqrtf( ( rl2<float>(child_->l_,l_) * cos_b ) + ( power<2>(l_) )+( power<2>(child_->l_) ) ) ) + atanf( ( child_->l_*cos_b  + l_) /( child_->l_*sin_b ) ) + pi) ; 
		cout << "next father a_: " << a_ << endl;
		}
	cout << "child a_: " << child_->a_ << endl;
	cout << "equation: " << equation << endl << endl;

	child_->a_ += childOffsetA_;
}

void Bone::anim_rear_step_start()
{	
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );

	float equation = ( sinf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) + ( child_->l_ ) * sin_b  * cosf( deg2rad(a_) ) );
	
	offsetA_ = off_;
	childOffsetA_ = off_;
	if(a_ > 30.f )
	{
		offsetA_ *= -1;
		cout << offsetA_ << " " << a_ << endl;
	}			
	a_ += offsetA_;

	cout << "father a_: " << a_ << endl;

	if(child_->a_ > -35.f )
	{
		animFlag_ = STEP_END;
	}

	cout << "child a_: " << child_->a_ << endl;
	cout << "equation: " << equation << endl << endl;

	child_->a_ += childOffsetA_;
}

