/*
 * DataController.cpp
 *
 *  Created on: Jan 29, 2017
 *      Author: matt
 */

#include "DataController.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sstream>
#include <string>

void error(const char *msg);

DataController::DataController() {
	UpdateAccel();
	rollOffset = -roll;
	pitchOffset = -pitch;
	myOffset = -my;
	mxOffset = -mx;

}

DataController::~DataController() {
	// TODO Auto-generated destructor stub
}

void DataController::UpdateOBD(){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char * buffer = "request\0";
    portno = 4001;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    printf("Please enter the message: ");
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");
    char receiveBuffer[256];
    bzero(receiveBuffer,256);
    n = read(sockfd,receiveBuffer,255);
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n",receiveBuffer);

    std::string input = receiveBuffer;
    std::istringstream ss(input);
    std::string token;

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), "RPM: %lf", &rpm);
    std::cout << rpm;
    std::cout << "Resolved rpm as " << rpm << "\n";

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " Speed: %lf", &speed);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " Throttle: %lf", &engineThrottle);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " IntakeTemp: %lf", &airIntakeTemp );

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " EngineCoolantTemp: %lf", &engineCoolantTemp);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " ManifoldABS: %lf", &manifoldABS);

    close(sockfd);
}

void DataController::UpdateAccel(){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char * buffer = "request\0";
    portno = 4000;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("10.42.0.5");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    printf("Please enter the message: ");
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");
    char receiveBuffer[256];
    bzero(receiveBuffer,256);
    n = read(sockfd,receiveBuffer,255);
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n",receiveBuffer);

    std::string input = receiveBuffer;
    std::istringstream ss(input);
    std::string token;

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), "Roll: %lf", &roll);
    std::cout << roll;
    std::cout << "Resolved rpm as " << roll << "\n";

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " Pitch: %lf", &pitch);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " Yaw: %lf", &yaw);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " MX: %lf", &mx );

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    sscanf(token.c_str(), " MY: %lf", &my );

    roll = roll + rollOffset;
    pitch = pitch + pitchOffset;
    mx = mx + mxOffset;
    my = my + myOffset;

    close(sockfd);
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
