/*
   Class Name:

      CBMPLoader.

   Created by:

      Allen Sherrod (Programming Ace of www.UltimateGameProgramming.com).

   Description:

      This class loads a .bmp texture into this object.
*/


#ifndef CTEXTURE_H
#define CTEXTURE_H

#include<windows.h>        // Windows header file.
#include<stdio.h>          // Standard input/output.
#include<gl/gl.h>          // OpenGl include.
#include<gl/glu.h>         // OpenGl utility include.

#define BITMAP_ID 0x4D42	// The universal bitmap ID


class CBMPLoader
{
   public:
      CBMPLoader();   // Constructor.
      ~CBMPLoader();  // Destructor.

      bool LoadBMPFile(char *filename);   // Load a .bmp image file.
      void FreeImage();                   // Delete a image.

      unsigned int ID;                    // ID used for generating the textures in OpenGl.
      int imageWidth;                     // Width of a texture.
      int imageHeight;                    // Height of a texture.

   protected:
      void GenerateTexture();             // Generate a texture in OpenGL.
      unsigned char* LoadBitmap(char *file, BITMAPINFOHEADER *bitmapInfoHeader);// Load a bitmap image.

      unsigned char *image;               // Texture image.
      bool textureExist;                  // This will be used if the image was loaded.
      int type;                           // Image format.
};

#endif


// Copyright September 2003
// All Rights Reserved!
// Allen Sherrod
// ProgrammingAce@UltimateGameProgramming.com
// www.UltimateGameProgramming.com


