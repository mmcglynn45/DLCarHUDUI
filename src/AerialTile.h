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

};

#endif /* AERIALTILE_H_ */
