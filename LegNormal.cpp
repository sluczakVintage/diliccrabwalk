#include "LegNormal.hpp"

LegNormal::LegNormal()//(GLfloat x, GLfloat y, GLfloat a, GLfloat b)
{	
	compShort = new LegCompShort();
	compLong = new LegCompLong();
	bone = new Bone(NULL, 0.f, 0.f, 0.f, 0.f, compShort, "compShort");
	
	bone->boneAddChild(0.f, 0.f, compLong , "compLong" );
	cout << "LegNormal has been created!" << endl;
	
}


void LegNormal::Draw()
{
//	bone->animate(0.f); ///////////////////////
//	bone->animate_child(0.f); ///////////////////////
	bone->Draw();
}


	