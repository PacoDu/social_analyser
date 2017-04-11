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

class Formation;
class GaussianSpace;

class Agent: public IdentifiedObject, public DrawnObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Agent(World* world, Point p = Point(), double theta=0, int id=0);
	~Agent();

	// --- METHOD
	ofVec2f getDirection();
	Agent * findNearestNeighbor(std::vector<Agent*> agents);

	void draw(World * world, bool drawPersonnalSocialSpace);
	void draw(World* world);
	GaussianSpace* getSocialSpace();
	void setSocialSpace(GaussianSpace* socialSpace);
	Formation* getFormation() const;
	void setFormation(Formation* formation);
	void deleteFormation();
	// --- Getter & Setter

protected:
	GaussianSpace* pSocialSpace;
	Formation* formation;

};

#endif /* SRC_AGENT_H_ */
