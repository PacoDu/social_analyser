/**
 * @file SocialPlanner.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 7 juin 2017
 */

#ifndef SRC_SOCIALPLANNER_H_
#define SRC_SOCIALPLANNER_H_

#include "PopulationManager.h"
#include "Robot.h"
#include <chrono>

/**
 * @class SocialPlanner
 * @brief This class is a state machine controlling the Robot behavior
 *
 * @todo This class should be an interface to implement different behavior for the robot
 */
class SocialPlanner {
public:
	/**
	 * @brief Constructor
	 *
	 * Constructor of the SocialPlanner class
	 *
	 * @param popManager : The Population where the robot evolves
	 * @param robot : The Robot controlled by this behavior
	 */
	SocialPlanner(PopulationManager * popManager, Robot * robot);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the SocialPlanner class
	 */
	virtual ~SocialPlanner();

	/**
	 * @brief Update the state of the robot behavior,
	 *
	 * Update the state of the robot behavior,
	 * by executing the function related to its actual state
	 */
	void update();

	/**
	 * @brief Seek interaction state
	 *
	 * The robot is looking for interaction, it goes randomly around the GridMap
	 * and after SEEK_INTERACTION_MIN_TIME it looks for the highest interaction potential available
	 * in the formations superior to INTERACTION_POTENTIAL_THRESHOLD then switch to the engage state
	 */
	void seek_interaction();

	/**
	 * @brief Engage state
	 *
	 * The robot move to the interaction position related to the Formation
	 * and process some social signal like mutual facial gaze to communicate its
	 * intentions. And switch to the interaction state when the goal is reached
	 */
	void engage();

	/**
	 * @brief Interaction state
	 *
	 * The robot simulate an interaction with the Formation for INTERACTION_MAX_TIME,
	 * then switch to the disengage state.
	 */
	void interact();

	/**
	 * @brief Disengage state
	 *
	 * The robot ends the interaction by going back to the seek interaction state
	 *
	 * @todo Execute some social signals for disengagement
	 */
	void disengage();

	/**
	 * @brief Simple getter
	 * @return PopulationManager
	 */
	PopulationManager* getManager() const;

	/**
	 * @brief Simple getter
	 * @return Robot
	 */
	Robot* getRobot() const;

	/**
	 * @brief The states available for the state machine
	 */
	enum SocialState { SEEK_INTERACTION, ENGAGEMENT, INTERACTION, DISENGAGE};

	bool interactionStarted = 0; //!< Interaction state started
	bool seekStarted = 0; //!< Seek interaction state started
	std::chrono::time_point<std::chrono::system_clock> startInteractionTime; //!< Time when interaction state started
	std::chrono::time_point<std::chrono::system_clock> startSeekTime; //!< Time when seek interaction state started
	std::chrono::time_point<std::chrono::system_clock> startMutualFacialGaze; //!< Time when mutual facial gaze started

	SocialState state = SEEK_INTERACTION; //!< Actual state, default is SEEK_INTERACTION
	PopulationManager * manager; //!< The PopulationManager used by the SocialPlanner
	Robot * robot; //!< The Robot controlled by the SocialPlanner
	Vector3d savedPosition; //!< Interaction position saved, dirty
};

#endif /* SRC_SOCIALPLANNER_H_ */
