
#include <vld.h>

#include <iostream>
#include <math.h>
#include <time.h>

#include "glut.h"

#include "TexLoader.hpp"
#include "glutFunc.hpp"
#include "camLights.hpp"

#include "LegCompShort.hpp"
#include "Bone.hpp"
#include "Crab.hpp"
#include "Plane.hpp"
//

using namespace std;
using namespace glut;

//Wysokosc kraba 
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

//mgla 
GLfloat fogColor[4]= {0.3f, 0.1f, 0.5f, 1.0f};	

//glOrtho range
GLfloat nRange = 25.0f;

//  pozycja okna na ekranie
int window_x;
int window_y;


//  Funkcje typu Callback
void display (void);
void reshape (int w, int h);
void myTimer(int i);

//  Funkcje dodatkowe
void centerOnScreen ();
void drawObject();
void createProjection();



// inicjalizacja OGL
void init ()
{    
	
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_CULL_FACE);
	
	glClearColor (0.3f, 0.1f, 0.5f, 1.0f);	//(1.0f, 1.0f, 1.0f, 0.5f);
	glClearDepth (1.0f);							
	
	glDepthFunc (GL_LEQUAL);
	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
// Mg³a
	glEnable(GL_FOG);							
	glFogi(GL_FOG_MODE, GL_LINEAR);				
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.3f);
	glFogf(GL_FOG_START,  180.0f);				
	glFogf(GL_FOG_END,    250.0f);				
	glHint(GL_FOG_HINT, GL_NICEST);					


	initSpot();
	initSpots();
    //initDirLight();

	glEnable( GL_LIGHTING );
	    
	createProjection();

	srand(time(NULL));
}


// wywolywana przy zmianie rozmiarow okna
void reshape (int w, int h)
{
	  if( h > 0 && w > 0 ) {
      glViewport( 0, 0, w, h );
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluPerspective(70,static_cast<GLdouble>(w/h), 1, 1000);
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


// Wyswietlenie wszystkiego
void display ()
{		
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
	camera();
	  
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	updateSpot();

		
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
	static Crab dilCrab2;
	
	//glCallList(PROJECTION);

	plane.Draw();
	
	dilCrab.Draw(0.0f, crab_y, crab_z);

	for(int i = 0; i <= 2; i++)
	{
		dilCrab2.StaticDraw(35+(i*24), 0.f, 70+27*i, 14+27*i);

		dilCrab2.StaticDraw(-60+(i)*4, 0.f, 60*+(i)*25, 25+18*i);

		dilCrab2.StaticDraw(-40, 0.f, 70+70*i, 25+41*i);

		dilCrab2.StaticDraw(60+(i*25), 0.f, 147+25*i, 90-67*i);

		dilCrab2.StaticDraw(-100+i*40, 0.f, 155, 30+19*i);
	}	

	glMatrixMode (GL_PROJECTION);
glPopMatrix();
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

	if (!BuildTexture("dil.jpg ", texture[0]))
		return 1;	
	if (!BuildTexture("leg.bmp", texture[1]))
		return 1;	
	if (!BuildTexture("plane.jpg", texture[2]))
		return 1;		

	// Ustawienie metod glut
	glutDisplayFunc (display);

	glutTimerFunc(1000/fps, glut::myTimer, 1);
	glutReshapeFunc  (reshape);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutPassiveMotionFunc (pmotion);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);

	glutMainLoop();

	return 0;
}

