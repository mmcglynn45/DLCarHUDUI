/*
 * OBJParser.h
 *
 *  Created on: Nov 4, 2016
 *      Author: matt
 */

#include <vector>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include "GraphicsHeader.h"


#ifndef OBJPARSER_H_
#define OBJPARSER_H_

class OBJParser {
private:
	FILE * objectFile;
	std::vector< glm::vec3 > out_vertices;
	std::vector< glm::vec2 > out_uvs;
	std::vector< glm::vec3 > out_normals;

	std::vector<GLfloat> simple_normals;
	std::vector<GLfloat> simple_vertices;

	//functions
	int parseOBJ();


public:
    double x;
    double y;
    double z;
    double roll;
    double pitch;
    double yaw;
    double scale;

    void drawOBJ();

    OBJParser();
    OBJParser(char * path);
	virtual ~OBJParser();
};

#endif /* OBJPARSER_H_ */
