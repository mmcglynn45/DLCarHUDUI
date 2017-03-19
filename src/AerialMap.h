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

class AerialMap {
public:
	float x = -1000.0;
	float y = -1080.0;

	TIFFRGBAImage img;
	uint32 *raster;
	size_t npixels;
	int imgwidth, imgheight;

	float offsetX = 0.5;
	float offetY = 0.5;
	float distX = 0.281;
	float distY = 0.114;

	GLuint tex;

	AerialMap(char * path);
	virtual ~AerialMap();
	AerialMap();
	void loadImage(char * path);

	void draw();
};

#endif /* AERIALMAP_H_ */
