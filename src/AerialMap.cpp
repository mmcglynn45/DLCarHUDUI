/*
 * AerialMap.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: matt
 */

#include "AerialMap.h"
#include <iostream>
#include <algorithm>

AerialMap::AerialMap(char * path) {
	  loadImage(path);
}
AerialMap::AerialMap() {
	// TODO Auto-generated destructor stub
	  glGenTextures(1, &tex);
	  glBindTexture(GL_TEXTURE_2D, tex);
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
	  displayImage();

	  free(raster);

}

void AerialMap::displayImage(){

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

	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.NELat);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.NELon);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.NWLat);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.NWLon);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.SELat);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.SELon);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.SWLat);
	    std::getline(ss, token, ',');
	    std::getline(ss, token, ',');
	    sscanf(token.c_str(), "%lf", &newTile.SWLon);



	    std::cout<<newTile.path<<std::endl;


	    aerialTiles.push_back(newTile);

	}


}

void AerialMap::LoadMyLocation(){
	for(size_t i = 0; i<aerialTiles.size(); i++){
		AerialTile currentTile = aerialTiles[i];
		if (myLatitude>=currentTile.borderSouth && myLatitude <= currentTile.borderNorth) {
			if(myLongitude>=currentTile.borderWest&&myLongitude<=currentTile.borderEast){

				if (mappedTile.path != currentTile.path) {
					loadImage(currentTile.path.c_str());
				}

				mappedTile = currentTile;

				//West Longitude boundaries at given latitude
				double deltaWestLatitude = myLatitude - currentTile.SWLat;
				double slopeWestLatLon = (currentTile.NWLon - currentTile.SWLon) / (currentTile.NWLat - currentTile.SWLat);
				double interceptWestLatLon = currentTile.SWLon;
				double adjustedBorderWestLon = slopeWestLatLon*(deltaWestLatitude) + interceptWestLatLon;

				//For east
				double deltaEastLatitude = myLatitude - currentTile.SELat;
				double slopeEastLatLon = (currentTile.NELon - currentTile.SELon) / (currentTile.NELat - currentTile.SELat);
				double interceptEastLatLon = currentTile.SELon;
				double adjustedBorderEastLon = slopeEastLatLon*(deltaEastLatitude) + interceptEastLatLon;

				//For South
				double deltaSouthLongitude = myLongitude - currentTile.SWLon;
				double slopeSouthLonLat = (currentTile.SELat - currentTile.SWLat) / (currentTile.SELon - currentTile.SWLon);
				double interceptSouthLonLat = currentTile.SWLat;
				double adjustedBorderSouthLat = slopeSouthLonLat*(deltaSouthLongitude) + interceptSouthLonLat;

				//For North
				double deltaNorthLongitude = myLongitude - currentTile.NWLon;
				double slopeNorthLonLat = (currentTile.NELat - currentTile.NWLat) / (currentTile.NELon - currentTile.NWLon);
				double interceptNorthLonLat = currentTile.NWLat;
				double adjustedBorderNorthLat = slopeNorthLonLat*(deltaNorthLongitude) + interceptNorthLonLat;





				double longWidth = currentTile.borderEast - currentTile.borderWest;
				double adjustedLongWidth = adjustedBorderEastLon - adjustedBorderWestLon;
				double adjustedOffsetLong = myLongitude - adjustedBorderWestLon;

				double offsetLong = myLongitude - currentTile.borderWest;
				double correctionX = -0.0;

				offsetX = adjustedOffsetLong/adjustedLongWidth + correctionX;
				//offsetX = offsetLong/longWidth + correctionX;

				double adjustedLatWidth = adjustedBorderNorthLat - adjustedBorderSouthLat;
				double adjustedOffsetLat = myLatitude - adjustedBorderSouthLat;
				double latWidth = currentTile.borderNorth - currentTile.borderSouth;
				double offsetLat = myLatitude - currentTile.borderSouth;
				double correctionY = -0.0;

				offsetY = adjustedOffsetLat/adjustedLatWidth + correctionY;
				//offsetY = offsetLat/latWidth  + correctionY;


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


	  glColor4f(0.3f,1.0f,1.0f,0.6f);

	  glBegin (GL_QUADS);
	  double centerX = (borderXStart+borderXEnd)/2;
	  double centerY = (borderYStart+borderYEnd)/2;
	  glVertex2d(centerX-5,centerY+5);
	  glVertex2d(centerX+5,centerY+5);
	  glVertex2d(centerX+5,centerY-5);
	  glVertex2d(centerX-5,centerY-5);
	  glEnd();

	  glColor4f(0.3f,1.0f,1.0f,0.6f);
	  //glColor4f(0.0f, 0.0f, 0.0f, 1-(radiusCycle/60.0));
	  double delta = (1-(radiusCycle/140.0))*5;
	  double innerRadius = std::max(radiusCycle-delta,10.0);
	  drawArc(centerX,centerY,innerRadius,radiusCycle,5000,0,360);

	  radiusCycle+=0.2;

	  if(radiusCycle>90.0){
		  radiusCycle = 20.0;
	  }


	  glEnable( GL_TEXTURE_2D );
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	  float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

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

	  LoadMyLocation();


}

void AerialMap::drawArc(float offsetX, float offsetY, float innerRadius,float radius,float resolution,float startAngle, float maxAngle){
	for(float i = startAngle; i<maxAngle; i+=maxAngle/resolution){
		float angleRadians = (i*2*M_PI)/360;
		float coordX = offsetX + cosf(angleRadians)*innerRadius;
		float coordY = offsetY + sinf(angleRadians)*innerRadius;
		float coord2X = offsetX + cosf(angleRadians)*radius;
		float coord2Y = offsetY + sinf(angleRadians)*radius;

		if((radius-innerRadius)>1){
			glLineWidth(0.2);
			glBegin(GL_LINES);
			glVertex3f(coordX,coordY,0);
			glVertex3f(coord2X,coord2Y,0);
			glEnd();

		}else{
			glPointSize(1.5);
			glBegin(GL_POINTS);
			glVertex3f(coordX,coordY,0);
			glEnd();

		}


	}
}

