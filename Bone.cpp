#include "Bone.hpp"

#include <iostream>
#include <string>

#include <math.h>

extern float crab_y;

bool Bone::oddHit_= false;

//-------------------------------------------------------------------angles
GLfloat MaxA = 30.f, MaxB = -45.f, MinA = -30.f, MinB = -110.f;

struct Vector3f {
	Vector3f() : x_(0), y_(0), z_(0) {};
	Vector3f(float x, float y, float z) : x_(x), y_(y), z_(z) {};
	float x_;
	float y_;
	float z_;
};

Vector3f substractV3f(Vector3f v1, Vector3f v2)
{
	float x = v1.x_ - v2.x_;
	float y = v1.y_ - v2.y_;
	float z = v1.z_ - v2.z_;
	
	return Vector3f(x,y,z);
}

Vector3f crossProduct(Vector3f v1, Vector3f v2) 
{
   float x = (v1.y_ * v2.z_) - (v2.y_ * v1.z_);
   float y = (v1.z_ * v2.x_) - (v2.z_ * v1.x_);
   float z = (v1.x_ * v2.y_) - (v2.x_ * v1.y_);
   
   return Vector3f(x,y,z);
}

Vector3f normalize(Vector3f v) 
{
	float r = sqrtf(v.x_*v.x_ + v.y_*v.y_ + v.z_*v.z_);

	float x = v.x_/r;
	float y = v.y_/r;
	float z = v.z_/r;

	return Vector3f(x,y,z);

}
using namespace std;

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
	GLfloat off = 0.8;
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

	// obliczanie wartosci wierzcholkow na potrzeby przeliczenia normalnej i wyswietlenia lacznika
	Vector3f vector1, vector2, vector3, normalV;

	vector1.x_ = child_->mesh_->ReturnD() * sinf(-deg2rad(child_->a_));
	vector1.y_ = child_->mesh_->ReturnD() * cosf(-deg2rad(child_->a_));
	vector1.z_ = child_->mesh_->ReturnW()/2;

	vector2.x_ = 0.f;
	vector2.y_ = mesh_->ReturnD();
	vector2.z_ = (mesh_->ReturnW()/2);

	vector3.x_ = vector1.x_;
	vector3.y_ = vector1.y_;
	vector3.z_ = -vector1.z_;

	// Obliczanie normalnej dla lacznika kryjacego staw
	Vector3f edge1 = substractV3f(vector1, vector3);
	Vector3f edge2 = substractV3f(vector3, vector2);
	normalV = normalize(crossProduct(edge1, edge2));
				
				//Wyrysowanie lacznika miedzy obudowami kosci
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(normalV.x_, normalV.y_, normalV.z_);
					glVertex3f(vector1.x_, vector1.y_, vector1.z_);
					glVertex3f(vector3.x_, vector3.y_, vector3.z_);
					glVertex3f(vector2.x_, vector2.y_, vector2.z_);
					glVertex3f(vector2.x_, vector2.y_, -vector2.z_);	
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(0.0f, 0.0f, 1.0f);
					glVertex3f(vector2.x_, vector2.y_, vector2.z_);
					glVertex3f(vector2.x_, 0.0f, vector2.z_);
					glVertex3f(vector1.x_, vector1.y_, vector1.z_);
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(0.0f, 0.0f, -1.0f);
					glVertex3f(vector2.x_, 0.0f, -vector2.z_);
					glVertex3f(vector2.x_, vector2.y_, -vector2.z_);	
					glVertex3f(vector1.x_, vector1.y_, -vector1.z_);								
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
