/*
 * GroupDetector.cpp
 *
 *  Created on: Apr 10, 2017
 *      Author: paco
 */

#include "GroupDetector.h"
#include "utils.h"
#include "ofMain.h"

GroupDetector::GroupDetector(Population* pop): _population(pop) {
}

GroupDetector::~GroupDetector() {
	// TODO Auto-generated destructor stub
}

void GroupDetector::detect() {
	checkExistingFormation();

	// Init create 1 formation for each agent
	for(unsigned int i = 0; i < _population->getAgents().size(); i++){
		if(!this->_population->isGrouped(this->_population->getAgents()[i])){
			ofLogNotice("GroupDetector::detect") << "Initialized formation for Agent#" << _population->getAgents()[i]->getId();
			Formation* f = new Formation(this->_population->getAgents()[i], formationId);
			formationId++;
			_population->pushFormation(f);
		}
	}

	for(unsigned int i = 0; i < _population->getAgents().size()-1; i++){
		std::vector<Agent*> agents = _population->getAgents();
		// Remove processed agent from vector
		agents.erase(std::remove(agents.begin(), agents.end(), _population->getAgents()[i]), agents.end());

		for(unsigned int j = 0; j < _population->getAgents().size(); j++){
			Agent * neighbor =  _population->getAgents()[i]->findNearestNeighbor(agents);

			// If nearest neighbor is too far, abort grouping for agent[i]
			if(distance(_population->getAgents()[i]->getPosition(), neighbor->getPosition()) > maxDistanceThreshold)
				break;

			// if Agents are already grouped, skip
			if(_population->getRelatedFormation(_population->getAgents()[i]) != _population->getRelatedFormation(neighbor)){

				// Check if FOV intersect
				if(_population->getAgents()[i]->getFOVIntersection(neighbor)){
					//add neighbor to formation
					ofLogNotice("GroupDetector::detect") << "Detected neighbor#" << neighbor->getId() << " for Agent#" << _population->getAgents()[i]->getId();
					_population->removeFormation(_population->getRelatedFormation(neighbor)->getId());
					_population->getRelatedFormation(_population->getAgents()[i])->pushAgent(neighbor);

					ofLogNotice("GroupDetector::detect") << "Formation#"
							<< _population->getRelatedFormation(_population->getAgents()[i])->getId()
							<< " size=" << _population->getRelatedFormation(_population->getAgents()[i])->getAgents().size();
				}

			}

			// Remove processed agent
			agents.erase(std::remove(agents.begin(), agents.end(), neighbor), agents.end());
			if(agents.size() == 0){
				break;
			}
		}
	}

	// Clear alone formation
	for(unsigned int i = 0; i < _population->getFormations().size(); i++){
		if(_population->getFormations()[i]->getAgents().size() <= 1){
			ofLogNotice("GroupDetector::detect") << "Removed alone Formation#" << _population->getFormations()[i]->getId();
			_population->removeFormation(_population->getFormations()[i]->getId());
		}
	}


}

void GroupDetector::checkExistingFormation() {
	for(unsigned int i = 0; i < _population->getFormations().size(); i++){
		// Find agent in range from formation
		for(unsigned int k = 0; k < _population->getAgents().size(); k++){
			if(_population->getFormations()[i] == _population->getRelatedFormation(_population->getAgents()[k])){
				// Agent k is already in formation, skip
				continue;
			}


			for(unsigned int l = 0; l < _population->getFormations()[i]->getAgents().size(); l++){
				// Is Agent k in range from formation i
				if(distance(_population->getAgents()[k]->getPosition(), _population->getFormations()[i]->getAgents()[l]->getPosition()) < maxDistanceThreshold){
					// Find agent k FOV intersection with one agent in formation i
					if(_population->getAgents()[k]->getFOVIntersection(_population->getFormations()[i]->getAgents()[l])){
						// match, group agent k in formation i
						_population->getFormations()[i]->pushAgent(_population->getAgents()[k]);
						break;
					}
				}
			}
		}

		for(unsigned int j = 0; j < _population->getFormations()[i]->getAgents().size(); j++){
			if(distance(_population->getFormations()[i]->getAgents()[j]->getPosition(), _population->getFormations()[i]->getSocialSpace()->getCenter()) > maxDistanceThreshold){
				// Agent is too far from formation center, remove
				ofLogNotice("GroupDetector::checkExistingFormation")
						<< "Removed Agent#" << _population->getFormations()[i]->getAgents()[j]->getId()
						<< " from Formation#" << _population->getFormations()[i]->getId();
				_population->getFormations()[i]->removeAgent(_population->getFormations()[i]->getAgents()[j]->getId());
				// Decrement index
				j--;

				// Check if formation is empty
				if(_population->getFormations()[i]->getAgents().size() == 0){
					ofLogNotice("GroupDetector::checkExistingFormation") << "Formation#" << _population->getFormations()[i]->getId() << " removed";
					_population->removeFormation(_population->getFormations()[i]->getId());
					i--;
				}
			}
		}
	}
}
