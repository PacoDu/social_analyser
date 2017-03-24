/*
 * Person.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Person.h"

Person::Person(int id): id(id) {
	this->x = 0;
	this->y = 0;
	this->theta = 0;
}

Person::Person(int id, double x, double y, double theta):
		id(id), x(x), y(y), theta(theta) {
}

Person::~Person() {
	// TODO Auto-generated destructor stub
}

ofVec2f Person::getPosition() {
	return ofVec2f(this->x, this->y);
}

ofVec2f Person::getDirection() {
	ofVec2f v = this->getPosition();
	v.rotate(ofRadToDeg(this->theta));

	return v;
}

// --------- GETTER - SETTER ----------

int Person::getId() const {
	return id;
}

void Person::setId(int id) {
this->id = id;
}

double Person::getX() const {
return x;
}

void Person::setX(double x) {
this->x = x;
}

double Person::getY() const {
return y;
}

void Person::setY(double y) {
this->y = y;
}

double Person::getTheta() const {
	return theta;
}

void Person::setTheta(double theta) {
	this->theta = theta;
}
