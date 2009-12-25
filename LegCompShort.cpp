#include "LegCompShort.hpp"

#include <iostream>
using namespace std;

LegCompShort::LegCompShort() : w_(2.0f), h_(6.0f), d_(1.0f)
{	
	CreateList();
	cout << "LegCompShort!" << endl;
}

void LegCompShort::CreateList()
{
		GLfloat cube_diffuse[]   = { 0.0, 0.2, 0.7, 1.0 };
				glMaterialfv( GL_FRONT, GL_DIFFUSE, cube_diffuse );

		glNewList(SH_COMP, GL_COMPILE);
				glBegin(GL_TRIANGLE_STRIP);
					//upper
					glVertex3f(h_,d_,w_/2);
					glVertex3f(h_,d_,-w_/2);
					glVertex3f(0,d_,w_/2);
					glVertex3f(0,d_,-w_/2);
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);				
					//front
					glVertex3f(0,d_,w_/2);
					glVertex3f(0,0,w_/2);
					glVertex3f(h_,d_,w_/2);
					glVertex3f(h_,0,w_/2);
				glEnd();
					//bottom
				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(h_,0,w_/2);
					glVertex3f(0,0,w_/2);
					glVertex3f(h_,0,-w_/2);
					glVertex3f(-0,0,-w_/2);	
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);
					//rear
					glVertex3f(0,0,-w_/2);				
					glVertex3f(0,d_,-w_/2);
					glVertex3f(h_,0,-w_/2);
					glVertex3f(h_,d_,-w_/2);
				glEnd();	
				glBegin(GL_TRIANGLE_STRIP);
					//left
					glVertex3f(0,d_,-w_/2);				
					glVertex3f(0,0,-w_/2);
					glVertex3f(0,d_,w_/2);
					glVertex3f(0,0,w_/2);
				glEnd();	
				glBegin(GL_TRIANGLE_STRIP);
					//right
					glVertex3f(h_,d_,w_/2);				
					glVertex3f(h_,0,w_/2);
					glVertex3f(h_,d_,-w_/2);
					glVertex3f(h_,0,-w_/2);
				glEnd();	
		glEndList();

		cout << "List SH_COMP created" << endl;
}


void LegCompShort::Draw()//GLfloat x, GLfloat y, GLfloat z)
{
	//  Show when are displaying an object

int x=0,y=0,z =0;
//  glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

//	glPushMatrix();
//				glTranslatef( x, y, z );
//				glCallList(PROJECTION);
	//begin drawing short component
				//glTranslatef(h_/2,0.0f,0.0f);
				//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
				//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glCallList(SH_COMP);				
//	glPopMatrix();
}
