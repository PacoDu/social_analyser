/**
 * @file World.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 29 mars 2017
 */

#include "World.h"

#if USE_OFX
	#include "ofMain.h"
#endif

World::World(double w, double h, int wv, int hv, Vector3d position, double theta):
		DrawnObject(position,theta), width(w), height(h), widthView(wv), heightView(hv){
}

World::~World() {
	// TODO Auto-generated destructor stub
}

#if USE_OFX
void World::draw(World* world) {
	// TODO dirty
	this->draw();
}

void World::draw(){
	ofNoFill();
	ofDrawRectangle(this->getX(), this->getY(), this->widthView, this->heightView);
	ofFill();
}
#endif

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
