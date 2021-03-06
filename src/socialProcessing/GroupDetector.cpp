/**
 * @file GroupDetector.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 10 avril 2017
 */

#include "GroupDetector.h"
#include "utils.h"
#include "config.h"

GroupDetector::GroupDetector(Population* pop): _population(pop) {
}

GroupDetector::~GroupDetector() {
	// TODO Auto-generated destructor stub
}

void GroupDetector::detect() {
	checkExistingFormation();

	// Init create 1 formation for each agent
	for(auto * a: this->_population->getAgents()){
		if(!this->_population->isGrouped(a)){
//			ofLogNotice("GroupDetector::detect") << "Initialized formation for Agent#" << a->getId();
			Formation* f = new Formation(a, this->formationId);
			this->formationId++;
			this->_population->pushFormation(f);
		}
	}

	for(unsigned int i = 0; i < _population->getAgents().size()-1; i++){
		std::vector<Agent*> agents = _population->getAgents();
		// Remove processed agent from vector
		agents.erase(std::remove(agents.begin(), agents.end(), _population->getAgents()[i]), agents.end());

		for(unsigned int j = 0; j < _population->getAgents().size(); j++){
			Agent * neighbor =  _population->getAgents()[i]->findNearestNeighbor(agents);

			// If nearest neighbor is too far, abort grouping for agent[i]
			if(distance(_population->getAgents()[i]->getPosition(), neighbor->getPosition()) > GROUP_DETECTION_DISTANCE_THRESHOLD)
				break;

			// if Agents are already grouped, skip
			if(_population->getRelatedFormation(_population->getAgents()[i]) != _population->getRelatedFormation(neighbor)){

				// Check if FOV intersect
				if(_population->getAgents()[i]->getFOVIntersection(neighbor)){
					//add neighbor to formation
//					ofLogNotice("GroupDetector::detect") << "Detected neighbor#" << neighbor->getId() << " for Agent#" << _population->getAgents()[i]->getId();
					if(_population->getRelatedFormation(neighbor))
						_population->removeFormation(_population->getRelatedFormation(neighbor)->getId());

					_population->getRelatedFormation(_population->getAgents()[i])->pushAgent(neighbor);

//					ofLogNotice("GroupDetector::detect") << "Formation#"
//							<< _population->getRelatedFormation(_population->getAgents()[i])->getId()
//							<< " size=" << _population->getRelatedFormation(_population->getAgents()[i])->getAgents().size();
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
//			ofLogNotice("GroupDetector::detect") << "Removed alone Formation#" << _population->getFormations()[i]->getId();
			_population->removeFormation(_population->getFormations()[i]->getId());
			i--;
		}
	}

	// Update social space for each formations
	for(auto * f: this->_population->getFormations()){
		f->update();
	}
}

void GroupDetector::checkExistingFormation() {
	for(unsigned int i = 0; i < _population->getFormations().size(); i++){
		// Find if an agent left the formation
		for(unsigned int j = 0; j < _population->getFormations()[i]->getAgents().size(); j++){
			bool isInRange = false;
			bool isInFOV = false;

			for(unsigned int l = 0; l < _population->getFormations()[i]->getAgents().size(); l++){
				// Skip same agent
				if(_population->getFormations()[i]->getAgents()[j] == _population->getFormations()[i]->getAgents()[l])
					continue;

				if(_population->getFormations()[i]->getAgents()[j]->getFOVIntersection(
						_population->getFormations()[i]->getAgents()[l]
				)){
					isInFOV = true;
				}

				if(distance(_population->getFormations()[i]->getAgents()[j]->getPosition(), _population->getFormations()[i]->getAgents()[l]->getPosition()) < GROUP_DETECTION_DISTANCE_THRESHOLD){
					isInRange = true;
				}
			}

			// Agent is too far from the formation, remove
			if(!isInRange || !isInFOV){
//				ofLogNotice("GroupDetector::checkExistingFormation")
//						<< "Removed Agent#" << _population->getFormations()[i]->getAgents()[j]->getId()
//						<< " from Formation#" << _population->getFormations()[i]->getId();
				_population->getFormations()[i]->removeAgent(_population->getFormations()[i]->getAgents()[j]->getId());
				// Decrement index for next loop
				j--;

				// Check if formation is empty
				if(_population->getFormations()[i]->getAgents().size() == 0){
//					ofLogNotice("GroupDetector::checkExistingFormation") << "Formation#" << _population->getFormations()[i]->getId() << " removed";
					_population->removeFormation(_population->getFormations()[i]->getId());
					if(i == 0)
						break;
					else
						i--;
				}
			}
		}

		// Find an agent is in range from formation
		for(unsigned int k = 0; k < _population->getAgents().size(); k++){
			if(_population->getFormations()[i] == _population->getRelatedFormation(_population->getAgents()[k])){
				// Agent k is already in formation, skip
				continue;
			}


			for(unsigned int l = 0; l < _population->getFormations()[i]->getAgents().size(); l++){
				// Is Agent k in range from formation i
				if(distance(_population->getAgents()[k]->getPosition(), _population->getFormations()[i]->getAgents()[l]->getPosition()) < GROUP_DETECTION_DISTANCE_THRESHOLD){
					// Find agent k FOV intersection with one agent in formation i
					if(_population->getAgents()[k]->getFOVIntersection(_population->getFormations()[i]->getAgents()[l])){
						// match, group agent k in formation i
						_population->getFormations()[i]->pushAgent(_population->getAgents()[k]);
						break;
					}
				}
			}
		}
	}
}
