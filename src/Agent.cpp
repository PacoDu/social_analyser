/*
 * Person.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Agent.h"
#include "PersonnalSocialSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
Agent::Agent(Point p, double theta, int id):
		IdentifiedObject(id), DrawnObject(p,theta) {
	// Warning pSocialSpace is not initialized
}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}


// --- METHOD
ofVec2f Agent::getDirection() {
	ofVec2f v = ofVec2f(1.0f, 0.0f);
	v.rotate(ofRadToDeg(this->theta));

	return v;
}

void Agent::draw(World * world) {
	Point pView = real_to_pixel(world, this->getPosition());
	ofPushMatrix();
		ofSetHexColor(0x6497b1);
		ofTranslate(pView.x, pView.y);
		ofRotateZ(ofRadToDeg(this->getTheta()));

		ofDrawBitmapString("#"+ofToString(this->getId()), -10, -20);
		ofDrawTriangle(0, 10, 25, 0, 0, -10);

		ofSetHexColor(0x011f4b);
		ofDrawCircle(0,0,5);
	ofPopMatrix();
}

//void Agent::draw(bool drawSocialSpace, double x, double y){
//	this->draw(x,y);
//	if(drawSocialSpace){
//		this->dra
//	}
//}

// --- Getter & Setter
PersonnalSocialSpace* Agent::getSocialSpace() const {
return pSocialSpace;
}

void Agent::setSocialSpace(PersonnalSocialSpace* socialSpace) {
pSocialSpace = socialSpace;
}
