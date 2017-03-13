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

	AerialMap(char * path);
	virtual ~AerialMap();

	void draw();
};

#endif /* AERIALMAP_H_ */
