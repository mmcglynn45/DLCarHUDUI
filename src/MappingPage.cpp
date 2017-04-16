/*
 * MappingPage.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: matt
 */

#include "MappingPage.h"

MappingPage::MappingPage(DataController * dataControllerPointer) : LandingPage(dataControllerPointer) {
	mainHeader.label = "map" ;
	mainHeader.subLabel = "current location";
}

void MappingPage::draw(void) {

	glColor3f(1, 1, 1);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	manageData();

	drawMap();
	calculateFPS();
	glutSwapBuffers();


	indexer++;

}

void MappingPage::drawMap(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);



	try{
		map.myLatitude = dataCont->latitude;
		map.myLongitude = dataCont->longitude;
		map.speed = dataCont->speed;
		map.heading = dataCont->heading;
		map.draw();
		glLineWidth(2.0);
		drawBorder();
		mainHeader.draw();
	}catch(...){
		std::cout << "Error occurred during map render.\n";
	}



	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

MappingPage::~MappingPage() {
	// TODO Auto-generated destructor stub
}

void MappingPage::drawBorder(){

	glPushMatrix();
	glTranslatef(0,200.0,0);

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//Border X = 182.95
	//Border y = 1012.45
	//Border yStart = 135.65
	//Border xEnd = 1727.05
	glBegin(GL_LINES);
	float coordX = 182.95;
	float coordY = -64.35;
	float coord2X = 1727.05;
	float coord2Y = -64.35;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = 182.95;
	coordY = 812.45;
	coord2X = 1727.05;
	coord2Y = 812.45;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = 182.95;
	coordY = -64.35;
	coord2X = 182.95;
	coord2Y = 812.45;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = 1727.05;
	coordY = -64.35;
	coord2X = 1727.05;
	coord2Y = 812.45;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = 477.05;
	coordY = -64.35;
	coord2X = 477.05;
	coord2Y = 812.45;
	//glVertex3f(coordX,coordY,0);
	//glVertex3f(coord2X,coord2Y,0);
	coordX = 1432.95;
	coordY = -64.35;
	coord2X = 1432.95;
	coord2Y = 812.45;
	//glVertex3f(coordX,coordY,0);
	//glVertex3f(coord2X,coord2Y,0);


	glEnd();
	glPopMatrix();

	glTranslatef(0,-200.0,0);
	glPopMatrix();

}

