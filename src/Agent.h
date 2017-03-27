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

class Agent: public IdentifiedObject, public DrawnObject {
public:
	Agent(int id);
	Agent(int id, double x, double y, double theta);
	~Agent();

	ofVec2f getPosition();
	ofVec2f getDirection();

	void draw(double x, double y);

	// Getters & Setters
	double getTheta() const {
		return theta;
	}

	void setTheta(double theta) {
		this->theta = theta;
	}

protected:
	double theta;

};

#endif /* SRC_AGENT_H_ */
