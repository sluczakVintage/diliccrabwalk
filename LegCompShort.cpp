#include "LegCompShort.hpp"

#include <iostream>
using namespace std;

LegCompShort::LegCompShort() : w_(2.0f), h_(4.0f), d_(1.0f)
{	
	CreateList();
	cout << "LegCompShort!" << endl;
}

void LegCompShort::CreateList()
{		
	glNewList(SH_COMP, GL_COMPILE);
		GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    	GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    	GLfloat mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    	GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    	GLfloat no_shininess = 0.0f;
    	GLfloat low_shininess = 5.0f;
    	GLfloat high_shininess = 100.0f;
    	
   
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glBindTexture(GL_TEXTURE_2D, 2);
						//gorna scianka
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(0.0f, 1.0f, 0.0f);
					glTexCoord2f(0.2f, 1.0f); glVertex3f(h_,d_,w_/2);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(h_,d_,-w_/2);
					glTexCoord2f(0.2f, 0.0f); glVertex3f(0,d_,w_/2);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0,d_,-w_/2);
				glEnd();
				//przednia scianka
				glBegin(GL_TRIANGLE_STRIP);				
					glNormal3f(0.0f, 0.0f, 1.0f);
					glTexCoord2f(0.4f, 1.0f); glVertex3f(0,d_,w_/2);
					glTexCoord2f(0.2f, 1.0f); glVertex3f(0,0,w_/2);
					glTexCoord2f(0.4f, 0.0f); glVertex3f(h_,d_,w_/2);
					glTexCoord2f(0.2f, 0.0f); glVertex3f(h_,0,w_/2);
				glEnd();
					//dolna scianka na ktorej lezy
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(0.0f, -1.0f, 0.0f);
					glTexCoord2f(0.6f, 1.0f); glVertex3f(h_,0,w_/2);
					glTexCoord2f(0.4f, 1.0f); glVertex3f(0,0,w_/2);
					glTexCoord2f(0.6f, 0.0f); glVertex3f(h_,0,-w_/2);
					glTexCoord2f(0.4f, 0.0f); glVertex3f(-0,0,-w_/2);	
				glEnd();
				//tylna scianka
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(0.0f, 0.0f, -1.0f);
					glTexCoord2f(0.8f, 1.0f); glVertex3f(0,0,-w_/2);				
					glTexCoord2f(0.6f, 1.0f); glVertex3f(0,d_,-w_/2);
					glTexCoord2f(0.8f, 0.0f); glVertex3f(h_,0,-w_/2);
					glTexCoord2f(0.6f, 0.0f); glVertex3f(h_,d_,-w_/2);
				glEnd();	
				//lewe (podstawa prostopadloscianu
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(1.0f, 0.0f, 0.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(0,d_,-w_/2);				
					glTexCoord2f(0.8f, 1.0f); glVertex3f(0,0,-w_/2);
					glTexCoord2f(1.0f, 0.5f); glVertex3f(0,d_,w_/2);
					glTexCoord2f(0.8f, 0.5f); glVertex3f(0,0,w_/2);
				glEnd();	
				//prawe (podstawa prostopadloscianu)
				glBegin(GL_TRIANGLE_STRIP);
					glNormal3f(-1.0f, 0.0f, 0.0f);
					glTexCoord2f(1.0f, 0.5f); glVertex3f(h_,d_,w_/2);				
					glTexCoord2f(0.0f, 0.5f); glVertex3f(h_,0,w_/2);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(h_,d_,-w_/2);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(h_,0,-w_/2);
				glEnd();			
		glEndList();

		cout << "List SH_COMP created" << endl;
}


void LegCompShort::Draw()
{
				glCallList(SH_COMP);				
}
