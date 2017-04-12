///*
// * GroupDetector.cpp
// *
// *  Created on: Apr 10, 2017
// *      Author: paco
// */
//
//#include "GroupDetector.h"
//#include "utils.h"
//
//GroupDetector::GroupDetector(Population* pop): _population(pop) {
//}
//
//GroupDetector::~GroupDetector() {
//	// TODO Auto-generated destructor stub
//}
//
//void GroupDetector::detect() {
//	checkExistingFormation();
//
//	// Init create 1 formation for each agent
//	for(unsigned int i = 0; i < _population->getAgents().size(); i++){
//		if(_population->getAgents()[i]->getFormation() == NULL){
//			ofLogNotice("GroupDetector::detect") << "Initialized formation for Agent#" << _population->getAgents()[i]->getId();
//			std::vector<Agent *> a;
//			a.push_back(_population->getAgents()[i]);
//			Formation* f = new Formation(a, Point(0,0), 0.0, formationId);
//			formationId++;
//			_population->pushFormation(f);
//		}
//	}
//
//
//	for(unsigned int i = 0; i < _population->getAgents().size(); i++){
//		std::vector<Agent*> agents = _population->getAgents();
//		// Remove current agent from vector
//		agents.erase(std::remove(agents.begin(), agents.end(), _population->getAgents()[i]), agents.end());
//
//		for(unsigned int j = 0; j < _population->getAgents().size(); j++){
//			Agent * neighbor =  _population->getAgents()[i]->findNearestNeighbor(agents);
//
//			// If nearest neighbor is too far, abort grouping for agent[i]
//			if(_population->getAgents()[i]->getPosition().distance(neighbor->getPosition()) > maxDistanceThreshold)
//				break;
//
//			// if Agents are already grouped, skip
//			if(_population->getAgents()[i]->getFormation()->getId() != neighbor->getFormation()->getId()){
//
//				// Check if FOV intersect
//				Point * intersection = new Point();
//				Point ad(agents[i]->getDirection().x, agents[i]->getDirection().y);
//				Point bd(neighbor->getDirection().x, neighbor->getDirection().y);
//
//				if(rayIntersectionPoint(agents[i]->getPosition(), ad, neighbor->getPosition(), bd, intersection)){
//					//add neighbor to formation
//					ofLogNotice("GroupDetector::detect") << "Detected neighbor#" << neighbor->getId() << " for Agent#" << _population->getAgents()[i]->getId();
//					_population->removeFormation(neighbor->getFormation()->getId());
//					neighbor->deleteFormation();
//					_population->getAgents()[i]->getFormation()->pushAgent(neighbor);
//					ofLogNotice("GroupDetector::detect") << "Formation#" << _population->getAgents()[i]->getFormation()->getId() << " size=" << _population->getAgents()[i]->getFormation()->getAgents().size();
//				}
//
//			}
//
//			// Remove processed agent
//			agents.erase(std::remove(agents.begin(), agents.end(), neighbor), agents.end());
//			if(agents.size() == 0){
//				break;
//			}
//		}
//	}
//
//	// Clear alone formation
//	for(unsigned int i = 0; i < _population->getAgents().size(); i++){
//		if(_population->getAgents()[i]->getFormation()->getAgents().size() <= 1){
//			ofLogNotice("GroupDetector::detect") << "Removed alone Formation#" << _population->getAgents()[i]->getFormation()->getId();
//			_population->removeFormation(_population->getAgents()[i]->getFormation()->getId());
//			_population->getAgents()[i]->deleteFormation();
//		}
//	}
//}
//
//void GroupDetector::checkExistingFormation() {
//	// TODO Check distance from computed formation center not from agent[0]
//	for(unsigned int i = 0; i < _population->getFormations().size(); i++){
//		for(unsigned int j = 0; j < _population->getFormations()[i]->getAgents().size(); j++){
//			if( _population->getFormations()[i]->getAgents()[j]->getPosition().distance(((OSpace*)(_population->getFormations()[i]->getSocialSpace()))->getCenter()) > maxDistanceThreshold){
//				int fId = _population->getFormations()[i]->getId();
//				_population->getFormations()[i]->getAgents()[j]->deleteFormation();
//				_population->removeFormation(fId);
//				// TODO Fix, formation is not removed correctly
//			}
//		}
//	}
//}
