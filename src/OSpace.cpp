/*
 * OSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "OSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
OSpace::OSpace(std::vector<Agent*>& a , Point p, int id):
		GroupSocialSpace(a, p, id){
	this->setX(a[0]->getX());
	this->setY(a[0]->getY());
}

OSpace::OSpace(double radius, Point p, int id):
		GroupSocialSpace(p,id), radius(radius){
}

OSpace::~OSpace() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
// TODO:
// - order agents vector clockwise
// - compute ospace center (C)
// - phi gaussian representation of ospace knowing C
// - compute social map
// - draw social map

void OSpace::draw(World* world) {
	Point pView = real_to_pixel(world, this->getPosition());
	ofPushMatrix();
		ofSetHexColor(0xd896ff);
		ofTranslate(pView.x, pView.y);

		ofDrawCircle(0, 0, 5);

	ofPopMatrix();
}

// Getter & Setter
double OSpace::getRadius() const {
	return radius;
}

void OSpace::setRadius(double radius) {
	this->radius = radius;
}
