/*
 * World.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "World.h"
#include "ofMain.h"

World::World(double w, double h, int wv, int hv, Vector3d position, double theta):
		DrawnObject(position,theta), width(w), height(h), widthView(wv), heightView(hv){
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::draw(World* world) {
	// TODO dirty
	this->draw();
}

void World::draw(){
	ofNoFill();
	ofDrawRectangle(this->getX(), this->getY(), this->widthView, this->heightView);
	ofFill();
}

double World::getHeight() const {
	return height;
}

void World::setHeight(double height) {
	this->height = height;
}

double World::getHeightView() const {
	return heightView;
}

void World::setHeightView(double heightView) {
	this->heightView = heightView;
}

double World::getWidth() const {
	return width;
}

void World::setWidth(double width) {
	this->width = width;
}

double World::getWidthView() const {
	return widthView;
}

void World::setWidthView(double widthView) {
	this->widthView = widthView;
}
