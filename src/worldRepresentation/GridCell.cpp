/*
 * GridCell.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#include "GridCell.h"
#include "ofMain.h"

GridCell::GridCell(double size, double value, Vector3d p, int id):
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
	Vector3d pView = real_to_pixel(world, this->getPosition());
	Vector3d sView = real_to_pixel(world, Vector3d(this->getX()+this->_size, 0, 0));

	ofPushMatrix();
		ofTranslate(pView.x(), pView.y());
		ofRotateZ(ofRadToDeg(this->getTheta()));
		if(isGoal())
			ofSetColor(255,255,0);
		else if(isStart())
			ofSetColor(0,255,255);
		else if(isCellSelected())
			ofSetColor(0, 255, 0);
		else if(isProcessed())
			ofSetColor(150,150,150);
		else if(isFrontier())
			ofSetColor(255,0,0);
		else
			ofSetColor((int)_value,(int)_value, (int)_value);

		ofFill();
		ofDrawRectangle(0,0, sView.x()-pView.x(), sView.x()-pView.x());
		ofSetColor(255, 255, 255);
		if(isBorderEnabled()){
			ofNoFill();
			ofSetLineWidth(0.01);
			ofDrawRectangle(0,0, sView.x()-pView.x(), sView.x()-pView.x());
			ofFill();
		}
		if(isInfoEnabled())
			ofDrawBitmapString("#"+ofToString(this->getId()), 5, 20);
	ofPopMatrix();

	if(isInfoEnabled()){
		pView = real_to_pixel(world, Vector3d(this->getX()+this->_size/2, this->getY()+this->_size/2, 0));
		ofPushMatrix();
			ofTranslate(pView.x(), pView.y());
			ofDrawBitmapString("A*:"+ofToString(this->_aStarScore), -20, 0);
			ofDrawBitmapString("v:"+ofToString(this->_value), -20, 15);
		ofPopMatrix();
	}

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

bool GridCell::isBorderEnabled() const {
	return borderEnabled;
}

void GridCell::setBorderEnabled(bool borderEnabled) {
	this->borderEnabled = borderEnabled;
}

double GridCell::getAStarScore() const {
	return _aStarScore;
}

void GridCell::setAStarScore(int starScore) {
	_aStarScore = starScore;
}

bool GridCell::isCellSelected() const {
	return cellSelected;
}

void GridCell::setCellSelected(bool cellSelected) {
	this->cellSelected = cellSelected;
}

bool GridCell::isFrontier() const {
	return frontier;
}

void GridCell::setFrontier(bool frontier) {
	this->frontier = frontier;
}

bool GridCell::isProcessed() const {
	return processed;
}

void GridCell::setProcessed(bool processed) {
	this->processed = processed;
}

bool GridCell::isGoal() const {
	return goal;
}

void GridCell::setGoal(bool goal) {
	this->goal = goal;
}

bool GridCell::isStart() const {
	return start;
}

void GridCell::setStart(bool start) {
	this->start = start;
}

double GridCell::getStarScore() const {
	return _aStarScore;
}

void GridCell::setStarScore(double starScore) {
	_aStarScore = starScore;
}

bool GridCell::isInfoEnabled() const {
	return infoEnabled;
}

void GridCell::setInfoEnabled(bool infoEnabled) {
	this->infoEnabled = infoEnabled;
}
