/**
 * @file AgentContainer.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 27 mars 2017
 */

#ifndef SRC_AGENTCONTAINER_H_
#define SRC_AGENTCONTAINER_H_

#include "Agent.h"

/**
 * @class AgentContainer
 * @brief This class is an interface for class that contains multiples Agents
 */
class AgentContainer {
public:
	/**
	 * @brief Constructor
	 *
	 * Constructor of the AgentContainer class, initialize an empty container
	 */
	AgentContainer();

	/**
	 * @brief Constructor
	 *
	 * Constructor of the AgentContainer class, initialize the container with agents
	 *
	 * @param agents : The Agents present in the container
	 */
	AgentContainer(std::vector<Agent*>& agents);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the AgentContainer class
	 */
	virtual ~AgentContainer();

	/**
	 * @brief Add an Agent to the container
	 *
	 * @param agent : The Agent to add
	 */
	void pushAgent(Agent* agent);

	/**
	 * @brief Remove an Agent by id from the container
	 *
	 * @param agentId : The Agent id to remove
	 *
	 * @return 0 on success, -1 if Agent id is not found
	 */
	int removeAgent(unsigned int agentId);

	/**
	 * @brief Clear the container
	 *
	 * Clear the container, this function doesn't call the Agent destructor
	 */
	void clearAgents();

	/**
	 * @brief Get an Agent by id from the container
	 *
	 * @param agentId : Agent id to get from the container
	 *
	 * @return The Agent, null otherwise
	 */
	Agent * getAgent(unsigned int agentId);

	/**
	 * @brief Simple getter
	 * @return Agents
	 */
	std::vector<Agent*> getAgents();

	/**
	 * @brief Simple setter
	 * @param agents
	 */
	void setAgents(const std::vector<Agent*>& agents);

protected:
	std::vector<Agent*> _agents; //!< The Agent container
};

#endif /* SRC_AGENTCONTAINER_H_ */
