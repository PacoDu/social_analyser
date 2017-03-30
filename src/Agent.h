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

class PersonnalSocialSpace;

class Agent: public IdentifiedObject, public DrawnObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Agent(Point p = Point(), double theta=0, int id=0);
	~Agent();

	// --- METHOD
	ofVec2f getDirection();

	void draw(World* world, Point p = Point());

	// --- Getter & Setter
	PersonnalSocialSpace* getSocialSpace() const;
	void setSocialSpace(PersonnalSocialSpace* socialSpace);

protected:
	PersonnalSocialSpace* pSocialSpace;

};

#endif /* SRC_AGENT_H_ */
