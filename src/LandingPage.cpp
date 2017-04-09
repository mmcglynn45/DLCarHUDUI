/*
 * LandingPage.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: matt
 */

#include "LandingPage.h"




struct webSocketData
{
	DataController * dataRef;
	bool currentlyAccepting = false;
};

struct webSocketData webData;

bool accelThreadCreated = false;
pthread_t accelThread;

struct accelSocketData
{
	DataController * dataRef;
	bool currentlyAccepting = false;
};

struct accelSocketData accelData;

LandingPage::LandingPage(DataController * dataContPointer) {
	mainModel = x5car(40.0f,-10.0f,0.0f);
	dataCont = dataContPointer;
	webData.dataRef = dataCont;
	accelData.dataRef = dataCont;
}

LandingPage::~LandingPage() {
}


void LandingPage::orientMe(float ang) {

	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);
}

void LandingPage::moveMeFlat(int direction) {
	x = x + direction*(lx)*0.1;
	z = z + direction*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);
}
void LandingPage::rotateMe(float ang) {
	orientMe(ang);
	ly = -sin(ang);
	lx = -cos(ang);
	lz = 1;
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);

}

void* webAccept(void * webSocketDataPointer) {

	struct webSocketData * myWebSocket;
	myWebSocket = (webSocketData*)webSocketDataPointer;
	myWebSocket->currentlyAccepting = true;

	DataController * dataContPointer;
	dataContPointer = (DataController *)myWebSocket->dataRef;

	try{
		dataContPointer->UpdateOBD();
	}catch(...){
		myWebSocket->currentlyAccepting = false;
	}

	myWebSocket->currentlyAccepting = false;

	return 0;
}

void* accelAccept(void * accelSocketDataPointer) {

	usleep(50000);
	struct accelSocketData * myAccelSocket;
	myAccelSocket = (accelSocketData*)accelSocketDataPointer;
	myAccelSocket->currentlyAccepting = true;

	DataController * dataContPointer;
	dataContPointer = (DataController *)myAccelSocket->dataRef;

	try{
		dataContPointer->UpdateAccel();
	}catch(...){
		myAccelSocket->currentlyAccepting = false;
	}

	myAccelSocket->currentlyAccepting = false;

	return 0;
}


void LandingPage::calculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if(timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
		totalFPS+=fps;
		iterations++;
		std::cout<<"FPS: "<<fps<<"\n";
		std::cout<<"Average FPS: "<<totalFPS/iterations<<"\n";
	}

}

void LandingPage::drawCar(){
	mainModel.measuredPitch = dataCont->pitch;
	mainModel.measuredRoll = dataCont->roll;
	mainModel.measuredYaw = dataCont->yaw;
	mainModel.measuredMX = dataCont->mx;
	mainModel.measuredMY = dataCont->my;
	mainModel.draw();
}


void LandingPage::drawGuage(){

	glPushMatrix();
	mainModel.drawOrientationText();
	glTranslatef(0,200.0,0);

	float baseY = 100.0f;
	float rightX = 330.0f;
	float leftX = 1580.0f;
	float spacing = 300.0f;

	//Throttle Guage
	float guageX=rightX,guageY=baseY;
	Guage throttleGuage;
	throttleGuage.x=guageX;
	throttleGuage.y=guageY;
	throttleGuage.label = "  throttle \0";
	throttleGuage.unitsLabel = " % ";
	throttleGuage.maxValue = 100.0;
	throttleGuage.currentValue = dataCont->engineThrottle;
	throttleGuage.drawGuage();



	//Speed Guage
	guageY=baseY+spacing;
	Guage speedGuage;
	speedGuage.x=guageX;
	speedGuage.y=guageY;
	speedGuage.label =    "  speed   \0";
	speedGuage.unitsLabel =    "mph";
	speedGuage.maxValue = 100.0;
	speedGuage.currentValue = dataCont->speed;
	speedGuage.drawGuage();

	//RPM Guage
	guageY=baseY+spacing*2;
	Guage rpmGuage;
	rpmGuage.x=guageX;
	rpmGuage.y=guageY;
	rpmGuage.label =    "   rpm   \0";
	rpmGuage.unitsLabel =    " k ";
	rpmGuage.maxValue = 6.0;
	rpmGuage.currentValue = dataCont->rpm;
	rpmGuage.drawGuage();

	//Air Intake Guage
	guageX=leftX;
	guageY=baseY;
	Guage intakeGuage;
	intakeGuage.x=guageX;
	intakeGuage.y=guageY;
	intakeGuage.label =    "  intake \0";
	intakeGuage.unitsLabel =    " °C ";
	intakeGuage.maxValue = 120;
	intakeGuage.currentValue = dataCont->airIntakeTemp;
	intakeGuage.drawGuage();

	guageY=baseY+spacing;
	Guage coolantGuage;
	coolantGuage.x=guageX;
	coolantGuage.y=guageY;
	coolantGuage.label =    "  engine \0";
	coolantGuage.unitsLabel = " °C ";
	coolantGuage.maxValue = 250;
	coolantGuage.currentValue = dataCont->engineCoolantTemp;
	coolantGuage.drawGuage();

	guageY=baseY+spacing*2;
	Guage manifestGuage;
	manifestGuage.x=guageX;
	manifestGuage.y=guageY;
	manifestGuage.label =    "  manifold \0";
	manifestGuage.unitsLabel = "kPA";
	manifestGuage.maxValue = 250;
	manifestGuage.currentValue = dataCont->manifoldABS;
	manifestGuage.drawGuage();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	float coordX = rightX-throttleGuage.outerGuageRadius*1.7;
	float coordY = baseY-throttleGuage.outerGuageRadius*1.9;
	float coord2X = leftX+throttleGuage.outerGuageRadius*1.7;
	float coord2Y = baseY-throttleGuage.outerGuageRadius*1.9;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = rightX-throttleGuage.outerGuageRadius*1.7;
	coordY = baseY+spacing*2+throttleGuage.outerGuageRadius*1.3;
	coord2X = leftX+throttleGuage.outerGuageRadius*1.7;
	coord2Y = baseY+spacing*2+throttleGuage.outerGuageRadius*1.3;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = rightX-throttleGuage.outerGuageRadius*1.7;
	coordY = baseY-throttleGuage.outerGuageRadius*1.9;
	coord2X = rightX-throttleGuage.outerGuageRadius*1.7;
	coord2Y = baseY+spacing*2+throttleGuage.outerGuageRadius*1.3;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = leftX+throttleGuage.outerGuageRadius*1.7;
	coordY = baseY-throttleGuage.outerGuageRadius*1.9;
	coord2X = leftX+throttleGuage.outerGuageRadius*1.7;
	coord2Y = baseY+spacing*2+throttleGuage.outerGuageRadius*1.3;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = rightX+throttleGuage.outerGuageRadius*1.7;
	coordY = baseY-throttleGuage.outerGuageRadius*1.9;
	coord2X = rightX+throttleGuage.outerGuageRadius*1.7;
	coord2Y = baseY+spacing*2+throttleGuage.outerGuageRadius*1.3;
	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);
	coordX = leftX-throttleGuage.outerGuageRadius*1.7;
	coordY = baseY-throttleGuage.outerGuageRadius*1.9;
	coord2X = leftX-throttleGuage.outerGuageRadius*1.7;
	coord2Y = baseY+spacing*2+throttleGuage.outerGuageRadius*1.3;


	glVertex3f(coordX,coordY,0);
	glVertex3f(coord2X,coord2Y,0);


	glEnd();
	glPopMatrix();

	glTranslatef(0,-200.0,0);
	glPopMatrix();

}

void LandingPage::drawPlane(){

	//Chase View

	y = mainPlane.y+2;
	double planeYawRad = mainPlane.planeYaw*3.14159262/180;
	z = mainPlane.z+30*sin(planeYawRad);
	x = mainPlane.x-30*cos(planeYawRad);
	orientMe(1.57-planeYawRad);
	moveMeFlat(0);

	//Move and draw plane
	mainPlane.convertDesiredToActual();
	//mainPlane.movePlane();
	//mainPlane.drawPlane();
}

void LandingPage::drawHUD(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);


	mainHeader.draw();
	drawGuage();


	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void LandingPage::draw(void) {

	glColor3f(1, 1, 1);

	if (deltaMove)
		moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}
	if (rotationAngleDelta) {
		rotationAngle+=rotationAngleDelta;
		rotationAngleDelta=0;
		rotateMe(rotationAngle);
	}

	if(!isClicked){
		carAngle = carAngle + (mouseSpeed/500)*360;
		mouseSpeed = mouseSpeed * 0.98;
	}
	while(carAngle>360){
		carAngle-=360;
	}
	while(carAngle<0){
		carAngle+=360;
	}
	mainModel.userOffset = (360-carAngle);



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(((int)frameCount)%20==0){	
		manageData();
	}
	drawPlane();
	drawCar();
	drawHUD();
	calculateFPS();
	glutSwapBuffers();


	indexer++;


}

void LandingPage::updateMousePos(int x, int y){
	mouseSpeed = lastX - x;
	int threshold = 8;
	if(mouseSpeed>threshold){
		mouseSpeed = threshold;
	}
	if(mouseSpeed<-threshold){
		mouseSpeed = -threshold;
	}

	carAngle = originalAngle - ((x - clickX)/15.0);
	std::cout<<"click pos"<<clickX <<std::endl;
	std::cout<<"current pos "<<x<<std::endl;
	std::cout<<"car angle"<<carAngle<< std::endl;

	lastX = x;
}

void LandingPage::mouse(int button, int state,int x, int y){
	if (state == GLUT_DOWN){
		isClicked = true;
		clickX = x;
		clickY = y;
		lastX = x;
		lastY = y;
		originalAngle = carAngle;
	}
	if (state == GLUT_UP){
		isClicked = false;
		clickX = x;
		clickY = y;
		lastX = x;
		lastY = y;
	}


}

void LandingPage::pressKey(unsigned char key, int x, int y) {
	std::cout << "Key press" << std::endl;
	switch (key) {
	case GLUT_KEY_LEFT :
		deltaAngle = -0.014f;break;
	case GLUT_KEY_RIGHT :
		deltaAngle = 0.014f;break;
	case GLUT_KEY_UP :
		deltaMove = 3;break;
	case GLUT_KEY_DOWN :
		deltaMove = -3;break;
	case 'v':
		rotationAngleDelta = -.008;break;
	case 'c':
		rotationAngleDelta = .008;break;
	case '8':

		//mainPlane.pitch-=6; break;
		//mainPlane.desiredPitch-=5; break;
	case '5':
		//mainPlane.pitch+=6; break;
		//mainPlane.desiredPitch+=5; break;
	case '4':
		//mainPlane.roll-=10;break;
		//mainPlane.desiredRoll-=9; break;
	case '6':
		//mainPlane.roll+=10;break;
		//mainPlane.desiredRoll+=9; break;
	case 'p':
		mainPlane.speed+=.1;break;
	case 'o':
		mainPlane.speed-=.1;
		if (mainPlane.speed<.01) {
			mainPlane.speed = .01;
		}
		break;
	case 'u':
		break;
	case 'y':
		break;

	}
}

void LandingPage::releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT :
	case GLUT_KEY_RIGHT :
		deltaAngle = 0.0f;break;
	case GLUT_KEY_UP :
	case GLUT_KEY_DOWN :
		deltaMove = 0;break;
	case 'm':
		rotationAngleDelta  = 0;break;
	case 'K':
		rotationAngleDelta = 0;break;


	}
}

void LandingPage::changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);
}

void LandingPage::manageData(){
	if (!webThreadCreated&&!webData.currentlyAccepting) {
		webData.currentlyAccepting = true;
		pthread_create(&webThread, NULL, webAccept, &webData);
		webThreadCreated = true;
	}

	if (webThreadCreated&&!webData.currentlyAccepting)
	{
		pthread_join(webThread, NULL);
		webThreadCreated = false;
	}

	if (!accelThreadCreated&&!accelData.currentlyAccepting) {
		accelData.currentlyAccepting = true;
		pthread_create(&accelThread, NULL, accelAccept, &accelData);
		accelThreadCreated = true;
	}

	if (accelThreadCreated&&!accelData.currentlyAccepting)
	{
		pthread_join(accelThread, NULL);
		accelThreadCreated = false;
	}
}


