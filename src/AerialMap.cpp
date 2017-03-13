/*
 * AerialMap.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: matt
 */

#include "AerialMap.h"
#include <iostream>

AerialMap::AerialMap(char * path) {
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






}

AerialMap::~AerialMap() {
	// TODO Auto-generated destructor stub
}

void AerialMap::draw(){
	  glTranslatef(x,y,0.0);
	  glPushMatrix();
	  glRasterPos4f(x,y,0.0,0.1);
	  glPixelZoom(0.05,0.05);
	  glDrawPixels(imgwidth, imgheight,GL_RGBA, GL_UNSIGNED_BYTE,
	    raster);
	  glPopMatrix();
	  glTranslatef(-x,-y,0.0);
	  std::cout<<"x"<<x<<"\n";
	  std::cout<<"y"<<y<<"\n";

	  x+=3.0;
	  y+=3.0;
}

