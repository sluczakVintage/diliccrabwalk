#include "LegShort.hpp"

LegShort::LegShort()//(GLfloat x, GLfloat y, GLfloat a, GLfloat b)
{	
	compShort0 = new LegCompShort();
	compShort1 = new LegCompShort();
	bone = new Bone(NULL, 0.f, 0.f, 0.f, 0, compShort0, "compShort0");
	
	bone->boneAddChild(60.f, 0, compShort1 , "compShort1 " );
	cout << "LegShort has been created!" << endl;
	
}


void LegShort::Draw()
{
//	bone->animate(0.f); ///////////////////////
//	bone->animate_child(0.f); ///////////////////////
	bone->Draw();
}


	