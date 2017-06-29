/**
 * @file SocialPlanner.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 7 juin 2017
 */

#include "SocialPlanner.h"
#include "config.h"
#include <algorithm>

SocialPlanner::SocialPlanner(PopulationManager * m, Robot * r): manager(m), robot(r) {
	// TODO Auto-generated constructor stub

}

SocialPlanner::~SocialPlanner() {
	// TODO Auto-generated destructor stub
}

void SocialPlanner::update() {
	switch(this->state){
	case SEEK_INTERACTION:
		seek_interaction();
		break;
	case ENGAGEMENT:
		engage();
		break;
	case INTERACTION:
		interact();
		break;
	case DISENGAGE:
		disengage();
		break;
	}
}

void SocialPlanner::seek_interaction() {
//	ofLogNotice("SocialPlanner") << "Seek interaction state";

	if(!seekStarted){
		seekStarted = 1;
		startSeekTime = std::chrono::system_clock::now();
	}

	std::chrono::duration<double> deltaT = std::chrono::system_clock::now() - startSeekTime;

	if(manager->getHighestFormationInteractionPotential() && deltaT.count() > SEEK_INTERACTION_MIN_TIME){
		double potential = manager->getHighestFormationInteractionPotential()->getInteractionPotential();

		if(potential > INTERACTION_POTENTIAL_THRESHOLD){
			robot->resetPathFinding();
			this->state = ENGAGEMENT;
			seekStarted = 0;
//			this->savedPosition = robot->getPosition();
		}
	}

	GridMap * map = manager->getMap();
	GridCell * robotCell = map->getCell(robot->getX(), robot->getY());

	if(robot->getGoal() == nullptr){
//		ofLogNotice("SocialPlanner") << "Finding random goal for robot";
		robot->resetPathFinding();

		GridCell * goal = map->getCell(rand()%(int)manager->getWorld()->getWidth(),rand()%(int)manager->getWorld()->getHeight());
		while(goal->getValue() > 0.1){
			goal = map->getCell(rand()%(int)manager->getWorld()->getWidth(),rand()%(int)manager->getWorld()->getHeight());
		}

//		currentGoal = goal;

		robot->setGoal(goal);
		robot->path = map->findPath(map->getCell(robot->getX(), robot->getY()), goal);
	}
	else if(robotCell == robot->getGoal())
	{
		robot->resetPathFinding();
	}
//	else{
//		GridCell * robotGoal = robot->getGoal();
//		std::vector<GridCell*> newPath = map->findPath(map->getCell(robot->getX(), robot->getY()), robot->getGoal());
//		robot->resetPathFinding();
//		robot->path = newPath;
//		robot->setGoal(robotGoal);
//	}

}

void SocialPlanner::engage() {
//	ofLogNotice("SocialPlanner") << "Engage state";
	Formation * target = manager->getHighestFormationInteractionPotential();
	if(target){
		GridCell * goal = manager->getMap()->getCell(
					target->getInteractionPosition().x(),
					target->getInteractionPosition().y()
				);

		GridCell * robotCell = manager->getMap()->getCell(robot->getX(), robot->getY());

		if(robotCell == goal){
			this->state = INTERACTION;
			robot->gazeTarget = nullptr;
//			robot->resetPathFinding();
			return;
		}
//		ofLogNotice("DEBUG") << "ROBOT position (" << robot->getX() << "," << robot->getY() << ")";

		if(robot->getGoal() == nullptr || (goal->getPosition() - robot->getGoal()->getPosition()).norm() > 0.25){
			robot->resetPathFinding();
			robot->path = manager->getMap()->findPath(robotCell, goal);
			robot->setGoal(goal);

			Vector3d rDirection = target->getInteractionDirection();
			robot->finalTargetAngle = new double(M_PI + atan2(rDirection.y(), rDirection.x()) - atan2(0,1));
		}


		if(robot->gazeTarget){
			std::chrono::duration<double> deltaT = std::chrono::system_clock::now() - startMutualFacialGaze;
			if(deltaT.count() > 5){
				robot->gazeTarget = nullptr;
				Agent * agentRobot = new Agent(robot->getPosition(), robot->getTheta());
				std::vector<Agent *> agents = target->getAgents();
				std::random_shuffle(agents.begin(), agents.end());

				for(auto * a: target->getAgents()){
					if(a->getFOVIntersection(agentRobot)){
						robot->gazeTarget = a;
						startMutualFacialGaze = std::chrono::system_clock::now();
					}
				}
			}
		}
		else{
			Agent * agentRobot = new Agent(robot->getPosition(), robot->getTheta());
			std::vector<Agent *> agents = target->getAgents();
			std::random_shuffle(agents.begin(), agents.end());

			for(auto * a: target->getAgents()){
				if(a->getFOVIntersection(agentRobot)){
					robot->gazeTarget = a;
					startMutualFacialGaze = std::chrono::system_clock::now();
				}
			}
		}


	}
	else{
		this->state = SEEK_INTERACTION;
		robot->resetPathFinding();
		robot->finalTargetAngle = nullptr;
		robot->gazeTarget = nullptr;
	}


}

int min_2(int a, int b){ return a>b?b:a; };

void SocialPlanner::interact() {
//	ofLogNotice("SocialPlanner") << "Interact state";
	if(!interactionStarted){
		interactionStarted = 1;
		startInteractionTime = std::chrono::system_clock::now();
	}
	Formation * target = manager->getHighestFormationInteractionPotential();

	std::chrono::duration<double> deltaT = std::chrono::system_clock::now() - startInteractionTime;

	Agent * agentRobot = new Agent(robot->getPosition(), robot->getTheta());

	if(robot->gazeTarget){
		std::chrono::duration<double> deltaT2 = std::chrono::system_clock::now() - startMutualFacialGaze;
		if(deltaT2.count() > 5){
			//		std::vector<Agent *> agents = target->getAgents();
			//		std::random_shuffle(agents.begin(), agents.end());

					Agent * targetA = target->getAgents()[min_2(gazeTargetIndex, target->getAgents().size())];

			//		for(auto * a: target->getAgents()){
//					do{
						robot->gazeTarget = targetA;
						startMutualFacialGaze = std::chrono::system_clock::now();
						gazeTargetIndex++;
						if(gazeTargetIndex >= target->getAgents().size()){
							gazeTargetIndex = 0;
						}
//					}
//					while(targetA->getFOVIntersection(agentRobot));
		}
	}
	else{
					Agent * targetA = target->getAgents()[min_2(gazeTargetIndex, target->getAgents().size())];

			//		for(auto * a: target->getAgents()){
//					do{
						robot->gazeTarget = targetA;
						startMutualFacialGaze = std::chrono::system_clock::now();
						gazeTargetIndex++;
						if(gazeTargetIndex > target->getAgents().size()){
							gazeTargetIndex = 0;
						}
//					}
//					while(targetA->getFOVIntersection(agentRobot));
	}

	if(!target || deltaT.count() > INTERACTION_MAX_TIME){
		this->state = DISENGAGE;
		interactionStarted = 0;
		robot->resetPathFinding();
		robot->gazeTarget = nullptr;
	}
}

void SocialPlanner::disengage() {
//	ofLogNotice("SocialPlanner") << "Disengage state";
	if(1){
		this->state = SEEK_INTERACTION;
	}
}

PopulationManager* SocialPlanner::getManager() const {
	return manager;
}

Robot* SocialPlanner::getRobot() const {
	return robot;
}

