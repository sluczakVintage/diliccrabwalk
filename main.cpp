/*
 * CrabWalk
 */


#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include "glut.h"
#include "CBMPLoader.h"

using namespace std;

static float g_fSpinX = 45.0f;
static float g_fSpinY = -15.0f;


	struct Vertex
	{
		float x, y, z;
	};

	struct Color
	{
		float r, g, b;
	};

	struct TexCoord
	{
		float tu, tv;
	};

	Vertex g_Vertices[] =
	{//Front_bottom
		{ -1.0f, 0.0f, 2.0f },
		{  1.0f, 0.0f, 2.0f },
		{  1.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f },
	//Front_top
		{ -1.0f,-1.0f, 1.0f },
		{  1.0f,-1.0f, 1.0f },
		{  1.0f, 0.0f, 2.0f },
		{ -1.0f, 0.0f, 2.0f },
	//Rear
		{ -1.0f,-1.0f,-3.0f },
		{ -1.0f, 1.0f,-3.0f },
		{  1.0f, 1.0f,-3.0f },
		{  1.0f,-1.0f,-3.0f },
	//Top
		{ -1.0f, 1.0f,-3.0f },
		{ -1.0f, 1.0f, 1.0f },
		{  1.0f, 1.0f, 1.0f },
		{  1.0f, 1.0f,-3.0f },
	//Bottom
		{ -1.0f,-1.0f,-3.0f },
		{  1.0f,-1.0f,-3.0f },
		{  1.0f,-1.0f, 1.0f },
		{ -1.0f,-1.0f, 1.0f },
	//Left
		{  1.0f,-1.0f,-3.0f },
		{  1.0f, 1.0f,-3.0f },
		{  1.0f, 1.0f, 1.0f },
		{  1.0f,-1.0f, 1.0f },
	//Right
		{ -1.0f,-1.0f,-3.0f },
		{ -1.0f,-1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f,-3.0f },
	//Front_left
		{ -1.0f, 1.0f, 1.0f },
		{ -1.0f,-1.0f, 1.0f },
		{ -1.0f, 0.0f, 2.0f },
	//Front_right
		{  1.0f, 1.0f, 1.0f },
		{  1.0f,-1.0f, 1.0f },
		{  1.0f, 0.0f, 2.0f }
	};

	Color g_Colors[] =
	{
		{ 1.0f, 0.0f, 0.0f },
	};


	TexCoord g_TexCoords[] =
	{//Front_bottom
		{ 0.5f, 0.25f },
		{ 1.0f, 0.25f },
		{ 1.0f, 0.5f },
		{ 0.5f, 0.5f },
	//Front_top
		{ 0.5f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 0.25f },
		{ 0.5f, 0.25f },
	//Rear
		{ 0.20f, 0.0f },
		{ 0.20f, 0.5f },
		{ 0.0f, 0.5f },
		{ 0.0f, 0.0f },
	//Top
		{ 0.5f, 1.0f },
		{ 0.5f, 0.5f },
		{ 1.0f, 0.5f },
		{ 1.0f, 1.0f },
	//Bottom
		{ 0.0f, 1.0f },
		{ 0.5f, 1.0f },
		{ 0.5f, 0.5f },
		{ 0.0f, 0.5f },
	//Left
		{ 0.20f, 0.0f },
		{ 0.20f, 0.5f },
		{ 0.25f, 0.5f },
		{ 0.25f, 0.0f },
	//Right
		{ 0.20f, 0.0f },
		{ 0.25f, 0.0f },
		{ 0.25f, 0.5f },
		{ 0.20f, 0.5f },
	//Front_left
		{ 0.25f, 0.5f },
		{ 0.25f, 0.0f },
		{ 0.5f, 0.25f },
	//Front_right
		{ 0.25f, 0.5f },
		{ 0.25f, 0.0f },
		{ 0.5f, 0.25f }

	};

void updateSpot()
{
    float direction[] = {0.f, 0.f, 3.f};
    float spotCutOff = 90.f;   
    //spot direction
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    //angle of the cone light emitted by the spot : value between 0 to 180
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutOff);
}


void spotInit()
{
	
	    float ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};       //low ambient light
        float diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
        float position[]  = {2.0f, 0.0f, 3.0f, 1.0f};

		      //properties of the light
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
       
                
        updateSpot();
       
        //exponent propertie defines the concentration of the light
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 30.0f);
       
        //light attenuation (default values used here : no attenuation with the distance)
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
}

void ambientInit()
{
				
		GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
		GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };
  
		glLightfv( GL_LIGHT0, GL_POSITION, light_position );
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );

}
	

void lightInit(int i)
{
	if( i == 1 )
		spotInit();
	else {
		ambientInit();
		cout << "Ambient" << endl;
	}
}

void init()
{
 
	GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };

	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );

	lightInit(0);

	glShadeModel( GL_PHONG_WIN );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_TEXTURE_2D );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );

}


void displayObjects()
{
	if( (g_fSpinX = (g_fSpinX - 0.2f) ) >= 360.f)
		g_fSpinX = 0;
//	if( (g_fSpinY = (g_fSpinY + 0.4f) ) >= 360.f)
//		g_fSpinY = 0;


	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glRotatef( -g_fSpinY, 1.0f, 0.0f, 0.0f );
	glRotatef( -g_fSpinX, 0.0f, 1.0f, 0.0f );

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	
			glVertexPointer( 3, GL_FLOAT, 0, g_Vertices );
			glTexCoordPointer( 2, GL_FLOAT, 0, g_TexCoords );
	
	glDrawArrays( GL_QUADS, 0, 28 );
	glDrawArrays( GL_TRIANGLES, 28, 6);

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		 
}

void display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    displayObjects();
    glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{   
	float ratio;

	if(h == 0)	h = 1;

	ratio = 1.0f * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective( 45.0f, ratio, 0.1f, 100.0f);
	glTranslatef(0.0f, 0.0f, -10.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0, 0, 30,
	//		  0,0,10,
	//		  0.0f,1.0f,0.0f);
			
}

int main(int argc, char** argv)
{
	CBMPLoader textureLoader;
   glutInit( &argc, argv );

   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

   glutInitWindowPosition( 0, 0 );
   glutInitWindowSize( 1200, 1000 );

   glutCreateWindow( "Fes Train" );

   glutDisplayFunc( display );
   glutReshapeFunc( reshape );
   glutIdleFunc( display );

   init();
   
   cout << textureLoader.LoadBMPFile("train.bmp") << endl;

   glutMainLoop();

   return 0;
}
