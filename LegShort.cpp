#include "LegShort.hpp"

LegShort::LegShort()
{	
	compShort0 = new LegCompShort();
	compShort1 = new LegCompShort();
	bone = new Bone(NULL, 0.f, 0.f, 0.f, 0, compShort0, "compShort0");
	
	bone->boneAddChild(-75.f, 0, compShort1 , "compShort1 " );
	cout << "LegShort stworzona!" << endl;
	
}

LegShort::~LegShort()
{
	delete compShort0;
	delete compShort1;
	delete bone;
	compShort0 = NULL;
	compShort1 = NULL;
	bone = NULL;
}
void LegShort::Draw()
{
	bone->Draw();
}


	