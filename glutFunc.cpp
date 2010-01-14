#include <iostream>
#include "stdlib.h"

#include "glut.h"
#include "glutFunc.hpp"
#include <math.h>

using namespace std;


namespace glut
{
/*-------------------------------------------------------------------------
  This function is passed to the glutMouseFunc and is called 
  whenever the mouse is clicked.
-------------------------------------------------------------------------*/
void mouse (int button, int state, int x, int y)
{
	switch (button)
	{
		//  Left Button Clicked
		case GLUT_LEFT_BUTTON:

			switch (state)
			{
				//  Pressed 
				case GLUT_DOWN:
					cout << "Mouse Left Button Pressed (Down)..."<< endl;  ;
					break;
				//  Released
				case GLUT_UP:
					cout << "Mouse Left Button Released (Up)..."<< endl;  ;
					break;
			}

			break;

		//  Middle Button clicked
		case GLUT_MIDDLE_BUTTON:
			
			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					cout << "Mouse Middle Button Pressed (Down)..."<< endl;  ;
					break;
				//  Released
				case GLUT_UP:
					cout << "Mouse Middle Button Released (Up)..."<< endl;  ;
					break;
			}

			break;

		//  Right Button Clicked
		case GLUT_RIGHT_BUTTON:
			
			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					cout << "Mouse Right Button Pressed (Down)..."<< endl;  ;
					break;
				//  Released
				case GLUT_UP:
					cout << "Mouse Right Button Released (Up)..."<< endl;  ;
					break;
			}

			break;

	}
}

//-------------------------------------------------------------------------
//  This function is passed to the glutMotionFunc and is called 
//  whenever the mouse is dragged.
//-------------------------------------------------------------------------
void motion (int x, int y)
{
	//  Print the mouse drag position
	cout << "Mouse Drag Position: "<<  x << ", " << y << endl;  
}

//-------------------------------------------------------------------------
//  This function is passed to the glutPassiveMotionFunc and is called 
//  whenever the mouse is moved.
//-------------------------------------------------------------------------
void pmotion (int x, int y)
{
	//  Print mouse move positopn
	cout << "Mouse Move Position: "<<  x << ", " << y << endl;  
}


GLfloat Rad2Deg (GLfloat Angle) {
  static GLfloat ratio = 180.0f / 3.141592653589793238f;
  return Angle * ratio;
}


}