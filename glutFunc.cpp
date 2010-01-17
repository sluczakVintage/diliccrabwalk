
#include "glutFunc.hpp"


using namespace std;

bool anim_toggle = false;

extern int fps;
int frames = 0;

extern float xpos , ypos, zpos , xrot, yrot;
float lastx, lasty;


Vector3f substractV3f(Vector3f v1, Vector3f v2)
{
	float x = v1.x_ - v2.x_;
	float y = v1.y_ - v2.y_;
	float z = v1.z_ - v2.z_;
	
	return Vector3f(x,y,z);
}

Vector3f crossProduct(Vector3f v1, Vector3f v2) 
{
   float x = (v1.y_ * v2.z_) - (v2.y_ * v1.z_);
   float y = (v1.z_ * v2.x_) - (v2.z_ * v1.x_);
   float z = (v1.x_ * v2.y_) - (v2.x_ * v1.y_);
   
   return Vector3f(x,y,z);
}

Vector3f normalize(Vector3f v) 
{
	float r = sqrtf(v.x_*v.x_ + v.y_*v.y_ + v.z_*v.z_);

	float x = v.x_/r;
	float y = v.y_/r;
	float z = v.z_/r;

	return Vector3f(x,y,z);
}


GLfloat Rad2Deg (GLfloat Angle) {
	static GLfloat ratio = 180.0f / 3.141592653589793238f;
	return Angle * ratio;
}

GLfloat Deg2Rad (GLfloat Rad) {
	static GLfloat ratio = 180.0f / 3.141592653589793238f;
	return Rad / ratio;
}

namespace glut
{

// timer ograniczajacy predkosc animacji
void myTimer(int value)
{
	frames++;
	glutPostRedisplay();
	glutTimerFunc(1000/fps, myTimer, 1);

}

void mouse (int button, int state, int x, int y) {};
void pmotion (int x, int y) {};

//  Metoda obslugi ruchu myszy przy kliknieciu i przytrzymaniu
void motion (int x, int y)
{
	int diffx=x-lastx; 
	int diffy=y-lasty; 
	lastx=x; 
	lasty=y; 
	xrot += (float) diffy; 
	yrot += (float) diffx;	

	cout << "xrot " << xrot << endl;
	cout << "yrot " << yrot << endl;
	
}

//Obsluga zdarzen klawiatury
void keyboard (unsigned char key, int x, int y)
{
		
	switch (key)
	{
		case 'q':
			exit(0);
			break;
		case 'w':
			xpos += sinf(Deg2Rad(yrot)) ;
			zpos -= cosf(Deg2Rad(yrot)) ;
			ypos -= sinf(Deg2Rad(xrot)) ;
			break;

		case 's':
			xpos -= sinf(Deg2Rad(yrot)) ;
			zpos += cosf(Deg2Rad(yrot)) ;
			ypos += sinf(Deg2Rad(xrot)) ;
			break;
		case 'a':
			xpos -= cosf(Deg2Rad(yrot)) * 0.2;
			zpos -= sinf(Deg2Rad(yrot)) * 0.2;
			break;

		case 'd':
			xpos += cosf(Deg2Rad(yrot)) * 0.2;
			zpos += sinf(Deg2Rad(yrot)) * 0.2;
		//SPACJA
		case ' ':
			anim_toggle = true;  
			break;
		//ESC
		case 27:
			exit(0);
			break;
	}
}


//Klawisze specjalne
void special (int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_F10 :
			fps = 1;
			cout << "F10 function key."<< endl;  
			break;
		case GLUT_KEY_F11 :
			fps++;
			cout << "F11 function key."<< endl; 
			break;
		case GLUT_KEY_F12 :
			fps--;
			if(fps < 1)
				fps = 1;
			cout << "F12 function key."<< endl;  
			break;
		case GLUT_KEY_LEFT :
			break;
		case GLUT_KEY_UP :
			xrot += 1;
			if (xrot >360) xrot -= 360;
			break;
		case GLUT_KEY_RIGHT :
			break;
		case GLUT_KEY_DOWN :
			xrot -= 1;
			if (xrot < -360) xrot += 360;
			break;

	}
}


}
