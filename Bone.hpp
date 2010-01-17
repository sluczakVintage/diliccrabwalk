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

enum{ FRONT_ODD, REAR_ODD, FRONT_EVEN, REAR_EVEN };
enum{ AN_IDLE, AN_UP_FRONT, AN_UP_REAR, AN_DOWN, AN_MOVE };

using namespace std;
class Bone
{
public:
	
	Bone(Bone* root, GLfloat x, GLfloat y, GLfloat a, int flag , Drawable *mesh, string name);
	~Bone();
	
	void boneAddChild(GLfloat a, int flag, Drawable *mesh, string name);
	void Draw();
	void animate(); 

	void animToggle();
	void Bone::newOffset(GLfloat off);
	
	void animInit();
	void animUpFront();
	void animUpRear();
	void animDown();
	void animMove();
	void animMoveToStop();

	void animIdle();

private:
	Bone();

	// krok z jakim zmienia sie kat (animacja przebiega tylko na poziomie rodzica
	GLfloat offsetA_;
	GLfloat childOffsetA_;
	// pole pomocnicze przy metodach animacyjnych
	GLfloat off_;
	// wspolrzedne poczatku kosci
	GLfloat x_;
	GLfloat y_;
	// kat nachylenia kosci i jej dlugosc
	GLfloat a_;
	GLfloat l_;
	// wskazniki na ojca i dziecko (root nie ma ojca)
	Bone *father_;
	Bone *child_;
	// wskaznik na siatke obudowujaca kosc
	Drawable *mesh_;
	// Nazwa kosci
	string name_;
	//Flaga kosci
	int flag_;

	// Rozpoczecie animacji
	//static bool started_;
	// Flaga animacji
	int animFlag_;
	// Uderzenie w ziemie
	//static bool oddHit_;
	//static bool evenHit_;
	// Gotowosc do kroku
	//static bool readyFront_;
	//static bool readyRear_;
	// Wartosc maksymalna 
//	static float max_x;
//	static float min_x;

	
};

#endif
