
#include <vld.h>

#include <iostream>
#include <map>

#include "glut.h"

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
float crab_z = 0.f;


//  rozmiar okna
int window_width = 1000;
int window_height = 800;

//  Etykieta okna
char *window_title = "DIL Crab Walk";

//  Czy pelen ekran?
int full_screen = 0;

//FPS
int fps = 60;

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
 
GLfloat fogColor[4]= {0.0f, 0.0f, 0.0f, 1.0f};	
glut::PFNGLFOGCOORDFEXTPROC glFogCoordfEXT = NULL;					// Our glFogCoordfEXT Function

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
    GLfloat ambientDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat position[] = { 0.0, 40.0, 10.0, 1.0 };
   
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientDiffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientDiffuse);
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
  
    GLfloat noAmbient[] = {0.0f, 0.0f, 0.5f, 1.0f};       
    GLfloat diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position[]  = { 0.0, 30.0, 0.0, 1.0 };
   

    glLightfv(GL_LIGHT2, GL_AMBIENT, noAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, position);
   
    updateSpot();
   
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50.0f);
   
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
	
	glClearColor (1.0f, 1.0f, 1.0f, 0.5f);
	glClearDepth (1.0f);							
	
	glDepthFunc (GL_LEQUAL);
	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
//	glAlphaFunc(GL_GREATER,0.1f);
//	glEnable(GL_ALPHA_TEST);

	
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	
	if (!Extension_Init())
		exit(0);

	glEnable(GL_FOG);							
	glFogi(GL_FOG_MODE, GL_LINEAR);				
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.02f);
	glFogf(GL_FOG_START,  0.0f);				
	glFogf(GL_FOG_END,    1.0f);				
	glHint(GL_FOG_HINT, GL_NICEST);				
	glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);		


	initSpot();
    initPosLight();

	glEnable( GL_LIGHTING );
	    

	glut::createProjection();
    

	
}


// Wyswietlenie wszystkiego
void display ()
{		
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	Camera.Render();
	updateSpot();

	glTranslatef(0.f,-20.f,-14.f);
		
	drawObject();
	glFlush();

	//  Zamiana buforow
	glutSwapBuffers ();


}

// Wyrysowanie sceny
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
	dilCrab.Draw(0.0f, crab_y, crab_z);
}

// timer ograniczajacy predkosc animacji
void myTimer(int value){

glutPostRedisplay();
glutTimerFunc(1000/fps, myTimer, 1);

}

// wywolywana przy zmianie rozmiarow okna
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
	
	cout << "Szer. okna: " << w << ", Wysokosc okna: " << h << endl;
}

// Centrowanie (okna) na srodek ekranu
void centerOnScreen ()
{
	window_x = (glutGet (GLUT_SCREEN_WIDTH) - window_width)/2;
	window_y = (glutGet (GLUT_SCREEN_HEIGHT) - window_height)/2;

}
int main (int argc, char **argv)
{
	centerOnScreen ();
	glutInit(&argc, argv);
	glutInitWindowSize (window_width, window_height);
	glutInitWindowPosition (window_x, window_y);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutCreateWindow (window_title);

	// pelen ekran
	if (full_screen)
		glutFullScreen ();

	// inicjalizacja
	init();

	//Ladowanie tekstur
	 GLuint	texture[10];	

	if (!BuildTexture("dil.bmp", texture[0]))
		return 1;	
	if (!BuildTexture("leg.bmp", texture[1]))
		return 1;	
	if (!BuildTexture("plane.jpg", texture[2]))
		return 1;	
	if (!BuildTexture("alpha.gif", texture[3]))
		return 1;	

	// Ustawienie metod glut
	glutDisplayFunc (display);

	glutTimerFunc(1000/fps, myTimer, 1);
	glutReshapeFunc  (reshape);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutPassiveMotionFunc (pmotion);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);

	glutMainLoop();

	return 0;
}

