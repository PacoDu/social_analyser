/*
 * Person.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Agent.h"

Agent::Agent(int id): IdentifiedObject(id), DrawnObject(0,0) {
	this->theta = 0;
}

Agent::Agent(int id, double x, double y, double theta):
		IdentifiedObject(id), DrawnObject(x,y), theta(theta) {
}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}

ofVec2f Agent::getPosition() {
	return ofVec2f(this->x, this->y);
}

ofVec2f Agent::getDirection() {
	ofVec2f v = ofVec2f(1.0f, 0.0f);
	v.rotate(ofRadToDeg(this->theta));

	return v;
}

void Agent::draw(double x, double y) {
	ofPushMatrix();
		ofSetHexColor(0x6497b1);
		ofTranslate(x+this->getX(), y+this->getY());
		ofRotateZ(ofRadToDeg(this->getTheta()));

		ofDrawBitmapString("#"+ofToString(this->getId()), -10, -20);
		ofDrawTriangle(0, 10, 25, 0, 0, -10);

		ofSetHexColor(0x011f4b);
		ofDrawCircle(0,0,5);

//		ofSetHexColor(0xFF0000);
//		ofDrawLine(0,0, 150,0);
	ofPopMatrix();
}
