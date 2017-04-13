/*
 * Formation.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

// TODO Merge constructor (e.i. lower constructor call the highest with default param)
#include "Formation.h"
#include "ofMain.h"

// --- CONSTRUCTOR & DESTRUCTOR
Formation::Formation(std::vector<Agent*> a , int id):
		IdentifiedObject(id), AgentContainer(a){
	_socialSpace = new OSpace(a);
}

Formation::Formation(int id): IdentifiedObject(id), AgentContainer(){
	_socialSpace = NULL; // TODO init empty OSpace ?
}

Formation::Formation(Agent* a, int id):
		Formation(initAgent(a), id){
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

	if(!this->_socialSpace)
		this->_socialSpace = new OSpace(this->_agents);
	else
		this->_socialSpace->pushAgent(a);

//	this->_socialSpace->update();
}

void Formation::removeAgent(unsigned int agentId) {
	AgentContainer::removeAgent(agentId);

	this->_socialSpace->removeAgent(agentId);

//	this->_socialSpace->update();
}

void Formation::update() {
	ofLogNotice("Formation::update") << "Updating social space for Formation#" << this->getId();
	this->_socialSpace->update();
}

void Formation::computeInteractionPotential() {
	double meanInterPersoDist = 0;
	double meanCenterDist = 0;

	// Mean interpersonnal distance
	for(unsigned int i = 0; i < this->_agents.size(); i++){
		unsigned int neighborIndex = i+1;
		if(neighborIndex >= this->_agents.size()) neighborIndex = 0;

		meanInterPersoDist += distance(this->_agents[i]->getPosition(), this->_agents[neighborIndex]->getPosition());
		meanCenterDist += distance(this->_agents[i]->getPosition(), this->_socialSpace->getCenter());
	}

	meanInterPersoDist /= this->_agents.size();
	meanCenterDist /= this->_agents.size();

	interactionPotential = meanInterPersoDist + meanCenterDist;
}

int Formation::isInFormation(unsigned int agentId) {
	if(this->getAgent(agentId)){
		return 1;
	}
	else{
		return 0;
	}
}

int Formation::isInFormation(Agent* a) {
	return this->isInFormation(a->getId());
}

std::vector<Agent*> Formation::initAgent(Agent* a) {
	std::vector<Agent *> av;
	av.push_back(a);
	return av;
}

// Getters & Setters
OSpace* Formation::getSocialSpace() const {
	return _socialSpace;
}

void Formation::setSocialSpace(OSpace* socialSpace) {
	_socialSpace = socialSpace;
}

