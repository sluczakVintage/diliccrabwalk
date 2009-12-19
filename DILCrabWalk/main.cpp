//*************************************************************************
//
//  File Name	: GLUT Window Template
//  Author		: Ali BaderEddin
//  Date		: December 2003
//  
//  Description	: Openning an OpenGL window using GLUT library...
//  
//*************************************************************************

//  Input\Output Stream
#include <iostream>
//  Include GLUT, OpenGL, and GLU libraries
#include "glut.h"

#include "glutFunc.hpp"
#include "Crab.hpp"
//
#include "LegCompShort.hpp"


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
//VARIABLES
//Rotation of observer
float xRot = 0, yRot = 0;
float xMov = 0, yMov = 0, zMov = 0;

//glOrtho range
GLfloat nRange = 10.0f;

//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
int window_width = 1000;
int window_height = 750;

//  variable representing the window title
char *window_title = "GLUT Window Template";

//  Tells whether to display the window full screen or not
//  Press Alt + Esc to exit a full screen.
int full_screen = 0;

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
	glShadeModel( GL_PHONG_WIN );
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

	//  Clear the window or more specifically the frame buffer...
	//  This happens by replacing all the contents of the frame
	//  buffer by the clear color (black in our case)
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glRotatef(xRot, 0.0f, 1.0f, 0.0f);
			glRotatef(yRot, 1.0f, 0.0f, 0.0f);
			xRot = yRot = 0.0f;
			cout << xRot << endl;
			cout << yRot << endl;
		
			glTranslatef(xMov, 0.0f, 0.0f);
			glTranslatef(0.0f, yMov, 0.0f);
			glTranslatef(0.0f, 0.0f, zMov);
			xMov = yMov = zMov = 0.f;
		
		glMatrixMode(GL_MODELVIEW);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			//  Draw object
			drawObject ();
			glFlush();

		//  Swap contents of backward and forward frame buffers
		glutSwapBuffers ();
		
	glPopMatrix();

}

//-------------------------------------------------------------------------
//  Draws our object.
//-------------------------------------------------------------------------
void drawObject ()
{
	static Crab* dilCrab = new Crab();
	dilCrab->Draw(0.0, 0.0, 0.0);
	//static LegCompShort* leg = new LegCompShort();
	//leg->Draw(0.0, 0.0, 0.0);

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
      //gluPerspective(70,static_cast<GLdouble>(w/h), 1, 80);
	   if( w <= h ) {
         glOrtho( -nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f , nRange*2.0f);
      }
      else {
         glOrtho( -nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
      }
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
	glutReshapeFunc  (reshape);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutPassiveMotionFunc (pmotion);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);

	//  Start GLUT event processing loop
	glutMainLoop();
}

