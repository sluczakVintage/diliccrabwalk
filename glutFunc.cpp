
#include "glutFunc.hpp"


using namespace std;

bool anim_toggle = false;
//TEST
extern GLfloat nRange;
extern int fps;
extern float xpos , ypos, zpos , xrot, yrot;
float lastx, lasty;


Vector3f substractV3f(Vector3f v1, Vector3f v2)
{
	float x = v1.x_ - v2.x_;
	float y = v1.y_ - v2.y_;
	float z = v1.z_ - v2.z_;
	
	return Vector3f(x,y,z);
}

Vector3f crossProduct(Vector3f v1, Vector3f v2) 
{
   float x = (v1.y_ * v2.z_) - (v2.y_ * v1.z_);
   float y = (v1.z_ * v2.x_) - (v2.z_ * v1.x_);
   float z = (v1.x_ * v2.y_) - (v2.x_ * v1.y_);
   
   return Vector3f(x,y,z);
}

Vector3f normalize(Vector3f v) 
{
	float r = sqrtf(v.x_*v.x_ + v.y_*v.y_ + v.z_*v.z_);

	float x = v.x_/r;
	float y = v.y_/r;
	float z = v.z_/r;

	return Vector3f(x,y,z);
}
	// Stworz uklad wspolrzednych
void createProjection()
{
	glNewList(PROJECTION, GL_COMPILE);
		glBegin(GL_LINES);
			//oX AXIS
			glVertex3f(-nRange,0.0f,0.0f);
			glVertex3f(nRange,0.0f,0.0f);

			glVertex3f(nRange,0.0f,0.0f);
			glVertex3f((nRange*0.95f),nRange*0.05f,0.0f);

			glVertex3f(nRange,0.0f,0.0f);
			glVertex3f((nRange*0.95f),-nRange*0.05f,0.0f);

			//oZ AXIS
			glVertex3f(0.f,0.0f,-nRange);
			glVertex3f(0.f,0.0f,nRange*1000.f);

			glVertex3f(0.0f,0.0f,nRange);
			glVertex3f(-nRange*0.05f,0.0f,(nRange*0.95f));
			
			glVertex3f(0.0f,0.0f,nRange);
			glVertex3f(nRange*0.05f,0.0f,(nRange*0.95f));
			
			//oY AXIS
			glVertex3f(0.f,nRange,0.0f);
			glVertex3f(0.f,-nRange,0.0f);

			glVertex3f(0.f,nRange,0.0f);
			glVertex3f(nRange*0.05f,(nRange*0.95f),0.0f);

			glVertex3f(0.f,nRange,0.0f);
			glVertex3f(-nRange*0.05f,(nRange*0.95f),0.0f);
		glEnd();
	glEndList();
}


namespace glut
{

GLfloat Rad2Deg (GLfloat Angle) {
	static GLfloat ratio = 180.0f / 3.141592653589793238f;
	return Angle * ratio;
}

GLfloat Deg2Rad (GLfloat Rad) {
	static GLfloat ratio = 180.0f / 3.141592653589793238f;
	return Rad / ratio;
}


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
	int diffx=x-lastx; //check the difference between the current x and the last x position
	int diffy=y-lasty; //check the difference between the current y and the last y position
	lastx=x; //set lastx to the current x position
	lasty=y; //set lasty to the current y position
	xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
	yrot += (float) diffx;	//set the xrot to yrot with the addition of the difference in the x position

	cout << "xrot " << xrot << endl;
	cout << "yrot " << yrot << endl;
	//  Print the mouse drag position
	//cout << "Mouse Drag Position: "<<  x << ", " << y << endl;  
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
			xpos += sinf(Deg2Rad(yrot)) ;
			zpos -= cosf(Deg2Rad(yrot)) ;
			ypos -= sinf(Deg2Rad(xrot)) ;
			//Camera.MoveForwards( -0.1 ) ;
			break;

		case 'W':
			//Camera.MoveForwards( -1.0 ) ;
			break;

		//  User hits s key
		case 's':
			xpos -= sinf(Deg2Rad(yrot)) ;
			zpos += cosf(Deg2Rad(yrot)) ;
			ypos += sinf(Deg2Rad(xrot)) ;
			//Camera.MoveForwards( 0.1 ) ;
			break;
		case 'S':
			//Camera.MoveForwards( 1.0 ) ;
			break;

		//  User hits a key
		case 'a':
			xpos -= cosf(Deg2Rad(yrot)) * 0.2;
			zpos -= sinf(Deg2Rad(yrot)) * 0.2;
			//Camera.StrafeRight(-0.5);
			break;

		//  User hits d key
		case 'd':
			xpos += cosf(Deg2Rad(yrot)) * 0.2;
			zpos += sinf(Deg2Rad(yrot)) * 0.2;
			//Camera.StrafeRight(0.5);
			break;
		//  User hits r key
		case 'r':

			break;
		//  User hits f key
		case 'f':

			break;
		//  User hits Enter
		case '\r':
			cout << "User is hitting the Return key."<< endl;   
			break;

		//  User hits Space
		case ' ':
			anim_toggle = true;
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
		

	//glutPostRedisplay ();
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

			break;
		case GLUT_KEY_F2 :

			break;
		case GLUT_KEY_F3 :	
			break;
		case GLUT_KEY_F4 :
			cout << "F4 function key."<< endl;  
			break;
		case GLUT_KEY_F5 :

			//cout << "F5 function key."<< endl;  
			break;
		case GLUT_KEY_F6 :

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
			fps = 1;
			cout << "F10 function key."<< endl;  
			break;
		case GLUT_KEY_F11 :
			fps++;
			cout << "F11 function key."<< endl; 
			break;
		case GLUT_KEY_F12 :
			fps--;
			if(fps < 1)
				fps = 1;
			cout << "F12 function key."<< endl;  
			break;
		case GLUT_KEY_LEFT :
			cout << "Left directional key."<< endl; 
			//Camera.RotateY(5.0);
			break;
		case GLUT_KEY_UP :
			xrot += 1;
			if (xrot >360) xrot -= 360;
			cout << "Up directional key."<< endl;  
			//Camera.Move(F3dVector(0.0,0.3,0.0));
			break;
		case GLUT_KEY_RIGHT :
			cout << "Right directional key."<< endl;  
			//Camera.RotateY(-5.0);
			break;
		case GLUT_KEY_DOWN :
			xrot -= 1;
			if (xrot < -360) xrot += 360;
			cout << "Down directional key."<< endl;  
			//Camera.Move(F3dVector(0.0,-0.3,0.0));
			break;
		case GLUT_KEY_PAGE_UP :
			//Camera.RotateX(5.0);
			cout << "Page up directional key."<< endl;  
			break;
		case GLUT_KEY_PAGE_DOWN :
			//Camera.RotateX(-5.0);
		cout << "Page down directional key."<< endl;  
			break;
		case GLUT_KEY_HOME :
			break;
		case GLUT_KEY_END :  
			break;
		case GLUT_KEY_INSERT :
			cout << "Inset directional key."<< endl;  
			break;
	}
	
	//glutPostRedisplay ();
}


}
