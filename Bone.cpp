#include "Bone.hpp"

#include <iostream>
#include <string>

#include <math.h>

extern float crab_y;

using namespace std;

bool Bone::oddHit_= false;

//-------------------------------------------------------------------angles
GLfloat MaxA = 30.f, MaxB = -45.f, MinA = -30.f, MinB = -110.f;

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


Bone::Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, int flag, Drawable *mesh, string name) : father_(root), x_(x), y_(y), a_(a), flag_(flag), mesh_(mesh), name_(name), child_(NULL)
{	
	GLfloat off = 0.4;
	l_ = mesh_->ReturnH();

	if(flag_ == FOR_ODD){
		animFlag_ = AN_IDLE;
		off_ = off;
	}
	else if(flag_ == FOR_EVEN){
		animFlag_ = AN_DOWN;
		off_ = off;
	}
	else if(flag_ == BACK_ODD){
		animFlag_ = AN_IDLE;
		off_ = -off;
	}
	else if(flag_ == BACK_EVEN){
		animFlag_ = AN_DOWN;
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
	
	// Obroc zgodnie z zadanym katem
	glRotatef(a_, 0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0); 	glVertex2f(0, 0);
	glColor3f(0.0, 0.0, 1.0);	glVertex2f(l_, 0);
	glEnd();

	// Odrysuj siatke
	mesh_->Draw();

	// Przemiesc na koncowy punkt kosci
	glTranslatef(l_, 0.0, 0.0);

	// Jesli ma dzieci, dokonaj odrysowania zamkniecia stawow
	if(child_!=NULL){

	float cosinus_a, sinus_a, d_, child_d, w_, child_w;
	cosinus_a = cosf(-deg2rad(child_->a_));
	sinus_a = sinf(-deg2rad(child_->a_));
	d_ = mesh_->ReturnD();
	child_d = child_->mesh_->ReturnD();
	w_ = mesh_->ReturnW();
	child_w = child_->mesh_->ReturnW();
	

				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(child_d *sinus_a, child_d * cosinus_a, child_w/2);
					glVertex3f(child_d * sinus_a, child_d * cosinus_a, -child_w/2);
					glVertex3f(0.f, d_,w_/2);
					glVertex3f(0.f, d_,-w_/2);	
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(0.f, d_, w_/2);
					glVertex3f(0.f, 0.f, w_/2);
					glVertex3f(child_d * sinus_a, child_d * cosinus_a,child_w/2);
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(0.f, 0.f, -w_/2);
					glVertex3f(0.f, d_, -w_/2);	
					glVertex3f(d_ * sinus_a,child_d * cosinus_a,-child_w/2);								
				glEnd();
	}

	// wywolaj rysowanie dzieci
	if(child_!=NULL){
		glRotatef(0.0f, 0.0, 0.0, 1.0);
		child_->Draw();
	}
		
	glPopMatrix();
}


void Bone::animate() 
{
		if(animFlag_ == AN_UP_FRONT)
			animUpFront();
		else if(animFlag_ == AN_UP_REAR)
			animUpRear();
		else if(animFlag_ == AN_DOWN)
			animDown();
		else if(animFlag_ == AN_MOVE)
			animMove();
		else if(animFlag_ == AN_IDLE)
		    animIdle();	
}


void Bone::animIdle()
{
	cout << "animIdle()" << endl;
	if( flag_ == FOR_EVEN && oddHit_ == true){
		animFlag_ = AN_UP_FRONT;
	}
	else if( flag_ == BACK_EVEN && oddHit_ == true){
		animFlag_ = AN_UP_REAR;
	}
	else if( flag_ == FOR_ODD  && oddHit_ == false){
		animFlag_ = AN_UP_FRONT;
	}
	else if( flag_ == BACK_ODD  && oddHit_ == false){
		animFlag_ = AN_UP_REAR;
	}
	else;
}

void Bone::animUpFront()
{
	cout << "animUpFront()" << endl;
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );
	
	offsetA_ = off_;
	childOffsetA_ = off_;
	if(a_ > (MaxA - 10.f) )
	{
		offsetA_ = 0.f;
	}			
	a_ += offsetA_;

	if(child_->a_ > (MaxB - 5.f) )
	{
			animFlag_ = AN_DOWN;	
	}
	child_->a_ += childOffsetA_;

}

void Bone::animUpRear()
{
	cout << "animUpRear()" << endl;
	offsetA_ = -off_;
	childOffsetA_ = off_;
	if(a_ > MaxA )
	{
		offsetA_ = 0.f;
	}			
	a_ += offsetA_;

	if(child_->a_ < MinB )
	{
		animFlag_ = AN_DOWN;
	}
	child_->a_ += childOffsetA_;

}

void Bone::animDown()
{
	cout << "animDown()" << endl;
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );
	
	float equation = ( sinf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) + ( child_->l_ ) * sin_b  * cosf( deg2rad(a_) ) );

	offsetA_ = -abs(off_);
	childOffsetA_ = 0;

	if( equation <= -crab_y ){
		if(flag_ == FOR_ODD)
			oddHit_ = true;
		if(flag_ == FOR_EVEN)
			oddHit_ = false;
	
		//if( flag_ == BACK_EVEN || flag_ == BACK_ODD )
		//	animFlag_ = AN_IDLE;
		//else 
			animFlag_ = AN_MOVE;
	}
	a_ += offsetA_;

}

void Bone::animMove()
{	
	cout << "animMove()" << endl;
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );

	float equation = ( sinf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) + ( child_->l_ ) * sin_b  * cosf( deg2rad(a_) ) );
	
	childOffsetA_ = -off_;

	if( ( flag_ == BACK_EVEN || flag_ == BACK_ODD ) && child_->a_ > MaxB ) 
	{
		animFlag_ = AN_IDLE;
		//animFlag_ = AN_UP_REAR;
	}
	else if ( ( flag_ == FOR_EVEN || flag_ == FOR_ODD ) && child_->a_ < MinB )  
	{
		animFlag_ = AN_IDLE;
	}
	if(flag_ == FOR_ODD)
		oddHit_ = true;
	if(flag_ == FOR_EVEN)
		oddHit_ = false;
	a_ = rad2deg( ( pi*signum<float>( child_->l_*sin_b ) )/2 - asinf( crab_y/sqrtf( ( rl2<float>(child_->l_,l_) * cos_b ) + ( power<2>(l_) )+( power<2>(child_->l_) ) ) ) + atanf( ( child_->l_*cos_b  + l_) /( child_->l_*sin_b ) ) + pi) ; 	
	child_->a_ += childOffsetA_;
}
