#include "GraphicsHeader.h"
#include <math.h>
//#include <random>

#include <iostream>
#include <vector>
#include <fstream>
#include "Plane.h"
#include "Bullet.h"
#include "HumanPlane.h"
#include "OBJParser.h"
#include "Guage.h"

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

OBJParser x5Car("/home/matt/Desktop/simpleX5.obj");



float angle=0.0,deltaAngle = 0.0,ratio,rotationAngleDelta = 0,rotationAngle = 0;
float x=0.0f,y=0.0f,z=0.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
float zero = 0;
int deltaMove = 0;
int indexer = 0;
int shipRotationAngle = 0;

double pi = 3.14159262;
HumanPlane mainPlane;
double frameCount,currentTime,fps,previousTime,totalFPS=0, iterations=0;

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
	float carX=40.0f,carY=-10.0f,carZ=0.0f;
	x5Car.x = carX;
	x5Car.y = carY;
	x5Car.z = carZ;
	x5Car.roll = 270;
	x5Car.pitch = 0;
	x5Car.yaw = 270;
	x5Car.drawOBJ();


}

void drawGuage(){
	float guageX=200.0f,guageY=200.0f;
	Guage fuelGuage;
	fuelGuage.x=guageX;
	fuelGuage.y=guageY;
	fuelGuage.drawGuage();


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
	//glPushMatrix();        ----Not sure if I need this
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	glTranslatef(300,300,0);
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(20.0, 0.0);
		glVertex2f(20.0, 20.0);
		glVertex2f(0.0, 20.0);
	glEnd();
	glTranslatef(-300,-300,0);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawPlane();
	drawCar();



	drawHUD();
	calculateFPS();
	glutSwapBuffers();
	indexer++;


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
		mainPlane.desiredPitch-=5; break;
	case '5':
		//mainPlane.pitch+=6; break;
		mainPlane.desiredPitch+=5; break;
	case '4':
		//mainPlane.roll-=10;break;
		mainPlane.desiredRoll-=9; break;
	case '6':
		//mainPlane.roll+=10;break;
		mainPlane.desiredRoll+=9; break;
	case 'p':
		mainPlane.speed+=.1;break;
	case 'o':
		mainPlane.speed-=.1;
		if (mainPlane.speed<.01) {
			mainPlane.speed = .01;
		}
		break;
	case 'u':
		mainPlane.userFire();
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



	glutInit(&argc, argv);
	//glutSetOption(GLUT_MULTISAMPLE,8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1366,768);
	glutCreateWindow("Car Heads Up Display");

	initScene();

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_MULTISAMPLE);
	//glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.1, 0.1, 0.1, 0.2 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 20.0, 30.0, 10, 1 };
	GLfloat light_dir[] = { 0.0, 0, 0};
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



	glClearColor(0.1f, 0.1f, .1f, .5f);

	glutIgnoreKeyRepeat(.05);

	glutKeyboardFunc(pressKey);


	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutReshapeFunc(changeSize);

	glutMainLoop();

	return(0);
}
