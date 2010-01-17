#include "LegNormal.hpp"

LegNormal::LegNormal(int flag)
{	
	GLfloat a = 0.f, child_a = 0.f;
	compShort = new LegCompShort();
	compLong = new LegCompLong();
	// przydzielenie wartosci poczatkowych
	if(flag == FRONT_ODD){
		a = 30.f;
		child_a = -105.f;
	}
	else if(flag == FRONT_EVEN){
		a = 30.f;
		child_a = -105.f;
	}
	if(flag == REAR_ODD){
		a = 30.f;
		child_a = -105.f;
	}
	else if(flag == REAR_EVEN){
		a = 30.f;
		child_a = -105.f;
	}

	bone = new Bone(NULL, 0.f, 0.f, a, flag, compShort, "compShort");
	
	bone->boneAddChild(child_a, flag, compLong , "compLong" );
	cout << "LegNormal  stworzona" << endl;
	
}

void LegNormal::animToggle() 
{
	bone->animToggle();
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

void LegNormal::StaticDraw()
{
	bone->Draw();
}



	