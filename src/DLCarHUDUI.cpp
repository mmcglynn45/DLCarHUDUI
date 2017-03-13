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

x5car mainModel(40.0f,-10.0f,0);
DataController dataCont;
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



double pi = 3.14159262;
HumanPlane mainPlane;
double frameCount,currentTime,fps,previousTime,totalFPS=0, iterations=0;

bool webThreadCreated = false;
pthread_t webThread;

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

void* webAccept(void * webSocketDataPointer);
void* accelAccept(void * accelSocketDataPointer);
void updateMousePos(int x, int y);
void mouse(int button, int state,int x, int y);

void calculateFPS()
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






void orientMe(float ang) {

	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);
}

void moveMeFlat(int direction) {
	x = x + direction*(lx)*0.1;
	z = z + direction*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);
}
void rotateMe(float ang) {
	orientMe(ang);
	ly = -sin(ang);
	lx = -cos(ang);
	lz = 1;
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);

}








void changeSize(int w, int h)
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


GLuint createDL() {
	GLuint flightsimDL;

	// Create the id for the list
	flightsimDL = glGenLists(1);

	// start list
	glNewList(flightsimDL,GL_COMPILE);


	// endList
	glEndList();

	return(flightsimDL);
}


void drawCar(){
	mainModel.measuredPitch = dataCont.pitch;
	mainModel.measuredRoll = dataCont.roll;
	mainModel.measuredYaw = dataCont.yaw;
	mainModel.measuredMX = dataCont.mx;
	mainModel.measuredMY = dataCont.my;
	mainModel.draw();
}


void drawGuage(){

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
	throttleGuage.currentValue = dataCont.engineThrottle;
	throttleGuage.drawGuage();



	//Speed Guage 
	guageY=baseY+spacing;
	Guage speedGuage;
	speedGuage.x=guageX;
	speedGuage.y=guageY;
	speedGuage.label =    "  speed   \0";
	speedGuage.unitsLabel =    "mph";
	speedGuage.maxValue = 100.0;
	speedGuage.currentValue = dataCont.speed;
	speedGuage.drawGuage();

	//RPM Guage
	guageY=baseY+spacing*2;
	Guage rpmGuage;
	rpmGuage.x=guageX;
	rpmGuage.y=guageY;
	rpmGuage.label =    "   rpm   \0";
	rpmGuage.unitsLabel =    " k ";
	rpmGuage.maxValue = 6.0;
	rpmGuage.currentValue = dataCont.rpm;
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
	intakeGuage.currentValue = dataCont.airIntakeTemp;
	intakeGuage.drawGuage();

	guageY=baseY+spacing;
	Guage coolantGuage;
	coolantGuage.x=guageX;
	coolantGuage.y=guageY;
	coolantGuage.label =    "  engine \0";
	coolantGuage.unitsLabel = " °C ";
	coolantGuage.maxValue = 250;
	coolantGuage.currentValue = dataCont.engineCoolantTemp;
	coolantGuage.drawGuage();

	guageY=baseY+spacing*2;
	Guage manifestGuage;
	manifestGuage.x=guageX;
	manifestGuage.y=guageY;
	manifestGuage.label =    "  manifold \0";
	manifestGuage.unitsLabel = "kPA";
	manifestGuage.maxValue = 250;
	manifestGuage.currentValue = dataCont.manifoldABS;
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



void initScene() {
	glEnable(GL_DEPTH_TEST);
}


void drawPlane(){

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

void drawHUD(){
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



void renderScene(void) {

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


	drawPlane();
	drawCar();
	drawHUD();
	calculateFPS();
	glutSwapBuffers();


	indexer++;


}

void updateMousePos(int x, int y){
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

void mouse(int button, int state,int x, int y){
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

void pressKey(unsigned char key, int x, int y) {
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

void releaseKey(int key, int x, int y) {

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



int main(int argc, char **argv) {

	webData.dataRef = &dataCont;
	accelData.dataRef = &dataCont;


	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE,8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("Car Heads Up Display");

	initScene();

	// Enable lighting

	glEnable(GL_LIGHTING);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LIGHT0);
	GLfloat light_ambient[] = { 0.8, 0.8, 0.8, 0.5 };
	GLfloat light_diffuse[] = { 0.1, 0.1, 0.1, 0.2 };
	GLfloat light_specular[] = { 0.3, 0.3, 0.3, 0.5 };
	GLfloat light_pos[] = { 0.0, 30.0, -10, 1 };
	GLfloat light_dir[] = { 0.5, 0.5, 0.5};
	GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat mat_shininess[] = { 10.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);



	glClearColor(0.0f, 0.0f, .0f, .4f);

	glutIgnoreKeyRepeat(.05);

	glutKeyboardFunc(pressKey);


	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutMotionFunc(updateMousePos);
	glutMouseFunc(mouse);

	glutReshapeFunc(changeSize);

	glutMainLoop();

	return(0);
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
