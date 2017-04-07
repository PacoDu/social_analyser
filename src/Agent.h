/*
 * Person.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_AGENT_H_
#define SRC_AGENT_H_

#include "ofMain.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "Point.h"

class GaussianSpace;

class Agent: public IdentifiedObject, public DrawnObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Agent(World* world, Point p = Point(), double theta=0, int id=0);
	~Agent();

	// --- METHOD
	ofVec2f getDirection();

	void draw(World * world, bool drawPersonnalSocialSpace);
	void draw(World* world);
	GaussianSpace* getSocialSpace();
	void setSocialSpace(GaussianSpace* socialSpace);

	// --- Getter & Setter

protected:
	GaussianSpace* pSocialSpace;

};

#endif /* SRC_AGENT_H_ */
