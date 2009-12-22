#include "LegNormal.hpp"

LegNormal::LegNormal(int flag)//(GLfloat x, GLfloat y, GLfloat a, GLfloat b)
{	
	compShort = new LegCompShort();
	compLong = new LegCompLong();
	bone = new Bone(NULL, 0.f, 0.f, 44.f, flag, compShort, "compShort");
	
	bone->boneAddChild(0.f, flag, compLong , "compLong" );
	cout << "LegNormal has been created!" << endl;
	
}


void LegNormal::Draw()
{
	bone->animate(); ///////////////////////
	//	bone->animate_child(); ///////////////////////
	bone->Draw();
}


	