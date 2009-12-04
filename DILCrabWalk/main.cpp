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

static float g_fSpinX = 0.0f;
static float g_fSpinY = 0.0f;


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

	Vertex g_cubeVertices[] =
	{
		{ -1.0f, 0.0f, 2.0f },
		{  1.0f, 0.0f, 2.0f },
		{  1.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f },

		{ -1.0f,-1.0f, 1.0f },
		{  1.0f,-1.0f, 1.0f },
		{  1.0f, 0.0f, 2.0f },
		{ -1.0f, 0.0f, 2.0f },

		{ -1.0f,-1.0f,-3.0f },
		{ -1.0f, 1.0f,-3.0f },
		{  1.0f, 1.0f,-3.0f },
		{  1.0f,-1.0f,-3.0f },

		{ -1.0f, 1.0f,-3.0f },
		{ -1.0f, 1.0f, 1.0f },
		{  1.0f, 1.0f, 1.0f },
		{  1.0f, 1.0f,-3.0f },
	
		{ -1.0f,-1.0f,-3.0f },
		{  1.0f,-1.0f,-3.0f },
		{  1.0f,-1.0f, 1.0f },
		{ -1.0f,-1.0f, 1.0f },

		{  1.0f,-1.0f,-3.0f },
		{  1.0f, 1.0f,-3.0f },
		{  1.0f, 1.0f, 1.0f },
		{  1.0f,-1.0f, 1.0f },

		{ -1.0f,-1.0f,-3.0f },
		{ -1.0f,-1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f,-3.0f },

		{ -1.0f, 1.0f, 1.0f },
		{ -1.0f,-1.0f, 1.0f },
		{ -1.0f, 0.0f, 2.0f },

		{  1.0f, 1.0f, 1.0f },
		{  1.0f,-1.0f, 1.0f },
		{  1.0f, 0.0f, 2.0f }
	};

	Color g_cubeColors[] =
	{
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },

		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f }
	};


	TexCoord g_cubeTexCoords[] =
	{
		{ 0.0f, 0.5f },
		{ 1.0f, 0.5f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },

		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 0.5f },
		{ 0.0f, 0.5f },

		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },

		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },

		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },

		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },

		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },

		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },

		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f }
	};


void init()
{
 /*   GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
    GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };

	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );
   
	glShadeModel( GL_PHONG_WIN );
 */
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_TEXTURE_2D );

    //glEnable( GL_LIGHTING );
    //glEnable( GL_LIGHT0 );

    //glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );

}


void displayObjects()
{
	if( (g_fSpinY = (g_fSpinY + 0.2f) ) >= 360.f)
		g_fSpinY = 0;
	if( (g_fSpinX = (g_fSpinX + 0.4f) ) >= 360.f)
		g_fSpinX = 0;


	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( 0.0f, 0.0f, -5.0f );
	glRotatef( -g_fSpinY, 1.0f, 0.0f, 0.0f );
	glRotatef( -g_fSpinX, 0.0f, 1.0f, 0.0f );

	glEnableClientState( GL_VERTEX_ARRAY );
	//glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	
			glVertexPointer( 3, GL_FLOAT, 0, g_cubeVertices );
		//	glColorPointer( 3, GL_FLOAT, 0, g_cubeColors );
			glTexCoordPointer( 2, GL_FLOAT, 0, g_cubeTexCoords );
	
	glDrawArrays( GL_QUADS, 0, 28 );
	glDrawArrays( GL_TRIANGLES, 28, 6);

	glDisableClientState( GL_VERTEX_ARRAY );
//	glDisableClientState( GL_COLOR_ARRAY );
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

   glutCreateWindow( "GPOB: OpenGL" );

   glutDisplayFunc( display );
   glutReshapeFunc( reshape );
   glutIdleFunc( display );

   init();
   
   cout << textureLoader.LoadBMPFile("test.bmp") << endl;

   glutMainLoop();

   return 0;
}
