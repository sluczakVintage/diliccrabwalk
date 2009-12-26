#include "LegNormal.hpp"

LegNormal::LegNormal(int flag)// GLfloat x, GLfloat y)
{	
	GLfloat a = 0.f, child_a = 0.f;
	compShort = new LegCompShort();
	compLong = new LegCompLong();
	
	if(flag == FOR_ODD){
		a = 20.f;
		child_a = -110.f;
	}
	else if(flag == FOR_EVEN){
		a = 20.f;
		child_a = -110.f;
	}
	if(flag == BACK_ODD){
		a = 20.f;
		child_a = -110.f;
	}
	else if(flag == BACK_EVEN){
		a = -20.f;
		child_a = -45.f;
	}

	bone = new Bone(NULL, 0.f, 0.f, a, flag, compShort, "compShort");
	
	bone->boneAddChild(child_a, flag, compLong , "compLong" );
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
	bone->animate(); 
	bone->Draw();
}


	