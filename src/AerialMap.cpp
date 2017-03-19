/*
 * AerialMap.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: matt
 */

#include "AerialMap.h"
#include <iostream>

AerialMap::AerialMap(char * path) {
	  loadImage(path);
}
AerialMap::AerialMap() {
	// TODO Auto-generated destructor stub
}

AerialMap::~AerialMap() {
	// TODO Auto-generated destructor stub
}

void AerialMap::loadImage(char * path){
	  TIFF *tif;
	  char emsg[1024];
	  int i;

	  tif = TIFFOpen(path, "r");
	  if (tif == NULL) {
	    fprintf(stderr, "Problem showing %s\n", path);
	    exit(1);
	  }
	  if (TIFFRGBAImageBegin(&img, tif, 0, emsg)) {
	    npixels = img.width * img.height;
	    raster = (uint32 *) _TIFFmalloc(npixels * sizeof(uint32));
	    if (raster != NULL) {
	      if (TIFFRGBAImageGet(&img, raster, img.width, img.height) == 0) {
	        TIFFError(path, emsg);
	        exit(1);
	      }
	    }
	    TIFFRGBAImageEnd(&img);
	  } else {
	    TIFFError(path, emsg);
	    exit(1);
	  }
	  imgheight = img.height;
	  imgwidth = img.width;

	  glGenTextures(1, &tex);
	  glBindTexture(GL_TEXTURE_2D, tex);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	  // Black/white checkerboard
	  float pixels[] = {
	      0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
	      1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	  };

	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgwidth, imgheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster);



}

void AerialMap::draw(){


		//Border X = 182.95
		//Border y = 1012.45
		//Border yStart = 135.65
		//Border xEnd = 1727.05

	    //Distance X = 1544
	    //Distance Y = 876.8

	    //0.281
	    //0.114

	  offsetX += .001;

	glEnable( GL_TEXTURE_2D );
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgwidth, imgheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster);


	  glColor4f(1.0f,1.0f,1.0f,1.0f);



	  glBegin (GL_QUADS);
	  glTexCoord2d(offsetX,offetY); glVertex2d(182.95,135.65);
	  glTexCoord2d(offsetX+distX,offetY); glVertex2d(1727.05,135.65);
	  glTexCoord2d(offsetX+distX,offetY+distY); glVertex2d(1727.05,1012.45);
	  glTexCoord2d(offsetX,offetY+distY); glVertex2d(182.95,1012.45);
	  glEnd();

	  glDisable( GL_TEXTURE_2D );



	  //glTranslatef(x,y,0.0);
	  //glPushMatrix();
	  //glRasterPos4f(x,y,0.0,0.1);
	  //glPixelZoom(0.05,0.05);
	 // glDrawPixels(imgwidth, imgheight,GL_RGBA, GL_UNSIGNED_BYTE,
	  //  raster);
	  //glPopMatrix();
	  //glTranslatef(-x,-y,0.0);
	  //std::cout<<"x"<<x<<"\n";
	  //std::cout<<"y"<<y<<"\n";

	  //x+=3.0;
	  //y+=3.0;
}

