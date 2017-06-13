/**
 * @file Population.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 24 mars 2017
 */

#include "Population.h"

#ifdef USE_OFX
	#include "ofMain.h"
#endif

// --- CONSTRUCTOR & DESTRUCTOR
Population::Population(Vector3d p, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer() {
}

Population::Population(std::vector<Agent*> a, Vector3d p, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer(a){
}

Population::~Population() {
	for(auto * f: this->_formations){delete f;}

	for(auto * a: this->_agents){delete a;}
}

// --- METHOD
#ifdef USE_OFX
void Population::draw(World* world) {
	std::stringstream ss;

	for(auto *f : this->_formations){
		ss << "Formation #" << f->getId() << ": ";

		for(auto * a: f->getSocialSpace()->getAgents()){
			ss << "Agent#" <<  a->getId() << ", ";
		}

		ss << " interactionPotential=" << f->getInteractionPotential()	<< std::endl;

		f->draw(world);
	}

	for(auto * a: this->_agents){
		ss << "Agent #" << a->getId()
				<< ": x = " << a->getX()
				<< ", y = " << a->getY()
				<< ", Theta = " << a->getTheta()
				<< ", Theta (degres) = " << ofRadToDeg(a->getTheta()) << std::endl;

		a->draw(world);
	}

	ofSetHexColor(0x2C291F);
	ofDrawBitmapString(ss.str(), world->getX(), world->getY()+world->heightView+20);
}
#endif

void Population::clear() {
	for(auto *a: this->_agents){ delete a;}

	this->_agents.clear();

	for(auto * f: this->_formations){delete f;}

	this->_formations.clear();

	ofLogNotice("Population::clear") << "Population#" << this->getId() << " cleared";
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

int Population::isGrouped(Agent* a) {
	return this->isGrouped(a->getId());
}

int Population::isGrouped(unsigned int agentId) {
	for(auto * f: this->_formations){
		if(f->isInFormation(agentId)){
			return 1;
		}
	}
	return 0;
}

Formation* Population::getRelatedFormation(unsigned int agentId) {
	for(auto * f: this->_formations){
		if(f->isInFormation(agentId)){
			return f;
		}
	}
	return nullptr;
}

Formation* Population::getRelatedFormation(Agent* a) {
	return this->getRelatedFormation(a->getId());
}

// --- Getter & Setter
const std::vector<Formation*>& Population::getFormations() const {
	return _formations;
}

void Population::setFormations(const std::vector<Formation*>& formations) {
	_formations = formations;
}
