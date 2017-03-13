/*
 * PageHeader.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: matt
 */

#include "PageHeader.h"

PageHeader::PageHeader() {
	// TODO Auto-generated constructor stub

}

PageHeader::~PageHeader() {
	// TODO Auto-generated destructor stub
}

void PageHeader::draw(){


	glTranslatef(x,y,z);
	glPushMatrix();
	glScalef(0.7,0.7,0.7);
	glRotatef(180, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glColor4f(0.201f, 0.9215f, 0.752f, 1.0f);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)label);
	glPopMatrix();
	glTranslatef(-x,-y,-z);


	glPushMatrix();
	glTranslatef(x+65,y,z);
	glScalef(0.25,0.25,0.3);
	glRotatef(180, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)subLabel);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	float coordX = x+20;
	float coordY = 0;
	float coord2X = x+20;
	float coord2Y = y;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
	glBegin(GL_LINES);

	for (int i = 0; i<5; i++){
	float coordX = x+80+i;
	float coordY = y-30;
	float coord2X = x+80+i;
	float coord2Y = y;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	}
	glEnd();
	glPopMatrix();





}
