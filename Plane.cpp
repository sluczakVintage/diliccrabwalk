#include "Plane.hpp"

#include <iostream>
using namespace std;


Plane::Plane() : w_(2000.0f), d_(2000.0f)
{	
	CreateList();
	cout << "Plane has been created!" << endl;
	
}


void Plane::CreateList()
{
	glNewList(PLANE, GL_COMPILE);
			GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    		GLfloat mat_ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};
    		GLfloat mat_ambient_color[] = {0.8f, 0.2f, 0.8f, 1.0f};
    		GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    		GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    		GLfloat no_shininess = 0.0f;
    		GLfloat low_shininess = 5.0f;
    		GLfloat high_shininess = 100.0f;
	    	
	   
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
			glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

			glBindTexture(GL_TEXTURE_2D, 3);
			//dol
		for(int x=0; x<w_/4; x++) {
			for(int y=0; y<d_/4; y++) {
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(0.0f, 1.0f, 0.0f);
					glTexCoord2f(1.0f-0.1*(x%10), 1.0f-0.1*(y%10)); glVertex3f(w_-4.f*(x), 0.0f, d_-4.f*(y)); 
					glTexCoord2f(1.0f-0.1*((x%10)+1), 1.0f-0.1*(y%10)); glVertex3f(w_-4.f*(x), 0.0f, d_-4.f*(y+1));
					glTexCoord2f(1.0f-0.1*(x%10), 1.0f-0.1*((y%10)+1)); glVertex3f(w_-4.f*(x+1), 0.0f, d_-4.f*(y));
					glTexCoord2f(1.0f-0.1*((x%10)+1), 1.0f-0.1*((y%10)+1)); glVertex3f(w_-4.f*(x+1), 0.0f, d_-4.f*(y+1));
				glEnd();
			}
		}
		glEndList();
}

void Plane::Draw(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef( x, y, z );
		glCallList(PLANE);
	glPopMatrix();
}
