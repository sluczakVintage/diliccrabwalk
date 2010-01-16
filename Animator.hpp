/**
*
*	Klasa opisujaca model kraba
*
*
**/
#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <iostream>
#include <string>
#include <math.h>

#include "Bone.hpp"

#include "glut.h"
#include "glutFunc.hpp"

#include "Drawable.hpp"


using namespace std;

class Animator
{
public:
	Animator();
	Animator(const Animator&);
	~Animator();
	/*static Animator* getInstance() {
		if(!pInstance_)
			pInstance_ = new Animator;
		return pInstance_;
	}
	void destroyInstance() {
		delete pInstance_;
	}*/
	//uruchamia animacje, przydziela odpowiednie flagi
	void animStart(Bone& bone);
	//zatrzymuje animacje
	void animStop(Bone& bone);
	//resetuje animacje
	void animReset(Bone& bone);
	void animate(Bone& bone); 
	
private:
	
	
	//static Animator* pInstance_;

		//czy noga uderzyla w podloze
	static bool oddHit_;
	static bool evenHit_;

	//okresla czy animacja trwa
	bool started_;
};