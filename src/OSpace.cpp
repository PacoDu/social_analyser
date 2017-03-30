/*
 * OSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "OSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
OSpace::OSpace(double radius, std::vector<Agent*>& a , double x, double y, int id):
		GroupSocialSpace(a, x, y, id), radius(radius){
}

OSpace::OSpace(double radius, double x, double y, int id):
		GroupSocialSpace(x,y,id), radius(radius){
}

OSpace::~OSpace() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
void OSpace::draw(double x, double y) {
	ofPushMatrix();
		ofSetHexColor(0xd896ff);
		ofTranslate(x+this->getX(), y+this->getY());

		ofDrawCircle(0, 0, this->getRadius());

	ofPopMatrix();
}

// Getter & Setter
double OSpace::getRadius() const {
	return radius;
}

void OSpace::setRadius(double radius) {
	this->radius = radius;
}
