#include "Crab.hpp"

#include <iostream>
using namespace std;
//extern GLfloat nRange;

Crab::Crab() : w_(20.0f), h_(2.0f), d_(8.0f)
{	
	CreateList();
	cout << "Crab has been created!" << endl;
	//firstLeft; 
	//firstRight;
	//secondLeft;
	//secondRight;
	//thirdLeft;
	//thirdRight;
	//forthLeft;
	//forthRight;
	//fifthLeft;
	//fifthRight;
}

void Crab::CreateList()
{
		GLfloat cube_diffuse[]   = { 0.0, 0.7, 0.7, 1.0 };
				glMaterialfv( GL_FRONT, GL_DIFFUSE, cube_diffuse );

	glNewList(CRAB, GL_COMPILE);
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

		cout << "List CRAB created" << endl;
}

void Crab::drawLegs(GLfloat x, GLfloat y, GLfloat z)
{
	static GLfloat leg_interval = 4.0f;
		

}

void Crab::Draw(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat cube_diffuse[]   = { 0.0, 0.7, 0.7, 1.0 };
	//  Show when are displaying an object
	cout << "Displaying object...\n" << endl;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glCallList(PROJECTION);
	//begin drawing crab torso
	glPushMatrix();
				glTranslatef( x, y, z );
				glCallList(CRAB);
				glPushMatrix();
					drawLegs(x, y, z );
				glPopMatrix();
	glPopMatrix();
}
