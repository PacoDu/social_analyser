/**
 * @file Formation.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 24 mars 2017
 */

#ifndef SRC_FORMATION_H_
#define SRC_FORMATION_H_

#include "Agent.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "AgentContainer.h"
#include "OSpace.h"
#include "World.h"

/**
 * @class Formation
 * @brief This class represent the social Formation
 *
 * This class manage the social Formations created by the Agents
 */
class Formation: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the Formation class, initialize a GroupSocialSpace
	 *
	 * @param agents : Agents that are part of the Formation
	 * @param id : Unique identifier of the Formation
	 */
	Formation(std::vector<Agent*> agents, int id=0);

	/**
	 * @brief Constructor
	 *
	 * Constructor of the Formation class, this constructor doesn't initialize any GroupSocialSpace
	 *
	 * @param agent : Agent that is part of the Formation
	 * @param id : Unique identifier of the Formation
	 */
	Formation(Agent* agent, int id=0);

	/**
	 * @brief Constructor
	 *
	 * Constructor of the Formation class, creates an empty formation.
	 * This constructor doesn't initialize any GroupSocialSpace
	 *
	 * @param id : Unique identifier of the Formation
	 */
	Formation(int id=0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the Formation class, destroy the related GroupSocialSpace if defined
	 */
	~Formation();

#ifdef USE_OFX
	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * @param world : The main frame coordinates
	 */
	void draw(World* world);
#endif

	/**
	 * @brief Compute the interaction potential of the formation
	 * based on the mean interpersonal distance and distance from the Formation center.
	 */
	void computeInteractionPotential();

	/**
	 * @brief Compute the interaction position from the robot to adopt
	 * in order to take part in the Formation
	 */
	void findInteractionPosition();

	/**
	 * @brief Update Formation related data by calling GroupSocialSpace update function, computeInteractionPotential
	 * and findInteractionPosition.
	 */
	void update();

	/**
	 * @brief Add an Agent to the Formation and update/create the corresponding GroupSocialSpace
	 *
	 * @param agent : Agent pointer to add to the formation
	 */
	void pushAgent(Agent* agent);

	/**
	 * @brief Remove an Agent by id from the Formation and the corresponding GroupSocialSpace
	 *
	 * @param agentId : Agent id to remove from the Formation
	 */
	void removeAgent(unsigned int agentId);

	/**
	 * @brief Check if the Agent passed in parameter is taking part in the Formation
	 * Alias to isInFormation function by Agent id
	 *
	 * @param agent : Agent pointer to check
	 *
	 * @return 1 if the Agent is taking part in the Formation, 0 otherwise
	 */
	int isInFormation(Agent* agent);

	/**
	 * @brief Check if the Agent passed in parameter is taking part in the Formation
	 *
	 * @param agentId : Agent id to check
	 *
	 * @return 1 if the Agent is taking part in the Formation, 0 otherwise
	 */
	int isInFormation(unsigned int agentId);

	/**
	 * @brief Initialization function for Formation Constructor with only one Agent
	 *
	 * @param agent : Agent initialized for the Formation
	 *
	 * @return A vector containing the Agent passed in parameter.
	 */
	std::vector<Agent *> initAgent(Agent * agent);

	// Getters & Setters
	/**
	 * @brief Simple getter
	 * @return GroupSocialSpace
	 */
	OSpace* getSocialSpace() const;

	/**
	 * @brief Simple setter
	 * @param socialSpace
	 */
	void setSocialSpace(OSpace* socialSpace);

	/**
	 * @brief Simple getter
	 * @return InteractionPotential
	 */
	double getInteractionPotential() const;

	/**
	 * @brief Simple setter
	 * @param interactionPotential
	 */
	void setInteractionPotential(double interactionPotential = 0);

	/**
	 * @brief Simple getter
	 * @return InteractionPosition
	 */
	const Vector3d& getInteractionPosition() const;

	/**
	 * @brief Simpler setter
	 * @param interactionPosition
	 */
	void setInteractionPosition(const Vector3d& interactionPosition);

	/**
	 * @brief Simpler getter
	 * @return InteractionDirection
	 */
	const Vector3d& getInteractionDirection() const;

	/**
	 * @brief Simple setter
	 * @param interactionDirection
	 */
	void setInteractionDirection(const Vector3d& interactionDirection);

protected:
	OSpace* _socialSpace; //!< GroupSocialSpace related to the Formation
	double interactionPotential = 0; //!< Estimated interaction potential of the Formation
	Vector3d interactionPosition; //!< Estimated interaction position for the Robot to take part in the Formation
	Vector3d interactionDirection; //!< Estimated interaction direction for the Robot to take part in the Formation
	std::vector<Vector3d> agentDir_ospace; //!< Vector3d of Agents direction to the Formation center
};


#endif /* SRC_FORMATION_H_ */
