/**
 * @file Population.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 24 mars 2017
 */

#ifndef SRC_POPULATION_H_
#define SRC_POPULATION_H_

#include "Agent.h"
#include "Formation.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "AgentContainer.h"
#include "Population.h"
#include "GaussianSpace.h"
#include "config.h"

/**
 * @class Population
 * @brief This class represent Population around the Robot.
 *
 * This class represent Population around the Robot, it contains all the Agents with the Formations detected in this Population.
 */
class Population: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the Population class
	 *
	 * @param agents : List of initial Agents that are part of the Population
	 * @param position : Position of the Population (required by DrawnObject but useless here)
	 * @param id : Unique identifier of the Population
	 */
	Population(std::vector<Agent*> agents, Vector3d position = Vector3d(), int id = 0);

	/**
	 * @brief Constructor
	 *
	 * Constructor of the Population class
	 *
	 * @param position : Position of the Population (required by DrawnObject but useless here)
	 * @param id : Unique identifier of the Population
	 */
	Population(Vector3d position = Vector3d(), int id = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the Population class, destroy every Agents and Formations related to this Population
	 */
	~Population();

#ifdef USE_OFX
	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * @param world : The main frame coordinates
	 */
	void draw(World* world);
#endif

	/**
	 * @brief Find the Formation with the highest interaction potential
	 *
	 * @return The Formation with the highest interaction potential in the Population
	 */
	Formation * getHighestFormationInteractionPotential();

	/**
	 * @brief Find the Formation related to the Agent
	 *
	 * @return The Formation in which the Agent is taking part
	 */
	Formation * getRelatedFormation(unsigned int agentId);

	/**
	 * @brief Find the Formation related to the Agent
	 * Alias to getRelatedFormation function by Agent id
	 *
	 * @return The Formation in which the Agent is taking part
	 */
	Formation * getRelatedFormation(Agent* a);

	/**
	 * @brief Clear the Population
	 *
	 * Destroy all Agents and Formations
	 */
	void clear();

	/**
	 * @brief Check if the Agent is part of a Formation
	 * Alias to isGrouped function by Agent id
	 *
	 * @param agent : The Agent to check
	 * @return 1 if Agent is in a Formation, 0 otherwise
	 */
	int isGrouped(Agent * agent);

	/**
	 * @brief Check if the Agent is part of a Formation
	 *
	 * @param agentId : The Agent to check
	 * @return 1 if Agent is in a Formation, 0 otherwise
	 */
	int isGrouped(unsigned int agentId);

	/**
	 * @brief Add a Formation to the Population
	 *
	 * @param formation : The Formation to add to the Population
	 */
	void pushFormation(Formation* formation);

	/**
	 * @brief Remove a Formation by id from the Population and the corresponding GroupSocialSpace
	 *
	 * @param formationId : Formation id to remove from the Population
	 *
	 * @return 0 on success, 0 otherwise (if the Formation does not exist)
	 */
	int removeFormation(unsigned int formationId);

	/**
	 * @brief Clear the Formation list
	 *
	 * This function do not call the Formation destructor
	 */
	void clearFormations();

	/**
	 * @brief Simple getter
	 * @return Formations
	 */
	const std::vector<Formation*>& getFormations() const;

	/**
	 * @brief Simpler setter
	 * @param formations
	 */
	void setFormations(const std::vector<Formation*>& formations);

private:
	std::vector<Formation*> _formations; //!< All the Formations detected in the Population
};

#endif /* SRC_POPULATION_H_ */
