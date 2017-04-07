/*
 * GridCell.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#include "GridCell.h"

GridCell::GridCell(double size, int id, Point p, double value):
	IdentifiedObject(id), DrawnObject(p), _size(size), _value(value) {
	assert(value <= 255 && value >= 0);
}

GridCell::~GridCell() {
	// TODO Auto-generated destructor stub
}

double GridCell::getValue() const {
	return _value;
}

void GridCell::draw(World* world) {
	Point pView = real_to_pixel(world, this->getPosition());
	Point sView = real_to_pixel(world, Point(this->getPosition().x+this->_size, 0));

	ofPushMatrix();
		ofTranslate(pView.x, pView.y);
		ofRotateZ(ofRadToDeg(this->getTheta()));
		ofSetColor((int)_value,(int)_value, (int)_value);
		ofFill();
		ofDrawRectangle(0,0, sView.x-pView.x, sView.x-pView.x);
//		ofSetColor(255, 255, 255);
//		ofNoFill();
//		ofSetLineWidth(0.05);
//		ofDrawRectangle(0,0, sView.x-pView.x, sView.x-pView.x);
	ofPopMatrix();
}

void GridCell::setValue(double value) {
	_value = value;
}

double GridCell::getSize() const {
	return _size;
}

void GridCell::setSize(double size) {
	_size = size;
}
