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
	// TODO Auto-generated constructor stub

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
    rpm = strtof(token.c_str(),NULL);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    speed = strtof(token.c_str(),NULL);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    engineThrottle = strtof(token.c_str(),NULL);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    airIntakeTemp = strtof(token.c_str(),NULL);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    engineCoolantTemp = strtof(token.c_str(),NULL);

    std::getline(ss, token, ',');
    std::cout << token << '\n';
    manifoldABS = strtof(token.c_str(),NULL);

    close(sockfd);
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
