/*
 * OBJParser.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: matt
 */

#include "OBJParser.h"

using namespace std;

OBJParser::OBJParser(char * path) {
	objectFile = fopen(path, "r");
	if( objectFile == NULL ){
		printf("Impossible to open the file !\n");
	}
	parseOBJ();

}

OBJParser::~OBJParser() {
	// TODO Auto-generated destructor stub
}

int OBJParser::parseOBJ(){

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(objectFile, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(objectFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(objectFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			unsigned int vertexIndex[3], normalIndex[3];
			int matches = fscanf(objectFile, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
			if (matches != 6){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

	}


	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		out_vertices.push_back(vertex);
	}


	// For each Normal of each triangle
	for( unsigned int i=0; i<normalIndices.size(); i++ ){
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		out_normals.push_back(normal);
	}

	cout << "Done parsing OBJ file!" <<endl;

	return 0;

}



void OBJParser::drawOBJ(){

	glTranslatef(x, y, z);

	glScalef(0.1,0.1,0.1);

	glPushMatrix();

	glRotatef(yaw, 0, 1, 0);
	glRotatef(roll, 1, 0, 0);
	glRotatef(pitch, 0, 0, 1);
	//glEnable( GL_LINE_SMOOTH );
	//glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );



	glLineWidth(3);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);


	for (int i = 0; i < out_vertices.size(); i+=3){
		glNormal3d(out_normals[i].x, out_normals[i].z, out_normals[i].y);
		glVertex3d(out_vertices[i].x, out_vertices[i].z, out_vertices[i].y);
		glNormal3d(out_normals[i+1].x, out_normals[i+1].z, out_normals[i+1].y);
		glVertex3d(out_vertices[i+1].x, out_vertices[i+1].z, out_vertices[i+1].y);
		glNormal3d(out_normals[i+2].x, out_normals[i+2].z, out_normals[i+2].y);
		glVertex3d(out_vertices[i+2].x, out_vertices[i+2].z, out_vertices[i+2].y);
		glColor4f(0.3, 0.3, 0.3,0.4);
	}

	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLES);


		for (int i = 0; i < out_vertices.size(); i+=3){
			glNormal3d(out_normals[i].x, out_normals[i].z, out_normals[i].y);
			glVertex3d(out_vertices[i].x, out_vertices[i].z, out_vertices[i].y);
			glNormal3d(out_normals[i+1].x, out_normals[i+1].z, out_normals[i+1].y);
			glVertex3d(out_vertices[i+1].x, out_vertices[i+1].z, out_vertices[i+1].y);
			glNormal3d(out_normals[i+2].x, out_normals[i+2].z, out_normals[i+2].y);
			glVertex3d(out_vertices[i+2].x, out_vertices[i+2].z, out_vertices[i+2].y);
			glColor4f(0.3, 0.3, 0.3,0.3);
			
			
			

		}

		glEnd();




	glPopMatrix();
	glScalef(10,10,10);
	glTranslatef(-x, -y, -z);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


}
