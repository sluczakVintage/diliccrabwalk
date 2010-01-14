
#include "glutFunc.hpp"
#include <math.h>

using namespace std;

extern CCamera Camera;

//TEST
extern GLfloat xSpotDir, ySpotDir, zOffset, spotCutOff;

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
					spotCutOff = static_cast<int>(spotCutOff - 0.5f)%180;
					cout << spotCutOff << endl;  ;
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
	//cout << "Mouse Move Position: "<<  x << ", " << y << endl;  
}

//-------------------------------------------------------------------------
//  This function is passed to the glutKeyboardFunc and is called 
//  whenever the user hits a key.
//-------------------------------------------------------------------------


void keyboard (unsigned char key, int x, int y)
{
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
			Camera.MoveForwards( -0.1 ) ;
			break;

		case 'W':
			Camera.MoveForwards( -1.0 ) ;
			break;

		//  User hits s key
		case 's':
			Camera.MoveForwards( 0.1 ) ;
			break;
		case 'S':
			Camera.MoveForwards( 1.0 ) ;
			break;

		//  User hits a key
		case 'a':
			Camera.StrafeRight(-0.5);
			break;

		//  User hits d key
		case 'd':
			Camera.StrafeRight(0.5);
			break;
		//  User hits r key
		case 'r':
			zOffset += 1.0f;
			break;
		//  User hits f key
		case 'f':
			zOffset -= 1.0f;
			break;
		//  User hits Enter
		case '\r':
			cout << "User is hitting the Return key."<< endl;   
			break;

		//  User hits Space
		case ' ':
			cout << "User is hitting the Space key."<< endl;  
			break;

		//  User hits back space
		case 8:
			cout << "User is hitting the Back Space key."<< endl; 
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
			ySpotDir += 0.5f;
			cout << ySpotDir << endl;  
			break;
		case GLUT_KEY_F2 :
			ySpotDir -= 0.5f;
			cout << ySpotDir << endl;  
			break;
		case GLUT_KEY_F3 :
			break;
		case GLUT_KEY_F4 :
			cout << "F4 function key."<< endl;  
			break;
		case GLUT_KEY_F5 :
			spotCutOff = static_cast<int>(spotCutOff + 1.0f)%180;
					cout << spotCutOff << endl;  ;
			//cout << "F5 function key."<< endl;  
			break;
		case GLUT_KEY_F6 :
			spotCutOff = static_cast<int>(spotCutOff - 1.0f)%180;
					cout << spotCutOff << endl;  ;
			//cout << "F6 function key."<< endl;  
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
			break;
		case GLUT_KEY_F12 :
			cout << "F12 function key."<< endl;  
			break;
		case GLUT_KEY_LEFT :
			cout << "Left directional key."<< endl; 
			Camera.RotateY(5.0);
			break;
		case GLUT_KEY_UP :
			cout << "Up directional key."<< endl;  
			Camera.Move(F3dVector(0.0,0.3,0.0));
			break;
		case GLUT_KEY_RIGHT :
			cout << "Right directional key."<< endl;  
			Camera.RotateY(-5.0);
			break;
		case GLUT_KEY_DOWN :
			cout << "Down directional key."<< endl;  
			Camera.Move(F3dVector(0.0,-0.3,0.0));
			break;
		case GLUT_KEY_PAGE_UP :
			Camera.RotateX(5.0);
			cout << "Page up directional key."<< endl;  
			break;
		case GLUT_KEY_PAGE_DOWN :
			Camera.RotateX(-5.0);
		cout << "Page down directional key."<< endl;  
			break;
		case GLUT_KEY_HOME :
			xSpotDir += 0.5f;
			cout << xSpotDir << endl;  
			break;
		case GLUT_KEY_END :
			xSpotDir -= 0.5f;
			cout << xSpotDir << endl;  
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