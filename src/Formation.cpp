/*
 * Formation.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

// TODO Merge constructor (e.i. lower constructor call the highest with default param)
#include "Formation.h"

// --- CONSTRUCTOR & DESTRUCTOR
Formation::Formation(std::vector<Agent*>& a , Point p,
		double theta, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer(a){
	_socialSpace = new OSpace(a);
}

Formation::Formation(GroupSocialSpace* sp, Point p, double theta, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer(), _socialSpace(sp){
}

Formation::Formation(Point p, double theta, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer(){
}

Formation::~Formation() {
	// TODO Auto-generated destructor stub

}

// --- METHOD
void Formation::draw(World* world) {
	_socialSpace->draw(world);
}

void Formation::computeSocialSpace() {
	// TODO Addapt to gaussian social space and enable auto compute for each agent
	// Compute center of O-Space (means between agents)
	double x = 0;
	double y = 0;
	for(unsigned int i=0; i < _agents.size(); i++){
		x += _agents[i]->getX();
		y += _agents[i]->getY();
	}

	x /= _agents.size();
	y /= _agents.size();

	ofPoint ospace_center = ofPoint(x,y);

	// Compute mean distance from OSpace
	double mean_dist = 0;

	for(unsigned int i=0; i < _agents.size(); i++){
		ofPoint agent = ofPoint(_agents[i]->getX(), _agents[i]->getY());

		mean_dist += agent.distance(ospace_center);
	}

	mean_dist /= _agents.size();

	//Set O-space
//	this->ospace->setX(ospace_center.x);
//	this->ospace->setY(ospace_center.y);
//
//	this->pspace->setX(ospace_center.x);
//	this->pspace->setY(ospace_center.y);
//
//	this->ospace->setRadius(mean_dist-10);
//	this->pspace->setInnerRadius(mean_dist-10);
//	this->pspace->setOuterRadius(mean_dist-10+30);

	ofLogNotice("Formation::computeSocialSpace") << "Social space computed for Formation#" << this->getId() << " O(" << x << "," << y << ").";
}

// Getters & Setters

