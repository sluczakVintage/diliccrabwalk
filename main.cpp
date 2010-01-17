
#include <vld.h>

#include <iostream>
#include <math.h>
#include <time.h>

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
extern float global_offset;


//  rozmiar okna
int window_width = 1000;
int window_height = 800;

//  Etykieta okna
char *window_title = "DIL Crab Walk";

//  Czy pelen ekran?
int full_screen = 0;

//FPS
int fps = 1000;

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
    GLfloat ambientDiffuse[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat redDiffuse[] = {0.6f, 0.2f, 0.2f, 1.0f};
    GLfloat position[] = { 0.f, 100.0, 100.0f, 1.0 };
   
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientDiffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, redDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, position);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0002f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.000004f);

	glEnable( GL_LIGHT1 );
}


/**
* GL_LIGHT3-5
spoty
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
    GLfloat diffuse[]   = {0.6f, 0.6f, 0.55f, 1.0f};

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
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 70);
}
/**
* GL_LIGHT2
spot
*/

void initSpot()
{
  
    GLfloat noAmbient[] = {0.1f, 0.1f, 0.1f, 1.0f};       
    GLfloat diffuse[]   = {0.9f, 0.9f, 0.8f, 1.0f};
   

    glLightfv(GL_LIGHT2, GL_AMBIENT, noAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);

    updateSpot();
   
   
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.000002f);
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
	initSpot2();
    //initDirLight();

	glEnable( GL_LIGHTING );
	    
	createProjection();

	srand(time(NULL));
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
	static int rate = 60;
	static float a = start;
	static float addition = 0;
	static float step = 0.005f;

	static bool part[10] = {false, false, false, false, false, false, false, false};

	if(part[0] == false) {
		// ustawienie obrotow
		xrot = 30.f;
		yrot = a+270;
		// uzaleznienie pozycji kamery od rotacji i oddalenia kamery od obiektu
		ypos = (cRadius)*sinf(Deg2Rad(xrot)) + crab_y;
		
		//warunek zakonczenia fazy
		if(frames > rate*2) 
		{
			part[0] = true;
			//zacznij isc
			anim_toggle = true;
		}
	}
	else if(part[1] == false) {
		//jednostajnie przyspieszony ruch kamery - obrót o 360 st wokó³ kraba
		//przyspieszanie
		if(a < (360 + start)/2)
		{
			if(addition <= 1.0f)
				addition += step;
		}
		//zwalnianie
		else if(a > 4*(360 + start)/5)
		{
			if(addition > 0.05f)
				addition -= step;
			else
				addition = step;
		}
		a += addition;	
		yrot = a+270.f;
		//jezeli wykonano caly obrot
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
		// z wolna zacznij oddalac kamere
		if(ypos < 10.f )
		{
			if(addition <= 1.0f)
				addition += step;
		}
		// a potem zacznij hamowac
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
		// zakoncz na okreslonej wysokosci
		if( ypos >= 40.f )
		{
			part[2] = true;
			step = 0.05;
			addition = 0.0f;
			a = yrot-270.0f;
			start = yrot - 270.0f;
		}
	}
	else if(part[3] == false)
	{
		//jednostajnie przyspieszony ruch kamery
		// wolno obiegaj kraba od tylu (widok na kraba od boku)
		if(a < (60 + start)/2)
		{
			if(addition <= 1.0f)
				addition += step*2;
		}
		//potem hamowanie
		else if(a > (60 + start)/2)
		{
			if(addition > 0.05f)
				addition -= step*2;
			else
				addition = step;
		}
		a += addition;	
		yrot = a+270.f;
		//zakoncz obrot w odpowiednim momencie
		if(a >= (60 + start)) 
		{
			part[3] = true;
			a = 0;
			step = 0.005;
			addition = 0.0;
		}
	}
	else if(crab_z >=100.f && part[4] == false)
	{	// scena zwalniania ze strachu wyzwalana
		static int curr_frame = frames;
		static bool done = false;
		static int odd = 10;

 		if(odd%10 == 0)
			global_offset -=step*10;
		odd++;
		if(frames > curr_frame + rate*2) 
		{
			if(odd%6 == 0)
			global_offset +=step*100;
			initPosLight();
			//anim_toggle = true;
			//zacznij uciekac
		}
		if(frames > curr_frame + rate*2.5)
			part[4] = true;

	}
	else if(crab_z >= 150.f && part[5] == false)
		{
			
		if(ypos < 100.f )
		{
			if(addition <= 1.0f)
				addition += step;
		}
		else if(ypos > 300.f )
		{
			if(addition > 0.05f)
				addition -= step;
			else
				addition = step;
		}
				
		cRadius += 0.4;
		//a += addition*2;

		if(xrot <= 70.f)
			xrot += addition;
		if(yrot >= 790.f)
			yrot -=addition;
		ypos = (cRadius)*sinf(Deg2Rad(xrot)) + crab_y;

		if( ypos >= 400.f )
		{
			part[5] = true;
			//addition = 0.0f;
			//a = yrot-270.0f;
			//start = yrot - 270.0f;
		}
	}
	else if(crab_z >= 200.f && part[6] == false)
	{
		anim_toggle = true;
		part[6] = true;
	}
	
	if(part[4] == false)
	{
		xpos = (cRadius)*cosf(Deg2Rad(yrot-270.f));
		zpos = (cRadius)*sinf(Deg2Rad(yrot-270.f)) + crab_z;
	}	

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
	
	glCallList(PROJECTION);

	plane.Draw();
	
	dilCrab.Draw(0.0f, crab_y, crab_z);

	for(int i = 0; i <= 2; i++)
	{
		dilCrab2.StaticDraw(35+((i%2)*24), 0.f, 120+27*i, 14+27*i);

		dilCrab2.StaticDraw(-60+(i)*4, 0.f, 120*+(i)*25, 25+18*i);

		dilCrab2.StaticDraw(-40, 0.f, 150+70*i, 25+41*i);

		//dilCrab2.StaticDraw(-26+((i%2)*25), 0.f, 112+25*i, 90-7*i);

	//	dilCrab2.StaticDraw(76, 0.f, 40+27*i, 30+15*i);
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

