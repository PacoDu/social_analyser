/*
 * UDPServer.cpp
 *
 *  Created on: Apr 19, 2017
 *      Author: paco
 */

#include "UDPServer.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

using namespace Eigen;
UDPServer::UDPServer(int port, SocialPlanner * p): portNumber(port), planner(p) {
	//---- create UDP socket ----
	udpReceiveSocket = socket(PF_INET,SOCK_DGRAM,0);
	udpSendSocket = socket(PF_INET,SOCK_DGRAM,0);

	// Init myAddr struct
	myAddr.sin_family=AF_INET;
	myAddr.sin_port=htons(portNumber);
	myAddr.sin_addr.s_addr=htonl(INADDR_ANY);

	// Bind to port
	bind(udpReceiveSocket, (struct sockaddr *)&myAddr, sizeof(myAddr));

	printf("UDP Server started on port: %d\n", portNumber);
}

UDPServer::~UDPServer() {
	// TODO Auto-generated destructor stub
}

int UDPServer::do_read() {
	socklen_t len = sizeof(fromAddr);
//	printf("READING SOCKET");

	// Read 122 bytes
	int ret = recvfrom(udpReceiveSocket, &recvBuffer, recvBuffer_size, 0, (struct sockaddr *)&fromAddr, &len);

	if(ret > 0){
//		printf("Received frame type#%u from %s:%d\n",
//				recvBuffer[0], inet_ntoa(fromAddr.sin_addr), ntohs(fromAddr.sin_port));
	}else{
		printf("Socket shutdown or error while reading socket");
	}

	return ret;
}

int UDPServer::do_send(uint8_t * sendBuffer, int sendBuffer_size) {
	struct sockaddr_in toAddr;
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(portNumber);
	toAddr.sin_addr.s_addr = inet_addr(IP_UDP_CLIENT);//fromAddr.sin_addr;

	int ret = sendto(udpSendSocket, sendBuffer, sendBuffer_size, 0, (struct sockaddr *)&toAddr, sizeof(toAddr));

#ifdef ENABLE_CLIENT2
	struct sockaddr_in toAddr2;
	toAddr2.sin_family = AF_INET;
	toAddr2.sin_port = htons(portNumber);
	toAddr2.sin_addr.s_addr = inet_addr(IP_UDP_CLIENT2);//fromAddr.sin_addr;

	sendto(udpSendSocket, sendBuffer, sendBuffer_size, 0, (struct sockaddr *)&toAddr2, sizeof(toAddr2));
#endif

#ifdef ENABLE_CLIENT3
	struct sockaddr_in toAddr3;
	toAddr3.sin_family = AF_INET;
	toAddr3.sin_port = htons(portNumber);
	toAddr3.sin_addr.s_addr = inet_addr(IP_UDP_CLIENT3);//fromAddr.sin_addr;

	sendto(udpSendSocket, sendBuffer, sendBuffer_size, 0, (struct sockaddr *)&toAddr3, sizeof(toAddr3));
#endif

//	printf("Send to client: %s:%d\n", inet_ntoa(toAddr.sin_addr), toAddr.sin_port);
	return ret;
}

int UDPServer::parse() {
	// Parse buffer depending on frame type
	switch(recvBuffer[0]){
		case 0:
			return parse_frame0();
			break;
		default:
			printf("Unknown frame type: %d, parsing failed\n", recvBuffer[0]);
			return -1;
			break;

	}
}

int UDPServer::parse_frame0() {
	int n = recvBuffer[1];
//	pop->clearAgents(); // TODO update existing agents
//	pop->clearFormations();

	for(int i = 2; i < 2+n*20; i+=20){
		int id;
		float x, y, z, theta;
		int tx, ty, tz, ttheta;

		memcpy(&id, &recvBuffer[i], sizeof(id));
		tx = recvBuffer[i+4]<<24|recvBuffer[i+5]<<16|recvBuffer[i+6]<<8|recvBuffer[i+7];
		ty = recvBuffer[i+8]<<24|recvBuffer[i+9]<<16|recvBuffer[i+10]<<8|recvBuffer[i+11];
		tz = recvBuffer[i+12]<<24|recvBuffer[i+13]<<16|recvBuffer[i+14]<<8|recvBuffer[i+15];
		ttheta = recvBuffer[i+16]<<24|recvBuffer[i+17]<<16|recvBuffer[i+18]<<8|recvBuffer[i+19];
		memcpy(&x, &tx, sizeof(x));
		memcpy(&y, &ty, sizeof(y));
		memcpy(&z, &tz, sizeof(z));
		memcpy(&theta, &ttheta, sizeof(theta));

		id = ntohl(id);
//		printf("Parsed Agent#%d (%.2f,%.2f,%.2f) theta=%.2f\n", id, x, y, z, theta);


		updateOrPushAgent(id, x, y, z, theta);
	}

//	if(n>0)
//		planner->getManager()->update();

	return n;
}

// Agents position
int UDPServer::send_frame0() {
	Population * pop = planner->getManager()->getPopulation();

	uint8_t * sendBuffer;
	sendBuffer = new uint8_t[2+20*pop->getAgents().size()];

	// set Frame type
	sendBuffer[0] = 0;

	sendBuffer[1] = pop->getAgents().size();

	for(unsigned int i = 0; i < pop->getAgents().size(); i++){
		// fill frame
		float x = 0, y=0, z=0, theta=0;
		int id;
		id = (int)pop->getAgents()[i]->getId();

		x = (float)pop->getAgents()[i]->getX();
		y = (float)pop->getAgents()[i]->getY();
		z = (float)pop->getAgents()[i]->getPosition().z();
		theta = (float)pop->getAgents()[i]->getTheta();

		memcpy(&sendBuffer[2+i*20], &id, sizeof(id));
		memcpy(&sendBuffer[2+i*20+4], &x, sizeof(x));
		memcpy(&sendBuffer[2+i*20+8], &y, sizeof(y));
		memcpy(&sendBuffer[2+i*20+12], &z, sizeof(z));
		memcpy(&sendBuffer[2+i*20+16], &theta, sizeof(theta));
	}

//	ofLogNotice("UDPServer") << "Sending frame#0 n=" << pop->getAgents().size();

	do_send(sendBuffer, 2+pop->getAgents().size()*20);

	return 0;
}

//Robot position
int UDPServer::send_frame1() {
	uint8_t sendBuffer[17] = {0}; // T(Bytes) | x(float) | y(float) | theta(float) | gazeId(int)

	// set Frame type
	sendBuffer[0] = 1;

	// fill frame
	float x = 0, y=0, theta=0;
	int gazeId = -1;
	x = (float)planner->getRobot()->getX();
	y = (float)planner->getRobot()->getY();
	theta = (float)planner->getRobot()->getTheta();

	if(planner->getRobot()->gazeTarget)
		gazeId = planner->getRobot()->gazeTarget->getId();

	memcpy(&sendBuffer[1], &x, sizeof(x));
	memcpy(&sendBuffer[5], &y, sizeof(y));
	memcpy(&sendBuffer[9], &theta, sizeof(theta));
	memcpy(&sendBuffer[13], &gazeId, sizeof(gazeId));

//	printf("UDPServer: Sending frame#1 Robot position(%.2f,%.2f,%.2f)\n", x, y, theta);

	do_send(sendBuffer, 17);

	return 0;
}


//Robot Path
int UDPServer::send_frame2() {
	std::vector<GridCell*> path = planner->getRobot()->getPath();

//	std::vector<uint8_t> sendBuffer;

	uint8_t sendBuffer[5+path.size()*8];

	// Set frame type
	sendBuffer[0] = 2;

	// Set path length
	int length = path.size();
	memcpy(&sendBuffer[1], &length, sizeof(length));

	int i = 0;
	for(auto * cell: path){
		float x,y;
		x = cell->getX()+cell->getSize()/2;
		y = cell->getY()+cell->getSize()/2;

		memcpy(&sendBuffer[5+8*i], &x, sizeof(x));
		memcpy(&sendBuffer[5+4+8*i], &y, sizeof(y));
		i++;
	}

	do_send(sendBuffer, path.size()*8+5);

	return 0;
}

// Formations
int UDPServer::send_frame3() {
	Population * pop = planner->getManager()->getPopulation();

	int nForm = 0;
	int nAgents = 0;
	for(auto * f: pop->getFormations()){
		nAgents += f->getAgents().size();
		nForm += 1;
	}

	uint8_t sendBuffer[2+nForm*13+nAgents*4];

	// set Frame type
	sendBuffer[0] = 3;

	// set formation number
	sendBuffer[1] = pop->getFormations().size();

	// Fill frame
	int offset = 0;
	for(auto * f: pop->getFormations()){
		sendBuffer[2+offset] = f->getAgents().size();
		offset ++;

		for(auto * a: f->getAgents()){
			int id = a->getId();

			memcpy(&sendBuffer[2+offset], &id, sizeof(id));
			offset += 4;
		}

		float x,y,pot;
		x = f->getSocialSpace()->getCenter().x();
		y = f->getSocialSpace()->getCenter().y();
		pot = f->getInteractionPotential();
		memcpy(&sendBuffer[2+offset], &x, sizeof(x));
		offset += 4;
		memcpy(&sendBuffer[2+offset], &y, sizeof(y));
		offset += 4;
		memcpy(&sendBuffer[2+offset], &pot, sizeof(pot));
		offset += 4;
	}

//	ofLogNotice("UDPServer") << "Sending frame#3 n=" << pop->getFormations().size();

	do_send(sendBuffer, 2+offset);

	return 0;
}

void UDPServer::update() {
//		do_read();
		parse();
		this->sendAll();
}

void UDPServer::run(){
	while(1){
		this->do_read();
	}
}

void UDPServer::sendAll() {
		this->send_frame0();
		this->send_frame1();
		this->send_frame2();
		this->send_frame3();
}

std::thread UDPServer::spawn() {
	return std::thread([this] { run(); } );
}

void UDPServer::updateOrPushAgent(int id, float x, float y, float z,
		float theta) {
	Agent* a = planner->getManager()->getPopulation()->getAgent(id);
	if(a){
		a->setX(x);
		a->setY(y);
//		a->setZ(z);
		a->setTheta(theta);
	}
	else{
		a = new Agent(Vector3d(x, y, z), theta, id);
		planner->getManager()->getPopulation()->pushAgent(a);
	}
}
