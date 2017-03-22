/*
 * AerialTile.h
 *
 *  Created on: Mar 18, 2017
 *      Author: matt
 */

#ifndef AERIALTILE_H_
#define AERIALTILE_H_

#include "GraphicsHeader.h"
#include <string>

class AerialTile {
public:
	AerialTile();
	virtual ~AerialTile();

	double borderWest = 0;
	double borderEast = 0;
	double borderSouth = 0;
	double borderNorth = 0;

	std::string path;

	double NELat = 0;
	double NELon = 0;
	double NWLat = 0;
	double NWLon = 0;
	double SELat = 0;
	double SELon = 0;
	double SWLat = 0;
	double SWLon = 0;

};

#endif /* AERIALTILE_H_ */
