//*************************************************************************
//
//  File Name	: GLUT Window Template
//  Author		: Ali BaderEddin
//  Date		: December 2003
//  
//  Description	: Openning an OpenGL window using GLUT library...
//  
//*************************************************************************
#include <vld.h>
//  Input\Output Stream
#include <iostream>
//  Include GLUT, OpenGL, and GLU libraries
#include "glut.h"

#include "Camera.hpp"
#include "glutFunc.hpp"

#include "LegCompShort.hpp"
#include "Bone.hpp"
#include "Crab.hpp"
#include "Plane.hpp"
//



using namespace std;
using namespace glut;
//  Initialization
void init ();

//  Callback functions
void display (void);
void reshape (int w, int h);

//  Support Functions
void centerOnScreen ();
void drawObject();
void createProjection();
void myTimer(int i);
void keyboard (unsigned char key, int x, int y);
//VARIABLES

CCamera Camera;


//glOrtho range
GLfloat nRange = 25.0f;

//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
int window_width = 600;
int window_height = 500;

//  variable representing the window title
char *window_title = "GLUT Window Template";

//  Tells whether to display the window full screen or not
//  Press Alt + Esc to exit a full screen.
int full_screen = 0;

//Crab Y
float crab_y = 8.f;

//FPS
int fps = 100;

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init ()
{	
	GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
    GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );
    
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );
    
	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );
	glEnable(GL_CULL_FACE);

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glDepthFunc( GL_LESS );

	glClearColor(255.f, 255.f, 255.f, 1.0f);
	createProjection();

    
}

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
			glVertex3f(0.f,0.0f,nRange);

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
//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display 
//	OpenGL contents on the window.
//-------------------------------------------------------------------------
void display (void)
{		
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	Camera.Render();
	
	glTranslatef(0.f,-10.f,-14.f);
		
	//  Draw object
	drawObject();
	glFlush();

	//  Swap contents of backward and forward frame buffers
	glutSwapBuffers ();


}

//-------------------------------------------------------------------------
//  Draws our object.
//-------------------------------------------------------------------------
void drawObject ()
{
	static Plane* plane = new Plane();
	static Crab* dilCrab = new Crab();
	//static LegNormal* leg = new LegNormal(FOR_ODD);//,0.f,8.f);
	glCallList(PROJECTION);

	plane->Draw();
	/*glPushMatrix();
	glRotatef(-90.f,0.f,1.f,0.f);
	glTranslatef(0.f, 8.f, 0.f);
	leg->Draw();
	glPopMatrix();*/
	dilCrab->Draw(0.f, crab_y, 0.f);
}

void myTimer(int value){

glutPostRedisplay();
glutTimerFunc(1000/fps, myTimer, 1);

}

//-------------------------------------------------------------------------
//  This function is passed to the glutReshapeFunc and is called 
//  whenever the window is resized.
//-------------------------------------------------------------------------
void reshape (int w, int h)
{
	  if( h > 0 && w > 0 ) {
      glViewport( 0, 0, w, h );
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective(70,static_cast<GLdouble>(w/h), 1, 80);
	  /* if( w <= h ) {
         glOrtho( -nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f , nRange*2.0f);
      }
      else {
		 glOrtho( -nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
      }*/
      glMatrixMode( GL_MODELVIEW );
	  glLoadIdentity();
    }
	//  Print current width and height on the screen
	cout << "Window Width: " << w << ", Window Height: " << h << endl;
}

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen ()
{
	window_x = (glutGet (GLUT_SCREEN_WIDTH) - window_width)/2;
	window_y = (glutGet (GLUT_SCREEN_HEIGHT) - window_height)/2;

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
			Camera.MoveForwards( 1 ) ;
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

//-------------------------------------------------------------------------
//  Program Main method.
//-------------------------------------------------------------------------
void main (int argc, char **argv)
{
	//  Set the window x and y coordinates such that the 
	//  window becomes centered
	centerOnScreen ();
	//  Connect to the windowing system + create a window
	//  with the specified dimensions and position
	//  + set the display mode + specify the window title.
	glutInit(&argc, argv);
	glutInitWindowSize (window_width, window_height);
	glutInitWindowPosition (window_x, window_y);
	 glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutCreateWindow (window_title);

	//  View in full screen if the full_screen flag is on
	if (full_screen)
		glutFullScreen ();

	//  Set OpenGL program initial state.
	init();
	
	// Set the callback functions
	glutDisplayFunc (display);
	//glutIdleFunc(display);
	glutTimerFunc(1000/fps, myTimer, 1);
	glutReshapeFunc  (reshape);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutPassiveMotionFunc (pmotion);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);

	//  Start GLUT event processing loop
	glutMainLoop();
}

