/**
 * @file Agent.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 24 mars 2017
 */

#ifndef SRC_AGENT_H_
#define SRC_AGENT_H_

#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "config.h"

class Formation;
class GaussianSpace;

/**
 * @class Agent
 * @brief This class represent the Agents
 *
 * This class manage the Agents detected around the robot
 */
class Agent: public IdentifiedObject, public DrawnObject {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the Agent class, initialize a PersonnalSocialSpace
	 *
	 * @param position : Initial position of the Agent in World
	 * @param theta : Initial angle of the Agent
	 * @param id : Unique identifier of the Agent
	 */
	Agent(Vector3d position = Vector3d(), double theta=0, int id=0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the Agent class, destroy the related PersonnalSocialSpace
	 */
	~Agent();

	/**
	 * @brief Find the nearest neighbor available in the list passed in parameters
	 *
	 * @param agents : A list of Agents
	 * @return The nearest Agent available in agents
	 */
	Agent * findNearestNeighbor(std::vector<Agent*> agents);

#if USE_OFX
	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * @param world : The main frame coordinates
	 */
	void draw(World* world);
#endif

	/**
	 * @brief Find the intersection point in the field of view with the other Agent passed in parameter
	 *
	 * @param agent : The targeted Agent
	 * @return The intersection point in the field of view of both Agent, returns NULL if there is no intersection
	 *
	 * @todo Take parallel Agent into account, actually return NULL if Agents are parallel
	 */
	Vector3d* getFOVIntersection(Agent * agent);

	/**
	 * @brief Simple getter
	 * @return PersonalSocialSpace
	 */
	GaussianSpace* getSocialSpace() const;

	/**
	 * @brief Simple setter
	 * @param socialSpace
	 */
	void setSocialSpace(GaussianSpace* socialSpace);

protected:
	GaussianSpace* pSocialSpace; //!< PersonnalSocialSpace related to the Agent
};

#endif /* SRC_AGENT_H_ */
