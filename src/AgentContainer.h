/*
 * AgentContainer.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_AGENTCONTAINER_H_
#define SRC_AGENTCONTAINER_H_

#include "ofMain.h"
#include "Agent.h"

class AgentContainer {
public:
	AgentContainer();
	AgentContainer(std::vector<Agent*>& agents);
	virtual ~AgentContainer();

	void pushAgent(Agent* a);
	int removeAgent(unsigned int agentId);
	std::vector<Agent*> getAgents();
	Agent * getAgent(unsigned int agentId);
	void setAgents(const std::vector<Agent*>& agents);

	void clearAgents();

protected:
	std::vector<Agent*> _agents;
};

#endif /* SRC_AGENTCONTAINER_H_ */
