/*
 * DrawnObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "DrawnObject.h"

// --- CONSTRUCTOR & DESTRUCTOR
DrawnObject::DrawnObject(double x, double y, double theta):
		LocalizedObject(x,y,theta) {
	node = new ofNode();
	node->setPosition(x,y, 0);
}

DrawnObject::~DrawnObject() {
}

// --- METHOD
int DrawnObject::real_to_pixel(World* world, double x) {
	ofMap(x, world->, x_max, 0, world->width)
}

double DrawnObject::pixel_to_real(World* world, int x, int x_min, int x_max) {
}

// --- Getter & Setter
ofNode* DrawnObject::getNode() const {
	return node;
}

void DrawnObject::setNode(ofNode* node) {
	this->node = node;
}

void DrawnObject::setX(double x){
	this-> x = x;
	this->node->setPosition(x,this->node->getPosition().y, this->node->getPosition().z);
}

void DrawnObject::setY(double y){
	this-> y = y;
	this->node->setPosition(this->node->getPosition().x, y, this->node->getPosition().z);
}
