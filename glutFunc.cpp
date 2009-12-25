#include <iostream>
#include "stdlib.h"

#include "glut.h"
#include "glutFunc.hpp"

using namespace std;

extern float xRot, yRot;
extern float xMov, yMov, zMov;
extern float aa, bb;/////////////

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

//-------------------------------------------------------------------------
//  This function is passed to the glutKeyboardFunc and is called 
//  whenever the user hits a key.
//-------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
	float step = 1.0f;
	//  Print what key the user is hitting
	cout << "User is hitting the " << key << " key."<< endl;  
	cout << "ASCII code is "<< key << endl;  
	
	switch (key)
	{
		//  User hits q key
		case 'q':
			exit(0);
			break;
		//  User hits w key
		case 'w':
			zMov = step;
			break;

		//  User hits s key
		case 's':
			zMov = -step;
			break;

		//  User hits a key
		case 'a':
			xMov = -step;
			break;

		//  User hits d key
		case 'd':
			xMov = step;
			break;
		//  User hits r key
		case 'r':
			yMov = step;
			break;
		//  User hits f key
		case 'f':
			yMov = -step;
			break;
		//  User hits Enter
		case '\r':
			cout << "User is hitting the Return key."<< endl;   
			break;

		//  User hits Space
		case ' ':
			cout << "User is hitting the Space key."<< endl;  
			aa += (step/10.f); //////////////////////
			break;

		//  User hits back space
		case 8:
			cout << "User is hitting the Back Space key."<< endl; 
			aa -= (step/10.f); //////////////////////
			break;

		//  User hits ESC key
		case 27:
			exit(0);
			break;
	}

	glutPostRedisplay ();
}

//-------------------------------------------------------------------------
//  This function is passed to the glutSpecialFunc and is called 
//  whenever the user hits a special key.
//-------------------------------------------------------------------------
void special (int key, int x, int y)
{
	float step = 1.0f;
	
	switch (key)
	{
		case GLUT_KEY_F1 :
			cout << "F1 function key."<< endl;  
			break;
		case GLUT_KEY_F2 :
			cout << "F2 function key."<< endl;  
			break;
		case GLUT_KEY_F3 :
			cout << "F3 function key."<< endl;  
			break;
		case GLUT_KEY_F4 :
			cout << "F4 function key."<< endl;  
			break;
		case GLUT_KEY_F5 :
			cout << "F5 function key."<< endl;  
			break;
		case GLUT_KEY_F6 :
			cout << "F6 function key."<< endl;  
			break;
		case GLUT_KEY_F7 :
			cout << "F7 function key."<< endl;  
			break;
		case GLUT_KEY_F8 :
			cout << "F8 function key."<< endl;  
			break;
		case GLUT_KEY_F9 :
			cout << "F9 function key."<< endl;  
			break;
		case GLUT_KEY_F10 :
			cout << "F10 function key."<< endl;  
			break;
		case GLUT_KEY_F11 :
			cout << "F11 function key."<< endl; 
			bb += (step/10.f); //////////////////////
			break;
		case GLUT_KEY_F12 :
			cout << "F12 function key."<< endl;  
			bb -= (step/10.f); //////////////////////
			break;
		case GLUT_KEY_LEFT :
			cout << "Left directional key."<< endl;  
			xRot = -step;
			break;
		case GLUT_KEY_UP :
			cout << "Up directional key."<< endl;  
			yRot = step;
			break;
		case GLUT_KEY_RIGHT :
			cout << "Right directional key."<< endl;  
			xRot = step;
			break;
		case GLUT_KEY_DOWN :
			cout << "Down directional key."<< endl;  
			yRot = -step;
			break;
		case GLUT_KEY_PAGE_UP :
			cout << "Page up directional key."<< endl;  
			break;
		case GLUT_KEY_PAGE_DOWN :
			cout << "Page down directional key."<< endl;  
			break;
		case GLUT_KEY_HOME :
			cout << "Home directional key."<< endl;  
			break;
		case GLUT_KEY_END :
			cout << "End directional key."<< endl;  
			break;
		case GLUT_KEY_INSERT :
			cout << "Inset directional key."<< endl;  
			break;
	}
	
	glutPostRedisplay ();
}

GLfloat Rad2Deg (GLfloat Angle) {
  static GLfloat ratio = 180.0f / 3.141592653589793238f;
  return Angle * ratio;
}


}