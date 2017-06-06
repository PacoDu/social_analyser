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
	double shoulderLength = real_to_pixel(world, Vector3d(0,0.45,0)).y() - world->getPosition().y();
	double headRadius = real_to_pixel(world, Vector3d(0.16,0,0)).x() - world->getPosition().x();
	ofPushMatrix();
		ofSetHexColor(0x6497b1);
		ofTranslate(pView.x(), pView.y());
		ofRotateZ(ofRadToDeg(this->getTheta()));

		ofSetHexColor(0xFF0000);
		ofDrawBitmapString("#"+ofToString(this->getId()), -shoulderLength/2, -shoulderLength/2);

		ofSetHexColor(0x6497b1);
		ofDrawTriangle(0, shoulderLength/2, shoulderLength, 0, 0, -shoulderLength/2);

//		ofSetHexColor(0x011f4b);
		ofSetHexColor(0xEEEEEE);
		ofDrawCircle(0,0,headRadius);
		ofSetHexColor(0xFF0000);
		ofDrawCircle(0,0,1);
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

Vector3d* Agent::getFOVIntersection(Agent* a) {
	// Return FOV intersection point or NULL if
	Vector3d* intersec = rayIntersectionPoint(this->getPosition(), this->getDirection(), a->getPosition(), a->getDirection());
	if(!intersec){
		// Agents are parallels or do not intersect
		if(fmod(a->getTheta()+M_PI,2*M_PI) == this->getTheta()){
			// Agents are face to face return middle point
			intersec = new Vector3d((this->getPosition()+a->getPosition())/2);
		}
	}

	return intersec;
}

// --- Getter & Setter
GaussianSpace* Agent::getSocialSpace() const {
	return pSocialSpace;
}

void Agent::setSocialSpace(GaussianSpace* socialSpace) {
	pSocialSpace = socialSpace;
}
