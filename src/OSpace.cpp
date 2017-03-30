/*
 * OSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "OSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
OSpace::OSpace(double radius, std::vector<Agent*>& a , Point p, int id):
		GroupSocialSpace(a, p, id), radius(radius){
}

OSpace::OSpace(double radius, Point p, int id):
		GroupSocialSpace(p,id), radius(radius){
}

OSpace::~OSpace() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
void OSpace::draw(World* world) {
//	ofPushMatrix();
//		ofSetHexColor(0xd896ff);
//		ofTranslate(x+this->getX(), y+this->getY());
//
//		ofDrawCircle(0, 0, this->getRadius());
//
//	ofPopMatrix();
}

// Getter & Setter
double OSpace::getRadius() const {
	return radius;
}

void OSpace::setRadius(double radius) {
	this->radius = radius;
}
