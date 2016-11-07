/*
 * Guage.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: matt
 */

#include "Guage.h"

Guage::Guage() {
	// TODO Auto-generated constructor stub

}

Guage::~Guage() {
	// TODO Auto-generated destructor stub
}

void Guage::drawGuage() {
	float RPM = 2.9;
	float maxRPM = 5.00;
	float startPos = 270;
	float endPos=(RPM/maxRPM)*360+startPos;


	glTranslatef(x,y,0);

	glColor4f(.7f, 0.36f, 0.0f, 1.0);
	drawGuageArc(73.5,86.5,5000,startPos,endPos,1);
	glColor4f(0.3f, 0.3f, 0.3f, 1.0);
	drawGuageArc(80,80,5000,0,360,0);

	glTranslatef(-x,-y,0);


}

void Guage::drawGuageArc(float innerRadius,float radius,float resolution,float startAngle, float maxAngle, int endingCirles){
	for(float i = startAngle; i<maxAngle; i+=maxAngle/resolution){
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*innerRadius;
		float coordY = sinf(angleRadians)*innerRadius;
		float coord2X = cosf(angleRadians)*radius;
		float coord2Y = sinf(angleRadians)*radius;

		if((radius-innerRadius)>1){
			glLineWidth(0.2);
			glBegin(GL_LINES);
			glVertex3f(coordX,coordY,0);
			glVertex3f(coord2X,coord2Y,0);
			glEnd();

		}else{
			glPointSize(1.5);
			glBegin(GL_POINTS);
			glVertex3f(coordX,coordY,0);
			glEnd();

		}


	}
	if(endingCirles){
		float angleRadians = (startAngle*2*M_PI)/360;
		float coordX = cosf(angleRadians)*(innerRadius + (radius-innerRadius)/2);
		float coordY = sinf(angleRadians)*(innerRadius + (radius-innerRadius)/2);
		glPointSize(radius-innerRadius);
		glBegin(GL_POINTS);
		glVertex3f(coordX,coordY,0);
		glEnd();

		angleRadians = (maxAngle*2*M_PI)/360;
		coordX = cosf(angleRadians)*(innerRadius + (radius-innerRadius)/2);
		coordY = sinf(angleRadians)*(innerRadius + (radius-innerRadius)/2);
		glPointSize(radius-innerRadius);
		glBegin(GL_POINTS);
		glVertex3f(coordX,coordY,0);
		glEnd();

	}




}

