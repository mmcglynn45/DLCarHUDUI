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
	loadTiles();
	  LoadMyLocation();

}

AerialMap::~AerialMap() {
	// TODO Auto-generated destructor stub
}

void AerialMap::loadImage(const char * path){
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

	  float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	  // Black/white checkerboard
	  float pixels[] = {
	      0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
	      1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	  };

	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgwidth, imgheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster);



}

void AerialMap::loadTiles(){
	std::ifstream tileLog(tileLogPath);

	std::string tileLine;
	while (std::getline(tileLog, tileLine))
	{

	    AerialTile newTile;

	    std::string input = tileLine;
	    std::istringstream ss(input);
	    std::string token;

	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.borderWest);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.borderEast);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.borderNorth);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.borderSouth );
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');

	    std::string pathEnd(token.c_str()+2);
	    std::string pathStart(basePath);
	    std::string overallPath;

	    overallPath = pathStart + pathEnd;
	    newTile.path = overallPath;

	    std::cout<<newTile.path<<std::endl;

	    aerialTiles.push_back(newTile);

	}


}

void AerialMap::LoadMyLocation(){
	for(size_t i = 0; i<aerialTiles.size(); i++){
		AerialTile currentTile = aerialTiles[i];
		if (myLatitude>=currentTile.borderSouth && myLatitude <= currentTile.borderNorth) {
			if(myLongitude>=currentTile.borderWest&&myLongitude<=currentTile.borderEast){
				std::cout << "Found" << currentTile.path;

				if (mappedTile.path != currentTile.path) {
					loadImage(currentTile.path.c_str());
				}

				mappedTile = currentTile;

				double longWidth = currentTile.borderEast - currentTile.borderWest;
				double offsetLong = myLongitude - currentTile.borderWest;
				double correctionX = -0.0;
				offsetX = offsetLong/longWidth + correctionX;

				double latWidth = currentTile.borderNorth - currentTile.borderSouth;
				double offsetLat = myLatitude - currentTile.borderSouth;
				double correctionY = -0.0;
				offsetY = offsetLat/latWidth  + correctionY;

				break;
			}
		}
	}



}



void AerialMap::draw(){


		double borderXStart = 182.95;
		double borderYEnd = 1012.45;
		double borderYStart = 135.65;
		double borderXEnd = 1727.05;

	    //Distance X = 1544
	    //Distance Y = 876.8

	    //0.281
	    //0.114

	  //offsetX += .001;


		  glColor4f(0.3f,1.0f,1.0f,0.6f);

		  glBegin (GL_QUADS);
		  double centerX = (borderXStart+borderXEnd)/2;
		  double centerY = (borderYStart+borderYEnd)/2;
		  glVertex2d(centerX-5,centerY+5);
		  glVertex2d(centerX+5,centerY+5);
		  glVertex2d(centerX+5,centerY-5);
		  glVertex2d(centerX-5,centerY-5);
		  glEnd();


	glEnable( GL_TEXTURE_2D );
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	  float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgwidth, imgheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster);


	  glColor4f(1.0f,1.0f,1.0f,1.0f);


	  glPushMatrix();
	  glBegin (GL_QUADS);
	  glTexCoord2d(offsetX-distX/2,offsetY-distY/2); glVertex2d(borderXStart,borderYEnd);
	  glTexCoord2d(offsetX+distX/2,offsetY-distY/2); glVertex2d(borderXEnd,borderYEnd);
	  glTexCoord2d(offsetX+distX/2,offsetY+distY/2); glVertex2d(borderXEnd,borderYStart);
	  glTexCoord2d(offsetX-distX/2,offsetY+distY/2); glVertex2d(borderXStart,borderYStart);
	  glEnd();
	  glPopMatrix();

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

