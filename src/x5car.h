/*
 * x5car.h
 *
 *  Created on: Nov 11, 2016
 *      Author: matt
 */

#ifndef X5CAR_H_
#define X5CAR_H_

#include "OBJParser.h"

class x5car {

private:


public:
	float x;
	float y;
	float z;
	float scale;
	float orientationRingRadius;
	float revolvingOffset;
	float revolvingOffsetDelta;
	float sinOffset;
	float userOffset;
	float measuredPitch;
	float measuredRoll;
	float measuredYaw;


	OBJParser carModel;
	x5car(float baseX,float baseY, float baseZ);
	virtual ~x5car();
	void draw();
	void drawOrientationRings();
	void drawSimpleArcXY(float innerRadius,float radius,float resolution,float startAngle, float maxAngle);
	void drawSimpleArcXY(float innerRadius,float radius,float resolution,float startAngle, float maxAngle, float thickness);
	void drawSimpleArcXZ(float innerRadius,float radius,float resolution,float startAngle, float maxAngle);
	void drawSimpleArcXZ(float innerRadius,float radius,float resolution,float startAngle, float maxAngle, float thickness);
	void drawSimpleArcYZ(float innerRadius,float radius,float resolution,float startAngle, float maxAngle);
	void drawSimpleArcYZ(float innerRadius,float radius,float resolution,float startAngle, float maxAngle, float thickness);
};

#endif /* X5CAR_H_ */
