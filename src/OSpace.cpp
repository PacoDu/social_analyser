/*
 * OSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "OSpace.h"

OSpace::~OSpace() {
	// TODO Auto-generated destructor stub
}

OSpace::OSpace(double radius, std::vector<Agent*>& a):
		SocialSpace(a), radius(radius) {
}

OSpace::OSpace(int id, double radius, std::vector<Agent*>& a):
		SocialSpace(id, a), radius(radius){
}

OSpace::OSpace(int id, double x, double y, double radius,
		std::vector<Agent*>& a):
		SocialSpace(id, x, y, a), radius(radius){
}

OSpace::OSpace(double x, double y, double radius, std::vector<Agent*>& a):
		SocialSpace(x,y,a), radius(radius){
}

void OSpace::draw(double x, double y) {
	ofPushMatrix();
		ofSetHexColor(0xd896ff);
		ofTranslate(x+this->getX(), y+this->getY());

		ofDrawCircle(0, 0, this->getRadius());

	ofPopMatrix();
}

OSpace::OSpace(double radius):
		SocialSpace(), radius(radius) {
}

OSpace::OSpace(int id, double radius):
		SocialSpace(id), radius(radius)  {
}

OSpace::OSpace(double x, double y, double radius):
		SocialSpace(x,y), radius(radius) {
}

OSpace::OSpace(int id, double x, double y, double radius):
		SocialSpace(id, x, y), radius(radius){
}
