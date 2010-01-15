
#include <vld.h>

#include <iostream>
#include <map>

#include "glut.h"

#include "Camera.hpp"
#include "CBMPLoader.hpp"
#include "glutFunc.hpp"

#include "LegCompShort.hpp"
#include "Bone.hpp"
#include "Crab.hpp"
#include "Plane.hpp"
//

using namespace std;
using namespace glut;

//  rozmiar okna
int window_width = 800;
int window_height = 600;

//  Etykieta okna
char *window_title = "DIL Crab Walk";

//  Czy pelen ekran?
int full_screen = 0;

//FPS
int fps = 100;

// predeklaracja funkcji inicjalizujacej OGL
void init ();

//  Funkcje typu Callback
void display (void);
void reshape (int w, int h);
void myTimer(int i);

//  Funkcje dodatkowe
void centerOnScreen ();
void drawObject();
void createProjection();

//Kamera
CCamera Camera;


//glOrtho range
GLfloat nRange = 25.0f;

//  pozycja okna na ekranie
int window_x;
int window_y;


//Wysokosc kraba //////////// @TODO
float crab_y = 8.f;

//wspolzedne spot
GLfloat xSpotDir= 0, ySpotDir= 0, zOffset= 0, spotCutOff= 80.f;

//Swiatla 
void initDirLight()
{
    GLfloat noAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat whiteDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    /*
     * Directional light source (w = 0)
     * The light source is at an infinite distance,
     * all the ray are parallel and have the direction (x, y, z).
     */
    GLfloat position[] = { 0.0, 40.0, 10.0, 0.0 };
   
    glLightfv(GL_LIGHT0, GL_AMBIENT, noAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable( GL_LIGHT0 );
}

/**
 * GL_LIGHT1
 * - positional light source
 * - yellow ambient
 * - yellow diffuse
 *
 * Rem:
 * To have a "real" effect, set the ambient and diffuse to the same color.
 */
void initPosLight()
{
    GLfloat yellowAmbientDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
    /*
     * Positional light source (w = 1)
     * The light source is positioned at (x, y, z).
     * The ray come from this particular location (x, y, z) and goes towards all directions.
     */
    GLfloat position[] = { 0.0, 40.0, 10.0, 1.0 };
   
    glLightfv(GL_LIGHT1, GL_AMBIENT, yellowAmbientDiffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowAmbientDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, position);

	glEnable( GL_LIGHT1 );
}

/*
 * Update position, direction and cut-off of the light
 */
void updateSpot()
{
    GLfloat direction[] = {xSpotDir, ySpotDir, zOffset};
   
    //spot direction
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
    //angle of the cone light emitted by the spot : value between 0 to 180
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutOff);
}

void initSpot()
{
  
    GLfloat noAmbient[] = {0.0f, 0.0f, 0.4f, 1.0f};       
    GLfloat diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position[]  = { 0.0, 40.0, 0.0, 1.0 };
   

    glLightfv(GL_LIGHT2, GL_AMBIENT, noAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, position);
   
    updateSpot();
   
    //exponent propertie defines the concentration of the light
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 15.0f);
   
    //light attenuation (default values used here : no attenuation with the distance)
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);

	glEnable( GL_LIGHT2 );
}


// inicjalizacja OGL
void init ()
{    
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );
	glShadeModel( GL_PHONG_WIN );
	glEnable(GL_CULL_FACE);

    glDepthFunc( GL_LESS );

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(255.f, 255.f, 255.f, 1.0f);
	
	initSpot();
    initPosLight();

	glEnable( GL_LIGHTING );
	    

	createProjection();
    

	
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
	updateSpot();

	glTranslatef(0.f,-20.f,-14.f);
		
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
	static Plane plane;
	static Crab dilCrab;

	//static LegNormal* leg = new LegNormal(FOR_ODD);//,0.f,8.f);
	glCallList(PROJECTION);

	plane.Draw();
	/*glPushMatrix();
	glRotatef(-90.f,0.f,1.f,0.f);
	glTranslatef(0.f, 8.f, 0.f);
	leg->Draw();
	glPopMatrix();*/
	dilCrab.Draw(0.f, crab_y, 0.f);
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
      gluPerspective(70,static_cast<GLdouble>(w/h), 1, 400);
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


	//Ladowanie tekstur
	CBMPLoader CrabTex;

	// teksturka
	CrabTex.LoadBMPFile("dil.bmp");
	CrabTex.FreeImage();
	CrabTex.LoadBMPFile("leg.bmp");
	CrabTex.FreeImage();
	CrabTex.LoadBMPFile("plane.bmp");
	CrabTex.FreeImage();

	// Set the callback functions
	glutDisplayFunc (display);

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

