#include "Plane.hpp"

#include <iostream>
using namespace std;


Plane::Plane() : w_(120.0f), d_(120.0f)
{	
	cout << "Plane has been created!" << endl;
	
}

void Plane::Draw(GLfloat x, GLfloat y, GLfloat z)
{
		GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    	GLfloat mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    	GLfloat mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    	GLfloat mat_diffuse[] = {0.4f, 0.4f, 0.4f, 1.0f};
    	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    	GLfloat no_shininess = 0.0f;
    	GLfloat low_shininess = 5.0f;
    	GLfloat high_shininess = 100.0f;
    	
   
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	//@todo zrobic z tego liste
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 3);
			glTranslatef( x, y, z );
			glBegin(GL_TRIANGLE_STRIP);
				glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(w_/2, 0.f, d_/2);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(w_/2, 0.f,-d_/2);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-w_/2, 0.f, d_/2);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-w_/2, 0.f,-d_/2);
			glEnd();
		glPopMatrix();
}
