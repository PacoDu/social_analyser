/*
 * Formation.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_FORMATION_H_
#define SRC_FORMATION_H_

#include "Agent.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "AgentContainer.h"
#include "OSpace.h"
//#include "PSpace.h"
#include "World.h"

// TODO Remove drawnobject formation, only map will be a drawnobject
class Formation: public IdentifiedObject, public AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Formation(std::vector<Agent*> a, int id=0);
	Formation(Agent* a, int id=0);
	Formation(int id=0);

	~Formation();

	// --- METHOD
	void draw(World* world);
	void update();
	void pushAgent(Agent* a);
	void removeAgent(unsigned int agentId);
	int isInFormation(Agent* a);
	int isInFormation(unsigned int agentId);
	std::vector<Agent *> initAgent(Agent * a);

	// Getters & Setters
	OSpace* getSocialSpace() const;
	void setSocialSpace(OSpace* socialSpace);


protected:
	OSpace* _socialSpace;
};


#endif /* SRC_FORMATION_H_ */
