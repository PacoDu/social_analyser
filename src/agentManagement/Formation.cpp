/*
 * Formation.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

// TODO Merge constructor (e.i. lower constructor call the highest with default param)
#include "Formation.h"

// --- CONSTRUCTOR & DESTRUCTOR
Formation::Formation(std::vector<Agent*> a , Vector3d p,
		double theta, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer(a){
	_socialSpace = new OSpace(a);
}

Formation::Formation(Vector3d p, double theta, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer(){
	_socialSpace = NULL; // TODO init empty OSpace ?
}

Formation::~Formation() {
	if(_socialSpace) delete _socialSpace;
}

// --- METHOD
void Formation::draw(World* world) {
	_socialSpace->draw(world);
}

void Formation::pushAgent(Agent* a) {
	AgentContainer::pushAgent(a);
	this->_socialSpace->pushAgent(a);
	this->_socialSpace->update();
}

// Getters & Setters
OSpace* Formation::getSocialSpace() const {
	return _socialSpace;
}

void Formation::setSocialSpace(OSpace* socialSpace) {
	_socialSpace = socialSpace;
}
