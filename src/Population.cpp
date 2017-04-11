/*
 * Population.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Population.h"

// --- CONSTRUCTOR & DESTRUCTOR
Population::Population(Point p, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer() {
}

Population::Population(std::vector<Agent*> a, Point p, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer(a){
}

Population::~Population() {
	for(unsigned int i=0; i<this->_formations.size(); i++){
		delete this->_formations[i];
	}

	for(unsigned int i=0; i<this->_agents.size(); i++){
		delete this->_agents[i];
	}
}

// --- METHOD
void Population::draw(World* world) {
	std::stringstream ss;

	for(unsigned int i=0; i<_formations.size(); i++){
		ss << "Formation #" << _formations[i]->getId()
				<< ": x = " << _formations[i]->getX()
				<< ", y = " << _formations[i]->getY() << std::endl;

		_formations[i]->draw(world);
	}

	for(unsigned int i=0; i<this->_agents.size(); i++){
		ss << "Agent #" << this->_agents[i]->getId()
				<< ": x = " << this->_agents[i]->getX()
				<< ", y = " << this->_agents[i]->getY()
				<< ", Theta = " << this->_agents[i]->getTheta()
				<< ", Theta (degres) = " << ofRadToDeg(this->_agents[i]->getTheta()) << std::endl;

		this->_agents[i]->draw(world, false);
	}

	ofSetHexColor(0x2C291F);
	ofDrawBitmapString(ss.str(), world->getX(), world->getY()+world->heightView+20);
}

void Population::update(World* world){
//	for(unsigned int i=0; i<this->_agents.size(); i++){
//		GaussianSpace* c = (GaussianSpace*)this->_agents[i]->getSocialSpace();
//		c->compute(world);
//	}
//	for(unsigned int i=0; i<this->_formations.size(); i++){
//		((OSpace*)_formations[i]->getSocialSpace())->compute(world);
//	}
}

void Population::clear() {
	for(unsigned int i=0; i<this->_agents.size(); i++){
		delete this->_agents[i];
	}

	this->_agents.clear();

	for(unsigned int i=0; i<_formations.size(); i++){
		delete _formations[i];
	}

	this->_formations.clear();

	ofLogNotice("Population::clear") << "Population cleared";
}

ofVec2f Population::getBoundX() {
	double x_max = -INFINITY;
	double x_min = INFINITY;


	for(unsigned int i=0; i<this->_agents.size(); i++){
		if(x_max < this->_agents[i]->getX()) x_max = this->_agents[i]->getX();
		if(x_min > this->_agents[i]->getX()) x_min = this->_agents[i]->getX();

	}

	return ofVec2f(x_min,x_max);
}

ofVec2f Population::getBoundY() {
	double y_max = -INFINITY;
	double y_min = INFINITY;

	for(unsigned int i=0; i<this->_agents.size(); i++){
		if(y_max < this->_agents[i]->getY()) y_max = this->_agents[i]->getY();
		if(y_min > this->_agents[i]->getY()) y_min = this->_agents[i]->getY();
	}

	return ofVec2f(y_min, y_max);
}

void Population::pushFormation(Formation* f) {
	_formations.push_back(f);
}

int Population::removeFormation(unsigned int formationId) {
	for(unsigned int i=0; i<_formations.size(); i++){
		if(_formations[i]->getId() == formationId) {
			_formations.erase(_formations.begin()+i);
			return 0;
		}
	}
	return -1;
}

void Population::clearFormations() {
	_formations.clear();
}

// --- Getter & Setter
const std::vector<Formation*>& Population::getFormations() const {
	return _formations;
}

void Population::setFormations(const std::vector<Formation*>& formations) {
	_formations = formations;
}
