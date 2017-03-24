/*
 * Population.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Population.h"

Population::Population() {
	// TODO Auto-generated constructor stub

}

Population::~Population() {
	for(unsigned int i=0; i<_population.size(); i++){
		delete _population[i];
	}
}

void Population::draw(int x, int y) {
	ofSetHexColor(0x00FF00);
	std::stringstream ss;

	for(unsigned int i=0; i<_population.size(); i++){
		ss << "Person #" << _population[i]->getId()
				<< ": x = " << _population[i]->getX()
				<< ", y = " << _population[i]->getY()
				<< ", Theta = " << _population[i]->getTheta()
				<< ", Theta (degres) = " << ofRadToDeg(_population[i]->getTheta()) << std::endl;

		ofPushMatrix();
			ofSetHexColor(0x6497b1);
			ofTranslate(x+_population[i]->getX(), y+_population[i]->getY());
			ofRotateZ(ofRadToDeg(_population[i]->getTheta()));

			ofDrawBitmapString("#"+ofToString(_population[i]->getId()), -10, -20);
			ofDrawTriangle(0, 10, 25, 0, 0, -10);

			ofSetHexColor(0x011f4b);
			ofDrawCircle(0,0,5);

			ofSetHexColor(0xFF0000);
			ofDrawLine(0,0, 150,0);
		ofPopMatrix();
	}

	ofSetHexColor(0x2C291F);
	ofDrawBitmapString(ss.str(), 10, 14);
}

void Population::push(Person* p) {
	this->_population.push_back(p);
}

void Population::clear() {
	for(unsigned int i=0; i<_population.size(); i++){
		delete _population[i];
	}

	this->_population.clear();

	for(unsigned int i=0; i<_formations.size(); i++){
		delete _formations[i];
	}

	this->_formations.clear();

	ofLogNotice("Population cleared");
}

ofVec2f Population::getBoundX() {
	double x_max = -INFINITY;
	double x_min = INFINITY;


	for(unsigned int i=0; i<_population.size(); i++){
		if(x_max < _population[i]->getX()) x_max = _population[i]->getX();
		if(x_min > _population[i]->getX()) x_min = _population[i]->getX();

	}

	return ofVec2f(x_min,x_max);
}

ofVec2f Population::getBoundY() {
	double y_max = -INFINITY;
	double y_min = INFINITY;

	for(unsigned int i=0; i<_population.size(); i++){
		if(y_max < _population[i]->getY()) y_max = _population[i]->getY();
		if(y_min > _population[i]->getY()) y_min = _population[i]->getY();
	}

	return ofVec2f(y_min, y_max);
}

void Population::addFormation(std::vector<Person*> p) {
	_formations.push_back(new Formation(p));
}
