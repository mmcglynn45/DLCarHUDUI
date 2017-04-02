/*
 * MappingPage.h
 *
 *  Created on: Mar 17, 2017
 *      Author: matt
 */

#include "AerialMap.h"

#ifndef MAPPINGPAGE_H_
#define MAPPINGPAGE_H_

#include "LandingPage.h"

class MappingPage: public LandingPage {
public:
	MappingPage(DataController * DataConrollerPointer);
	virtual ~MappingPage();
	void draw(void);
	void drawMap();
	AerialMap map;
	void drawBorder();

};

#endif /* MAPPINGPAGE_H_ */
