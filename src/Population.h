/*
 * Population.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_POPULATION_H_
#define SRC_POPULATION_H_

#include "Agent.h"
#include "Formation.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "AgentContainer.h"
#include "ofMain.h"

class Population: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:
	Population();
	Population(int id);
	Population(double x, double y);
	Population(int id, double x, double y);
	Population(std::vector<Agent*>& a);
	Population(int id, std::vector<Agent*>& a);
	Population(int id, double x, double y, std::vector<Agent*> a);
	Population(double x, double y, std::vector<Agent*>& a);
	~Population();

	void draw(double x, double y);
	void clear();

	ofVec2f getBoundX();
	ofVec2f getBoundY();

	void pushFormation(Formation* f);
	void clearFormations();
	int removeFormation(unsigned int formationId);

private:
	std::vector<Formation*> _formations;
};

#endif /* SRC_POPULATION_H_ */
