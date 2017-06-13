/**
 * @file AgentContainer.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 27 mars 2017
 */

#include "AgentContainer.h"

// --- CONSTRUCTOR & DESTRUCTOR
AgentContainer::AgentContainer() {
}

AgentContainer::AgentContainer(std::vector<Agent*>& agents) {
	_agents = agents;
}

AgentContainer::~AgentContainer() {
}

// --- METHOD
int AgentContainer::removeAgent(unsigned int agentId) {
	for(unsigned int i=0; i<_agents.size(); i++){
		if(_agents[i]->getId() == agentId) {
			_agents.erase(_agents.begin()+i);
			return 0;
		}
	}

	return -1;
}

void AgentContainer::pushAgent(Agent* p) {
	this->_agents.push_back(p);
}

Agent* AgentContainer::getAgent(unsigned int agentId) {
	for(unsigned int i=0; i<_agents.size(); i++){
		if(_agents[i]->getId() == agentId) {
			return _agents[i];
		}
	}

	return nullptr;
}

void AgentContainer::clearAgents() {
	_agents.clear();
}

// Getter & Setter
std::vector<Agent*> AgentContainer::getAgents() {
	return this->_agents;
}

void AgentContainer::setAgents(const std::vector<Agent*>& agents) {
	_agents = agents;
}
