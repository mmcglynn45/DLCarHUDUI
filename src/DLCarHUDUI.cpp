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
#include "LandingPage.h"
#include "MappingPage.h"
//#include "AerialMap.h"

LandingPage statusPage;
MappingPage mapPage;
LandingPage * home;
int pageIndex = 1;
int pageTotal = 2;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


void updateMousePos(int x, int y);
void mouse(int button, int state,int x, int y);
void incrementPage();


void changeSize(int w, int h)
{
   home->changeSize(w,h);
}

void initScene() {
	glEnable(GL_DEPTH_TEST);
}


void renderScene(void) {
	home->draw();
}

void updateMousePos(int x, int y){
	home->updateMousePos(x,y);
}

void mouse(int button, int state,int x, int y){
	if(x>SCREEN_WIDTH*0.9&&y<SCREEN_HEIGHT*0.1){
		if(state==GLUT_DOWN){
			incrementPage();
		}
	}
    home->mouse(button,state,x,y);

}

void pressKey(unsigned char key, int x, int y) {
	home->pressKey(key,x,y);
}

void releaseKey(int key, int x, int y) {
    home->releaseKey(key,x,y);
}

void incrementPage(){

	pageIndex++;
	pageIndex = pageIndex % pageTotal;

	if(pageIndex == 1){
	   home = &statusPage;
	}else{
	   home = &mapPage;
	}

	glutKeyboardFunc(pressKey);


	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutMotionFunc(updateMousePos);
	glutMouseFunc(mouse);

	glutReshapeFunc(changeSize);


}


int main(int argc, char **argv) {

	home = &statusPage;

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


