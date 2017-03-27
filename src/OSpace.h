/*
 * OSpace.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_OSPACE_H_
#define SRC_OSPACE_H_

#include "SocialSpace.h"

class OSpace: public SocialSpace {
public:
	OSpace(double radius);
	OSpace(int id, double radius);
	OSpace(double x, double y, double radius);
	OSpace(int id, double x, double y, double radius);

	OSpace(double radius, std::vector<Agent*>& a);
	OSpace(int id, double radius, std::vector<Agent*>& a);
	OSpace(int id, double x, double y, double radius, std::vector<Agent*>& a);
	OSpace(double x, double y, double radius, std::vector<Agent*>& a);

	~OSpace();

	void draw(double x, double y);

	// Getters & Setters
	double getRadius() const {
		return radius;
	}

	void setRadius(double radius) {
		this->radius = radius;
	}

protected:
	double radius;

};

#endif /* SRC_OSPACE_H_ */
