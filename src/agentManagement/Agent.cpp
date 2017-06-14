/**
 * @file Agent.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 24 mars 2017
 */

#include "Agent.h"
#include "GaussianSpace.h"
#include "Formation.h"
#include <limits>
#include "utils.h"

#if USE_OFX
	#include "ofMain.h"
#endif

// --- CONSTRUCTOR & DESTRUCTOR
Agent::Agent(Vector3d position, double theta, int id):
		IdentifiedObject(id), DrawnObject(position,theta) {

	pSocialSpace = new GaussianSpace(this);
}

Agent::~Agent() {
	delete this->pSocialSpace;
}

// --- METHOD
#ifdef USE_OFX
void Agent::draw(World * world) {
	// Coordinates projection
	Vector3d pView = real_to_pixel(world, this->getPosition());
	double shoulderLength = real_to_pixel(world, Vector3d(0,0.45,0)).y() - world->getPosition().y();
	double headRadius = real_to_pixel(world, Vector3d(0.16,0,0)).x() - world->getPosition().x();

	// Drawing
	ofPushMatrix();
		ofSetHexColor(0x6497b1);
		ofTranslate(pView.x(), pView.y());
		ofRotateZ(ofRadToDeg(this->getTheta()));

		ofSetHexColor(0xFF0000);
		ofDrawBitmapString("#"+ofToString(this->getId()), -shoulderLength/2, -shoulderLength/2);

		ofSetHexColor(0x6497b1);
		ofDrawTriangle(0, shoulderLength/2, shoulderLength, 0, 0, -shoulderLength/2);

		ofSetHexColor(0xEEEEEE);
		ofDrawCircle(0,0,headRadius);
		ofSetHexColor(0xFF0000);
		ofDrawCircle(0,0,1);
	ofPopMatrix();
}
#endif

Agent* Agent::findNearestNeighbor(std::vector<Agent*> agents) {
	// TODO use kd tree ?

	double min_distance = std::numeric_limits<double>::infinity();
	Agent * nearestNeighbor;

	for(auto * a: agents){
		if(a->getId() != this->getId()){
			double computedDist = distance(this->position, a->getPosition());
			if(computedDist < min_distance){
				min_distance = computedDist;
				nearestNeighbor = a;
			}
		}
	}

	return nearestNeighbor;
}

Vector3d* Agent::getFOVIntersection(Agent* agent) {
	// Return FOV intersection point or NULL if
	Vector3d* intersec = rayIntersectionPoint(this->getPosition(), this->getDirection(), agent->getPosition(), agent->getDirection());
	if(!intersec){
		// Agents are parallels or do not intersect
		if(fmod(agent->getTheta()+M_PI,2*M_PI) == this->getTheta()){
			// Agents are face to face return middle point
			intersec = new Vector3d((this->getPosition()+agent->getPosition())/2);
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
