/*
 * SocialPlanner.h
 *
 *  Created on: Jun 7, 2017
 *      Author: paco
 */

#ifndef SRC_SOCIALPLANNER_H_
#define SRC_SOCIALPLANNER_H_

#include "PopulationManager.h"
#include "Robot.h"
#include <chrono>

class SocialPlanner {
public:
	SocialPlanner(PopulationManager * m, Robot * r);
	virtual ~SocialPlanner();

	void update();
	void seek_interaction();
	void engage();
	void interact();
	void disengage();
	PopulationManager* getManager() const;
	Robot* getRobot() const;

	enum SocialState { SEEK_INTERACTION, ENGAGEMENT, INTERACTION, DISENGAGE};

	bool interactionStarted = 0;
	bool seekStarted = 0;
	std::chrono::time_point<std::chrono::system_clock> startInteractionTime;
	std::chrono::time_point<std::chrono::system_clock> startSeekTime;
	SocialState state = SEEK_INTERACTION;
	PopulationManager * manager;
	Robot * robot;
	Vector3d savedPosition;
};

#endif /* SRC_SOCIALPLANNER_H_ */
