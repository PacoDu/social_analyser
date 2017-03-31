/*
 * OSpace.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_OSPACE_H_
#define SRC_OSPACE_H_

#include "GroupSocialSpace.h"

class OSpace: public GroupSocialSpace {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	OSpace(double radius, Point p = Point(), int id = 0);
	OSpace(std::vector<Agent*>& a, Point p = Point(), int id = 0);
	~OSpace();

	// --- METHOD
	void draw(World* world);

	// Getter & Setter
	double getRadius() const;
	void setRadius(double radius);

protected:
	double radius;

};

#endif /* SRC_OSPACE_H_ */
