
#include <vld.h>

#include <iostream>
#include <math.h>

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

static int frames = 0;
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

//mgla 
GLfloat fogColor[4]= {0.3f, 0.1f, 0.5f, 1.0f};	

//glOrtho range
GLfloat nRange = 25.0f;

//  pozycja okna na ekranie
int window_x;
int window_y;

///////////////////////////
//Kamera
float xpos = 0.0f, ypos = 0.0f, zpos = 0.0f, xrot = 0.0f, yrot = 0.0f;
float cRadius = 25.f;
///////////////////////////

extern bool anim_toggle;

//Swiatla 
/**
* GL_LIGHT0
kierunkowe
*/
void initDirLight()
{
    GLfloat noAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat whiteDiffuse[] = {0.2f, 0.2f, 0.2f, 1.0f};
    
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
* GL_LIGHT3-5
spot
*/
void initSpot2()
{	
	GLfloat position3[]  = { -150.0, 30.0f, -150.0, 1.0f };
	GLfloat position4[]  = { 150.0, 30.0f, -150.0, 1.0f };
	GLfloat position5[]  = { 0.0, 30.0f, -150.0, 1.0f };
   
	GLfloat direction3[] = {1.0f, -0.3f, 1.0f};
	GLfloat direction4[] = {-1.0f, -0.3f, 1.0f};
	GLfloat direction5[] = {0.0f, -0.4f, 1.0f};
      
    GLfloat noAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};       
    GLfloat diffuse[]   = {0.4f, 0.4f, 0.35f, 1.0f};

    glLightfv(GL_LIGHT3, GL_AMBIENT, noAmbient);  glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT3, GL_POSITION, position3); glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction3);  
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 90); glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 128);
   
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.00000f);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.000004f);

	glLightfv(GL_LIGHT4, GL_AMBIENT, noAmbient);  glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT4, GL_POSITION, position4); glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction4);  
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 90); glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.00000f);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION,0.000004f);

	glLightfv(GL_LIGHT5, GL_AMBIENT, noAmbient);  glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT5, GL_POSITION, position5); glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direction5);  
    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 40); glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 128);

	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.00000f);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION,0.000004f);

	glEnable( GL_LIGHT3 );
	glEnable( GL_LIGHT4 );
	glEnable( GL_LIGHT5 );
}


/**
* odswiezanie pozycji spota LIGHT2
*/
void updateSpot()
{	
	GLfloat position[]  = { 0.0, 100.f, crab_z - 40.f, 1.0f };
    GLfloat direction[] = {0.0f, -1.0f, 0.33};
   
	glLightfv(GL_LIGHT2, GL_POSITION, position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50);
}
/**
* GL_LIGHT2
spot
*/

void initSpot()
{
  
    GLfloat noAmbient[] = {0.2f, 0.2f, 0.1f, 1.0f};       
    GLfloat diffuse[]   = {0.9f, 0.9f, 0.8f, 1.0f};
   

    glLightfv(GL_LIGHT2, GL_AMBIENT, noAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);

    updateSpot();
   
   
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.00002f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.000009f);

	glEnable( GL_LIGHT2 );
}


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
	
//	glAlphaFunc(GL_GREATER,0.1f);
//	glEnable(GL_ALPHA_TEST);

	
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	
	glEnable(GL_FOG);							
	glFogi(GL_FOG_MODE, GL_LINEAR);				
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.2f);
	glFogf(GL_FOG_START,  400.0f);				
	glFogf(GL_FOG_END,    550.0f);				
	glHint(GL_FOG_HINT, GL_NICEST);				
	//glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);		


	initSpot();
	initSpot2();
   // initDirLight();

	glEnable( GL_LIGHTING );
	    
	createProjection();

}


// timer ograniczajacy predkosc animacji
void myTimer(int value)
{
frames++;
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
void camera () {
	
	static float start = 140;
	static float a = start;
	static float addition = 0;
	static float step = 0.005f;

	static bool part[10] = {false, false, false, false, false, false, false, false, false, false};

	if(part[0] == false) {
		// ustawienie obrotow
		xrot = 30.f;
		yrot = a+270;
		// uzaleznienie pozycji kamery od rotacji i oddalenia kamery od obiektu
		ypos = (cRadius)*sinf(Deg2Rad(xrot)) + crab_y;
		
		//warunek zakonczenia fazy
		if(frames > fps*2)
			part[0] = true;
			anim_toggle = true;
	}
	else if(part[1] == false) {
		//jednostajnie przyspieszony ruch kamery
		if(a < (360 + start)/2)
		{
			if(addition <= 1.0f)
				addition += step;
		}
		else if(a > 4*(360 + start)/5)
		{
			if(addition > 0.05f)
				addition -= step;
			else
				addition = step;
		}
		a += addition;	
		yrot = a+270.f;

		if(a >= (360 + start)) 
		{
			part[1] = true;
			a = 0;
			step = 0.05;
			addition = 0.0;
		}
	}
	else if(part[2] == false)
	{
		if(ypos < 10.f )
		{
			if(addition <= 1.0f)
				addition += step;
		}
		else if(ypos > 30.f )
		{
			if(addition > 0.05f)
				addition -= step;
			else
				addition = step;
		}
				
		cRadius += 0.4;
		a += addition*2;
		xrot += addition;

		ypos = (cRadius)*sinf(Deg2Rad(xrot)) + crab_y + a;

		if( ypos >= 40.f )
		{
			part[2] = true;
			addition = 0.0f;
			a = yrot-270.0f;
			start = yrot - 270.0f;
		}
	}
	else if(part[3] == false)
	{
		//jednostajnie przyspieszony ruch kamery
		if(a < (90 + start)/2)
		{
			if(addition <= 1.0f)
				addition += step;
		}
		else if(a > (90 + start)/2)
		{
			if(addition > 0.05f)
				addition -= step;
			else
				addition = step;
		}
		a += addition;	
		yrot = a+270.f;

		if(a >= (90 + start)) 
		{
			part[3] = true;
			a = 0;
			step = 0.05;
			addition = 0.0;
		}
	}
	
	xpos = (cRadius)*cosf(Deg2Rad(yrot-270.f));
	zpos = (cRadius)*sinf(Deg2Rad(yrot-270.f)) + crab_z;
		

   	glRotatef(yrot,0.0,1.0,0.0);  
	glRotatef(xrot,cosf(Deg2Rad(yrot)),0.0,sinf(Deg2Rad(yrot)));  
	glTranslatef(-xpos,-ypos,-zpos); 
	

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

	//glTranslatef(0.f,-30.f,-24.f);
		
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

	plane.Draw(-300.f, -0.2f, -200.f);
	
	//cout << xpos << endl;
	/*glPushMatrix();
	glRotatef(-90.f,0.f,1.f,0.f);
	glTranslatef(0.f, 8.f, 0.f);
	leg->Draw();
	glPopMatrix();*/
	
	dilCrab.Draw(0.0f, crab_y, crab_z);

	//dilCrab.StaticDraw(0.0f, crab_y, crab_z);
	

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

