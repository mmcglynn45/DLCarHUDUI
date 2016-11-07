/*
 * Guage.h
 *
 *  Created on: Nov 6, 2016
 *      Author: matt
 */

#ifndef GUAGE_H_
#define GUAGE_H_
#include "math.h"
#include "GraphicsHeader.h"

class Guage {

private:


public:
	double x = 0;
	double y = 0;
	double z = 0;

	Guage();
	virtual ~Guage();
	void drawGuage();
	void drawGuageArc(float innerRadius,float radius,float resolution,float startAngle, float maxAngle, int endingCirles);


};

#endif /* GUAGE_H_ */
