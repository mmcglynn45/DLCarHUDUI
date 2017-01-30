/*
 * x5car.cpp
 *
 *  Created on: Nov 11, 2016
 *      Author: matt
 */

#include "x5car.h"

x5car::x5car(float baseX,float baseY, float baseZ) {
	carModel = OBJParser("./data/simpleX5.obj");
	x = baseX;
	y = baseY;
	z = baseZ;
	scale = 0.17;
	orientationRingRadius = 45.0;
	revolvingOffset = 0.0f;
	revolvingOffsetDelta = 0.0f;
	sinOffset = 1.2f;
	userOffset = 0.0f;
	measuredPitch = 0.0f;
	measuredRoll = 0.0f;
	measuredYaw = 270.0f;
	measuredMX = 0.0f;
	measuredMY = 0.0f;
	carModel.x = x;
	carModel.y = y;
	carModel.z = z;
	carModel.roll = 270+measuredRoll;
	carModel.pitch = 0+measuredPitch;
	carModel.yaw = 245;
	carModel.scale = scale;
}

x5car::~x5car() {

}


void x5car::draw(){
	glRotatef(userOffset, 0, 0, 1);
	glRotatef(30, 0, 0, 1);
	glRotatef(measuredRoll, 1, 0, 0);
	glRotatef(measuredPitch, 0, 1, 0);
	carModel.drawOBJ();
	glRotatef(-measuredPitch, 0, 1, 0);
	glRotatef(-measuredRoll, 1, 0, 0);
	drawOrientationRings();
	glRotatef(-30, 0, 0, 1);
	glRotatef(-userOffset, 0, 0, 1);
}

void x5car::drawOrientationText(){
	    glTranslatef(x,y,0);
		glPushMatrix();
		glTranslatef(550,scale*400,0);
		//Draw Guage Value
		glScalef(0.2,0.2,0.2);
		glScalef(1,-1, 1);
		glColor4f(0.3f, 0.5f, 0.6f, 1.0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"Roll: ");
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		char textBuffer[255];
		int n = sprintf(textBuffer, "%2.2f \0",measuredRoll);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)textBuffer);
		glColor4f(0.3f, 0.5f, 0.6f, 1.0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"Pitch: ");
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		n = sprintf(textBuffer, "%2.2f \0",measuredPitch);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)textBuffer);
		glColor4f(0.3f, 0.5f, 0.6f, 1.0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"Yaw: ");
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		n = sprintf(textBuffer, "%2.2f \0",measuredYaw);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)textBuffer);
		glColor4f(0.3f, 0.5f, 0.6f, 1.0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"MX: ");
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		n = sprintf(textBuffer, "%2.2f \0",measuredMX);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)textBuffer);
		glColor4f(0.3f, 0.5f, 0.6f, 1.0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"MY: ");
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		n = sprintf(textBuffer, "%2.2f \0",measuredMY);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)textBuffer);

		glPopMatrix();
	    glTranslatef(-x,-y,0);
}

void x5car::drawOrientationRings(){

	if(measuredYaw>360){
		measuredYaw-=360;
	}if(measuredYaw<0){
		measuredYaw+=360;
	}


	glTranslatef(x,y,z);
	float xOffset = 0.0f;
	float yOffset = -3.0f;
	float zOffset = 0.0f;

	//Translate to car center
	glTranslatef(xOffset,yOffset,zOffset);




	float ringRadius = orientationRingRadius;



	//Draw outer Yaw measured ring
	for(int i = 0; i<360; i+=360/180){
		glColor4f(0.3f, 0.5f, 0.6f, 0.7);
		glLineWidth(2.0);
		//glBegin(GL_LINES);
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*((ringRadius+ringRadius/8));
		float coordZ = sinf(angleRadians)*((ringRadius+ringRadius/8));
		float coord2X = cosf(angleRadians)*((ringRadius+ringRadius/5));
		float coord2Z = sinf(angleRadians)*((ringRadius+ringRadius/5));
		glVertex3f(coordX,0,coordZ);
		glVertex3f(coord2X,0,coord2Z);
		glEnd();
	}






	//Implement car orientation visualization

	//Implement yaw measurement
	//Anchor will be equivalent to true north
	float anchorPoint = 290.0f;
	float measurePoint = measuredYaw+anchorPoint;
	float rotateDelta = 0.0f;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0);
	//drawSimpleArcXZ(ringRadius+ringRadius/5,ringRadius+ringRadius/5,50,measurePoint+0.2,measurePoint+0.2,8.0);
	//drawSimpleArcXZ(ringRadius+ringRadius/5,ringRadius+ringRadius/5,50,anchorPoint+0.2,anchorPoint+0.2,5.0);

	glColor4f(0.2f, 0.2f, 0.9f, 0.7);
	if (measurePoint<(anchorPoint+180)){
		drawSimpleArcXZ(ringRadius+ringRadius/5,ringRadius+ringRadius/5,5000,anchorPoint,measurePoint,5.0);
	}else {
		anchorPoint+=360;
		drawSimpleArcXZ(ringRadius+ringRadius/5,ringRadius+ringRadius/5,5000,measurePoint,anchorPoint,5.0);
	}


	glColor4f(0.3f, 0.5f, 0.6f, 0.7);
	drawSimpleArcXZ(ringRadius+ringRadius/5,ringRadius+ringRadius/5,1500,0,360);


	//Rotate to follow actual yaw measurement
	if(measuredYaw>180){
		glRotatef(-measuredYaw, 0, 1, 0);
	}else{
		glRotatef(-(measuredYaw-360), 0, 1, 0);
	}


	//Visual flourish inner rings
	glColor4f(0.3f, 0.3f, 0.3f, 1.0);
	drawSimpleArcXZ(ringRadius,ringRadius,1500,0,360);
	drawSimpleArcXZ(ringRadius,ringRadius,1500,140,200,5.0);
	drawSimpleArcXZ(ringRadius,ringRadius,1500,260,320,5.0);
	drawSimpleArcXZ(ringRadius,ringRadius,1500,380,440,5.0);



	//Rotate back
	if(measuredYaw>180){
		glRotatef(measuredYaw, 0, 1, 0);
	}else{
		glRotatef(measuredYaw-360, 0, 1, 0);
	}


	//Visual flourish revolving outer rings
	//Handle ring orientation shifts
	if(revolvingOffset>720){
		revolvingOffset-=360;
	}else if (revolvingOffset<0){
		revolvingOffset+=360;
	}
	float inverseOffset = 360.0f-revolvingOffset;
	if(inverseOffset<0){
		inverseOffset+=360;
	}


	glColor4f(0.4f, 0.2f, 0.2f, 0.2);
	glTranslatef(0,20,0);
	//glRotatef(20,0,0,1);

	//drawSimpleArcXZ(ringRadius+ringRadius/3.5,ringRadius+ringRadius/3.5,2500,revolvingOffset,revolvingOffset+60,2.0);
	//drawSimpleArcXZ(ringRadius+ringRadius/3.5,ringRadius+ringRadius/3.5,2500,revolvingOffset+180,revolvingOffset+240,2.0);

	//inverse rings
	//drawSimpleArcXZ(ringRadius+ringRadius/3,ringRadius+ringRadius/3,2500,inverseOffset+30,inverseOffset+60,2.0);
	//drawSimpleArcXZ(ringRadius+ringRadius/3,ringRadius+ringRadius/3,2500,inverseOffset+210,inverseOffset+280,2.0);
	//glRotatef(-20,0,0,1);
	glTranslatef(0,-20,0);

	float speedFactor = 0.003;
	sinOffset+=speedFactor;
	revolvingOffset+=sinf(sinOffset)*0.8;







	//Ring 2
	glRotatef(-20, 0, 1, 0);

	for(float i = 40; i<140; i+=360/180){
		glColor4f(0.3f, 0.5f, 0.6f, 0.7);
		glLineWidth(2.0);
		glBegin(GL_LINES);
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*((ringRadius+ringRadius/8));
		float coordY = sinf(angleRadians)*((ringRadius/1.3+ringRadius/8));
		float coord2X = cosf(angleRadians)*((ringRadius+ringRadius/6));
		float coord2Y = sinf(angleRadians)*((ringRadius/1.3+ringRadius/6));
		glVertex3f(coordX,coordY,-ringRadius/30);
		glVertex3f(coordX,coordY,ringRadius/30);
		glEnd();
	}
	drawSimpleArcXY(ringRadius+ringRadius/8,ringRadius/1.3+ringRadius/8,1500,40,140);
	glColor4f(0.3f, 0.3f, 0.9f, 0.9);
	if(measuredRoll>0){
		drawSimpleArcXY(ringRadius+ringRadius/8,ringRadius/1.3+ringRadius/8,1500,90,90+measuredRoll,10);
	}else{
		drawSimpleArcXY(ringRadius+ringRadius/8,ringRadius/1.3+ringRadius/8,1500,90+measuredRoll,90,10);
	}

	glColor4f(0.3f, 0.5f, 0.6f, 0.7);

	//Ring 3
	glRotatef(-90, 0, 1, 0);

	for(float i = 40; i<140; i+=360/180){
		glColor4f(0.3f, 0.5f, 0.6f, 0.7);
		glLineWidth(2.0);
		glBegin(GL_LINES);
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*((ringRadius+ringRadius/8));
		float coordY = sinf(angleRadians)*((ringRadius/1.4+ringRadius/8));
		float coord2X = cosf(angleRadians)*((ringRadius+ringRadius/6));
		float coord2Y = sinf(angleRadians)*((ringRadius/1.4+ringRadius/6));
		glVertex3f(coordX,coordY,0);
		glVertex3f(coord2X,coord2Y,0);
		glEnd();
	}
	drawSimpleArcXY(ringRadius+ringRadius/6,ringRadius/1.4+ringRadius/6,1500,40,140);
	glColor4f(0.3f, 0.3f, 0.9f, 0.9);
	if(measuredPitch>0){
		drawSimpleArcXY(ringRadius+ringRadius/6,ringRadius/1.4+ringRadius/6,1500,90,90+measuredPitch,10);
	}else{
		drawSimpleArcXY(ringRadius+ringRadius/6,ringRadius/1.4+ringRadius/6,1500,90+measuredPitch,90,10);
	}
	glColor4f(0.3f, 0.5f, 0.6f, 0.7);


	glTranslatef(-xOffset,-yOffset,-zOffset);
	glTranslatef(-x,-y,-z);
}

void x5car::drawSimpleArcXY(float xRadius,float yRadius,float resolution,float startAngle, float maxAngle){
	for(float i = startAngle; i<maxAngle; i+=maxAngle/resolution){
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*xRadius;
		float coordY = sinf(angleRadians)*yRadius;

		glPointSize(0.05);
		glBegin(GL_POINTS);
		glVertex3f(coordX,coordY,0);
		glEnd();

	}
}

void x5car::drawSimpleArcXY(float xRadius,float yRadius,float resolution,float startAngle, float maxAngle, float thickness){
	for(float i = startAngle; i<maxAngle; i+=maxAngle/resolution){
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*(xRadius-thickness/2);
		float coordY = sinf(angleRadians)*(yRadius-thickness/2);
		float coord2X = cosf(angleRadians)*(xRadius+thickness/2);
		float coord2Y = sinf(angleRadians)*(yRadius+thickness/2);

		glLineWidth(2.0);
		glBegin(GL_LINES);
		glVertex3f(coordX,coordY,0);
		glVertex3f(coord2X,coord2Y,0);
		glEnd();

	}
}

void x5car::drawSimpleArcXZ(float xRadius,float zRadius,float resolution,float startAngle, float maxAngle){
	for(float i = startAngle; i<maxAngle; i+=maxAngle/resolution){
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*xRadius;
		float coordZ = sinf(angleRadians)*zRadius;

		glPointSize(3.0);
		glBegin(GL_POINTS);
		glVertex3f(coordX,0,coordZ);
		glEnd();

	}
}

void x5car::drawSimpleArcXZ(float xRadius,float zRadius,float resolution,float startAngle, float maxAngle, float thickness){
	for(float i = startAngle; i<maxAngle; i+=maxAngle/resolution){
		float angleRadians = (i*2*M_PI)/360;
		float coordX = cosf(angleRadians)*(xRadius-thickness/2);
		float coordZ = sinf(angleRadians)*(zRadius-thickness/2);
		float coord2X = cosf(angleRadians)*(xRadius+thickness/2);
		float coord2Z = sinf(angleRadians)*(zRadius+thickness/2);

		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(coordX,0,coordZ);
		glVertex3f(coord2X,0,coord2Z);
		glEnd();

	}
}

void x5car::drawSimpleArcYZ(float yRadius,float zRadius,float resolution,float startAngle, float maxAngle){
	for(float i = startAngle; i<maxAngle; i+=maxAngle/resolution){
		float angleRadians = (i*2*M_PI)/360;
		float coordY = cosf(angleRadians)*yRadius;
		float coordZ = sinf(angleRadians)*zRadius;

		glPointSize(0.2);
		glBegin(GL_POINTS);
		glVertex3f(0,coordY,coordZ);
		glEnd();

	}
}

