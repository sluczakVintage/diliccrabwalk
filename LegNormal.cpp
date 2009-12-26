#include "LegNormal.hpp"

LegNormal::LegNormal(int flag)// GLfloat x, GLfloat y)
{	
	compShort = new LegCompShort();
	compLong = new LegCompLong();
	bone = new Bone(NULL, 0.f, 0.f, 15.f, flag, compShort, "compShort");
	
	bone->boneAddChild(-75.f, flag, compLong , "compLong" );
	cout << "LegNormal has been created!" << endl;
	
}

LegNormal::~LegNormal()
{
	delete compShort;
	delete compLong;
	delete bone;
	compShort = NULL;
	compLong = NULL;
	bone = NULL;
}

void LegNormal::Draw()
{
	bone->animate(); ///////////////////////
	//	bone->animate_child(); ///////////////////////
	bone->Draw();
}


	