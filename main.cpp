
#include <vld.h>

#include <iostream>
#include <map>

#include "glut.h"
//#include "glext.h"

#include "Camera.hpp"
#include "TexLoader.hpp"
#include "glutFunc.hpp"

#include "LegCompShort.hpp"
#include "Bone.hpp"
#include "Crab.hpp"
#include "Plane.hpp"
//

using namespace std;
using namespace glut;


//Wysokosc kraba //////////// @TODO
float crab_y = 10.f;


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

//mgla
 
GLfloat fogColor[4]= {0.25f, 0.105f, 0.33f, 1.0f};	
glut::PFNGLFOGCOORDFEXTPROC glFogCoordfEXT = NULL;					// Our glFogCoordfEXT Function

//bump
#define MAX_EMBOSS (GLfloat)0.01f						// Maximum Emboss-Translate. Increase To Get Higher Immersion

//glOrtho range
GLfloat nRange = 25.0f;

//  pozycja okna na ekranie
int window_x;
int window_y;

//wspolzedne spot
GLfloat xSpotDir= 0, ySpotDir= 0, zOffset= 0, spotCutOff= 90.f;



//Swiatla 
/**
* GL_LIGHT0
kierunkowe
*/
void initDirLight()
{
    GLfloat noAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat whiteDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    GLfloat position[] = { 0.0, 40.0, 10.0, 0.0 };
   
    glLightfv(GL_LIGHT0, GL_AMBIENT, noAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable( GL_LIGHT0 );
}

/**
 * GL_LIGHT1
pozycyjne
 */
void initPosLight()
{
    GLfloat yellowAmbientDiffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat position[] = { 0.0, 40.0, 10.0, 1.0 };
   
    glLightfv(GL_LIGHT1, GL_AMBIENT, yellowAmbientDiffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowAmbientDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, position);

	glEnable( GL_LIGHT1 );
}

/**
* odswiezanie pozycji spota
*/
void updateSpot()
{
    GLfloat direction[] = {xSpotDir, ySpotDir, zOffset};
   
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutOff);
}

/**
* GL_LIGHT2
spot
*/
void initSpot()
{
  
    GLfloat noAmbient[] = {0.0f, 0.0f, 0.1f, 1.0f};       
    GLfloat diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position[]  = { 0.0, 30.0, 0.0, 1.0 };
   

    glLightfv(GL_LIGHT2, GL_AMBIENT, noAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, position);
   
    updateSpot();
   
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 25.0f);
   
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.00f);

	glEnable( GL_LIGHT2 );
}

int Extension_Init()
{
	char Extension_Name[] = "EXT_fog_coord";

	// Allocate Memory For Our Extension String
	char* glextstring=(char *)malloc(strlen((char *)glGetString(GL_EXTENSIONS))+1);
	strcpy (glextstring,(char *)glGetString(GL_EXTENSIONS));		// Grab The Extension List, Store In glextstring

	if (!strstr(glextstring,Extension_Name))				// Check To See If The Extension Is Supported
		return FALSE;							// If Not, Return FALSE

	free(glextstring);							// Free Allocated Memory

	// Setup And Enable glFogCoordEXT
	glFogCoordfEXT = (PFNGLFOGCOORDFEXTPROC) wglGetProcAddress("glFogCoordfEXT");

	return TRUE;
}


// inicjalizacja OGL
void init ()
{    
	
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_CULL_FACE);
	
	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth (1.0f);							
	
	glDepthFunc (GL_LEQUAL);
	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
//	glAlphaFunc(GL_GREATER,0.1f);
//	glEnable(GL_ALPHA_TEST);

	
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	
	
	//if (!Extension_Init())
	//	exit(0);

	//glEnable(GL_FOG);							
	//glFogi(GL_FOG_MODE, GL_LINEAR);				
	//glFogfv(GL_FOG_COLOR, fogColor);
	//glFogf(GL_FOG_DENSITY, 0.02f);
	//glFogf(GL_FOG_START,  0.0f);				
	//glFogf(GL_FOG_END,    1.0f);				
	//glHint(GL_FOG_HINT, GL_NICEST);				
	//glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);		


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
int main (int argc, char **argv)
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
	 GLuint	texture[10];	

	// teksturka
	 
	if (!BuildTexture("dil.bmp", texture[0]))
		return 1;	
	if (!BuildTexture("leg.bmp", texture[1]))
		return 1;	
	if (!BuildTexture("plane.bmp", texture[2]))
		return 1;	
	if (!BuildTexture("alpha.gif", texture[3]))
		return 1;	

	
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

	return 0;
}

