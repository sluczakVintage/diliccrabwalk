#ifndef CAMLIGHTS_H
#define CAMLIGHTS_H

#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include "stdlib.h"

#include "glut.h"
#include "glutFunc.hpp"
#include "Drawable.hpp"
#include <math.h>

void initDirLight();
void initPosLight();
void initSpots();
void updateSpot();
void initSpot();
// tworzenie ukladu wspolzednych
void createProjection();
void camera();



#endif
