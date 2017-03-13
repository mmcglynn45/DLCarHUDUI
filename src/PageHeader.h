/*
 * PageHeader.h
 *
 *  Created on: Feb 11, 2017
 *      Author: matt
 */

#ifndef PAGEHEADER_H_
#define PAGEHEADER_H_
#include "math.h"
#include "GraphicsHeader.h"

class PageHeader {
public:
	double x =70;
	double y = 500;
	double z = 0;
	char * label = "status";
	char * subLabel = "BMW X5";

	PageHeader();
	virtual ~PageHeader();

	void draw();
};

#endif /* PAGEHEADER_H_ */
