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
	float startPos = startOrientation;
	float endPos=(currentValue/maxValue)*360+startPos;

	glTranslatef(x,y,0);
	glPushMatrix();
	glTranslatef(-innerGuageRadius/2,innerGuageRadius/6,0);

	//Draw Guage Value
	glRotatef(0, 0, 0, 1);
	glScalef(0.3,0.3,0.3);
	glScalef(1,-1, 1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	char textBuffer[20];
	int n = sprintf(textBuffer, "%2.1f\0",currentValue);
	glPushMatrix();
	if(n>4){
		glTranslatef(-innerGuageRadius/2,0,0);
	}
	if(n==4){
		glTranslatef(-innerGuageRadius/4,0,0);
	}
	if(n==3){
		glTranslatef(0,0,0);
	}
	glPopMatrix();
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)textBuffer);

	glPushMatrix();
	glTranslatef(-innerGuageRadius*2.0,-innerGuageRadius*1.7,0);
	glScalef(0.7,0.7,0.7);
	glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)unitsLabel);
	glPopMatrix();

	//Draw Guage Label
	glScalef(0.5,0.5,0.5);
	glTranslatef(-innerGuageRadius*12,innerGuageRadius*12,0);
	glScalef(2.0,2.0,0.5);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)label);


	glRotatef(0, 0, 0, 1);
	glPopMatrix();




	float severity = (currentValue/maxValue)*.8+0.2;
	glColor4f(severity, 0.2f, 0.9f, 0.7);
	drawGuageArc(innerGuageRadius,outerGuageRadius,5000,startPos,endPos,1);

	//draw Major Ticks
	glColor4f(1.0f, 1.0f, 1.0f, 1.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	float angleRadians = (0*2*M_PI)/360;
	float coordX = cosf(angleRadians)*((ringRadius-ringRadius/3));
	float coordY = sinf(angleRadians)*((ringRadius-ringRadius/3));
	float coord2X = cosf(angleRadians)*((ringRadius+ringRadius/3));
	float coord2Y = sinf(angleRadians)*((ringRadius+ringRadius/3));
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	glEnd();


	glColor4f(1.0f, 1.0f, 1.0f, 1.0);
	glBegin(GL_LINES);
	angleRadians = (180*2*M_PI)/360;
	coordX = cosf(angleRadians)*((ringRadius-ringRadius/3));
	coordY = sinf(angleRadians)*((ringRadius-ringRadius/3));
	coord2X = cosf(angleRadians)*((ringRadius+ringRadius/3));
	coord2Y = sinf(angleRadians)*((ringRadius+ringRadius/3));
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	glEnd();


	//draw Minor Ticks
	for(float i = 0; i<360; i+=360/120){
		glColor4f(0.3f, 0.3f, 0.3f, 1.0);
		glLineWidth(2);
		glBegin(GL_LINES);
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*((ringRadius+ringRadius/8));
		float coordY = sinf(angleRadians)*((ringRadius+ringRadius/8));
		float coord2X = cosf(angleRadians)*((ringRadius+ringRadius/6));
		float coord2Y = sinf(angleRadians)*((ringRadius+ringRadius/6));
		glVertex3f(coordX,coordY,0);
		glVertex3f(coord2X,coord2Y,0);
		glEnd();
	}
   for(float i = 0; i<360; i+=360/73){
		glColor4f(0.3f, 0.3f, 0.3f, 1.0);
		glBegin(GL_LINES);
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*((ringRadius-ringRadius/8));
		float coordY = sinf(angleRadians)*((ringRadius-ringRadius/8));
		float coord2X = cosf(angleRadians)*((ringRadius-ringRadius/6));
		float coord2Y = sinf(angleRadians)*((ringRadius-ringRadius/6));
		glVertex3f(coordX,coordY,0);
		glVertex3f(coord2X,coord2Y,0);
		glEnd();
	}


	glColor4f(0.3f, 0.3f, 0.3f, 1.0);
	drawGuageArc(ringRadius,ringRadius,5000,0,360,0);
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

