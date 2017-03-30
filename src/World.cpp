/*
 * World.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "World.h"

World::World(double w, double h, int wv, int hv, double x, double y, double theta):
		DrawnObject(x,y,theta), width(w), height(h), widthView(wv), heightView(hv){
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::draw() {
	ofNoFill();
	ofDrawRectangle(this->x, this->y, this->width, this->height);
	ofFill();
}
