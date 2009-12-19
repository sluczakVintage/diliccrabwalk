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
					glVertex3f(w_/2,h_/2,d_/2);
					glVertex3f(w_/2,h_/2,-d_/2);
					glVertex3f(-w_/2,h_/2,d_/2);
					glVertex3f(-w_/2,h_/2,-d_/2);
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);				
					//front
					glVertex3f(-w_/2,h_/2,d_/2);
					glVertex3f(-w_/2,-h_/2,d_/2);
					glVertex3f(w_/2,h_/2,d_/2);
					glVertex3f(w_/2,-h_/2,d_/2);
				glEnd();
					//bottom
				glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(w_/2,-h_/2,d_/2);
					glVertex3f(-w_/2,-h_/2,d_/2);
					glVertex3f(w_/2,-h_/2,-d_/2);
					glVertex3f(-w_/2,-h_/2,-d_/2);	
				glEnd();
				glBegin(GL_TRIANGLE_STRIP);
					//rear
					glVertex3f(-w_/2,-h_/2,-d_/2);				
					glVertex3f(-w_/2,h_/2,-d_/2);
					glVertex3f(w_/2,-h_/2,-d_/2);
					glVertex3f(w_/2,h_/2,-d_/2);
				glEnd();	
				glBegin(GL_TRIANGLE_STRIP);
					//left
					glVertex3f(-w_/2,h_/2,-d_/2);				
					glVertex3f(-w_/2,-h_/2,-d_/2);
					glVertex3f(-w_/2,h_/2,d_/2);
					glVertex3f(-w_/2,-h_/2,d_/2);
				glEnd();	
				glBegin(GL_TRIANGLE_STRIP);
					//right
					glVertex3f(w_/2,h_/2,d_/2);				
					glVertex3f(w_/2,-h_/2,d_/2);
					glVertex3f(w_/2,h_/2,-d_/2);
					glVertex3f(w_/2,-h_/2,-d_/2);
				glEnd();	
		glEndList();

		cout << "List SH_COMP created" << endl;
}


void LegCompShort::Draw(GLfloat x, GLfloat y, GLfloat z)
{
	//  Show when are displaying an object
	cout << "Displaying object...\n" << endl;

//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
	glCallList(PROJECTION);
	//begin drawing short component
	//glPushMatrix();
//				glTranslatef( x, y, z );
				glCallList(SH_COMP);
//	glPopMatrix();
}
