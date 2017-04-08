/*
 * AerialMap.h
 *
 *  Created on: Feb 4, 2017
 *      Author: matt
 */

#ifndef AERIALMAP_H_
#define AERIALMAP_H_

#include <tiffio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <vector>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "AerialTile.h"
#include "math.h"

class AerialMap {
public:
	float x = -1000.0;
	float y = -1080.0;

	TIFFRGBAImage img;
	uint32 *raster;
	size_t npixels;
	int imgwidth, imgheight;

	float offsetX = 0.5;
	float offsetY = 0.5;
	float distX = 0.281;
	float distY = 0.114;

	double borderXStart = 182.95;
	double borderYEnd = 1012.45;
	double borderYStart = 135.65;
	double borderXEnd = 1727.05;

	float myLatitude = 47.608608;
	float myLongitude = -122.150523;

	double speed = 0.0;
	double heading = 0.0;

	double radiusCycle = 20.0;

	AerialTile mappedTile;

	std::vector<AerialTile> aerialTiles;

	std::string tileLogPath;
	std::string basePath;

	GLuint tex;

	AerialMap(char * path);
	virtual ~AerialMap();
	AerialMap();
	void loadImage(const char * path);
	void loadTiles();
	void LoadMyLocation();
	void displayImage();
	void drawArc(float offsetX, float offsetY, float innerRadius,float radius,float resolution,float startAngle, float maxAngle);
	void drawMetadata();
	void loadTileLocation();

	void draw();
};

#endif /* AERIALMAP_H_ */
