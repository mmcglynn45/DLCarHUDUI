/*
 * LandingPage.h
 *
 *  Created on: Mar 17, 2017
 *      Author: matt
 */

#ifndef LANDINGPAGE_H_
#define LANDINGPAGE_H_

#include "GraphicsHeader.h"
#include <math.h>
//#include <random>

#include <iostream>
#include <vector>
#include <fstream>
#include "Plane.h"
#include "HumanPlane.h"
#include "OBJParser.h"
#include "Guage.h"
#include "x5car.h"
#include "DataController.h"
#include <pthread.h>
#include "PageHeader.h"
//#include "AerialMap.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class LandingPage {
public:
	DataController * dataCont;
	LandingPage(DataController * dataControllerPointer);
	virtual ~LandingPage();


	void mouse(int button, int state,int x, int y);
	void pressKey(unsigned char key, int x, int y);
	void releaseKey(int key, int x, int y);
	void updateMousePos(int x, int y);
	void changeSize(int w, int h);

	virtual void draw(void);

protected:
	x5car mainModel;

	PageHeader mainHeader;

	float angle=0.0,deltaAngle = 0.0,ratio,rotationAngleDelta = 0,rotationAngle = 0;
	float x=0.0f,y=0.0f,z=0.0f;
	float lx=0.0f,ly=0.0f,lz=-1.0f;
	float zero = 0;
	int deltaMove = 0;
	int indexer = 0;
	int shipRotationAngle = 0;
	int lastX = 0;
	int lastY = 0;
	double rotationalSpeed = 0;
	double mouseSpeed = 0;
	bool isClicked = false;
	int clickX = 0;
	int clickY = 0;
	double carAngle = 0;
	double originalAngle = 0;
	int dragStartX = 0;
	int dragStartY = 0;
	bool isBeingDragged = false;
	int dragEndX = 0;
	int dragEndY = 0;

	double pi = 3.14159262;
	HumanPlane mainPlane;
	double frameCount,currentTime,fps,previousTime,totalFPS=0, iterations=0;

	bool webThreadCreated = false;
	pthread_t webThread;

	void calculateFPS();
	void drawCar();
	void drawGuage();
	void drawPlane();
	void drawHUD();
	void orientMe(float ang);
	void moveMeFlat(int direction);
	void rotateMe(float ang);
	void manageData();

};
#endif /* LANDINGPAGE_H_ */
