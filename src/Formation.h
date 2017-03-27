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
#include "PSpace.h"

class Formation: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:
	Formation(double ospace_radius, double pspace_radius);
	Formation(int id, double ospace_radius, double pspace_radius);
	Formation(double x, double y, double ospace_radius, double pspace_radius);
	Formation(int id, double x, double y, double ospace_radius, double pspace_radius);
	Formation(double ospace_radius, double pspace_radius, std::vector<Agent*>& a);
	Formation(int id, double ospace_radius, double pspace_radius, std::vector<Agent*>& a);
	Formation(int id, double x, double y, double ospace_radius, double pspace_radius, std::vector<Agent*>& a);
	Formation(double x, double y, double ospace_radius, double pspace_radius, std::vector<Agent*>& a);

	~Formation();

	void draw(double x, double y);


	// Getters & Setters
	const OSpace* getOspace() const {
		return ospace;
	}

	void setOspace(OSpace* ospace) {
		this->ospace = ospace;
	}

	const PSpace* getPspace() const {
		return pspace;
	}

	void setPspace(PSpace* pspace) {
		this->pspace = pspace;
	}

protected:
	std::vector<Agent*> _agents;
	OSpace* ospace;
	PSpace* pspace;
};


#endif /* SRC_FORMATION_H_ */
