//
// This code was created by Jeff Molofee '99
// (ported to SDL by Sam Lantinga '2000)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe 
//
#include <math.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

#include "SDL.h"

#include "LegCompShort.hpp"
#include "Bone.hpp"
//#include "Crab.hpp"

//glOrtho range
GLfloat nRange = 10.0f;

int light = 0;           // lighting on/off
GLfloat xrot;            // x rotation
GLfloat yrot;            // y rotation
GLfloat xspeed;          // x rotation speed
GLfloat yspeed;          // y rotation speed

GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;

GLfloat lookupdown = 0.0;
const float piover180 = 0.0174532925f;


float xpos, zpos;

GLfloat z=0.0f;                       // depth into the screen.

GLfloat LightAmbient[]  = {0.5f, 0.5f, 0.5f, 1.0f}; 
GLfloat LightDiffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f}; 
GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};

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

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int w, int h)	        // We call this right after our OpenGL window is created.
{
	GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
	GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );

    glClearColor(255.f, 255.f, 255.f, 1.0f);
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer

	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );
	glDepthFunc(GL_LESS);                       // type of depth test to do.
	glEnable(GL_CULL_FACE);

    
	createProjection();
    
    
   
	////
	if( h > 0 && w > 0 ) {
      glViewport( 0, 0, w, h );
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
	  //gluPerspective(45.0f,static_cast<GLdouble>(w/h),0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
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

	////
    
    // set up lights.
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    glEnable(GL_LIGHT1);
}

//-------------------------------------------------------------------------
//  Draws our object.
//-------------------------------------------------------------------------


/* The main drawing function. */
void DrawGLScene()
{
    GLfloat xtrans, ztrans, ytrans;
    GLfloat sceneroty;

    // calculate translations and rotations.
    xtrans = -xpos;
    ztrans = -zpos;
    ytrans = -walkbias-0.25f;
    sceneroty = 360.0f - yrot;
    	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    glRotatef(lookupdown, 1.0f, 0, 0);
    glRotatef(sceneroty, 0, 1.0f, 0);

    glTranslatef(xtrans, ytrans, ztrans);    

	glMatrixMode(GL_MODELVIEW);
			//  Draw object
}

int main(int argc, char **argv) 
{  
    int done;
	int w, h;
	w = 640;
	h = 480;
    Uint8 *keys;

	LegCompShort* leg = new LegCompShort();
	Bone* bone = new Bone(NULL, 0.f, 0.f, 0.f, leg, "LegShort");

    /* Initialize SDL for video output */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Create a 640x480 OpenGL screen */
    if ( SDL_SetVideoMode(w, h, 0, SDL_OPENGL) == NULL ) {
        fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
        SDL_Quit();
        exit(2);
    }

    /* Set the title bar in environments that support it */
    SDL_WM_SetCaption("dilCrab", NULL);

    /* Loop, drawing and checking events */
    InitGL(w, h);
    done = 0;
    while ( ! done ) {
        DrawGLScene();
		bone->Draw();
		glFlush();
		// swap buffers to display, since we're double buffered.
		SDL_GL_SwapBuffers();

        /* This could go in a separate function */
        { SDL_Event event;
          while ( SDL_PollEvent(&event) ) {
              if ( event.type == SDL_QUIT ) {
                  done = 1;
              }
              if ( event.type == SDL_KEYDOWN ) {
                  switch(event.key.keysym.sym) {
                      case SDLK_ESCAPE:
                          done = 1;
                          break;
                      case SDLK_l:
	                  printf("Light was: %d\n", light);
	                  light = light ? 0 : 1;              // switch the current value of light, between 0 and 1.
	                  printf("Light is now: %d\n", light);
	                  if (!light) {
	                      glDisable(GL_LIGHTING);
	                  } else {
	                      glEnable(GL_LIGHTING);
	                  }
	                  break;
                  }
              }
          }
        }

        /* Check current key state for special commands */
        keys = SDL_GetKeyState(NULL);
        if ( keys[SDLK_PAGEUP] == SDL_PRESSED ) {
	    z -= 0.2f;
	    lookupdown -= 0.2f;
        }
        if ( keys[SDLK_PAGEDOWN] == SDL_PRESSED ) {
	    z += 0.2f;
	    lookupdown += 1.0f;
        }
        if ( keys[SDLK_UP] == SDL_PRESSED ) {
	    xpos -= (float)sin(yrot*piover180) * 0.05f;
	    zpos -= (float)cos(yrot*piover180) * 0.05f;	
	    if (walkbiasangle >= 359.0f)
	        walkbiasangle = 0.0f;	
	    else 
	        walkbiasangle+= 10;
	    walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
        }
        if ( keys[SDLK_DOWN] == SDL_PRESSED ) {
	    xpos += (float)sin(yrot*piover180) * 0.05f;
	    zpos += (float)cos(yrot*piover180) * 0.05f;	
	    if (walkbiasangle <= 1.0f)
	        walkbiasangle = 359.0f;	
	    else 
	        walkbiasangle-= 10;
	    walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
        }
        if ( keys[SDLK_LEFT] == SDL_PRESSED ) {
	    yrot += 1.5f;
        }
        if ( keys[SDLK_RIGHT] == SDL_PRESSED ) {
	    yrot -= 1.5f;
        }
    }
    SDL_Quit();
    return 1;
}

////*************************************************************************
////
////  File Name	: GLUT Window Template
////  Author		: Ali BaderEddin
////  Date		: December 2003
////  
////  Description	: Openning an OpenGL window using GLUT library...
////  
////*************************************************************************
//
////  Input\Output Stream
//#include <iostream>
////  Include GLUT, OpenGL, and GLU libraries
//#include "glut.h"
//
//#include "glutFunc.hpp"
//
//#include "LegCompShort.hpp"
//#include "Bone.hpp"
////#include "Crab.hpp"
////
//
//
//
//using namespace std;
//using namespace glut;
////  Initialization
//void init ();
//
////  Callback functions
//void display (void);
//void reshape (int w, int h);
//
////  Support Functions
//void centerOnScreen ();
//void drawObject();
//void createProjection();
////VARIABLES
////Rotation of observer
//float xRot = 0, yRot = 0;
//float xMov = 0, yMov = 0, zMov = 0;
//
////glOrtho range
//GLfloat nRange = 10.0f;
//
////  define the window position on screen
//int window_x;
//int window_y;
//
////  variables representing the window size
//int window_width = 1000;
//int window_height = 750;
//
////  variable representing the window title
//char *window_title = "GLUT Window Template";
//
////  Tells whether to display the window full screen or not
////  Press Alt + Esc to exit a full screen.
//int full_screen = 0;
//
//LegCompShort* leg = new LegCompShort();
//
////-------------------------------------------------------------------------
////  Set OpenGL program initial state.
////-------------------------------------------------------------------------
//void init ()
//{	
//	GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
//    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
//    GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
//    GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
//    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );
//    
//	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
//    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );
//    
//	glEnable( GL_DEPTH_TEST );
//	glShadeModel( GL_PHONG_WIN );
//	glEnable(GL_CULL_FACE);
//
//    glEnable( GL_LIGHTING );
//    glEnable( GL_LIGHT0 );
//
//    glDepthFunc( GL_LESS );
//
//	glClearColor(255.f, 255.f, 255.f, 1.0f);
//	createProjection();
//
//    
//}
//
//void createProjection()
//{
//	glNewList(PROJECTION, GL_COMPILE);
//		glBegin(GL_LINES);
//			//oX AXIS
//			glVertex3f(-nRange,0.0f,0.0f);
//			glVertex3f(nRange,0.0f,0.0f);
//
//			glVertex3f(nRange,0.0f,0.0f);
//			glVertex3f((nRange*0.95f),nRange*0.05f,0.0f);
//
//			glVertex3f(nRange,0.0f,0.0f);
//			glVertex3f((nRange*0.95f),-nRange*0.05f,0.0f);
//
//			//oZ AXIS
//			glVertex3f(0.f,0.0f,-nRange);
//			glVertex3f(0.f,0.0f,nRange);
//
//			glVertex3f(0.0f,0.0f,nRange);
//			glVertex3f(-nRange*0.05f,0.0f,(nRange*0.95f));
//			
//			glVertex3f(0.0f,0.0f,nRange);
//			glVertex3f(nRange*0.05f,0.0f,(nRange*0.95f));
//			
//			//oY AXIS
//			glVertex3f(0.f,nRange,0.0f);
//			glVertex3f(0.f,-nRange,0.0f);
//
//			glVertex3f(0.f,nRange,0.0f);
//			glVertex3f(nRange*0.05f,(nRange*0.95f),0.0f);
//
//			glVertex3f(0.f,nRange,0.0f);
//			glVertex3f(-nRange*0.05f,(nRange*0.95f),0.0f);
//		glEnd();
//	glEndList();
//}
////-------------------------------------------------------------------------
////  This function is passed to glutDisplayFunc in order to display 
////	OpenGL contents on the window.
////-------------------------------------------------------------------------
//void display (void)
//{
//
//	//  Clear the window or more specifically the frame buffer...
//	//  This happens by replacing all the contents of the frame
//	//  buffer by the clear color (black in our case)
//	glMatrixMode(GL_PROJECTION);
//		glPushMatrix();
//			glRotatef(xRot, 0.0f, 1.0f, 0.0f);
//			glRotatef(yRot, 1.0f, 0.0f, 0.0f);
//			xRot = yRot = 0.0f;
//			cout << xRot << endl;
//			cout << yRot << endl;
//		
//			glTranslatef(xMov, 0.0f, 0.0f);
//			glTranslatef(0.0f, yMov, 0.0f);
//			glTranslatef(0.0f, 0.0f, zMov);
//			xMov = yMov = zMov = 0.f;
//		
//		glMatrixMode(GL_MODELVIEW);
//			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//			//  Draw object
//			drawObject ();
//			glFlush();
//
//		//  Swap contents of backward and forward frame buffers
//		glutSwapBuffers ();
//		
//	glPopMatrix();
//
//}
//
////-------------------------------------------------------------------------
////  Draws our object.
////-------------------------------------------------------------------------
//void drawObject ()
//{
//	//static Crab* dilCrab = new Crab();
//	//dilCrab->Draw(0.0, 0.0, 0.0);
//	
//	//leg->Draw(0.0, 0.0, 0.0);
//	static Bone* bone = new Bone(NULL, 0.f, 0.f, 0.f, leg, "Crab");
//	bone->Draw();
//
//}
//
////-------------------------------------------------------------------------
////  This function is passed to the glutReshapeFunc and is called 
////  whenever the window is resized.
////-------------------------------------------------------------------------
//void reshape (int w, int h)
//{
//	  if( h > 0 && w > 0 ) {
//      glViewport( 0, 0, w, h );
//      glMatrixMode( GL_PROJECTION );
//      glLoadIdentity();
//      //gluPerspective(70,static_cast<GLdouble>(w/h), 1, 80);
//	   if( w <= h ) {
//         glOrtho( -nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f , nRange*2.0f);
//      }
//      else {
//         glOrtho( -nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
//      }
//      glMatrixMode( GL_MODELVIEW );
//	  glLoadIdentity();
//    }
//	//  Print current width and height on the screen
//	cout << "Window Width: " << w << ", Window Height: " << h << endl;
//}
//
////-------------------------------------------------------------------------
////  This function sets the window x and y coordinates
////  such that the window becomes centered
////-------------------------------------------------------------------------
//void centerOnScreen ()
//{
//	window_x = (glutGet (GLUT_SCREEN_WIDTH) - window_width)/2;
//	window_y = (glutGet (GLUT_SCREEN_HEIGHT) - window_height)/2;
//
//}
//
////-------------------------------------------------------------------------
////  Program Main method.
////-------------------------------------------------------------------------
//void main (int argc, char **argv)
//{
//	//  Set the window x and y coordinates such that the 
//	//  window becomes centered
//	centerOnScreen ();
//	//  Connect to the windowing system + create a window
//	//  with the specified dimensions and position
//	//  + set the display mode + specify the window title.
//	glutInit(&argc, argv);
//	glutInitWindowSize (window_width, window_height);
//	glutInitWindowPosition (window_x, window_y);
//	 glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
//	glutCreateWindow (window_title);
//
//	//  View in full screen if the full_screen flag is on
//	if (full_screen)
//		glutFullScreen ();
//
//	//  Set OpenGL program initial state.
//	init();
//	
//	// Set the callback functions
//	glutDisplayFunc (display);
//	glutReshapeFunc  (reshape);
//	glutMouseFunc (mouse);
//	glutMotionFunc (motion);
//	glutPassiveMotionFunc (pmotion);
//	glutKeyboardFunc (keyboard);
//	glutSpecialFunc (special);
//
//	//  Start GLUT event processing loop
//	glutMainLoop();
//}
//
