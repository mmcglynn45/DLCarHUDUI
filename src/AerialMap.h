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

	float myLatitude = 47.9375;
	float myLongitude = -121.6875;

	AerialTile mappedTile;

	std::vector<AerialTile> aerialTiles;

	char * tileLogPath = "/media/matt/MapsFast/MapsStore/tileLog.csv";
	char * basePath = "/media/matt/MapsFast/MapsStore/";

	GLuint tex;

	AerialMap(char * path);
	virtual ~AerialMap();
	AerialMap();
	void loadImage(const char * path);
	void loadTiles();
	void LoadMyLocation();

	void draw();
};

#endif /* AERIALMAP_H_ */
