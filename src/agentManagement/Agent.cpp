/*
 * Person.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Agent.h"
#include "GaussianSpace.h"
#include "Formation.h"
#include <limits>
#include "utils.h"
#include "ofMain.h"

// --- CONSTRUCTOR & DESTRUCTOR
Agent::Agent(Vector3d p, double theta, int id):
		IdentifiedObject(id), DrawnObject(p,theta) {

	pSocialSpace = new GaussianSpace(this);
}

Agent::~Agent() {
	delete this->pSocialSpace;
}

// --- METHOD
void Agent::draw(World * world) {
	Vector3d pView = real_to_pixel(world, this->getPosition());
	ofPushMatrix();
		ofSetHexColor(0x6497b1);
		ofTranslate(pView.x(), pView.y());
		ofRotateZ(ofRadToDeg(this->getTheta()));

		ofDrawBitmapString("#"+ofToString(this->getId()), -10, -20);
		ofDrawTriangle(0, 10, 25, 0, 0, -10);

		ofSetHexColor(0x011f4b);
		ofDrawCircle(0,0,5);
	ofPopMatrix();
}

Agent* Agent::findNearestNeighbor(std::vector<Agent*> agents) {
	// TODO use kd tree ?
	double min_distance = std::numeric_limits<double>::infinity();
	Agent * a;
	for(unsigned int i = 0; i < agents.size(); i++){
		if(agents[i]->getId() != this->getId()){
			double computedDist = distance(this->position, agents[i]->getPosition());
			if(computedDist < min_distance){
				min_distance = computedDist;
				a = agents[i];
			}
		}
	}
	return a;
}

// --- Getter & Setter
GaussianSpace* Agent::getSocialSpace() const {
	return pSocialSpace;
}

void Agent::setSocialSpace(GaussianSpace* socialSpace) {
	pSocialSpace = socialSpace;
}
