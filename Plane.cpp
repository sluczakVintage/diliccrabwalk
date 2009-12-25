#include "Plane.hpp"

#include <iostream>
using namespace std;


Plane::Plane() : w_(45.0f), d_(45.0f)
{	
	cout << "Plane has been created!" << endl;
	
}

void Plane::Draw(GLfloat x, GLfloat y, GLfloat z)
{
		glPushMatrix();
			glTranslatef( x, y, z );
			glBegin(GL_TRIANGLE_STRIP);
				glVertex3f(w_/2, 0.f, d_/2);
				glVertex3f(w_/2, 0.f,-d_/2);
				glVertex3f(-w_/2, 0.f, d_/2);
				glVertex3f(-w_/2, 0.f,-d_/2);
			glEnd();
		glPopMatrix();
}
