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

	void update();
	void pushAgent(Agent* agent);
	void removeAgent(unsigned int agentId);
	int isInFormation(Agent* a);
	int isInFormation(unsigned int agentId);
	std::vector<Agent *> initAgent(Agent * a);
	void computeInteractionPotential();
	void findInteractionPosition();


	// Getters & Setters
	OSpace* getSocialSpace() const;
	void setSocialSpace(OSpace* socialSpace);
	double getInteractionPotential() const;
	void setInteractionPotential(double interactionPotential = 0);
	const Vector3d& getInteractionPosition() const;
	void setInteractionPosition(const Vector3d& interactionPosition);
	const Vector3d& getInteractionDirection() const;
	void setInteractionDirection(const Vector3d& interactionDirection);

protected:
	OSpace* _socialSpace;
	double interactionPotential = 0;
	Vector3d interactionPosition;
	std::vector<Vector3d> agentDir_ospace;
	Vector3d interactionDirection;
};


#endif /* SRC_FORMATION_H_ */
