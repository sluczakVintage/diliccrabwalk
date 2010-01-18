#include "Bone.hpp"

#include <iostream>
#include <string>

#include <math.h>

extern float crab_y;
extern float crab_z;

extern bool show_bones;
// obliczenie przesuniecia po ziemi
static float last_equation_z = 0.0f;
static float mov_offset = 0.0f;

float global_offset = 0.8f;
// Wartosc maksymalna ruchu po ziemi
static float max_z = 0.0f;
static float min_z = 0.0f;
// Uderzenie w ziemie
static bool oddHit_= true;
static bool evenHit_= false;
// Gotowosc do kroku
static bool readyFront_ = false;
static bool readyRear_ = false;
// Czy animacja rozpoczeta
static bool started_ = false;



//-------------------------------------------------------------------Granice ruchu w stawach
GLfloat MaxA = 50.f, MaxB = -45.f, MinA = -30.f, MinB = -110.f;

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
//-----------------------------------------------------------------obliczenia w czasie kompilacji
template <typename T> inline float rl2(float r, float l) {
	return (2.0f*r*l);
}


Bone::Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, int flag, Drawable *mesh, string name) : father_(root), x_(x), y_(y), a_(a), flag_(flag), mesh_(mesh), name_(name), child_(NULL)
{	
	GLfloat off = global_offset;

	l_ = mesh_->ReturnH();

	if(flag_ == FRONT_ODD){
		off_ = off;
	}
	else if(flag_ == FRONT_EVEN){
		off_ = off;
	}
	else if(flag_ == REAR_ODD){
		off_ = -off;
	}
	else if(flag_ == REAR_EVEN){
		off_ = -off;
	}
	childOffsetA_ = off_;
	offsetA_ = off_;

	animInit();

	cout << "Bone " << name << " kosc zostala stworzona. Flag: " << flag_ << "!" << endl;
}

void Bone::newOffset(GLfloat off)
{
	mov_offset = 0.0f;
	last_equation_z = 0.0f;

	if(flag_ == FRONT_ODD){
		off_ = off;
	}
	else if(flag_ == FRONT_EVEN){
		off_ = off;
	}
	else if(flag_ == REAR_ODD){
		off_ = -off;
	}
	else if(flag_ == REAR_EVEN){
		off_ = -off;
	}

}


void Bone::boneAddChild(GLfloat a, int flag, Drawable *mesh, string name)
{
	child_ = new Bone(this, 0.0f, 0.0f, a, flag, mesh, name);
	cout << "Bone " << name << " kosc zostala dodana jako dziecko!" << endl;
}

Bone::~Bone()
{
	if(child_!=NULL){
		delete child_;
		child_ = NULL;
	}
}


void Bone::animate() 
{
	if(global_offset != abs(off_))
		newOffset(global_offset);

	if(started_)
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
}

void Bone::animInit()
{
	if( flag_ == FRONT_EVEN )
		animFlag_ = AN_UP_FRONT;
	if( flag_ == FRONT_ODD )
		animFlag_ = AN_IDLE;
	if( flag_ == REAR_EVEN )
		animFlag_ = AN_UP_REAR;
	if( flag_ == REAR_ODD )
		animFlag_ = AN_IDLE;
	
	oddHit_ = true;
	evenHit_ = false;
}

void Bone::animToggle()
{
 	started_ = !started_;
}

void Bone::animIdle()
{
	//cout << "animIdle()" << endl;
	if( flag_ == FRONT_EVEN && oddHit_ == true){
		animFlag_ = AN_UP_FRONT;
	}
	else if( flag_ == REAR_EVEN && oddHit_ == true){
		animFlag_ = AN_UP_REAR;
	}
	else if( flag_ == FRONT_ODD  && evenHit_ == true){
		animFlag_ = AN_UP_FRONT;
	}
	else if( flag_ == REAR_ODD  && evenHit_ == true){
		animFlag_ = AN_UP_REAR;
	}
	else;
}

void Bone::animUpFront()
{
	//cout << "animUpFront()" << endl;
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );
	
	offsetA_ = off_;
	childOffsetA_ = off_;
	if(a_ > (MaxA - 30.f) )
	{
		offsetA_ = 0.f;
	}			
	a_ += offsetA_;

	if(child_->a_ > (MaxB - 20.f) )
	{
			animFlag_ = AN_DOWN;	
	}
	else
		child_->a_ += childOffsetA_;

}

void Bone::animUpRear()
{
	//cout << "animUpRear()" << endl;
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
	else
		child_->a_ += childOffsetA_;

}

void Bone::animDown()
{
	//cout << "animDown()" << endl;
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );
	
	float equation_y = ( sinf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) + ( child_->l_ ) * sin_b  * cosf( deg2rad(a_) ) );

	offsetA_ = -abs(off_);
	childOffsetA_ = 0;

	if( equation_y <= -crab_y ){
		if(flag_ == FRONT_ODD){
			oddHit_ = true;
			evenHit_ = false;
		}
		else if(flag_ == FRONT_EVEN){
			evenHit_ = true;
			oddHit_ = false;
		}	
		// czy obie nogi moga juz ruszyc
		if(flag_ == FRONT_ODD || flag_ == FRONT_EVEN)
			readyFront_ = true;
		else if(flag_ == REAR_ODD || flag_ == REAR_EVEN)
			readyRear_ = true;

		if(readyFront_ && readyRear_)
			animFlag_ = AN_MOVE;
	}
	else
		a_ += offsetA_;

}


void Bone::animMove()
{	
	readyRear_ = false;
	readyFront_ = false;
	//cout << "animMove()" << endl;
	float sin_b = sinf( deg2rad(child_->a_) );
	float cos_b = cosf( deg2rad(child_->a_) );
	
	float equation_z = ( cosf( deg2rad(a_ ) ) * ( l_ + child_->l_* cos_b ) - ( child_->l_ ) * sin_b  * sinf( deg2rad(a_) ) );

	childOffsetA_ = -off_;
	if( ( flag_ == REAR_EVEN || flag_ == REAR_ODD )) 
	{
		if(min_z == 0.0f)
			min_z = equation_z;
		if(equation_z >= max_z)
			animFlag_ = AN_IDLE;
	}
	else if ( ( flag_ == FRONT_EVEN || flag_ == FRONT_ODD ) )  
	{
		if( last_equation_z == 0.0f )
			last_equation_z = equation_z;
		if( mov_offset == 0.0f )
			mov_offset = (last_equation_z - equation_z)/2;
		if( max_z == 0.0f )
			max_z = equation_z;

		if( equation_z <= min_z )
			animFlag_ = AN_IDLE;
		else
			crab_z += mov_offset;
	}

	a_ = rad2deg( ( pi*signum<float>( child_->l_*sin_b ) )/2 - asinf( crab_y/sqrtf( ( rl2<float>(child_->l_,l_) * cos_b ) + ( power<2>(l_) )+( power<2>(child_->l_) ) ) ) + atanf( ( child_->l_*cos_b  + l_) /( child_->l_*sin_b ) ) + pi) ; 	
	child_->a_ += childOffsetA_;
	
}

void Bone::Draw()
{
	glPushMatrix();
	
	// Obroc zgodnie z zadanym katem
	glRotatef(a_, 0.0f, 0.0f, 1.0f);

	if(show_bones)
	{
	   	GLfloat mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    	GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    	GLfloat high_shininess = 100.0f;
    	
   
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_diffuse);

		glBegin(GL_LINES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(l_, 0.0f);
		glEnd();
	}

	// Odrysuj siatke
	mesh_->Draw();

	// Przemiesc na koncowy punkt kosci
	glTranslatef(l_, 0.0f, 0.0f);

	// Jesli ma dzieci, dokonaj odrysowania zamkniecia stawow
	if(child_!=NULL){

	// obliczanie wartosci wierzcholkow na potrzeby przeliczenia normalnej i wyswietlenia lacznika
		Vector3f vector1, vector2, vector3, normalV;
		int segments = 12;
		for(int i = 0; i < segments; i++)
		{
			vector1.x_ = child_->mesh_->ReturnD() * sinf(-deg2rad((i+1)*child_->a_/segments));
			vector1.y_ = child_->mesh_->ReturnD() * cosf(-deg2rad((i+1)*child_->a_/segments));
			vector1.z_ = child_->mesh_->ReturnW()/2;

			vector2.x_ = child_->mesh_->ReturnD() * sinf(-deg2rad(i*child_->a_/segments));
			vector2.y_ = child_->mesh_->ReturnD() * cosf(-deg2rad(i*child_->a_/segments));
			vector2.z_ = mesh_->ReturnW()/2;

			vector3.x_ = vector1.x_;
			vector3.y_ = vector1.y_;
			vector3.z_ = -vector1.z_;

			// Obliczanie normalnej dla lacznika kryjacego staw
			Vector3f edge1 = substractV3f(vector1, vector3);
			Vector3f edge2 = substractV3f(vector3, vector2);
			normalV = normalize(crossProduct(edge1, edge2));
			
						//Wyrysowanie lacznika miedzy obudowami kosci
						glBindTexture(GL_TEXTURE_2D, 2);
						glBegin(GL_TRIANGLE_STRIP);
							glNormal3f(normalV.x_, normalV.y_, normalV.z_);
							glTexCoord2f(0.2f, 0.46f+0.03f*(i)  ); glVertex3f(vector1.x_, vector1.y_, vector1.z_);
							glTexCoord2f(0.4f, 0.46f+0.03f*(i)  ); glVertex3f(vector3.x_, vector3.y_, vector3.z_);
							glTexCoord2f(0.4f, 0.43f+0.03f*(i) ); glVertex3f(vector2.x_, vector2.y_, vector2.z_);
							glTexCoord2f(0.2f, 0.43f+0.03f*(i) ); glVertex3f(vector2.x_, vector2.y_, -vector2.z_);	
						glEnd();
						glBegin(GL_TRIANGLE_STRIP);
							glNormal3f(0.0f, 0.0f, 1.0f);
							glTexCoord2f( 0.2f, 1.0f ); glVertex3f(vector2.x_, vector2.y_, vector2.z_);
							glTexCoord2f( 0.0f, 1.0f ); glVertex3f(0.0f, 0.0f, vector2.z_);
							glTexCoord2f( 0.2f, 0.95f); glVertex3f(vector1.x_, vector1.y_, vector1.z_);
						glEnd();
						glBegin(GL_TRIANGLE_STRIP);
							glNormal3f(0.0f, 0.0f, -1.0f);
							glTexCoord2f( 0.2f, 1.0f ); glVertex3f(vector2.x_, vector2.y_, -vector2.z_);
							glTexCoord2f( 0.0f, 1.0f); glVertex3f(vector3.x_, vector3.y_, vector3.z_);								
							glTexCoord2f( 0.2f, 0.95f ); glVertex3f(0.0f, 0.0f, -vector2.z_);	
							
						glEnd();
		}
	}

	// wywolaj rysowanie dzieci
	if(child_!=NULL){
		glRotatef(0.0f, 0.0, 0.0, 1.0);
		child_->Draw();
	}
		
	glPopMatrix();
}