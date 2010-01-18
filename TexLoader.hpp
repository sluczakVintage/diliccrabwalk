#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <windows.h>													// Header File For Windows
#include <gl\gl.h>														// Header File For The OpenGL32 Library
#include <gl\glu.h>														// Header File For The GLu32 Library
#include <olectl.h>														// Header File For The OLE Controls Library	(Used In BuildTexture)
#include <math.h>														// Header File For The Math Library			(Used In BuildTexture)


// ladowanie tekstur z NEHE.gamedev zmodyfikowane do tworzenia mipmap i ograniczone w funkcjonalnosci
int BuildTexture(char *szPathName, GLuint &texid, bool mip = true);
bool loadTex();


#endif
